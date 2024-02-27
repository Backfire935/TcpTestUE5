#ifndef __TCPCLIENT_H
#define  __TCPCLIENT_H

#include"IDefine.h"
#include "HAL/Runnable.h"
#include"HAL/RunnableThread.h"
#include"Sockets.h"
#include"SocketSubsystem.h"

namespace net
{
	class TcpClient;
	typedef void(*TCPCLIENTNOTIFY_EVENT)(TcpClient* tcp, const int32 code);

	class TcpClient_Thread : public FRunnable
	{
	public:
		TcpClient_Thread(TcpClient* c);//���캯��
		virtual ~TcpClient_Thread();
		virtual uint32 Run();
		virtual void Exit();
		//virtual void Stop();
		//virtual bool Init();

		void StopThread();
		FRunnableThread * thread;
		TcpClient* m_tcp;
	};
	
	class TcpClient
	{

		bool isFirstConnect;//�ж��Ƿ��ǵ�һ������
		bool isRunning;//�߳����ж��Ƿ��������з�����
		bool isPause;//�Ƿ���ͣ�߳�

		FSocket*		socketfd;
		S_SERVER_BASE	m_data;
		TcpClient_Thread* m_workthread;//�ͻ�����һ���߳̾Ϳ���

		TCPCLIENTNOTIFY_EVENT	onAcceptEvent;//��������
		TCPCLIENTNOTIFY_EVENT	onSecureEvent;//��ȫ����
		TCPCLIENTNOTIFY_EVENT	onDisconnectEvent;//ʧȥ����
		TCPCLIENTNOTIFY_EVENT	onExceptEvent;//�쳣����
		TCPCLIENTNOTIFY_EVENT	onCommand;//�й�

		int32		initSocket();

		int32		onRecv();//��������
		int32		onSend();//��������

		void		onHeart();//�ͻ��˻᲻ͣ�ĸ�����˷���������
		void		parseCommand(uint16 cmd);//������Ϣ������
		

	public:
		TcpClient();
		 ~TcpClient();
		 inline S_SERVER_BASE* getData() { return &m_data; };

		void run();
		void stop();
		void setThread(bool ispause);
		 void runClient(uint32 sid, char* ip, int32 port) ;
		 bool connectServer() ;
		 void disconnectServer(const int32 errcode,FString err) ;

		 void begin(const uint16 cmd) ;// ������������±� �� ͷָ��
		 void end() ;

		 void sss(const int8 v) ;
		 void sss(const uint8 v) ;

		 void sss(const int16 v) ;
		 void sss(const uint16 v) ;

		 void sss(const int32 v) ;
		 void sss(const uint32 v) ;

		 void sss(const int64 v) ;

		 void sss(const bool v) ;
		 void sss(const float v) ;
		 void sss(const double v) ;
		 void sss(void* v, const int32 len) ;

		 void read(int8& v) ;
		 void read(uint8& v) ;

		 void read(int16& v) ;
		 void read(uint16& v) ;

		 void read(int32& v) ;
		 void read(uint32& v) ;

		 void read(int64& v) ;

		 void read(float& v) ;
		 void read(double& v) ;

		 void read(bool& v) ;
		 void read(void* v, const int32 len) ;

		 void parseCommand() ;

		 void setOnConnect(TCPCLIENTNOTIFY_EVENT event) ;
		 void setOnSecure(TCPCLIENTNOTIFY_EVENT event) ;//��ȫ����
		 void setOnDisConnect(TCPCLIENTNOTIFY_EVENT event) ;//ʧȥ����
		 void setOnExcept(TCPCLIENTNOTIFY_EVENT event) ;//�쳣
		void setOnCommand(TCPCLIENTNOTIFY_EVENT event) ;//ע���¼�
	};


}


#endif
