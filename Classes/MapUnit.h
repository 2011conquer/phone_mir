#ifndef MAPUNIT_H_
#define MAPUNIT_H_

#include <string>
#include <map>
#include <vector>
#include <stdio.h>

#include "cocos2d.h"
#include "GameStruct.h"




class TMapMaskInfo
{
public:
	TMapMaskInfo(void);
	~TMapMaskInfo(void);
	
public:
	TRect_ MaskRect;
	std::vector<TPoint> Points;
	bool InClientRect(TRect_ clientrect);
	void LoadPointsFromStream(const unsigned char* pData,int nCount);
	
};
class VDMap
{
public:
	VDMap(void);
	virtual ~VDMap(void);
	
	static VDMap* GetInstance();
public:
	TMapHeader Header ;
	std::string m_sMapBase;
	std::vector<std::vector<TMapInfo> > m_MArr;
	//TMapInfo** m_MArr;
	std::vector<TMapMaskInfo> m_MaskList;

	bool m_boChange;
	int m_ShiftX;        //��ͼƫ�ƣ���Ҫ��Ա�Ե����
	int m_ShiftY;
	TRect_ m_ClientRect;
	TRect_ m_OldClientRect;
	
	int m_nBlockLeft;
	int m_nBlockTop;
	int m_nOldLeft;
	int m_nOldTop;
	std::string m_sMapName; //��ͼ���� ���ǵ�ͼ�����ǵ�ͼ����
	std::string m_sOldMap;   //��ͼ�ļ�������ͼ�ļ������ܶ����ͼ����һ���ļ�
	int m_nCurUnitX;
	int m_nCurUnitY;
	std::string m_sCurrentMap;
	bool m_boSegmented;
	int m_nSegXCount;
	int m_nSegYCount;
	bool m_Loaded;

public:
	bool LoadMapAllArr();
	void ClearMasks();
	void ClearMap();
	void ChangeMap(const char* MpaStr);
	bool CanMove(int mx,int my);
};

#endif