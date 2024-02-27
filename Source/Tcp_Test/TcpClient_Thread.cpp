#include "TcpClient.h"
#include "CoreMinimal.h"

namespace net
{
	
	TcpClient_Thread::TcpClient_Thread(TcpClient* c)
	{
		this->m_tcp = c;
		thread = FRunnableThread::Create(this, TEXT("TcpClient_Thread"), 0);
	}

	
	TcpClient_Thread::~TcpClient_Thread()//��������
	{
		if(thread != nullptr)
		{
			delete thread;
			thread = nullptr;		
		}
	}

	uint32 TcpClient_Thread::Run()//�߳����к���
	{
		FString ss = FString::Printf(TEXT("TcpClient_Thread::Run()"));
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, ss);//��ӡ��Ϣ
		
		m_tcp->run();
		return 0;
	}

	void TcpClient_Thread::Exit()
	{
		FString ss = FString::Printf(TEXT("TcpClient_Thread::Exit()"));
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, ss);//��ӡ��Ϣ
		
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
		while(isRunning)//����߳���������
		{
			if(!isPause)//���������ͣ״̬
			{
				switch (m_data.state)//�жϵ�ǰ״̬
				{
				case func::C_Free://����״̬
					{
						if(isFirstConnect == false)//������ǵ�һ������
						{
							m_data.reset();//��������
							FPlatformProcess::Sleep(func::__ClientInfo->AutoTime);//����һ��ʱ��

							FString ss = FString::Printf(TEXT("auto connect run()"));
							if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, ss);//��ӡ��Ϣ
						}
						else
						{
							isFirstConnect = false;//����Ϊ���ǵ�һ������
						}
						this->connectServer();//���ӷ�����
					}
						break;
					default:
						this->onRecv();//��������
						break;
					
				}
			}
			FPlatformProcess::Sleep(0.02);//����20����
		}
	}
}
