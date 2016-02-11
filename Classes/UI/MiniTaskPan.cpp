#include "MiniTaskPan.h"
#include "../VDImage.h"
#include "../MShare.h"
#include "../PlayScene.h"
#include "../Common/SoundUtil.h"
#include "../FrmMain.h"
#include "../Net/NetClient.h"
#include "../Net/NetSendMsg.h"
namespace VD_UI
{

	CMiniTaskPan::CMiniTaskPan(void)
	{
		m_Layer = nullptr;
		LastestClickTime = GetTickCount();
	}


	CMiniTaskPan::~CMiniTaskPan(void)
	{
	}

	void CMiniTaskPan::Show(cocos2d::Layer* layer )
	{
		if(m_Layer)Hide();
		CBaseDialog::Show(layer);
		m_Layer = cocos2d::Layer::create();
		m_Layer->retain();
		layer->addChild(m_Layer);


	}

	void CMiniTaskPan::Hide()
	{
		if(!m_Layer)return;
		m_Layer->removeAllChildrenWithCleanup(true);
		m_Layer->release();
		m_Layer = nullptr;
		CBaseDialog::Hide();
	}


	void CMiniTaskPan::MouseDown(cocos2d::Vec2 pos)
	{

	}
	bool CMiniTaskPan::DMiniTaskPanelClickFun(cocos2d::Vec2 pos)
	{
		if(GetTickCount() < LastestClickTime)return false;
		//�����ű����ȵ�����
		SelectMenuStr = "";
		TClickPoint* p;
		bool bType;
		int L = m_Size.Left;
		int T = m_Size.Top;
		int x = pos.x; int y = pos.y;
		int id = 0;
		for(int i = 0;i < (int)MDlgPoints.size();i++)
		{
			p = MDlgPoints[i];
			if(p->nType == 0 || p->nType == 2)
			{
				bType = true;
				if(x >= L + p->rc.Left && x <= L + p->rc.Right
					&& y >= T + p->rc.Top && y < T + p->rc.Bottom)
				{
					SelectMenuStr = p->rstr;
					id = p->id;
					break;
				}
			}
		}
		if(SelectMenuStr.length() > 0)
		{
			PlaySound_(s_glass_button_click);
			FrmMain::GetInstance()->StopAutoRun();
			if((int)SelectMenuStr.find("local:") >= 0)
			{
				FrmMain::GetInstance()->DoLocalTaskCMD(id,SelectMenuStr);
			}else
			{
				VD_Net::CNetClient::GetInstance()->GetSendMsg()->SendTaskSelect(id,SelectMenuStr);
			}
			return true;
		}
		return false;
	}
	void CMiniTaskPan::Render()
	{
	//	TVDImage* img = GetUIImage(520);
	}
	void CMiniTaskPan::ProcessTask()
	{
		
		m_ListImg.clear();
		m_Layer->removeAllChildrenWithCleanup(true);
		DestoryClickPoint();//֮ǰ���ȵ����� ���
		TVDImage* img = GetUIImage(520);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left,m_Size.Top));
		}
		int Linewidth = m_Size.Right;
		int lx = 0,ly = 25;
		int sx = 0,sy = 0,nx = 0,ny = 0,n = 0;
		TClientTaskItem* clientitem;
		int line = 0,len = 0,i = 0,nadd = 0,nID = 0;
		std::string str,data,fdata,cmdstr,str1,sChar,str2,cmdparam;
		RequireAddPoints=  true;
		unsigned long UseColor = 0xffffffff;
		std::vector<std::string> TempList1;
		int Left = m_Size.Left;
		int Top = m_Size.Top;
		TVDImage* cmdimg;
		bool drawCenter;
		TempList1.clear();
		TClickPoint* pcp;
		int nWidth = 0,nHeight = 0;
		for(int ti = 0;ti < (int)g_TaskList.size();ti++)
		{
			sx = 0;
			clientitem = g_TaskList[ti];
			str  =clientitem->ShortDesc;
			while(true)
			{
				if(str.length() <= 0)break;
				str = GetValidStr3Ex(str,data,'\\');
				if(data.length() <= 0)data = " ";
				TempList1.push_back(data);
			}
			//��νű������Ǵ� npcDialog.cpp ֱ�Ӹ���ճ��������- -��- 2015.8.8
			for(int j = 0;j < (int)TempList1.size();j++)
			{
				
				data = TempList1[j];
				//�滻�»���Ϊ�ո�
				StringReplace(data,"_"," ");
				if(data.length() > 0)
				{
					sx = 0;
					fdata = "";
					while(true)
					{
						if(data.length() <= 0)break;
						if(((int)data.find("<") < 0 && (int)data.find(">") < 0) &&
							((int)data.find("{") < 0 && (int)data.find("}") < 0))
						{
							break;
						}
						{
							int n1 = data.find("<");
							int n2 =data.find("{");
							fdata = "";
							cmdstr = "";
							///�����Ŵ��� �м����Ŵ��ڣ������ڴ�����ǰ
							///fdata�Ǽ�����ǰ�Ĳ��֣������
							///cmdstr�Ǽ�����������
							///dataʣ�µ������ź���Ĳ�����
							if(n1 >= 0 && (n1 < n2 || n2 == -1))
							{
								if(data[0] != '<')
								{
									data = "<" + GetValidStr3Ex(data,fdata,'<');
								}
								data = ArrestStringEx(data, "<", ">", cmdstr);
							}
							//����ǰ���ֻ���
							if(fdata.length() > 0)
							{
								if(lx + sx + TextWidth(fdata)> Linewidth)
								{
									str1 = fdata;
									len = 0;
									i = 0;
									while(true)
									{
										sChar =  str1[i];
										nadd = 1;
										if(sChar[0] >= 0 && sChar[0] <= 127)nadd = 0;
										i += nadd;
										len += TextWidth(sChar);
										if(lx + sx + len > Linewidth)
										{
											nadd = 1;
											if(sChar[0] >= 0 && sChar[0] <= 127)nadd = 0;
											i += nadd;
											fdata = str1.substr(0,i);//дǰ����
											str1 = str1.substr(i,str1.length() - i); //���󲿷ּ����Ƚ�
											//ǰ���
											TPlayScene::GetInstance()->DrawFontEx(m_Layer,fdata,Left + lx + sx,Top + ly,UseColor,true);
											ly = ly + 18;
											sx = 0;
											len = 0;
											//���������������ֱ����һ�л���
											if(TextWidth(str1) <= Linewidth)
											{
												TPlayScene::GetInstance()->DrawFontEx(m_Layer,str1,Left + lx + sx,Top + ly,UseColor,true);
												sx += TextWidth(str1);
												break;
											}
											i = 0;
										}else
										{
											i++;
										}
									}
								}else
								{
									TPlayScene::GetInstance()->DrawFontEx(m_Layer,fdata,Left + lx + sx,Top + ly,UseColor,true);
									sx += TextWidth(fdata);
								}
							}
							////�����Ŵ���
							if(n2 >= 0  && (n2 < n1 || n1 == -1))
							{
								fdata = "";
								if(data[0] != '{')
								{
									data = GetValidStr3Ex(data,fdata,'{');//���data= FCOLOR=XX}��������
								}else
								{
									data = data.substr(1,data.length() - 1);
								}
								if(fdata.length() > 0)
								{
									if(lx + sx + TextWidth(fdata) > Linewidth)//������
									{
										str1 = fdata;
										len = 0;
										i = 0;
										while(true)
										{
										
											sChar  = str1[i];
											nadd = 1;
											if(sChar[0] >= 0 && sChar[0] <= 127)nadd = 0;
											i += nadd;
											len += TextWidth(sChar);
											if(lx + sx + len > Linewidth)
											{
												//˫�ֽڵ��ֽ��ж�
												nadd = 1;
												if(sChar[0] >= 0 && sChar[0] <= 127)nadd = 0;
												i += nadd;
												fdata = str1.substr(0,i);//дǰ����
												str1 = str1.substr(i,str1.length()); //���󲿷ּ����Ƚ�
												str2 = fdata;
												TPlayScene::GetInstance()->DrawFontEx(m_Layer,str2,Left + lx + sx,Top + ly,UseColor,true);
											
												ly = ly + 18;
												sx = 0;
												len = 0;
												if(TextWidth(str1) <= Linewidth)
												{
													str2 = str1;
													TPlayScene::GetInstance()->DrawFontEx(m_Layer,str2,Left + lx + sx,Top + ly,UseColor,true);	
													sx += TextWidth(str1);
													break;
												}
												i = 0;
											}else
											{
												i++;
											}
										}
									}else
									{
										TPlayScene::GetInstance()->DrawFontEx(m_Layer,fdata,Left + lx + sx,Top + ly,UseColor,true);
									
										sx += TextWidth(fdata);
									}
								}
								//��������������ַ���
							
								std::string sColor;
								if(data.find("}")>= 0)
								{
									data = GetValidStr3Ex(data, cmdparam, '}');
									if(cmdparam.find("FCOLOR=") == 0)
									{
										sColor = cmdparam.substr(7,cmdparam.length() - 7);
										UseColor = GetRGB(atoi(sColor.c_str()));
									}else if(cmdparam == "-")
									{
										if(sx > lx) //���ǰ���Ѿ���һЩ�����ˣ���һ�л�����
										{ 
											ly = ly + 18;
											sx = 0;
											len = 0;
										}
										//������
										cmdimg = GetUIImage(32);
										if(cmdimg && cmdimg->Image_)
										{
											nx = Left + lx + sx + (Linewidth - lx - cmdimg->pWidth) / 2;
											ny = Top + ly + (18 - cmdimg->pHeight ) / 2;
											m_Layer->addChild(cmdimg->GetImage(nx,ny));
											m_ListImg.push_back(cmdimg);
										}
										//������
										ly = ly + 18;
										sx = 0;
										len = 0;
									}else if(cmdparam.find("item=") == 0)//��Ʒͼ��
									{
										sColor = cmdparam.substr(5,cmdparam.length() - 5);
										n = atoi(sColor.c_str());
										cmdimg = GetBagImage(n);
										if(cmdimg && cmdimg->Image_)
										{
											// //��Ʒͼ�걳��
											////ͼ��
											nx = Left + lx + sx;
											ny = Top + ly + (12 - cmdimg->pHeight );
											m_Layer->addChild(cmdimg->GetImage(nx,ny));
											sx = sx + cmdimg->pWidth;
											m_ListImg.push_back(cmdimg);
										}

									}else if(cmdparam.find("i=") == 0) //������Ʒͼ�꣬��������ƶ�����Ʒtips��Ϣ
									{
										sColor = cmdparam.substr(2,cmdparam.length() - 2);
										n = atoi(sColor.c_str());
										TStdItem* stditem = GetStdItemInfo(n);
										if(stditem)
										{
											cmdimg = GetBagImage(stditem->Looks);
											if(cmdimg && cmdimg->Image_)
											{
												//��Ʒͼ�걳��
												////ͼ��
												nx = Left + lx + sx;
												ny = Top + ly + (12 - cmdimg->pHeight );
												m_Layer->addChild(cmdimg->GetImage(nx,ny));
												sx = sx + cmdimg->pWidth;
												m_ListImg.push_back(cmdimg);
											}
										}
									}else if(cmdparam.find("img:") == 0)////�����Զ���ͼƬ����  2013.5.24
									{
										std::string sImgID;
										std::string sStr;
										sStr = GetValidStr3Ex(cmdparam,sImgID,',');
										int nImgX; int nImgY;
										int nLen = sImgID.length();
										std::string s = sImgID.substr(sImgID.length() - 4,sImgID.length());
										int nImgID = atoi(s.c_str());
										sStr = GetValidStr3Ex(sStr,sImgID,',');
										nImgX = atoi(sImgID.c_str());
										nImgY = atoi(sStr.c_str());
										img = GetUIImage(nImgID);
										if(img && img->Image_)
										{
											m_Layer->addChild(img->GetImage(Left + nImgX,Top + nImgY));
											m_ListImg.push_back(img);
										}

									}
									cmdparam = "";
								}

							}
							if(cmdstr.length() > 0)
							{
								if(StringUpper(cmdstr.c_str()) == "C")
								{
									drawCenter = true;
									continue;
								}
								if(StringUpper(cmdstr.c_str()) == "/C")
								{
									drawCenter = false;
									continue;;
								}
								cmdparam = GetValidStr3Ex(cmdstr, cmdstr, '/');
							}

							//�������ֻ���
							if(cmdstr.length() > 0)
							{
								//��������ȵ�����
								if(RequireAddPoints && cmdparam.length() > 0)
								{
										pcp = new TClickPoint;
										pcp->rc.Rect(lx + sx, ly, lx + sx + TextWidth(cmdstr), ly + 14);
										pcp->rstr = cmdparam;
										pcp->nType = 0;
										pcp->id = clientitem->item.TaskID;
										MDlgPoints.push_back(pcp);
								}
								if(SelectMenuStr == cmdparam) //ѡ�е��ȵ������ǩ //2006-10-24 Mars���Ӳ�ɫNPC����
								{
									if(cmdparam.length() > 0 && cmdparam[0] == '@')
									{
										if(cmdstr[0] == ':')
										{
											if(((int)cmdstr.find("|")) > 0)
											{
												TPlayScene::GetInstance()->DrawFontEx(m_Layer,cmdstr,Left + lx + sx,Top + ly,GetRGB(249),true,
													0xFF000000,true);
											
											}
										}else   //ͼƬ�ȵ�����
										{
											nID = atoi(cmdstr.substr(cmdstr.length() - 4,cmdstr.length()).c_str());
											img = GetUIImage(nID);
											if(img && img->Image_)
											{
												m_Layer->addChild(img->GetImage(Left + lx + sx,Top + ly - img->TexHeight / 2));
												m_ListImg.push_back(img);
											}
											sx += sx + TextWidth(cmdstr);
										}
									}else
									{
										TPlayScene::GetInstance()->DrawFontEx(m_Layer,cmdstr,Left + lx + sx,Top + ly,UseColor,true);
										sx += TextWidth(cmdstr);
									}
								}else
								{
									if(cmdparam.length() > 0 && cmdparam[0] == '@')
									{
										 //�ȵ������ͼƬ�����ֵĿ��----
										if(cmdstr[0] != ':')
										{
											nWidth = TextWidth(cmdstr);
											nHeight = 0;
										}else
										{
											nID = atoi(cmdstr.substr(cmdstr.length() - 4,cmdstr.length()).c_str());
											img = GetUIImage(nID);
											if(img && img->Image_)
											{
												nWidth  = img->TexWidth;
												nHeight =img->TexHeight;
											}
										}

										//��ֹ�����ֺ�ͼƬ
										int nPoint = (int)cmdstr.find(":");
										if(nPoint == -1)
										{
											TPlayScene::GetInstance()->DrawFontEx(m_Layer,cmdstr,Left + lx +sx,Top + ly,GetRGB(250),true,0xFF000000,true);
										}else
										{
											nID = atoi(cmdstr.substr(cmdstr.length() - 4,cmdstr.length()).c_str());
											img = GetUIImage(nID);
											if(img && img->Image_)
											{
												m_Layer->addChild(img->GetImage(Left + lx +sx,Top + ly - img->TexHeight / 2));
												m_ListImg.push_back(img);
											}
										}
										sx += TextWidth(cmdstr);
									}else
									{
										//����ƶ���ȥ��tips�� ����ľ��~~
										TPlayScene::GetInstance()->DrawFontEx(m_Layer,cmdstr,Left + lx + sx,Top + ly,UseColor);
										sx += TextWidth(cmdstr);
									}
								}
							}

						}//else break;;

					}

					// //358:NPC�Ի�����ʾ�Ŀ��
					if(data.length() > 0)
					{
						if(lx + sx + TextWidth(data) > Linewidth)//������
						{
							str1 = data;
							len = 0;
							i = 0;
						
							while(true)
							{
								sChar = str1[i];
								//˫�ֽڵ��ֽ��ж�
								nadd = 1;
								if(sChar[0] >= 0 && sChar[0] <= 127)nadd = 0;
								i += nadd;
								nWidth = TextWidth(sChar);
							
								len += nWidth;
								if(lx + sx + len > Linewidth)
								{
									//˫�ֽڵ��ֽ��ж�
									nadd = 1;
									if(sChar[0] >= 0 && sChar[0] <= 127)nadd = 0;
									i += nadd;
									data = str1.substr(0,i);//дǰ����
									str1 = str1.substr(i,str1.length() - i); //���󲿷ּ����Ƚ�
									str2 = data;
									TPlayScene::GetInstance()->DrawFontEx(m_Layer,str2,Left + lx + sx,Top + ly,UseColor,true);
									ly = ly + 18;
									sx = 0;
									len = 0;
									if(TextWidth(str1) <= Linewidth)
									{
										TPlayScene::GetInstance()->DrawFontEx(m_Layer,str1,Left + lx + sx,Top + ly,UseColor,true);
										sx =+ TextWidth(str1);
										break;
									}
									i = 0;
								}else 
								{
									i++;
								}
							}
						}else
						{
							TPlayScene::GetInstance()->DrawFontEx(m_Layer,data,Left + lx + sx,Top + ly,UseColor,true);
						}
					}
					ly = ly + 18;
				}
			
			}
			TempList1.clear();
		}
	}

	void CMiniTaskPan::DestoryClickPoint()
	{
		SelectMenuStr = ""; 
		//�ȵ������ڴ��ͷ�
		for(int i = 0;i < (int)MDlgPoints.size();i++)
		{
			TClickPoint* p = MDlgPoints[i];
			delete p;
		}
		MDlgPoints.clear();
	}
}

