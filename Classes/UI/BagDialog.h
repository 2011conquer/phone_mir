#ifndef BAGDIALOG_H_
#define BAGDIALOG_H_
//������� 2015.7.18
#include "BaseDialog.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
namespace VD_UI
{
	class CBagDialog : public CBaseDialog
	{
	public:
		CBagDialog(void);
		~CBagDialog(void);
		void Show(cocos2d::Layer* layer /* = nullptr */);
		void Hide();
		void Render();
		void MouseDown(cocos2d::Vec2 pos);
	private:
		cocos2d::Layer* m_Layer;
		cocos2d::Label* m_LabelGold; //���
		cocos2d::Label* m_LabelBindGold; //�󶨽��
		cocos2d::Label* m_LabelGameGold;//Ԫ��

		cocos2d::ui::Button* m_BtnClose;//�رհ�ť
		void btn_Close_click(Ref* pSender,ui::Widget::TouchEventType type);
	};

}

#endif