#include "JoyStick.h"
#include "GameStruct.h"
#include "VD_Share.h"
#include "MShare.h"
#include "../FrmMain.h"
#include "../GuaJiHelper.h"
static CJoyStick* m_Instance = nullptr;
CJoyStick::CJoyStick(void)
{
	m_joystick = nullptr;
	m_Layer = nullptr;
	m_R = 0;
	m_O.x = 0; m_O.y = 0;
	m_IsMove = false;
}


CJoyStick::~CJoyStick(void)
{
}

CJoyStick* CJoyStick::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance =new CJoyStick();
	}
	return m_Instance;
}

void CJoyStick::Show(cocos2d::Layer* layer)
{
	m_Layer = cocos2d::Layer::create();
	m_Layer->retain();
	layer->addChild(m_Layer,1,DIALOG_TYPE::JOYSTICK);
	//����ҡ�����沿��  
	cocos2d::Sprite *joystick1=cocos2d::Sprite::create("joystick1.png"); 
	
	//����͸���ȣ�ê�㣬λ��  
	joystick1->setOpacity(191); 
	joystick1->setAnchorPoint(cocos2d::Vec2(0,0));  
	joystick1->setPosition(cocos2d::Vec2(50,50));  
	//��Բ�뾶  
	m_R=joystick1->getContentSize().width/2;  
	//���ĵ�  
	m_O=Vec2(m_R + joystick1->getPosition().x,m_R+ joystick1->getPosition().y);  
	//��ӽ�����  
	m_Layer->addChild(joystick1,1,1);  

	//����ҡ������ԲȦ����  
	m_joystick=cocos2d::Sprite::create("joystick2.png");  
	//����λ��Ϊҡ�����ĵ㲢��ӽ�����  
	m_joystick->setPosition(Vec2(m_O.x,m_O.y ));  
	m_Layer->addChild(m_joystick,2);  

	//���ÿɴ���  
	m_Layer->setTouchEnabled(true);  

	m_Layer->schedule(schedule_selector(CJoyStick::_Update));


	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();  
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(CJoyStick::onTouchesBegan,this); //������ʼ 
	listen->onTouchMoved = CC_CALLBACK_2(CJoyStick::onTouchesMove,this);  //�����ƶ�
	listen->onTouchEnded = CC_CALLBACK_2(CJoyStick::onTouchesEnded,this);  //��������
	eventDispatcher->addEventListenerWithSceneGraphPriority(listen,m_Layer); 
}

void CJoyStick::Hide()
{
	m_Layer->getParent()->removeChildByTag(DIALOG_TYPE::JOYSTICK);
	m_Layer->release();
}
void CJoyStick::_Update(float dt)
{
	
	//ҡ���ƶ�--
	bool isMove = GetInstance()->IsMove();
	if(isMove)
	{
		if(GetTickCount() - g_dwLastMoveTick > 600)
		{
			cocos2d::Vec2 pos = CJoyStick::GetInstance()->GetMovePos();
			g_ChrAction = caRun;
			g_nTargetX = g_MySelf->m_nCurrX + pos.x * 2;
			g_nTargetY = g_MySelf->m_nCurrY + pos.y * 2;
			//�ƶ���ʱ��ȥ��Ŀ����ȥ���Զ��һ�Ѱ·״̬,��Ȼ���ȥ����.
			g_TargetCret = nullptr;
			FrmMain::GetInstance()->StopAutoRun();
			//�Զ��һ�Ҳ����2015.8.10
			TGuaJiHelper::GetInstance()->Stop();
		}
	}

}

bool CJoyStick::onTouchesBegan(Touch *touch, Event *unused_event)
{
 
	cocos2d::Vec2 location = touch->getLocation();  
	cocos2d::Rect rect= m_joystick->getBoundingBox();  
	if (rect.containsPoint(location))  
	{  
		m_IsMove = true;
	}  
	return true;
}

//������������
void CJoyStick::onTouchesMove(Touch *touch, Event *unused_event)
{
	cocos2d::Vec2 location = touch->getLocation();  
	//�жϴ����������Ƿ���ҡ�˷�Χ��  
	bool inRange=pow(m_O.x-location.x,2)+pow(m_O.y-location.y,2)<pow(m_R,2);  
	inRange = true;
	if(m_IsMove&&inRange){  
	//	cocos2d::Vec2 position= plane->getPosition();  
		m_joystick->setPosition(location);  

		float r = m_R*2/6;  
		float d= m_R*2/3;  
		//�ϣ�����2��5  
		
		if(triangleContainPoint(m_O.x,m_O.y,m_O.x-r,m_O.y+r,m_O.x+r,m_O.y+r,location.x,location.y)  
			||Rect(m_O.x-r,m_O.y+r,d,d).containsPoint(location)){  
				m_nX=0;  
				m_nY=-1;  
		}  
		//�£�����6��11  
		else if(triangleContainPoint(m_O.x,m_O.y,m_O.x-r,m_O.y-r,m_O.x+r,m_O.y-r,location.x,location.y)  
			||Rect(m_O.x-r,m_O.y-r-d,d,d).containsPoint(location)){  
				m_nX=0;  
				m_nY=1;  
		}  
		//������4��7  
		else if(triangleContainPoint(m_O.x,m_O.y,m_O.x-r,m_O.y+r,m_O.x-r,m_O.y-r,location.x,location.y)  
			||Rect(m_O.x-r-d,m_O.y-r,d,d).containsPoint(location)){  
				m_nX=-1;  
				m_nY=0;  
		}  
		//�ң�����9��8  
		else if(triangleContainPoint(m_O.x,m_O.y,m_O.x+r,m_O.y+r,m_O.x+r,m_O.y-r,location.x,location.y)  
			||Rect(m_O.x+r,m_O.y-r,d,d).containsPoint(location)){  
				m_nX=1;  
				m_nY=0;  
		}  
		//���ϣ�����3  
		else if(location.x-(m_O.x+r)>0&&location.y-(m_O.y+r)>0){  
			m_nX=1;  
			m_nY=-1;  
		}  
		//���ϣ�����1  
		else if(location.x-(m_O.x-r)<0&&location.y-(m_O.y+r)>0){  
			m_nX=-1;  
			m_nY=-1;  
		}  
		//���£�����10  
		else if(location.x-(m_O.x-r)<0&&location.y-(m_O.y-r)<0){  
			m_nX=-1;  
			m_nY=1;  
		}  
		//���£�����12  
		else if(location.x-(m_O.x+r)>0&&location.y-(m_O.y-r)<0){  
			m_nX=1; 
			m_nY=1;  
		}  
	}  
}

void CJoyStick::onTouchesEnded(Touch *touch, Event *unused_event)
{
	m_IsMove=false;  
	m_joystick->setPosition(m_O);
	m_nX = m_nY = 0;
 
}

//������������ĺ���  
float CJoyStick::heronsformula(float x1,float y1,float x2,float y2,float x3,float y3)
{
	//��߳�a  
	float a=sqrt(pow(x1-x2,2)+pow(y1-y2,2));  
	//��߳�b  
	float b=sqrt(pow(x2-x3,2)+pow(y2-y3,2));  
	//��߳�c  
	float c=sqrt(pow(x3-x1,2)+pow(y3-y1,2));  
	//����ܳ�s  
	float s=(a+b+c)/2;  

	//���ݺ��׹�ʽ�������������  
	return sqrt(s*(s-a)*(s-b)*(s-c));  

}

//�ж�������������������Ƿ����ԭ������������ĺ���  
bool CJoyStick::triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py)
{
	//��S1�����  
	float s1=heronsformula(x1,y1,x2,y2,px,py);  
	//��S2�����  
	float s2=heronsformula(x2,y2,x3,y3,px,py);  
	//��S3�����  
	float s3=heronsformula(x3,y3,x1,y1,px,py);  
	//��S�����  
	float s=heronsformula(x1,y1,x2,y2,x3,y3);  

	//����S�Ƿ����S1,S2,S3�ĺ�  
	return abs(s-(s1+s2+s3))<0.001f;  

}