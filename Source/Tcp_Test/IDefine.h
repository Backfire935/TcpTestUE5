#ifndef __IDEFINE_H
#define  __IDEFINE_H

//#include"UnrealString.h"


#define MAX_MD5_LEN	35 //服务端和客户端进行通讯时进行MD5码验证的最大长度

#define CMD_HEART		60000 //心跳包
#define CMD_RCODE		65001 //加密码
#define CMD_SECURITY	65002 //安全验证



namespace  func
{


	enum C_SOCKET_STATE
	{
		C_Free = 0,
		C_ConnectTry = 1,
		C_Connect = 2,
		C_ConnectSecure = 3,
		C_Login = 4,
	};



	//缓存最大数据量 IP 端口 版本号验证 啥的
	struct ConfigXML
	{
		int32	ID; //当前应用程序启动的ID号是多少
		uint8	Type;//当前运行的服务器是个什么类型的服务器,ds服务器，中心服务器，地图服务器

			
		uint8	RCode; //缓存客户端发来的消息数据，做一些加密的运算啥的
		int32	Version; //版本号，用于在连接的过程中验证
		int32	ReceOne;	//服务端接收数据的时候一次最多接收多少数据
		int32	ReceMax; //客户端新连接所开辟缓存空间的大小
		int32	SendOne; //一次最多发送多少字节的数据
		int32	SendMax; //最大发送缓冲区，当一次发不完的时候，就不允许发等下一次再发
		int32	HeartTime; //通过心跳来判断服务端和客户端连接是否有效，是否要释放
		int32	AutoTime; //自动重连时间

		FString	SafeCode;//安全码 最大20字节,产生新连接时判断是否是合法连接
		uint8	Head[2];//验证消息头

	};

	


	extern ConfigXML* __ClientInfo; //客户端XML指针变量
	

}

namespace net
{
	struct S_SERVER_BASE
	{
		int32			ID;
		FString			ip;
		uint16			port;
		int32			serverID;
		uint8			serverType;

		uint8			state;
		uint8			rCode;

		//生产者--接收数据
	//消费者--解析数据
		uint8* recvBuf;//存放接收到的数据，读取到的客户端的数据，存放进，开辟的空间大小是初始化时ConfigXML的ReceMax值
		uint8* recvBuf_Temp;//存放一次最大允许接收的数据的大小，大小是ConfigXML的ReceOne
		int32			recv_Head;//接收数据头的偏移量 生产者
		int32			recv_Tail;//接收数据尾的偏移量 消费者
		int32			recv_TempHead;//临时头
		int32			recv_TempTail;//临时尾
		bool			is_Recved;//数据是否接收完成

		//生产者--封包
	//消费者--发送数据
		uint8* sendBuf;//发送缓冲区,大小是ConfigXML的SendMax
		int32			send_Head;//发送数据头的偏移量 消费者 滑动窗口
		int32			send_Tail;//发送数据尾的偏移量 生产者
		int32			send_TempTail;//
		bool			is_Sending;//是否正在发送数据封包
		bool			is_SendCompleted;//是否发送完毕

		//时间类
		int32			time_AutoConnect;//存放连接时间
		int32			time_Heart;//记录心跳时间
		FString			md5;//MD5码安全验证

		void	Init(int sid);
		void	reset();
	};
}

#endif


