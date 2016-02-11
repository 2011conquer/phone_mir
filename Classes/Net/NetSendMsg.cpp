
#include "NetSendMsg.h"
#include <string>
#include "NetClient.h"
#include "../Common/Grobal2.h"
#include "../MShare.h"
namespace VD_Net
{
	CNetSendMsg::CNetSendMsg(CNetClient* net)
	{
		m_NetClient = net;
		m_GetIconsTick = GetTickCount();
	}


	CNetSendMsg::~CNetSendMsg(void)
	{
	}


	void CNetSendMsg::Login(const char* username,const char* paswd)
	{
		std::string text = username;
		text += "/";
		text += paswd;
		m_NetClient->username = username;
		m_NetClient->sendDefMsg(CM_IDPASSWORD,0,0,0,0,text.c_str());
	}

	void CNetSendMsg::selectServer(const char* servername)
	{
		m_NetClient->sendDefMsg(CM_SELECTSERVER,0,0,0,0,servername);
	}

	void CNetSendMsg::QuestChr()
	{
		char buf[10];
		memset(buf, 0, sizeof(buf));
		std::string str = m_NetClient->username;
		str += "/";
		sprintf(buf,"%d",m_NetClient->Certification);
		//	itoa(m_NetClient->Certification, buf, 10);
		str += buf;
		m_NetClient->sendDefMsg(CM_QUERYCHR, 0, 0, 0, 0, str.c_str());

	}

	void CNetSendMsg::SelectChr(const char* chrname)
	{
		std::string str = m_NetClient->username;
		str += "/";
		str += chrname;
		m_NetClient->sendDefMsg(CM_SELCHR, 0, 0, 0, 0, str.c_str());
	}
	void CNetSendMsg::SendNewChr(const char* uname,const char* sjob,const char* ssex)
	{
		std::string str ;
		char c[128]; sprintf(c,"%s/%s/0/%s/%s",m_NetClient->username.c_str(),uname,sjob,ssex);
		str = c;
		m_NetClient->sendDefMsg(CM_NEWCHR, 0, 0, 0, 0, str.c_str());
	}

	void CNetSendMsg::SendDelChr(const char* sChrname)
	{
		m_NetClient->sendDefMsg(CM_DELCHR, 0, 0, 0, 0, sChrname);
	}
	void CNetSendMsg::RunLogin()
	{
		char buf[512];
		sprintf(buf, "**%s/%s/%d/%d/%d", m_NetClient->username.c_str(), m_NetClient->chrname.c_str(), m_NetClient->Certification, CLIENT_VERSION_NUMBER, 0);
		m_NetClient->sendSocket(buf, strlen(buf), true);
	}

	void CNetSendMsg::SendHeartPacket()
	{
		char bf ='*';
		m_NetClient->sendSocket(&bf,1);
	}

	void CNetSendMsg::SendLogon()
	{
		const char LOGON_STR[]   = "�װ�����ң����ã��㻹δͨ����������֤��������Ϸ������ܻ��ܵ�Ӱ�죬�뼰ʱ������½Ƿ����԰�ť��д��֤��Ϣ��������Ϸʱ�䳬��3Сʱ�󣬽���ǿ��������Ϣ����Ϣʱ����5Сʱ��ſ��Լ�����Ϸ��";
		int CRC = -1898912658;
		int n =	CLIENT_VERSION_NUMBERFIX ^ CRC;
		m_NetClient->sendDefMsg(CM_LOGON,CRC, 0,0, n);


	}

	void CNetSendMsg::SendPickup(int x,int y)
	{
		m_NetClient->sendDefMsg(CM_PICKUP,0,x,y,0);
	}

	void CNetSendMsg::SendMerchantDlgSelect(int merchant,std::string rstr)
	{
		//���� ���۰� - ��ʱ��д
		// 20120630ǰ��Ĵ����У��Ὣ�ַ����е��»���_��Ϊ�ո��������
		//ĳЩ���»��ߵ���������޷���ȷ���󣬹ʴ˴����°ѿո�
		//�滻Ϊ�»���  ��������s_repair

		std::string str = rstr;
		StringReplace(str," ","_");
		m_NetClient->sendDefMsg(CM_MERCHANTDLGSELECT,merchant,0,0,0,str.c_str());

	}
	void CNetSendMsg::SendQueryUserName(int targetid,int x,int y)
	{
		m_NetClient->sendDefMsg(CM_QUERYUSERNAME,targetid,x,y,0);
	}

	void CNetSendMsg::SendTaskSelect(int nTaskId,std::string rstr)
	{
		m_NetClient->sendDefMsg(CM_TASKSELECT,nTaskId,0,0,0,rstr.c_str());
	}

	void CNetSendMsg::SendGetIcons()
	{
		if(m_GetIconsTick < GetTickCount())
		{
			m_NetClient->sendDefMsg(CM_GETICONS,0,0,0,0);
			m_GetIconsTick = GetTickCount() + 600000;

		}
	}
}
