#include"TcpClient.h"

#include "Interfaces/IPv4/IPv4Address.h"

namespace func
{
	ConfigXML* __ClientInfo = nullptr;
}

namespace net
{
	//初始化客户端数据
	void S_SERVER_BASE::Init(int sid) //连接的时候去连接哪个服务器ID
	{
		ID = 0;
		serverID = sid;
		serverType = 0;
		recvBuf = (uint8*)FMemory::Malloc(func::__ClientInfo->ReceMax);
		sendBuf = (uint8*)FMemory::Malloc(func::__ClientInfo->SendMax);
		recvBuf_Temp = (uint8*)FMemory::Malloc(func::__ClientInfo->ReceOne);

		ip = "127.0.0.1";
		port = 13550;

		reset();
	}

	void S_SERVER_BASE::reset()
	{
		state = 0;
		rCode = func::__ClientInfo->RCode;
		recv_Head = 0;
		recv_Tail = 0;
		recv_TempHead = 0;
		recv_TempTail = 0;
		is_Recved = false;

		send_Head = 0;
		send_Tail = 0;
		send_TempTail = 0;
		is_Sending = false;
		is_SendCompleted = true;

		time_Heart = 0;
		time_AutoConnect = 0;

		FMemory::Memset(recvBuf, 0, func::__ClientInfo->ReceMax);
		FMemory::Memset(sendBuf, 0, func::__ClientInfo->SendMax);
		FMemory::Memset(recvBuf_Temp, 0, func::__ClientInfo->ReceOne);
	}

	TcpClient::TcpClient()
	{
		isPause = false;
		isFirstConnect = true;
		isRunning = false;
		socketfd = nullptr;

		onAcceptEvent = nullptr;
		onSecureEvent = nullptr;
		onDisconnectEvent = nullptr;
		onExceptEvent = nullptr;
		onCommand = nullptr;

		m_workthread = nullptr;
		socketfd =nullptr;
	}

	TcpClient::~TcpClient()
	{
		if (m_workthread != nullptr)
		{
			delete m_workthread;
			m_workthread = nullptr;
		}
		if (socketfd != nullptr)
		{
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socketfd); //销毁套接字
			socketfd = nullptr;
		}
		m_data.reset();
	}

	//客户端线程
	void TcpClient::runClient(int32 sid, FString ip, int32 port)
	{
		m_data.Init(sid);
		m_data.time_AutoConnect = 0;
		m_data.ip = ip;
		m_data.port = port;

		isRunning = true;
		m_workthread = new TcpClient_Thread(this);//创建一个线程
	}

	//初始化套接字
	int32 TcpClient::initSocket()
	{
		if(socketfd != nullptr)
		{
			//销毁套接字,PLATFORM_SOCKETSUBSYSTEM是平台套接字子系统
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socketfd);
			socketfd = nullptr;
		}

		//创建一个套接字,NAME_Stream是流式套接字TCP专用，TEXT("default")是套接字的标识，false是是否是阻塞套接字
		socketfd = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);//创建一个套接字
		return 0;
	}

	//连接服务器
	bool TcpClient::connectServer()
	{
		if(m_data.state >= func::C_Connect) return false;

		initSocket(); 
		if(socketfd == nullptr) return false;
		
		//FIPv4Address是一个IPV4地址类，FIPv4Address::Parse是一个静态函数，用来解析IP地址
		FIPv4Address ip;
		FIPv4Address::Parse(m_data.ip, ip);

		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		addr->SetIp(ip.Value);//设置IP地址
		addr->SetPort(m_data.port);//设置端口

		//连接服务器,Connect是一个阻塞函数，如果连接成功返回true，否则返回false
		bool isconnect = socketfd->Connect(*addr);
		if( isconnect)
		{
			socketfd->SetNonBlocking();//设置为非阻塞
			m_data.state = func::C_Connect;//设置状态为连接
			m_data.time_Heart = 0;//设置心跳时间为0
			//if(onAcceptEvent != nullptr) onAcceptEvent(this, 0);//如果接受连接事件不为空，调用接受连接事件
			return true;
		}
		
		return false;
	}

	//断开服务器
	void TcpClient::disconnectServer(const int32 errcode, FString err)
	{
		if(m_data.state == func::C_Free) return;
		if(socketfd == NULL) return;

		socketfd->Close();//关闭套接字
		m_data.reset();//重置数据

		if(onDisconnectEvent != nullptr) onDisconnectEvent(this, errcode);//如果失去连接事件不为空，调用失去连接事件
	}

	//在工作线程调用 发送数据
	int32 TcpClient::onRecv()
	{
		if(socketfd == nullptr) return -1 ;
		FMemory::Memset(m_data.recvBuf_Temp, 0, func::__ClientInfo->ReceOne);//清空临时接收缓存

		uint32 size;
		if(socketfd->HasPendingData(size) == false) return -1;//如果没有数据返回0

		int32 recvsize = 0;//实际接收到的数据大小
		bool isrecv = socketfd->Recv(m_data.recvBuf_Temp, func::__ClientInfo->ReceOne, recvsize);//接收数据
		if(isrecv && recvsize >0)//如果接收成功
		{
			auto c = this->getData();
			if(c->recv_Tail == c->recv_Head)
			{
				c->recv_Tail = 0;
				c->recv_Head = 0;
			}
			//如果接收的数据大于缓存的数据,重新继续接收，也是正常情况
			if(c->recv_Tail + recvsize >= func::__ClientInfo->ReceMax) return -1;

			FMemory::Memcpy(&c->recvBuf[c->recv_Tail], c->recvBuf_Temp, recvsize);//拷贝数据
			c->recv_Tail += recvsize;//设置尾指针
			
		}
		
		return 0;
	}

	//在主线程调用 接收数据
	int32 TcpClient::onSend()
	{
		auto c = this->getData();//获取数据
		if(c->send_Tail <= c->send_Head) return 0;//如果发送的数据小于等于0，返回0
		if(c->state < func::C_Connect) return -1;//如果状态小于连接状态，返回-1
		int32 sendlen = c->send_Tail - c->send_Head;//发送数据的长度
		if(sendlen < 1 ) return 0;//如果发送的数据小于1，返回0

		int32 sendBytes = 0;//实际发送的数据长度
		bool issend = socketfd->Send(&c->sendBuf[c->send_Head], sendlen, sendBytes);//发送数据
		if(issend && sendBytes > 0)//如果发送成功
		{
			c->send_Head += sendBytes;//设置头指针
		}
		return 0;
	}
}
