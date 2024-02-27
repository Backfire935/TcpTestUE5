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
		TcpClient_Thread(TcpClient* c);//构造函数
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

		bool isFirstConnect;//判断是否是第一次连接
		bool isRunning;//线程中判断是否正在运行服务器
		bool isPause;//是否暂停线程

		FSocket*		socketfd;
		S_SERVER_BASE	m_data;
		TcpClient_Thread* m_workthread;//客户端用一个线程就可以

		TCPCLIENTNOTIFY_EVENT	onAcceptEvent;//接受连接
		TCPCLIENTNOTIFY_EVENT	onSecureEvent;//安全连接
		TCPCLIENTNOTIFY_EVENT	onDisconnectEvent;//失去连接
		TCPCLIENTNOTIFY_EVENT	onExceptEvent;//异常连接
		TCPCLIENTNOTIFY_EVENT	onCommand;//托管

		int32		initSocket();

		int32		onRecv();//接收数据
		int32		onSend();//发送数据

		void		onHeart();//客户端会不停的给服务端发送心跳包
		void		parseCommand(uint16 cmd);//解析消息体内容
		

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

		 void begin(const uint16 cmd) ;// 玩家数据索引下标 和 头指令
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
		 void setOnSecure(TCPCLIENTNOTIFY_EVENT event) ;//安全连接
		 void setOnDisConnect(TCPCLIENTNOTIFY_EVENT event) ;//失去连接
		 void setOnExcept(TCPCLIENTNOTIFY_EVENT event) ;//异常
		void setOnCommand(TCPCLIENTNOTIFY_EVENT event) ;//注册事件
	};


}


#endif
