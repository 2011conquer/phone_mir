#ifndef NETCLIENT_H_
#define NETCLIENT_H_
#include <string>

namespace VD_Net
{
	class CTcpSocket;
	class CNetRecvMsg;
	class CNetSendMsg;
	class CNetClient
	{
	public:
		CNetClient(void);
		~CNetClient(void);

		static CNetClient* GetInstance();
	private:
		CTcpSocket* m_Socket;
	public:
		bool Connect(const char* szServerIP,int nServerPort,bool isReconnect = false/*��������*/);
		bool ProcessMsg();

		CNetRecvMsg* GetRecvMsg(){return m_NetRecvMsg;}
		CNetSendMsg* GetSendMsg(){return m_NetSendMsg;}
		void sendDefMsg(int mIdent, int mRecog, int mParam, int  mTag,int mSeries, const char *str = NULL, bool strEncode = true,const char* adddata=nullptr);
		void sendSocket(char *buf, int size, bool strEncode = false);
	private:
		char m_Data[65535];
		char m_SendData[65535]; //�������ݻ�����
		unsigned char msgCode;
		bool m_bCon;
	private:
		CNetRecvMsg* m_NetRecvMsg;
		CNetSendMsg* m_NetSendMsg;
	public:
		char mEncodeBuf[1024*30];
		char mDecodeBuf[1024*30];
		int Certification;
		std::string username;	//��Ϸ�ʺ�
		std::string serverhost; //��Ϸip
		std::string chrname; //��ɫ����


	};

}


#endif
