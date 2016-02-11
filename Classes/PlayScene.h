#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_
#include "cocos2d.h"
#include <vector>
#include "GameStruct.h"
#include "VD_Share.h"
class TActor;
class TMagicEff;
//��ͼ�ɰ�--

class TPlayScene
{
public:
	TPlayScene(void);
	 ~TPlayScene(void);
	 static TPlayScene* GetInstance();
	 void PlayScene(); //���Ƶ�ש ����- ����������Ϣ
	 void DrawScreen(); //�������� ����֮���
	 void DrawTileMap();
	 //void DrawMapMask(cocos2d::GLProgram* gl);//���Ƶ�ͼ�����ɰ���Ϣ
	  bool IsMapMask(TActor* actor);
	 void ProcessNetEvent();
	 TActor* GetAttackFocusCharacter(int X,int Y,int wantsel,int &nowsel,bool liveonly);
	 TActor* GetCharacter(int X,int Y,int wantsel, int &nowsel,bool liveonly);
	 void SendMsg(int ident,int chrid,int x,int y,int cdir,int Feature,
		 int State,const char* str,int Fetureex = 0);
private:
	int m_nDefXX;
	int m_nDefYY;
private:
	cocos2d::Layer* m_LayerTitle;
	cocos2d::Layer* m_LayerActor; //npc ���ﳡ��
	cocos2d::Layer* m_LayerUI; //UI����
	int m_nLastTime;
public:
	cocos2d::Layer* GetTitleLayer(){return m_LayerTitle;} //ȡ��ש��_
	cocos2d::Layer* GetActorLayer(){return m_LayerActor;} //ȡ��ɫ��
	cocos2d::Layer* GetUILayer(){return m_LayerUI;} //ȡUI��
	void CXYfromMouseXY(int x,int y,int &ccx,int &ccy);
	TActor* NewActor(int chrid,unsigned short cx,unsigned short cy,unsigned short cdir,
		int cfeature,int cstate, int featureEx = 0);

	void NewMagic(TActor* aowner,int magid,int magnumb,int cx,int cy,int tx,int ty,int targetcode
		,TMagicType mtype,bool Recusion,int anitime,bool &bofly);
	TActor* FindActor(int id);
	TActor* FindNPC(std::string sName); //����npc���������ֲ���
	void DelActor(TActor* actor);

	bool IsChangingFace(int recogid);

	bool CanWalk(int mx,int my);
	bool CanWalkEx(int mx,int my);
	bool CanRun(int sx,int sy,int ex,int ey);
	bool CrashManEx(int mx,int my);
	bool CrashMan(int mx,int my);
	void ActorDied(TActor* Actor);

	void DrawFontEx(std::string str,int nx,int ny,unsigned long color = 0xFFFFFFFF,
		bool HaveStroke = false,int StrokeColor = 0xFF000000);
	cocos2d::Label* DrawFontEx(cocos2d::Layer* layer,std::string str,int nx,int ny,
		unsigned long Color = 0xFFFFFFFF,bool HaveStroke = false,unsigned long StrokeColor = 0xFF000000,
		bool underline = false,bool HaveBackGround= false, unsigned long BackGroundColor = 0xFF000000);
	int FindTargetXYCount(int nX,int nY,int nRange);
	TActor* FindActorXY(int nX,int nY);
	void ScreenXYfromMCXY(int cx,int cy,int &sx,int &sy);//��ͼ����ת��Ϊ�������
	bool IsValidActor(TActor* actor);//��������Ƿ���Ч
	void CleanObjects();
	
private:
	void ClearMapImage(); //��������ͼ����
	void ClearHumImage(); //�������NPC��Ӣ�۾���
	void ClearMonsterImage();//���������ﾫ��
	void ClearMemoryObject();
	void ClearUIImage(); //�������UI����
	void DrawImgMsg();
	//cocos2d::Color4B HexColorToColor4B(unsigned long color); //ʮ������ת��rgba��ɫֵ
	std::vector<cocos2d::Label*> m_LabelList; //��ǩ
private:
	

	int m_dwMoveTime;
	int m_dwAniTime;
	int m_nMoveStepCount;
	int m_nAniCount;

	int m_dwFrameTime;
	int m_dwFrameCount;
	int m_dwDrawFrameCount;

	//��ʾ�м��ͼƬ����..ʲô�������ʲô��- 2015.8.8
	int m_ShowImgMsgIdx;
	unsigned long m_ShowImgMsgTick;
	int m_ShowImgMsgTop;
public:
	std::vector<TActor*> m_ActorList;
	std::vector<TMagicEff*>m_EffectList;

public:
	//UI����
	void Show_Dialog(DIALOG_TYPE type); //��ʾ���
	void Hide_Dialog(DIALOG_TYPE type); //�������

	

};

#endif