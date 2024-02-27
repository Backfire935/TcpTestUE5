#include "TcpClient.h"
#include "CoreMinimal.h"

namespace net
{
	
	TcpClient_Thread::TcpClient_Thread(TcpClient* c)
	{
		this->m_tcp = c;
		thread = FRunnableThread::Create(this, TEXT("TcpClient_Thread"), 0);
	}

	
	TcpClient_Thread::~TcpClient_Thread()//析构函数
	{
		if(thread != nullptr)
		{
			delete thread;
			thread = nullptr;		
		}
	}

	uint32 TcpClient_Thread::Run()//线程运行函数
	{
		FString ss = FString::Printf(TEXT("TcpClient_Thread::Run()"));
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, ss);//打印消息
		
		m_tcp->run();
		return 0;
	}

	void TcpClient_Thread::Exit()
	{
		FString ss = FString::Printf(TEXT("TcpClient_Thread::Exit()"));
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, ss);//打印消息
		
	}

	void TcpClient_Thread::StopThread()
	{
		m_tcp->stop();
		if(thread != nullptr) thread->WaitForCompletion();
	}

	//****************************************
	void TcpClient::stop()
	{
		isRunning = false;
	}

	void TcpClient::setThread(bool ispause)
	{
		isPause = isPause;
	}

	bool TcpClient::connectServer()
	{
		return true;
	}

	void TcpClient::run()
	{
		while(isRunning)//如果线程正在运行
		{
			if(!isPause)//如果不是暂停状态
			{
				switch (m_data.state)//判断当前状态
				{
				case func::C_Free://空闲状态
					{
						if(isFirstConnect == false)//如果不是第一次连接
						{
							m_data.reset();//重置数据
							FPlatformProcess::Sleep(func::__ClientInfo->AutoTime);//休眠一段时间

							FString ss = FString::Printf(TEXT("auto connect run()"));
							if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, ss);//打印消息
						}
						else
						{
							isFirstConnect = false;//设置为不是第一次连接
						}
						this->connectServer();//连接服务器
					}
						break;
					default:
						this->onRecv();//接收数据
						break;
					
				}
			}
			FPlatformProcess::Sleep(0.02);//休眠20毫秒
		}
	}
}
