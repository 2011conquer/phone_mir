#include "NpcDialog.h"
#include "VDImage.h"
#include "MShare.h"
#include "VD_Share.h"
#include <vector>
#include "./Common/SoundUtil.h"
#include "./Common/IconvString.h"
#include "./Net/NetClient.h"
#include "./Net/NetSendMsg.h"
#include "../FrmMain.h"
namespace VD_UI
{
//	static CNpcDialog* m_Insatnce = nullptr;
	CNpcDialog::CNpcDialog(void)
	{
		m_Layer = nullptr;
		MDlgPoints.clear();
		LastestClickTime = GetTickCount();
	}


	CNpcDialog::~CNpcDialog(void)
	{
	}

	//CNpcDialog* CNpcDialog::GetInstance()
	//{
	//	if(!m_Insatnce)
	//	{
	//		m_Insatnce = new CNpcDialog();
	//	}
	//	return m_Insatnce;
	//}

	void CNpcDialog::DestoryClickPoint()
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
	void CNpcDialog::Show(std::string npcname,std::string saying,cocos2d::Layer* layer)
	{
		m_ListImg.clear();
		m_Size = mOldSize;
		if(m_Layer) Hide();
		CBaseDialog::Show();
		m_Layer = cocos2d::Layer::create();
		m_Layer->retain();
		layer->addChild(m_Layer);
		m_sNpcName = npcname;
		m_sSaying = saying;
		RequireAddPoints = true;
		ProcessScripte();
		//�رհ�ť
		ui::Button* btn_Close = ui::Button::create(CLOSE_NORMAL,CLOSE_CLICK);
		cocos2d::Vec2 pos;
		if(mBtnCloseXY.x == 0 && mBtnCloseXY.y == 0)
		{
			pos = Vec2(m_Size.Left + 276,m_Size.Top + 30);
		}else
		{
			pos = mBtnCloseXY;
		}
		
		pos = Director::getInstance()->convertToGL(pos);
		btn_Close->setAnchorPoint(cocos2d::Vec2(0,0));
		btn_Close->setPosition(pos);
		m_Layer->addChild(btn_Close);

		btn_Close->addTouchEventListener(CC_CALLBACK_2(CNpcDialog::btn_Close_click, this));
		
		
	}

	void CNpcDialog::btn_Close_click(cocos2d::Ref* pSender,ui::Widget::TouchEventType type)
	{
		if(type == ui::Widget::TouchEventType::ENDED)
		{
			Hide();
			g_UIClick = true;
		}

	}
	void CNpcDialog::Hide()
	{
		if(!m_Layer)return;
		CBaseDialog::Hide();
		DestoryClickPoint();
		m_Layer->removeAllChildrenWithCleanup(true);
		m_Layer->release();
		m_Layer = nullptr;
		RequireAddPoints = false;
	}

	void CNpcDialog::ProcessScripte()
	{
		bool centerdlg = false;
		bool vcenter = false;
		TClickPoint* pcp;
		int bgImgIndex = 31;
		int lx = 17;   //�����ڶԻ����е������x
		int ly = 52;   //������ y
		int line = 0;  //��ǰ�����ֳ��ȼ�����
		int Width = 0; int Height = 0;
		int Left = m_Size.Left; int Top = m_Size.Top;
		//�Ի��򱳾�
		TVDImage* img = GetUIImage(bgImgIndex);
		if(img && img->Image_)
		{
			Width = img->pWidth;    //���ݱ���ͼƬ���öԻ����С
			Height = img->pHeight;
		}

		int Linewidth = Width - 16;
		mBtnCloseXY = cocos2d::Vec2(0,0);
		//һЩ�Ի����������ʹ������Ի��򱳾�
		std::string fdata= "";
		std::string bdata = m_sSaying;
		int n;
		std::string cmdstr;
		while(true)
		{
			n = bdata.find("<DCMD:");
			cmdstr = "";
			if(n >= 0)
			{
				fdata = fdata + bdata.substr(0,n);
				bdata = bdata.substr(n + 6,bdata.length() - (n + 6));
				n = bdata.find(">");
				if(n >= 0)
				{
					cmdstr =  bdata.substr(0,n);
					cmdstr = StringToLower(cmdstr.c_str());
					bdata = bdata.substr(n+1,bdata.length() -(n + 1));
					if(cmdstr.length() > 0)
					{
						if(cmdstr.find("bgimg") == 0)	//����Ի��򱳾�ͼƬ
						{
							cmdstr = cmdstr.substr(5,cmdstr.length() - 5);
							n = atoi(cmdstr.c_str());
							bgImgIndex = n;
						}else if(cmdstr.find("clientleft") == 0)	//�ͻ�����������left
						{ 
							cmdstr = cmdstr.substr(10,cmdstr.length() - 10);
							n = atoi(cmdstr.c_str());
							lx = n;
						}else if(cmdstr.find("clienttop") == 0)//�ͻ�����������top
						{
							cmdstr = cmdstr.substr(9,cmdstr.length() - 9);
							n = atoi(cmdstr.c_str());
							ly = n;
						}else if(cmdstr.find("clientwidth") == 0) //�ͻ�����������width
						{
							cmdstr = cmdstr.substr(11,cmdstr.length() - 11);
							n = atoi(cmdstr.c_str());
							Linewidth = lx + n;
						}else if(cmdstr.find("closeleft") == 0) //�رհ�ťx
						{
							cmdstr = cmdstr.substr(9,cmdstr.length() - 9);
							n = atoi(cmdstr.c_str());
							mBtnCloseXY.x = n;
							//�رհ�ťĬ��λ��
						}else if(cmdstr.find("closetop") == 0)  //�رհ�ťy
						{
							cmdstr = cmdstr.substr(8,cmdstr.length() - 8);
							n = atoi(cmdstr.c_str());
							mBtnCloseXY.y = n;
						
						}else if(cmdstr.find("center") == 0) //���жԻ���
						{
							centerdlg = true;
						}else if(cmdstr.find("vcenter") == 0) ////�������-- 2013.4.12-
						{
							vcenter = true;
						}

					}
				}
			}else
			{
				fdata = fdata + bdata;
				break;
			}
		}
		std::string str = fdata;
		//�Ի��򱳾�
		img = GetUIImage(bgImgIndex);
		if(img && img->Image_)
		{
			Width = img->pWidth;    //���ݱ���ͼƬ���öԻ����С
			Height = img->pHeight;
			if(centerdlg)
			{
				Left = (SCREENWIDTH - Width) / 2;
			}
			if(vcenter)
			{
				Top = (SCREENHEIGHT - Height) / 2;
			}
			m_Layer->addChild(img->GetImage(Left,Top));
			m_Size.Left = Left;
			m_Size.Top = Top;
			m_Size.Right = Left + Width;
			m_Size.Bottom = Top + Height;
			m_ListImg.push_back(img);
		}
		int sx;
		bool drawCenter = false;
		//ͨ��\б�ܷ��ŷ������֣�����templist1
		std::vector<std::string>  TempList1;
		TempList1.clear();
		std::string data;
		TVDImage* cmdimg;
		while(true)
		{
			if(str.length() <= 0)break;;
			str = GetValidStr3Ex(str,data,'\\');
			if(data.length() <= 0) data = " ";
			TempList1.push_back(data);
		}
		unsigned long UseColor = 0xFFFFFFFF;
		int len = 0; int i = 0;
		int nx = 0;int ny = 0;
		std::string str1;
		std::string str2;
		std::string sChar ;
		std::string cmdparam;
		int nID  = 0;
		int nWidth = 0;
		int nHeight = 0;
		int nadd;
		//���д�������
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
										DrawFontEx(fdata,Left + lx + sx,Top + ly,UseColor,true);
										ly = ly + 18;
										sx = 0;
										len = 0;
										//���������������ֱ����һ�л���
										if(TextWidth(str1) <= Linewidth)
										{
											DrawFontEx(str1,Left + lx + sx,Top + ly,UseColor,true);
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
								DrawFontEx(fdata,Left + lx + sx,Top + ly,UseColor,true);
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
											DrawFontEx(str2,Left + lx + sx,Top + ly,UseColor,true);
											
											ly = ly + 18;
											sx = 0;
											len = 0;
											if(TextWidth(str1) <= Linewidth)
											{
												str2 = str1;
												DrawFontEx(str2,Left + lx + sx,Top + ly,UseColor,true);	
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
									DrawFontEx(fdata,Left + lx + sx,Top + ly,UseColor,true);
									
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

								if(cmdstr.find("img:") > -1)	//����ͼƬ�ȵ�����
								{
									pcp = new TClickPoint;
									nID  = atoi(cmdstr.substr(cmdstr.length() - 4,cmdstr.length()).c_str());
									img = GetUIImage(nID);
									if(img && img->Image_)
									{
										pcp->rc.Rect(lx + sx,Top + ly - 14, lx + sx + img->TexWidth,ly + 14);
									}
									pcp->nType = 2;
									pcp->rstr = cmdparam;

								}else
								{
									pcp = new TClickPoint;
									pcp->rc.Rect(lx + sx, ly, lx + sx + TextWidth(cmdstr), ly + 14);
									
									pcp->rstr = cmdparam;
									pcp->nType = 0;
									
								}
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
											
											//����ƶ���ȥ��tips�� ����ľ��~~
											/*	if (g_nMouseX >= SurfaceX(Left + lx + sx))
											and (g_nMouseX - SurfaceX(Left + lx + sx) < g_MainDraw.Textwidth(cmdstr))
											and (g_nMouseY >= SurfaceY(Top + ly))
											and (g_nMouseY - SurfaceY(Top + ly) <= 11) then begin
											DScreen.ShowHint(g_nMouseX + 10, g_nMouseY + 10, hint, clWhite, False);
											end;*/
											DrawFontEx(cmdstr,Left + lx + sx,Top + ly,GetRGB(249),true,
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
									if(((int)cmdstr.find("|")) > -1)
									{//����ƶ���ȥ��tips�� ����ľ��~~
										//hint = GetValidStr3Ex(cmdstr,cmdstr,'|');
										//hint := GetValidStr3(cmdstr, cmdstr, ['|']);
										//if (g_nMouseX >= SurfaceX(Left + lx + sx)) and (g_nMouseX - SurfaceX(Left + lx + sx) < g_MainDraw.Textwidth(cmdstr))
										//	and (g_nMouseY >= SurfaceY(Top + ly)) and (g_nMouseY - SurfaceY(Top + ly) <= 11) then
										//	DScreen.ShowHint(g_nMouseX + 10, g_nMouseY + 10, hint, clWhite, False);
									}
									DrawFontEx(cmdstr,Left + lx + sx,Top + ly,UseColor,true);
									sx += TextWidth(cmdstr);
								}
							}else
							{
								if(cmdparam.length() > 0 && cmdparam[0] == '@')
								{
									//����ƶ���ȥ��tips�� ����ľ��~~
									//if pos('|', cmdstr) > 0 then
									//	begin
									//	hint := GetValidStr3(cmdstr, cmdstr, ['|']);
									//if (g_nMouseX >= SurfaceX(Left + lx + sx)) and (g_nMouseX - SurfaceX(Left + lx + sx) < g_MainDraw.Textwidth(cmdstr))
									//	and (g_nMouseY >= SurfaceY(Top + ly)) and (g_nMouseY - SurfaceY(Top + ly) <= 11) then
									//	DScreen.ShowHint(g_nMouseX + 10, g_nMouseY + 10, hint, clWhite, False);

									//end;
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
									//if (g_nMouseX >= SurfaceX(Left + lx + sx)) and (g_nMouseX - SurfaceX(Left + lx + sx) < nWidth)
									//	and (g_nMouseY >= SurfaceY(Top + ly) - nHeight) and (g_nMouseY - SurfaceY(Top + ly) <= 11) then
									//	begin
									//	//��ȼ--��������ͼƬ
									//nPoint := Pos(':',cmdstr);
									//if nPoint = 0 then begin
									//	g_MainDraw.drawfontex(cmdstr, SurfaceX(Left + lx + sx), SurfaceY(Top + ly), g_ButtonMouseMovecolor, true, $FF000000, True);
									//end else begin
									//	Inc(nID);
									//img := GetUIImage(nID);
									//g_MainDraw.Draw(img,SurfaceX(Left + lx + sx),SurfaceY(Top + ly) - img.TexHeight div 2);
									//end;
									//end else begin
									//��ֹ�����ֺ�ͼƬ
									int nPoint = (int)cmdstr.find(":");
									if(nPoint == -1)
									{
										DrawFontEx(cmdstr,Left + lx +sx,Top + ly,GetRGB(250),true,0xFF000000,true);
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
									//if pos('|', cmdstr) > 0 then
									//	begin
									//hint := GetValidStr3(cmdstr, cmdstr, ['|']);
									//if (g_nMouseX >= SurfaceX(Left + lx + sx)) and (g_nMouseX - SurfaceX(Left + lx + sx) < g_MainDraw.Textwidth(cmdstr))
									//	and (g_nMouseY >= SurfaceY(Top + ly)) and (g_nMouseY - SurfaceY(Top + ly) <= 11) then
									//	DScreen.ShowHint(g_nMouseX + 10, g_nMouseY + 10, hint, clWhite, False);
									//end;
									DrawFontEx(cmdstr,Left + lx + sx,Top + ly,UseColor);
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
								DrawFontEx(str2,Left + lx + sx,Top + ly,UseColor,true);
								ly = ly + 18;
								sx = 0;
								len = 0;
								if(TextWidth(str1) <= Linewidth)
								{
									DrawFontEx(str1,Left + lx + sx,Top + ly,UseColor,true);
									sx =+ TextWidth(str1);
									break;
								}
								i = 0;
							}else 
							{
								//if(nWidth == 12)i += 2; //˫�ֽ�
								//else i++;
								i++;
							}
						}
					}else
					{
						DrawFontEx(data,Left + lx + sx,Top + ly,UseColor,true);
					}
				}
				ly = ly + 18;
			}
			
		}
		TempList1.clear();
	}

	void CNpcDialog::DrawFontEx(std::string str,int nx,int ny, 
		unsigned long Color /* = 0xFFFFFFFF */,bool HaveStroke /* = false */,
		unsigned long StrokeColor /* = 0xFF000000 */, bool underline /* = false */,
		bool HaveBackGround/* = false */, unsigned long BackGroundColor /* = 0xFF000000 */)
	{
		std::string utf_str = GBKToUTF8_string(str.c_str(),str.length());
		//static cocos2d::TTFConfig font("fonts/simsun.ttf");
		static cocos2d::TTFConfig font("fonts/fangzheng_simsun.ttf");
		cocos2d::Label* label = cocos2d::Label::createWithTTF(font,"");
		cocos2d::Color4B c = HexColorToColor4B(Color);
		
		label->setTextColor(c);
		label->setString(utf_str);
		cocos2d::Vec2 pos; pos.x = nx; pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y - 12;
		label->setAnchorPoint(cocos2d::Vec2(0,0));
		label->setPosition(pos);
		//������
		if(underline)
		{
			cocos2d::DrawNode* node = cocos2d::DrawNode::create();
			node->setAnchorPoint(cocos2d::Vec2(0,0));
			//
			cocos2d::Vec2 endpos = cocos2d::Vec2(nx + TextWidth(str),ny);
			endpos = Director::getInstance()->convertToGL(endpos);
			endpos.y  = endpos.y - 12;
			
			pos = cocos2d::Vec2(nx,ny);
			pos = Director::getInstance()->convertToGL(pos);
			pos.y = pos.y - 12;
			//node->setPosition(pos);
			node->drawSegment(pos,endpos,0.5,Color4F(0, 1, 0, 1));//Color4F(c.r,c.g,c.b,c.a));
			m_Layer->addChild(node);
		}
		//���m_ListImg
		//if(HaveStroke)
		//{
			//c = HexColorToColor4B(StrokeColor);
			//label->enableOutline(c,1);
			//��ӰЧ��
			//label->enableGlow(c);
				
		//}
		m_Layer->addChild(label);
	}


	void CNpcDialog::MouseDown(cocos2d::Vec2 pos)
	{
		if(GetTickCount() < LastestClickTime)return;
		//�����ű����ȵ�����
		SelectMenuStr = "";
		TClickPoint* p;
		bool bType;
		int L = m_Size.Left;
		int T = m_Size.Top;
		int x = pos.x; int y = pos.y;
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
					break;
				}
			}
		}

		if(SelectMenuStr.length() > 0)
		{
			
			PlaySound_(s_glass_button_click);
			if((int)SelectMenuStr.find("@http://") > -1)
			{
				return;
			}
			if((int)SelectMenuStr.find("@rmst://") > -1)
			{
				return;
			}
			//��������
			if((int)SelectMenuStr.find("local:") > -1)
			{
				FrmMain::GetInstance()->DoLocalTaskCMD(p->id,p->rstr);
				return;
			}
			//���͵�������������
			std::string rstr = p->rstr;
			Hide();
			VD_Net::CNetClient::GetInstance()->GetSendMsg()->SendMerchantDlgSelect(g_nCurMerchant,rstr);
			
			//ResetMenuDlg;//�رչ���Ի���
			LastestClickTime = GetTickCount() + 1500;
		}
	}



	void CNpcDialog::SetRect(int x,int y,int width,int height)
	{
		CBaseDialog::SetRect(x,y,width,height);
		mOldSize = m_Size;
	}

	void CNpcDialog::Render()
	{
		TVDImage* img;
		for(int i = 0;i < (int)m_ListImg.size();i++)
		{
			img = m_ListImg[i];
			img->dwLatestTime = GetTickCount();
		}
	}
}


