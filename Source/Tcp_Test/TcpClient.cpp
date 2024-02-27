#include"TcpClient.h"

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


	int32 TcpClient::initSocket()
	{
		return 0;
	}

	int32 TcpClient::onRecv()
	{
		return 0;
	}
}
