#include"TcpClient.h"

#include "Interfaces/IPv4/IPv4Address.h"

namespace func
{
	ConfigXML* __ClientInfo = nullptr;
}

namespace net
{
	//��ʼ���ͻ�������
	void S_SERVER_BASE::Init(int sid) //���ӵ�ʱ��ȥ�����ĸ�������ID
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
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socketfd); //�����׽���
			socketfd = nullptr;
		}
		m_data.reset();
	}

	void TcpClient::runClient(int32 sid, FString ip, int32 port)
	{
		m_data.Init(sid);
		m_data.time_AutoConnect = 0;
		m_data.ip = ip;
		m_data.port = port;

		isRunning = true;
		m_workthread = new TcpClient_Thread(this);//����һ���߳�
	}

	int32 TcpClient::initSocket()
	{
		if(socketfd != nullptr)
		{
			//�����׽���,PLATFORM_SOCKETSUBSYSTEM��ƽ̨�׽�����ϵͳ
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(socketfd);
			socketfd = nullptr;
		}

		//����һ���׽���,NAME_Stream����ʽ�׽���TCPר�ã�TEXT("default")���׽��ֵı�ʶ��false���Ƿ��������׽���
		socketfd = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);//����һ���׽���
		return 0;
	}

	int32 TcpClient::onRecv()
	{
		return 0;
	}

	

	bool TcpClient::connectServer()
	{
		if(m_data.state >= func::C_Connect) return false;

		initSocket();
		if(socketfd == nullptr) return false;
		
		//FIPv4Address��һ��IPV4��ַ�࣬FIPv4Address::Parse��һ����̬��������������IP��ַ
		FIPv4Address ip;
		FIPv4Address::Parse(m_data.ip, ip);

		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		addr->SetIp(ip.Value);//����IP��ַ
		addr->SetPort(m_data.port);//���ö˿�

		//���ӷ�����,Connect��һ������������������ӳɹ�����true�����򷵻�false
		bool isconnect = socketfd->Connect(*addr);
		if( isconnect)
		{
			socketfd->SetNonBlocking();//����Ϊ������
			m_data.state = func::C_Connect;//����״̬Ϊ����
			m_data.time_Heart = 0;//��������ʱ��Ϊ0
			if(onAcceptEvent != nullptr) onAcceptEvent(this, 0);//������������¼���Ϊ�գ����ý��������¼�
			return true;
		}
		
		return false;
	}

	void TcpClient::disconnectServer(const int32 errcode, FString err)
	{
		if(m_data.state == func::C_Free) return;
		if(socketfd == NULL) return;

		socketfd->Close();//�ر��׽���
		m_data.reset();//��������

		if(onDisconnectEvent != nullptr) onDisconnectEvent(this, errcode);//���ʧȥ�����¼���Ϊ�գ�����ʧȥ�����¼�
	}
}
