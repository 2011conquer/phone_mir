//���ػ������ݿ�-
#ifndef BASECONFIG_H_
#define BASECONFIG_H_
#include "GameStruct.h"
#include <vector>
#include <map>
class CBaseConfig
{
public:
	CBaseConfig(void);
	~CBaseConfig(void);
	static CBaseConfig* GetInstance();

	bool LoadConfig();
	bool LoadClientStdItemsData(); //���ػ�����Ʒ���ݿ�
	bool LoadClientAdditionItemsData(); //������Ʒ�������ݿ�,������ʱֻ��Ʒ��
private:

};

#endif

