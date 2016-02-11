#include "PathHelper.h"
#include "MShare.h"
#include <map>
#include "MapUnit.h"
std::vector<TMapGateInfo*> g_MapGateRoadList;	//Ѱ··����ͼ
std::vector<TFindNode*> g_RoadList;
std::vector<unsigned long> g_passPoint;
std::vector<TTree*> g_FreeTreeList;
int g_nEcount;
int g_nGcount ;
//std::vector<TFindNode*> GuajiRoadList;
TLink* Queue,*GuajiQueue;// ����û�д�������߷����Ľڵ�
void FindMapPath(std::string sMap,std::string sDescMap)
{
	g_MapGateRoadList.clear();
	if(sMap == sDescMap) return;
	std::vector<TLocalMapInfo*> FindMapList;
	std::vector<TLocalMapInfo*> tmplist;
	TMapGateInfo* dgate;
	TLocalMapInfo* mapinfo = nullptr;
	TMapGateInfo* tmpgate;
	int findcount;
	FindMapList.clear();
	tmplist.clear();
	std::map<std::string,TLocalMapInfo*>::iterator it;
	it = g_alllocalmap.find(sMap);
	if(it == g_alllocalmap.end())
	{
		return;
	}
	mapinfo = it->second;
	FindMapList.push_back(mapinfo);
	 //��ʼ��ͼ�����������ͼ�б�
	dgate = nullptr;
	findcount = 0;
	while(true)
	{
		findcount ++;
		if( findcount > 1000)break;    //1000�㶼�Ҳ�������ȥ
		if(FindMapList.size() == 0)break;  //�б����껹û�ҵ�
		mapinfo = FindMapList[0];
		tmplist.push_back(mapinfo);
		///ѭ����ǰ������ͼ���������㣬���Ƿ�������Ŀ���ͼ
		///���������Ŀ���ͼ�����������Ӧ��Ŀ���ͼ�������
		///��������������ͼ�б�
		for(int i = 0;i < (int)mapinfo->Gates.size();i++)
		{
			tmpgate = (TMapGateInfo*)mapinfo->Gates[i];
			if(!tmpgate->DMapInfo)continue;
			bool bFind = false;
			for(int j = 0;j < (int)tmplist.size();j++)
			{
				if(tmplist[j] == tmpgate->DMapInfo)
				{
					bFind = true;
					break;
				}
			}
			if(bFind)continue;
			if(tmpgate->DMapName == sDescMap)
			{
				dgate = tmpgate;
				break;
			}else
			{
				//��Ŀ���ͼ�ϵ������������Դ������Ϊ��ǰ����
				for(int k = 0;k < (int)tmpgate->DMapInfo->Gates.size();k++)
				{
					((TMapGateInfo*)tmpgate->DMapInfo->Gates[k])->fromGate = tmpgate;
				}
				FindMapList.push_back(tmpgate->DMapInfo);;
			}
			tmplist.push_back(tmpgate->DMapInfo);
		}
		FindMapList.erase(FindMapList.begin());
		if(dgate != nullptr) break;
	}
	
	while(true)
	{
		if(dgate == nullptr)break;
		g_MapGateRoadList.insert(g_MapGateRoadList.begin(), dgate);
		if(dgate->SMapName == sMap)break;
		if(dgate->fromGate == nullptr) break;
		dgate = dgate->fromGate;
	}
	FindMapList.clear();
	tmplist.clear();
	
}

void FindPath(int Startx,int Starty,int end_x,int end_y)
{
	TTree* root,*p;
	int x,y,dir;

	TFindNode* temp;
	bool bTry;
	int ii;

	g_nEcount = 0; g_nGcount = 0;
	if(! VDMap::GetInstance()->CanMove(end_x,end_y))
	{
		return;
	}
	g_passPoint.resize(VDMap::GetInstance()->Header.Height * VDMap::GetInstance()->Header.Width);
	for(int i =0;i < (int)g_passPoint.size();i++)
	{
			g_passPoint[i] = 0xFFFFFFFF;
	}
	Init_Queue();
	root = new TTree();
	root->x = Startx;
	root->y = Starty;
	root->h = 0;
	root->Father = nullptr;
	Enter_Queue(root,judge(Startx,Starty,end_x,end_y));
	g_FreeTreeList.push_back(root);
	ii = 0;
	int index = 0;
	while(true)
	{
		root = Get_From_Queue(); //����һ������
		ii++;
		if(ii == 86610)ii = 0;
		if(root == nullptr) break;

	/*	FILE* f_ = fopen("c:/1.txt","a");
		char sLog[1024];
		sprintf(sLog,"index: %d x: %d y: %d h: %d \n",index,root->x,root->y,root->h);
		fputs(sLog,f_);
		sprintf(sLog,"---------------------------------------------------------------\n");
		fputs(sLog,f_);
		fputs(sLog,f_);
		fclose(f_);*/

		index++;

		x = root->x;
		y = root->y;
		if(x == end_x && y == end_y)
		{
			break;
		}
		bTry =false;
		if (Trytile(x, y - 1, end_x, end_y, root, 0)) bTry = true; //���������ƶ�
		if (Trytile(x + 1, y - 1, end_x, end_y, root, 1)) bTry = true; //�����������ƶ�
		if (Trytile(x + 1, y, end_x, end_y, root, 2)) bTry = true; //���������ƶ�
		if (Trytile(x + 1, y + 1, end_x, end_y, root, 3)) bTry = true; //�����������ƶ�
		if (Trytile(x, y + 1, end_x, end_y, root, 4) ) bTry = true; //���������ƶ�
		if (Trytile(x - 1, y + 1, end_x, end_y, root, 5)) bTry = true; //�����������ƶ�
		if (Trytile(x - 1, y, end_x, end_y, root, 6)) bTry = true; //���������ƶ�
		if (Trytile(x - 1, y - 1, end_x, end_y, root, 7)) bTry = true; //�����������ƶ�
	}

	if(root == nullptr) return;
	g_RoadList.clear();
	temp = new TFindNode();
	temp->x = root->x;
	temp->y = root->y;
	g_RoadList.push_back(temp);
	p = root;
	dir = -1;
	root = root->Father;
	while(root != nullptr)
	{
		if(p->dir != dir || root->dir != dir)
		{
			temp = new TFindNode();
			temp->x = p->x;
			temp->y = p->y;
			g_RoadList.insert(g_RoadList.begin(),temp);
			dir = p->dir;
		}
		p = root;
		root = root->Father;
	}
	FreeTree();
}
void Init_Queue()
{
	if(Queue)
	{
		if(Queue->next)
		{
			delete Queue->next;
		}
		if(Queue->node)delete Queue->node;
		delete Queue;
	}
	Queue = new TLink;
	Queue->node = nullptr;
	Queue->f = -1;
	Queue->next=new TLink;
	Queue->next->f = 0xfffffff;
	Queue->next->node = nullptr;
	Queue->next->next = nullptr;
	for(int i = 0;i < (int)g_RoadList.size();i++)
	{
		TFindNode* n = g_RoadList[i];
		delete n;
	}
	g_RoadList.clear();
}

// ������ڵ������, ������Ŀ�ĵع��۾����������
void Enter_Queue(TTree* node,int f)
{

	TLink *p = nullptr,*Father = nullptr,*q = nullptr;
	p = Queue;
	Father = p;
	while (f > p->f)
	{
		Father = p;
		p = p->next;
		if(p == nullptr)
		{
			break;
		}
	}
	q = new TLink;
	q->f = f;
	q->node = node;
	q->next = p;
	Father->next =q;

	//FILE* f_ = fopen("c:/1.txt","a");
	//char sLog[1024];
	//sprintf(sLog,"x: %d y: %d h: %d \n",node->x,node->y,node->h);
	//fputs(sLog,f_);
	//fclose(f_);
}

TTree* Get_From_Queue()
{
	TTree* bestchoice;
	TLink* Next;
	bestchoice =Queue->next->node;
	Next = Queue->next->next;
	delete Queue->next;
	Queue->next = Next;
	return bestchoice;
}
// ������һ���ƶ��� x,y ���з�
bool Trytile(int x,int y,int end_x,int end_y,TTree* father,unsigned char dir)
{
	TTree* p;
	unsigned long h;
	bool Result  = false;
	if(!VDMap::GetInstance()->CanMove(x,y))
	{
		return Result;
	}
	p = father;
	while(p != nullptr)
	{
		if(x == p->x && y == p->y)
		{
			return false;
		}
		p = p->Father;
	}
	if(dir == 0 || dir == 2 || dir == 4 || dir == 6)
	{
		h = father->h + 10;
	}else
	{
		h = father->h + 14;
	}
	if(h >= (unsigned long)g_passPoint[x * VDMap::GetInstance()->Header.Height + y])
	{
		return false; //// ��������и��õķ����ƶ��� (x,y) ʧ��
	}
	g_passPoint[x * VDMap::GetInstance()->Header.Height + y] = h; // ��¼��ε� (x,y) �ľ���Ϊ��ʷ��Ѿ���
	g_nEcount ++;
	p = new TTree;
	p->Father = father;
	p->h = h;
	p->x = x;
	p->y = y;
	p->dir = dir;
	Enter_Queue(p,p->h + judge(x,y,end_x,end_y));
	g_FreeTreeList.push_back(p);
	return true;
}

// ���ۺ���,���� x,y ��Ŀ�ĵصľ���,����ֵ���뱣֤��ʵ��ֵС		
int judge(int x,int y,int end_x,int end_y)
{
	int nx = end_x - x;
	int ny = end_y - y;
	return abs(nx) + abs(ny);
}
// �ͷ�����������нڵ�
void FreeTree()
{
	TLink* p;
	while(Queue != nullptr)
	{
		p = Queue;
		Queue = Queue->next;
		delete p;
	}
	for(int i = 0;i < (int)g_FreeTreeList.size();i++)
	{
		TTree* t = g_FreeTreeList[i];
		delete t;
	}
	g_FreeTreeList.clear();
}