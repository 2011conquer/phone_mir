#ifndef GAMESTRUCT_H_
#define  GAMESTRUCT_H_

#include <string>
#include "./Common/Grobal2.h"
#include <vector>

enum TSceneType
{
	stDownload = 0, //���س���
	stIntro = 1, //LOGO����
	stLogin = 2, //��¼����
	stSelectChr = 3,//ѡ���ɫ����
	stNewChr = 4, //������ɫ����
	stLoginNotice = 5,//���泡��
	stPlayGame = 6, //��Ϸ����
};
struct TVDDataHeader
{
	char Title[40];
	int DBCount;
	int VerFlag;
	TVDDataHeader();
	void reset(void);
};


struct TVDDataInfo
{
	unsigned char nType;
	unsigned char n1,n2,n3;	//����
	int nSize;	 //���ݴ�С
	short px;
	short py;
	TVDDataInfo();
	void reset(void);
};


struct TMapHeader
{
	char Title[20];
	unsigned short Width;
	unsigned short Height;
	double UpdateDate;
	int	ZipSize;
	char Reserved[20];
	TMapHeader();
	void reset(void);
};

struct TMapInfo
{
	unsigned short BkAree;	//�ײ㱳��ͼ�����ڵ�vdd�ļ�����
	unsigned short BkImg;	 //�ײ�ͼƬ���� 2  //���λΪ1���������ߣ�ͼƬ����Ϊ��17λ
	unsigned short MidImg;	//�м��ͼƬ���� //ͼƬ����Ϊ��17λ
	unsigned short Area;	 //���ͼƬ��ӦOBJECT����
	unsigned short FrImg;	//���ͼƬ����   //���λΪ1����������
	char	DoorIndex;		//���λΪ1���ţ�����Ϊ��7λ	
	char	DoorOffset;		//���λΪ1�ǿ���0�ǹ�	
	char AniFrame;			 //����Ч�� (Draw Alpha)
	char	AniTick;		//��ӰЧ��
	char light;				 //���Ч�������ߣ�
	char flags;				//����
	TMapInfo();
	void reset(void);
};

struct TPoint
{
	int x;
	int y;
	TPoint();
	void reset(void);
};

struct TRect_
{
	int Left;
	int Top;
	int Right;
	int Bottom;
	TRect_();
	void reset(void);
	void Rect(int ALeft,int ATop,int ARight,int ABottom);
};

//����ṹ��Ҫ�ڴ����
#pragma pack(push)
#pragma pack(1)
struct TAbility
{
	unsigned short Level;                      
	int AC;  //����
	int AC2;
	int MAC;   //ħ��
	int MAC2;
	int DC;    //������
	int DC2;
	int MC;   //ħ��
	int MC2;
	int SC;   //����
	int SC2;
	int HP;                    
	int MP;                        
	int MaxHP;                   
	int MaxMP;                   
	unsigned long Exp;                   
	unsigned long MaxExp;                
	int Weight;                   //���������������������ʹ�� 2014.326 Loser.DieYoung
	int MaxWeight;                
	int WearWeight;              
	int MaxWearWeight;           
	int HandWeight;              
	int MaxHandWeight;   
	TAbility();
	void reset(void);
};
#pragma pack(pop)   

enum TMagicType
{
	mtReady = 0,
	mtFly,
	mtExplosion,
	mtFlyAxe,
	mtFireWind,
	mtFireGun,
	mtLightingThunder,
	mtThunder,
	mtExploBujauk,
	mtBujaukGroundEffect,
	mtKyulKai,
	mtFlyArrow,
	mt12,
	mt13,
	mt14,
	mt15,
	mt16,
	mHeroMagic
};
struct TUseMagicInfo
{
	int ServerMagicCode;
	int MagicSerial;
	int target;
	TMagicType EffectType;
	int EffectNumber;
	int targx;
	int targy;
	bool Recusion;
	int anitime;
	TUseMagicInfo();
	void reset(void);
};

struct TActionInfo
{
	unsigned short start;
	unsigned short frame;
	unsigned short skip;
	unsigned short ftime;
	unsigned short usetick;
	TActionInfo();
	void reset(void);
};

struct TMonsterAction 
{
	TActionInfo ActStand ;
	TActionInfo ActWalk;   
	TActionInfo ActRun;
	TActionInfo ActAttack;
	TActionInfo ActCritical;
	TActionInfo ActStruck;
	TActionInfo ActDie;
	TActionInfo ActDeath;
	TActionInfo ActSpell;
	TActionInfo ActAttack1;
	TActionInfo ActAttack2;
	TActionInfo ActAttack3;
	TActionInfo ActAttack4;
	TActionInfo ActAttack5;
	TActionInfo ActAttack6;
	TMonsterAction();
	void reset();
};


struct  THumanAction 
{
	TActionInfo ActStand;
	TActionInfo ActWalk;
	TActionInfo ActRun;
	TActionInfo ActRush;
	TActionInfo ActWarMode;
	TActionInfo ActHit;
	TActionInfo ActHeavyHit;
	TActionInfo ActBigHit;
	TActionInfo ActFireHitReady;
	TActionInfo ActTSpell;
	TActionInfo ActFSpell;
	TActionInfo ActSitdown;
	TActionInfo ActStruck;
	TActionInfo Act34Hit;
	TActionInfo Act35Hit;
	TActionInfo Act103Hit;
	TActionInfo ActKQStruck;
	TActionInfo ActDie;
	TActionInfo ActMeditation;
	THumanAction();
	void reset(void);
};

//�����¼�����
enum TNETEVENTTYPE
{
	NORMAL = 0,
	SOCKET_CONNECT_SELGATE = 1, //����ѡ�˷�����ʧ��
	SOCKET_CONNECT_RUNGATE = 2,		//�������ط�����ʧ��
	NETPACKET = 3,					//������-
	NETPACKET_SPECIAL = 4 //������
};
struct TNetEvent
{

	TNETEVENTTYPE event_type;
	tagDefaultMessage msg;
	std::string Body;
	TNetEvent();
	void reset(void);
};

struct TMessageBodyWL
{
	int	lParam1;
	int	lParam2;
	int	lTag1;
	int	lTag2;
	TMessageBodyWL();
	void reset(void);
};


struct TChrMsg
{
	int Ident;
	int x;
	int y;
	int dir;
	int State;
	int feature;
	std::string saying;
	int sound;
	TChrMsg();
	void reset(void);
};

struct TMagicInfo
{
	char name[20];
	char Biao;
	unsigned short Fu;
	unsigned short magicID;
	TMagicInfo();
	void reset(void);
};
struct TActorInfo
{
	char name[20];
	char dirChar[2];
	unsigned short nx;
	unsigned short ny;
	char sType[4];
	TActorInfo();
	void reset(void);
};
struct TShared                    //�ڹ�
{
	bool boLongAttack;              //������ɱ
	bool boSmartLongAttack ; //�Զ���λ��ɱ ��λ��ɱ
	bool boShowUserName;            //chatop ����ʾ���� 2010-12-2
	bool boShowInformation;         //chatop����ͷ����ʾ��Ϣ  2010-11-30
	std::string stimenow;                   //chatop����ͷ����ʾ��ʱ����Ϣ  2010-11-30
	std::string chrname;              //chatop���½���ɫ������ 2011-1-8
	int leftchr;                     //chatop���½���ɫ�����ֵ���ʾλ�� 2011-1-8
	int topchr;                    //chatop���½���ɫ�����ֵ���ʾλ�� 2011-1-8
	bool chrnameeditshow;       //chatop���½���ɫ�������Ƿ���ʾ 2011-1-8
	int  left;
	int  top;
	char sID[20];
	char sPass[20];
	bool boEnter;
	unsigned char btLoad;
	char name[20];
	bool boWarrC;
	bool bocloseform;
	bool boShowBlood;
	bool boShowNumBlood; //������Ѫ
	bool boRunAndRun;
	bool boDuraAlern;
	bool boClearBody;  //����ʬ�壬ֻ�����أ�����������������
	bool boNoHit;    //������������
	bool boAttackLock;     //�������� ħ������
	bool boShowAttactTarget;
	bool boForceExit;
	bool boNoStone;
	bool boAttackChangeColor;
	bool boTeamChangeColor;
	bool boUseMagicDownHorse;    //ʹ��ħ���Զ�����
	bool boCloseExp;
	bool boItemFlash;
	bool boShowItem;
	bool boAutoPickUp;  //�Զ���ȡ��Ʒ
	bool boShowLocalFashion;//��ʾ����ʱװ-
	bool boAutoPickUpDrug ; //�Զ���ȡҩ��
	bool boAutoPickUpGold ; //�Զ���ȡ���
	bool boCTRLPickUp;     //ctrl������ȡ��Ʒ ����Ϊ�ո��
	bool boBindItem;
	unsigned char unsbtMouseMiddle;
	unsigned char btMouseMiddelMagic;
	unsigned char boWarrLock;
	bool boWarrTbs;
	bool boWarrPx;
	bool boAutoThree;
	bool boAutoFour;
	bool boBuffTime;
	bool boMoDun;
	bool boMoHiddent;//�Զ�����
	bool boAutoDF;  //�Զ�����
	char sProtect[10];    //����ģʽ
	bool boHpMin;     //�Զ���ҩ
	int nHpMin; //�Զ���ҩ����
	int nHpTick; //ʱ����
	bool boMpMin;     //�Զ���ħ��ҩ
	int nMpMin; //�Զ���ħ��ҩ����
	int nMpTick; //ʱ����
	bool boHPMPfast  ;//���ٻָ�ҩ
	int nHPMPFastMin ;//���ٻָ�ҩ����
	int nHPMPFastTack ;//ʱ����
	int boUseJuan;    //ʹ�ûسǾ�
	int nUseJuanMin ;  //ʹ�ûسǾ�hp����
	int nUseJuanTick ;  //ʱ����
	bool boAutorecallBaobao ;//�Զ��ٻ�����
	bool boAutoAnswer;
	char sAnswer[50];
	char sBlackName[255];
	bool boAutoSay;
	char sSayString[255];
	int nAutoSayTime;
	bool boSaveChat;
	unsigned char btAddChatType;
	char sAddString[255];
	char  sBossName[255];
	bool boBossA;
	TActorInfo rInfo[100];
	char sChatName[20];
	TMagicInfo rMagic[51];
	char sChatStr[255];
	bool boSendChat;
	bool boHideActor;      //������Χ��ɫ-  2014.12.31
	TShared();
	void reset(void);
};


enum TChrAction
{
	caWalk = 0,
	caRun,
	caHorseRun,
	caHit,
	caSpell,
	caSitdown
};

struct TCharDesc
{
	int feature;
	int featureEx;
	TCharDesc();
	void reset(void);
};
// 20120627 �������й�˳�����������������ֶΣ�������
//������Ӣ�ۼ��ܣ�ԭ����Ӣ�ۼ�����ͨ�������ֶ��жϵ�
struct TMagic
{
	char sMagicName[16];
	unsigned short wMagicId;
	unsigned char wMagicType;//���ͣ�0��ͨ��1 Ӣ�۵�
	unsigned char  bt1;//����������
	unsigned char TrainLevel[4];
	int MaxTrain[4];
	unsigned char btEffectType;
	unsigned char btEffect;
	unsigned short wSpell;
	unsigned short wPower;
	unsigned short wMagicIdx;
	unsigned long dwDelayTime;
	unsigned char btTrainLv;
	unsigned char btJob;
	unsigned char btDefSpell;
	unsigned char btDefPower;
	unsigned short wMaxPower;
	unsigned char btDefMaxPower;
	unsigned char bt11;
	char sDescr[24]; //���޸ĳ����뿼��ʵ��ռ���ڴ��С�Ƿ����
	TMagic();
	void reset(void);
};

struct TClientMagic
{
	unsigned char Key;//����֤
	unsigned char Level;
	int CurTrain;
	TMagic Def;
	TClientMagic();
	void reset(void);
};
struct THumBaseInfo
{
	int MaxMP;
	int MP;
	THumBaseInfo();
	void reset(void);
};
//���ص�ͼ��Ϣ�������ͻ��˿��ͼѰ·
struct   TLocalMapInfo
{
	std::string sMapName;
	std::vector<void*> Gates;/*TMapGateInfo*/
	TLocalMapInfo();
	void reset(void);
	void release(); //�ͷ�
};
struct TMapGateInfo
{
	TLocalMapInfo* SMapInfo; //��Դ��ͼ��Ϣ, ��Ҫ���ڿ��ͼѰ·
	std::string SMapName;
	int SX;
	int SY; 
	TLocalMapInfo* DMapInfo; //Ŀ���ͼ��Ϣ
	std::string DMapName;
	std::string DMapTitle;
	int DX;
	int DY;
	TMapGateInfo* fromGate;
	TMapGateInfo();
	void reset(void);
};

struct TSoundInfo
{
	std::string sFileName;
	unsigned long dwLastTick;
	TSoundInfo();
	void reset(void);
};

struct TSubAbilityExt
{
	int MaxWrathPoint;
	int WrathPoint;
	TSubAbilityExt();
	void reset(void);
};

struct TNakedAbility
{
	int DC;
	int MC;
	int SC;
	int AC;
	int MAC;
	int HP;
	int MP;
	int Hit;
	int Speed;
	int X2;
	TNakedAbility();
	void reset(void);
};

struct TReNewInfo
{
	unsigned short NeedLevel;  //��Ҫ�ȼ�
	unsigned char Probability ;    //�ɹ�����
	unsigned char DownLevel;     //�½��ȼ��� 
	int BonusPoint;    //��������
	unsigned short Count;         //ÿ��ת������
	unsigned short Crit;          //����
	unsigned short w1;    //������Ԥ����
	unsigned short w2;
	int i1;
	int i2;
	TReNewInfo();
	void reset(void);
};

//������Ʒ�ṹ 20120627 ����������˳��������id���ֽھ�������
struct TStdItem
{
	char Name[32];//��Ʒ����
	unsigned short ID ;	 //��Ʒid�����ݿ��е��������
	unsigned char job;   //ְҵ
	unsigned char NeedIdentify; //��Ҫ��¼��־
	unsigned short Reserved;//���� ��20120801 ���й����õ��������ҩ��Ѫ���ĵ�λ�ǰٷֱȻ��ǵ���
	//reserved ��Ÿ������й� ���������� 8 �����ص� 10 �����ص�??? 4�޷�ȡ�� ʵ���Ѿ�����
	unsigned short StdMode; ///��Ʒ���� 0/1/2/3��ҩ�� 5/6:������10/11�����ף�
	///15��ͷ����22/23����ָ��24/26������19/20/21������
	///20130326���� 100 ͷ�� 101 ���� 102 ��  103 ���� 104 ����
	///  2013.5.18 200.��ʯ-
	unsigned short Shape;	//װ�����
	unsigned short Weight; //����
	unsigned short CharLooks; //:20121220 �������û�������ã�Ŀǰ������Ϊ�������������ã���Ƕ��Ʒstdmode 200 ���ֵ��ʶ��Ƕ����ƷMID
	unsigned short AniCount;
	unsigned short Source;    //Դ����
	unsigned short	_throw;
	int Looks;   //��ۣ���Items.WIL�е�ͼƬ����
	int DuraMax;     //���־�
	int AC;                        //0x1A
	int AC2;
	int MAC;                       //0x1C
	int MAC2;
	int DC;                        //0x1E
	int DC2;
	int MC;                        //0x20
	int MC2;
	int SC;
	int SC2;
	int Need;                      //0x24
	int NeedLevel;                 //0x25
	int Price;                     //0x28
	 char memo[52];
	TStdItem();
	void reset(void);
};

struct TAdditionItem
{
	int id;
	int quality;
	TAdditionItem();
	void reset(void);
};
struct TShortMessage
{
	unsigned short Ident;
	unsigned short wMsg;
	TShortMessage();
	void reset(void);
};

struct TUserCharacterInfo
{
	std::string name;
	unsigned char job;
	unsigned char hair;
	unsigned short level;
	unsigned char sex;
	TUserCharacterInfo();
	void reset(void);
};


struct TDropItem
{
	int x;
	int y;
	int id;
	int Looks;
	std::string sName;
	unsigned long FlashTime;
	unsigned long FlashStepTime;
	int	FlashStep;
	bool boFlash;
	unsigned short stdmode;
	TDropItem();
	void reset(void);
};


struct TClientItem
{
	TStdItem s;
	int MakeIndex;
	int Dura;
	int DuraMax;
	unsigned short btValue[20];
	TClientItem();
	void reset(void);
};

struct TFindNode
{
	int x;
	int y;
	TFindNode();
	void reset(void);
};

struct TTree
{
	int h;
	int x;
	int y;
	unsigned char dir;
	TTree* Father;
	TTree();
	void reset(void);
};

struct TLink
{
	TTree* node;
	int f;
	TLink* next;
	TLink();
	void reset(void);
};

struct TUserItem
{
	int MakeIndex;		 // ���кŰ�?
	int wIndex;				//��Ʒid
	unsigned short Dura;	 //��ǰ�־�ֵ
	unsigned short DuraMax;	 //���־�ֵ
	unsigned short btValue[20];
	TUserItem();
	void reset(void);
};

//����ȵ�
struct TClickPoint
{
	TRect_ rc;
	std::string rstr;
	int id;					//����ű��ĵ���ȵ�������¼����id
	unsigned char nType;	//���� Ĭ��0 ��Ʒͼ��1
	TClickPoint();
	void reset(void);
};

struct TMovingItem
{
	int index;
	TClientItem item;
	TMovingItem();
	void reset(void);
};

struct TMapWalkXY
{
	bool boWalk;
	int nMonCount;
	int nX;
	int nY;
	TMapWalkXY();
	void reset(void);
};
struct TIconInfo
{
	int imgIndex;
	char title[24];
	TIconInfo();
	void reset(void);
};

struct TGroupItem
{
	std::string FLD_USEITEMS[MAXEQUIP];
	int FLD_RATE[20];
	bool FLD_FLAG[20];
	std::string FLD_TITLE;
	std::string FLD_HINTMSG;
	TGroupItem();
	void reset(void);
};

struct TClientUserStateInfo
{
	int feature;
	unsigned long NAMECOLOR;
	char UserName[ACTORNAMELEN];
	char GuildName[ACTORNAMELEN];
	char GuildRankName[17];
	TClientItem UseItems[MAXEQUIP];
	unsigned char GuildFlag;
	TIconInfo useIcons[10];
	TClientUserStateInfo();
	void reset(void);
};


struct TTaskItem
{
	unsigned short TaskID;
	unsigned short State;
	unsigned short param1;
	unsigned short param2;
	unsigned short param3;
	unsigned short param4;
	TTaskItem();
	void reset(void);
};

struct TClientTaskItem
{
	TTaskItem item;
	std::string Title;
	std::string ShortDesc;
	std::string Desc;
	TClientTaskItem();
	void reset(void);
};

 //��չ��һЩħ�������ԣ�Ŀǰ�Ǵ����Ҫ������
struct TClientMagicExInfo
{
	unsigned short wMagIdx;
	unsigned long UpdateTime;
	unsigned long NeedTime;
	int NeedWrathPoint;
	TClientMagicExInfo();
	void reset(void);
};
#endif