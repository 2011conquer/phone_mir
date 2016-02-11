#ifndef ROLESTATEDIALOG_H_
#define ROLESTATEDIALOG_H_
#include "BaseDialog.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
//��ɫ״̬�Ի���
namespace VD_UI
{
	

	class CRoleStateDialog : public CBaseDialog
	{
	public:
		CRoleStateDialog(void);
		~CRoleStateDialog(void);
		void Show(cocos2d::Layer* layer /* = nullptr */);
		void Hide();
		void Render();
	private:
		cocos2d::Layer* m_Layer;
		cocos2d::Label* m_LabelUserName;

		////ְҵ
		cocos2d::Label* m_LabelJobTips;
		cocos2d::Label* m_LabelJob;
		//�Ա�
		cocos2d::Label* m_LabelSexTips;
		cocos2d::Label* m_LabelSex;
		//�ȼ�
		cocos2d::Label* m_LabelLvTips;
		cocos2d::Label* m_LabelLv;
		//����
		cocos2d::Label* m_LabelLifeTips;
		cocos2d::Label* m_LabelLife;
		//ħ��
		cocos2d::Label* m_LabelMageTips;
		cocos2d::Label* m_LabelMage;
		//�������
		cocos2d::Label* m_LabelAcTips;
		cocos2d::Label* m_LabelAc;
		//ħ������
		cocos2d::Label* m_LabelMacTips;
		cocos2d::Label* m_LabelMac;
		//������
		cocos2d::Label* m_LabelDcTips;
		cocos2d::Label* m_LabelDc;
		//ħ������
		cocos2d::Label* m_LabelMcTips;
		cocos2d::Label* m_LabelMc;
		//��������
		cocos2d::Label* m_LabelScTips;
		cocos2d::Label* m_LabelSc;
		//׼ȷ
		cocos2d::Label* m_LabelHitTips;
		cocos2d::Label* m_LabelHit;
		//����
		cocos2d::Label* m_LabelSpeedTips;
		cocos2d::Label* m_LabelSpeed;
		//PKֵ
		cocos2d::Label* m_LabelPKTips;
		cocos2d::Label* m_LabelPK;
		//����
		cocos2d::Label* m_LabelProtectTips;
		cocos2d::Label* m_LabelProtect;
		//�ػ�
		cocos2d::Label* m_LabelCritTips;
		cocos2d::Label* m_LabelCrit;
		//�رհ�ť
		ui::Button* m_BtnClose;

		void btn_Close_click(Ref* pSender,ui::Widget::TouchEventType type);
		
	};
}


#endif