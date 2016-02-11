#ifndef GROBAL2_H_
#define GROBAL2_H_
#include "../Net/EnDecode.h"
#include <string>

const int UNITX = 48;
const int UNITY = 32;
const int LONGHEIGHT_IMAGE = 35;
const int HALFX  = 24;
const int HALFY  = 16;
const int MAXMAGIC = 20;  
const int LOGICALMAPUNIT  = 80;

#define ACTORNAMELEN      30

#define DEFAULT_FONTSIZE 12 //Ĭ�������С
//һ�������1024����������- �������������
const int MAX_NETEVENT_COUNT = 1024;

#define MAKEWORD_(a, b)      ((unsigned short)(((unsigned char)(((unsigned long)(a)) & 0xff)) | ((unsigned short)((unsigned char)(((unsigned long)(b)) & 0xff))) << 8))
#define MAKELONG_(a, b)      ((long)(((unsigned short)(((unsigned long)(a)) & 0xffff)) | ((unsigned long)((unsigned short)(((unsigned long)(b)) & 0xffff))) << 16))
#define LOWORD_(l)           ((unsigned short)(((unsigned long)(l)) & 0xffff))
#define HIWORD_(l)           ((unsigned short)((((unsigned long)(l)) >> 16) & 0xffff))
#define LOBYTE_(w)           ((unsigned char)(((unsigned long)(w)) & 0xff))
#define HIBYTE_(w)           ((unsigned char)((((unsigned long)(w)) >> 8) & 0xff))

unsigned char RACEfeature(int cfeature);
unsigned char HAIRfeature(int cfeature);
unsigned char DRESSfeature(int cfeature);
unsigned char WEAPONfeature(int cfeature);
unsigned char Horsefeature(int cfeature);
unsigned char Effectfeature(int cfeature);
unsigned char Colorfeature(int cfeature);
unsigned short APPRfeature(int cfeature);
int PrivDir(int ndir);
int NextDir(int ndir);
int GetDistance(int sx, int sY, int dx, int dy);
int GetFlyDirection(int sx,int sy,int ttx,int tty);
std::string GetValidStr3Ex(std::string src,std::string &dest,char divider,bool utf8 = false);
std::string ArrestStringEx(std::string Source,std::string SearchAfter,std::string ArrestBefore,std::string& ArrestStr);

typedef struct tagDefaultMessage
{
	int	Recog;
	int	Ident;
	int	Param;
	int	Tag;
	int	Serise;
	tagDefaultMessage();
	void reset(void);
}DEFAULTMESSAGE, *PDEFAULTMESSAGE;
#define	MAKEDEFMSG(m, i, r, p, t, s)	{(m)->Recog = r; (m)->Ident = i; (m)->Param = p; (m)->Tag = t; (m)->Serise = s;}
#define MAX_(x,y) (((x) < (y)) ? (y) : (x))
static const int NEXTX[8] = {0, 1, 1, 1, 0, -1, -1, -1};
static const int NEXTY[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
//Э��ͷ�����С
#define	DEFBLOCKSIZE	27   /*16*/

#define     EncodeDefMessage(buf,msg) fnEncode6BitBufA((char*)msg,buf,sizeof(DEFAULTMESSAGE),DEFBLOCKSIZE)
#define     DecodeDefMessage(msg,buf) fnDecode6BitBufA(buf,(char*)msg,sizeof(DEFAULTMESSAGE))

#define CLIENT_VERSION_NUMBER  220540328
#define CLIENT_VERSION_NUMBERFIX  113022060

#define ENEMYCOLOR 69
#define RUN_MINHEALTH 10 //�������Ѫ��ֵΪ��·
#define MAXWPEFFECTFRAME 5
#define   DEFSPELLFRAME     10
#define  HUMANFRAME  3000
#define  STATE_OPENHEATH 1
// 20120821 ԭ��RC_��RCC_Ӧ���Ƿֱ��ʾ�������˺Ϳͻ������Ͷ��壬��
///���������ݱ��д˶���ʹ�ý�Ϊ���ң�Ҫ�޸Ļ��н϶�Ӱ�졣�־�����ԭ�ж���
///  �����޸ģ����������У���RS_��ʾ��������race���壬RC_��ʾ�ͻ��˵Ķ���
#define RC_PLAYOBJECT      0
#define RC_GUARD			12		//������
#define RC_PLAYMOSTER      150              //���ι���
#define RC_HEROOBJECT      66              //Ӣ��
#define RC_GUARD           12               //������
#define RC_PEACENPC        15
#define RC_MON0            20        //����0����
#define RC_ANIMAL          50
#define RC_MONSTER         80
#define RC_NPC             10
#define RC_ARCHERGUARD     112    //������
#define RC_PLANT           200   //ֲ��
#define RC_MINE            201//��ʯ��
#define RC_HORSE           210      //��ƥ���
#define RC_BIAOCHE         222//�ڳ�   //�������˵�ֵ

#define RCC_PLANT     160//ֲ���� �������˵�ֵ
#define RCC_MINE     161//������ �������˵�ֵ
#define RCC_LIANGONG  162//���������Ѫ�������
#define RCC_LIANGONG1  163//���������Ѫ�������
#define RCC_USERHUMAN     RC_PLAYOBJECT
#define RCC_MERCHANT       RC_ANIMAL
#define  RCC_GUARD          RC_GUARD
#define RS_HORSE           165 //��ƥ ��������ֵ

#define SM_WINEXP		44		//��þ���
#define SM_LEVELUP		45		//����
#define SM_BAGITEMS		201		//��������
#define SM_PASSWD_FAIL   503      //��¼����ʧ��
#define SM_PASSOK_SELECTSERVER 529 //��¼�ɹ�����ʼѡ�������
#define CM_SELECTSERVER    104      //�ͻ��˷���ѡ�������
#define SM_SELECTSERVER_OK  530     //ѡ��������ɹ�
#define SM_STARTPLAY       525      //������Ϸ
#define SM_STARTFAIL       526      //ѡ�����������Ϸʧ��
#define SM_SENDNOTICE      658
#define SM_ITEMSHOW 610			//������Ʒ��ʾ
#define SM_ITEMHIDE 611			//������Ʒ����
#define SM_WEIGHTCHANGED 622
#define SM_IDPASSWORDOK  32001
#define SM_HORSERUN        5
#define SM_RUSH            6
#define SM_RUSHKUNG       7               //Ұ����ײ
#define SM_FIREHIT        8                //�һ�
#define SM_BACKSTEP        9             
#define SM_TURN				10				//ת��
#define SM_WALK            11               //��
#define SM_SITDOWN         12
#define SM_RUN            13               //��
#define SM_HIT             14               //��
#define SM_HEAVYHIT       15               //
#define SM_BIGHIT          16               //
#define SM_SPELL         17               //ʹ��ħ��
#define SM_POWERHIT       18               //��ɱ
#define SM_LONGHIT         19               //��ɱ
#define SM_DIGUP         20
#define SM_DIGDOWN         21
#define SM_FLYAXE         22
#define SM_LIGHTING       23
#define SM_WIDEHIT        24
#define SM_CRSHIT         25   //���µ�
#define SM_TWINHIT         26   //����ն�ػ�
#define SM_ALIVE           27
#define SM_MOVEFAIL        28              //
#define SM_HIDE            29               //
#define SM_DISAPPEAR       30
#define SM_STRUCK          31
#define SM_DEATH           32
#define SM_SKELETON        33
#define SM_NOWDEATH        34
#define SM_34SKILLHIT     35               //����
#define SM_35SKILLHIT      36              //���
#define SM_103SKILLHIT    37
#define SM_REMOTEHIT	38
#define SM_MONSPELL 39
#define SM_FEATURECHANGED 41
#define SM_USERNAME 42
#define SM_MONSPELLEFF 47
#define SM_MAGICEFF 49
#define SM_ABILITY 52		//��������
#define  SM_HEALTHSPELLCHANGED 53
#define SM_MAPDESCRIPTION 54
#define SM_GAMEGOLDNAME 55
#define SM_SYSMESSAGE 100 //ϵͳ��Ϣ
#define SM_ADDITEM 200
#define SM_UPDATEITEM 203
#define SM_ADDMAGIC 210 //��ѧ����
#define SM_SENDMYMAGIC 211 //���ؼ�����Ϣ
#define SM_EATITEM 609
#define SM_TAKEON_OK 615 //�����ɹ�
#define SM_SENDUSEITEMS 621 //�������װ����Ϣ
#define SM_CLEAROBJECTS 633
#define  SM_BUTCH 637
#define SM_MAGICFIRE 638
#define SM_MAGICFIRE_FAIL 639
#define SM_MERCHANTSAY 643 //npc�Ի�
#define SM_DURACHANGE 642 //��Ķ�
#define SM_MERCHANTDLGCLOSE 644 //�ر�npc�Ի���
#define SM_CHANGELIGHT 654 //��Ϸ����- ò��������
#define SM_CHANGENAMECOLOR 656 //�ı�������ɫ
#define SM_CHARSTATUSCHANGED 657
#define SM_AREASTATE 708
#define SM_SUBABILITY 752 
#define SM_SPACEMOVE_HIDE  800
#define SM_GHOST 803
#define MAXMAGICTYPE 16
#define SM_SHOWEVENT 804
#define SM_HIDEEVENT 805
#define SM_SPACEMOVE_HIDE2  806
#define SM_SPACEMOVE_SHOW  801  //�ɵ�ĳ�غ� ����˲�� gm��
#define SM_SPACEMOVE_SHOW2 807   //���ܷ� ˲���ƶ�����
#define SM_SPACEMOVE_SHOW3  808
#define SM_ADJUST_BONUS 811
#define CM_PICKUP	1001
#define CM_BUTCH 1007
#define CM_CLICKNPC 1010
#define CM_MERCHANTDLGSELECT 1011 //npc�Ի�
#define CM_IDPASSWORD	2001  //�ʺ�����
#define CM_THROW           3005
#define CM_HORSERUN 3009
#define CM_TURN 3010
#define CM_SITDOWN 3012
#define CM_RUN            3013
#define CM_HIT 3014
#define CM_HEAVYHIT        3015//�ڿ�//stdmode=6���ܿ��Դ���ģ�������˫���������ܣ���ʱ����
#define CM_BIGHIT 3016
#define CM_SPELL 3017
#define  CM_POWERHIT 3018 //��ɱ
#define CM_LONGHIT 3019 //��ɱ
#define  CM_REMOTEHIT       3020
#define CM_WIDEHIT         3024             //����
#define CM_FIREHIT         3025             //�һ�
#define CM_34SKILLHIT      3026             //����
#define CM_35SKILLHIT      3027            //����
#define CM_103SKILLHIT     3028
#define CM_SAY             3030
#define CM_CRSHIT          3036             //���µ�
#define CM_TWNHIT          3037            //����ն�ػ�
#define CM_TWINHIT         CM_TWNHIT  //����ն�ػ�
#define CM_PHHIT           3038;            //�ƻ�ն
#define SM_CREATEHERO 5004
#define CM_ACTORHP 6000
#define SM_ACTORHP 6001
#define SM_SERVERCONFIG 20002
#define CM_QUERYCHR       24001   //��ѯ��ɫ
#define CM_NEWCHR         24002  //�½���ɫ/
#define CM_DELCHR		  24003  //ɾ����ɫ
#define CM_SELCHR         24004  //ѡ���ɫ
#define SM_QUERYCHR       24005 //���������ؽ�ɫ��Ϣ *����/ְҵ/ͷ������ʱ����/�ȼ�/�Ա�/
#define SM_QUERYCHR_FAIL  24006  //���������ؽ�ɫʧ��
#define SM_DELCHR_SUCCESS  24009 //ɾ����ɫ�ɹ�
#define SM_DELCHR_FAIL     24010 //ʧ��
#define SM_TASK				25001 //����
#define CM_TASKSELECT		25004
#define SM_WALKTO			25007 //�Զ��ߵ�Ŀ��
#define	SM_SHOWIMGMSG		25008 //��ʾ�������
#define SM_MEDITATION  25042	//���� 
#define SM_KILLMON 25044 //�Զ���֣�������
#define SM_SHOWPACKAGE 25120 //��ʾ���ͼ��
#define CM_GETICONS 25121
#define SM_GETICONS 25122
#define SM_SENDJINGMAI 25225 //������Ϣ
#define SM_SPELLNEED 25253 //����ļ�������
#define SM_PACKS 25295  //����һ�����ͼ��
#define CM_LOGINNOTICEOK  1018   //ȷ����¼֪ͨ
#define SM_LOGON          50
#define CM_LOGON          2 
#define CM_WANTMINIMAP          1033 
#define CM_WALK           3011
#define CM_QUERYBAGITEMS          81 
#define CM_QUERYUSERNAME          80 
#define SM_CHANGEMAP      634        //�ı��˵�ͼ
#define SM_MAGIC_LVEXP		640		//��������
#define SM_NEWMAP         51      //�µ�ͼ
#define SM_NEWCHR_SUCCESS  24007 //�½���ɫ�ɹ�
#define SM_NEWCHR_FAIL     24008 //�½���ɫʧ��
#define  SM_MISS 25298
#define  SM_THROW         65069


//����
#define DR_UP             0
#define DR_UPRIGHT        1
#define DR_RIGHT          2
#define DR_DOWNRIGHT      3
#define DR_DOWN           4
#define DR_DOWNLEFT       5
#define DR_LEFT           6
#define DR_UPLEFT         7

#define U_DRESS           0             //�·�
#define U_WEAPON          1              //����
#define U_RIGHTHAND       2              //����
#define U_NECKLACE        3              //����
#define U_HELMET          4              //ͷ��
#define U_ARMRINGL        5              //
#define U_ARMRINGR        6
#define U_RINGL           7              //
#define U_RINGR           8
#define U_BUJUK           9               //�� �����������ñ�ʯ
#define U_BELT            10              //ѫ��/��
#define U_BOOTS           11              //Ь
#define U_CHARM           12            //��ʯ ����������ֹħѪʯ

#define U_WINGS           13              //���
#define U_FASHIONDRESS    14              //ʱװ
//��贩��λ��
#define HU_Headdress      0       //ͷ��
#define HU_armor          1       //����
#define HU_Saddle         2       //��
#define HU_Stirrup        3       //����
#define HU_Rein           4       //����
#define HU_GEM            5      //��ʯħѪʯ

#define ET_DIGOUTZOMBI    1
#define ET_PILESTONES     3
#define ET_HOLYCURTAIN    4 //��ȫ��
#define ET_FIRE           5
#define ET_SCULPEICE      6

#define MAXBAGITEMS		64 //����������
#define MAXEQUIP		15 //���װ������
int GetBack(int dir);
int GetNpcOffset(int nAppr);
int GetCodeMsgSize(double x);

#endif