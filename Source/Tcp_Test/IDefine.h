#ifndef __IDEFINE_H
#define  __IDEFINE_H

//#include"UnrealString.h"


#define MAX_MD5_LEN	35 //����˺Ϳͻ��˽���ͨѶʱ����MD5����֤����󳤶�

#define CMD_HEART		60000 //������
#define CMD_RCODE		65001 //������
#define CMD_SECURITY	65002 //��ȫ��֤



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



	//������������� IP �˿� �汾����֤ ɶ��
	struct ConfigXML
	{
		int32	ID; //��ǰӦ�ó���������ID���Ƕ���
		uint8	Type;//��ǰ���еķ������Ǹ�ʲô���͵ķ�����,ds�����������ķ���������ͼ������

			
		uint8	RCode; //����ͻ��˷�������Ϣ���ݣ���һЩ���ܵ�����ɶ��
		int32	Version; //�汾�ţ����������ӵĹ�������֤
		int32	ReceOne;	//����˽������ݵ�ʱ��һ�������ն�������
		int32	ReceMax; //�ͻ��������������ٻ���ռ�Ĵ�С
		int32	SendOne; //һ����෢�Ͷ����ֽڵ�����
		int32	SendMax; //����ͻ���������һ�η������ʱ�򣬾Ͳ���������һ���ٷ�
		int32	HeartTime; //ͨ���������жϷ���˺Ϳͻ��������Ƿ���Ч���Ƿ�Ҫ�ͷ�
		int32	AutoTime; //�Զ�����ʱ��

		FString	SafeCode;//��ȫ�� ���20�ֽ�,����������ʱ�ж��Ƿ��ǺϷ�����
		uint8	Head[2];//��֤��Ϣͷ

	};

	


	extern ConfigXML* __ClientInfo; //�ͻ���XMLָ�����
	

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

		//������--��������
	//������--��������
		uint8* recvBuf;//��Ž��յ������ݣ���ȡ���Ŀͻ��˵����ݣ���Ž������ٵĿռ��С�ǳ�ʼ��ʱConfigXML��ReceMaxֵ
		uint8* recvBuf_Temp;//���һ�����������յ����ݵĴ�С����С��ConfigXML��ReceOne
		int32			recv_Head;//��������ͷ��ƫ���� ������
		int32			recv_Tail;//��������β��ƫ���� ������
		int32			recv_TempHead;//��ʱͷ
		int32			recv_TempTail;//��ʱβ
		bool			is_Recved;//�����Ƿ�������

		//������--���
	//������--��������
		uint8* sendBuf;//���ͻ�����,��С��ConfigXML��SendMax
		int32			send_Head;//��������ͷ��ƫ���� ������ ��������
		int32			send_Tail;//��������β��ƫ���� ������
		int32			send_TempTail;//
		bool			is_Sending;//�Ƿ����ڷ������ݷ��
		bool			is_SendCompleted;//�Ƿ������

		//ʱ����
		int32			time_AutoConnect;//�������ʱ��
		int32			time_Heart;//��¼����ʱ��
		FString			md5;//MD5�밲ȫ��֤

		void	Init(int sid);
		void	reset();
	};
}

#endif


