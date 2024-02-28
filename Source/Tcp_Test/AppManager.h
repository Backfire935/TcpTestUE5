#ifndef ____APPMANAGER_H
#define ____APPMANAGER_H

#include"TcpClient.h"

namespace app
{
	class AppManager
	{
	public:
		AppManager();
		~AppManager();

		void init();
		
	};

	extern int run();
	extern void onUpdate();//不停的检查连接，解析指令,不停的投递数据
	extern net::TcpClient* __TcpClient;

}

#endif
