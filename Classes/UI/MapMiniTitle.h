#ifndef MAPMINITITLE_H_
#define MAPMINITITLE_H_
//�����ͼ�򣬻��Ƶ�ͼ����������
#include "BaseDialog.h"
#include "cocos2d.h"
namespace VD_UI
{
	class CMapMiniTitle : public CBaseDialog
	{
	public:
		CMapMiniTitle(void);
		~CMapMiniTitle(void);
		void Show(cocos2d::Layer* layer /* = nullptr */);
		void Hide();
		void Render();
		void MouseDown(cocos2d::Vec2 pos);
	private:
		cocos2d::Layer* m_Layer;
		cocos2d::Label* m_LabelName; //��ͼ���Ʊ�ǩ
		cocos2d::Label* m_LabelPoint; //��ͼ����
	};
}

#endif
