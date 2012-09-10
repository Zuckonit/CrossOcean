// CrossOceanView.cpp : implementation of the CCrossOceanView class
//

#include "stdafx.h"
#include "CrossOcean.h"
#include "time.h"
#include "CrossOceanDoc.h"
#include "CrossOceanView.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanView

IMPLEMENT_DYNCREATE(CCrossOceanView, CView)

BEGIN_MESSAGE_MAP(CCrossOceanView, CView)
//{{AFX_MSG_MAP(CCrossOceanView)
ON_WM_KEYDOWN()
ON_WM_ERASEBKGND()
ON_WM_TIMER()
ON_COMMAND(IDM_PAUSE, OnPause)
ON_COMMAND(IDM_START, OnStart)
ON_WM_MOUSEMOVE()
ON_COMMAND(IDM_GAMESET, OnGameset)
ON_COMMAND(IDM_PLAYAGAIN, OnPlayagain)
ON_COMMAND(IDM_SAVE, OnSave)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanView construction/destruction

CCrossOceanView::CCrossOceanView()
{
	// TODO: add construction code here
	m_bkimg.LoadBitmap(IDB_BITMAPBK);
	m_scorebmp.LoadBitmap(IDB_BITMAPSCORE);
    m_fishnum = 10;	
	m_level = 1;
}

CCrossOceanView::~CCrossOceanView()
{
    
}

BOOL CCrossOceanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanView drawing
extern int curSize;
extern int total_score;
extern CPoint curPos;

void CCrossOceanView::OnDraw(CDC* pDC)
{
	CCrossOceanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CDC Mdc;
	CDC bdc;
	CDC sdc;
	m_level = total_score/60;    //游戏难度随着分数的增加而增加
	if (Mdc.CreateCompatibleDC(pDC) == FALSE)
	{
		AfxMessageBox("fail to create mdc");
	}
	if (bdc.CreateCompatibleDC(pDC) == FALSE)
	{
		AfxMessageBox("fail to create bdc ");
	}
	if (sdc.CreateCompatibleDC(pDC) == FALSE)
	{
		AfxMessageBox("fail to create sdc ");
	}
	CRect rt;
	GetClientRect(rt);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rt.Width(),rt.Height());
	Mdc.SelectObject(&bmp);
	//绘图
	bdc.SelectObject(m_bkimg);
	sdc.SelectObject(m_scorebmp);
	
	Mdc.BitBlt(0,0,744,447,&bdc,0,0,SRCCOPY);
	
    Mdc.StretchBlt(0,0,774,447,&sdc,0,0,744,447,SRCCOPY);
	
	if(myFish[curSize].m_life > 0)
	{
		TransparentBitmap(Mdc.GetSafeHdc(),myFish[curSize].m_image[(myFish[curSize].m_moveDirection+1)/2],
			myFish[curSize].m_curPos.x,myFish[curSize].m_curPos.y,0,0,RGB(0,0,0));
	}
	
	for (int i = 0;i<m_fishnum;i++)
	{
		if(freeFish[i].isAlive)
		{
			TransparentBitmap(Mdc.GetSafeHdc(),freeFish[i].m_image[(freeFish[i].m_moveDirection+1)/2],
				freeFish[i].m_curPos.x,freeFish[i].m_curPos.y,0,0,RGB(0,0,0));
		}
        
		
	}
	OnDrawScore(&Mdc,680,5,total_score);
	OnDrawScore(&Mdc,680,45,curSize);
	pDC->BitBlt(0,0,rt.Width(),rt.Height(),&Mdc,0,0,SRCCOPY);
	Mdc.DeleteDC();
	bmp.DeleteObject();
	
}

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanView diagnostics

#ifdef _DEBUG
void CCrossOceanView::AssertValid() const
{
	CView::AssertValid();
}

void CCrossOceanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCrossOceanDoc* CCrossOceanView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCrossOceanDoc)));
	return (CCrossOceanDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanView message handlers

/*键盘方向键响应*/
void CCrossOceanView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_LEFT:
		myFish[curSize].m_moveDirection = -1;     //按向上键，m_moveDirection = -1
		break;
	case VK_RIGHT:
		myFish[curSize].m_moveDirection = 1;      //按向上键，m_moveDirection = 1
		break;
	case VK_UP:
		myFish[curSize].m_moveDirection = -2;     //按向上键，m_moveDirection = -2
		break;
	case VK_DOWN:
		myFish[curSize].m_moveDirection = 2;     //按向上键，m_moveDirection = 2
		break;
	}
	myFish[curSize].Move();        //响应方向键，实现鱼的游动
	OnDraw(GetDC());               //绘图
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCrossOceanView::TransparentBitmap(HDC hdc, HBITMAP hBitmap, short xStart, short yStart, short xadd, short yadd, COLORREF cTransparentColor)
{
    BITMAP     m_bm;
	COLORREF   cColor;  
	
	// 创建临时DC
	HDC     hMem, hBack, hObject, hTemp, hSave;
	hBack   = CreateCompatibleDC(hdc);
	hObject = CreateCompatibleDC(hdc);
	hMem    = CreateCompatibleDC(hdc);
	hSave   = CreateCompatibleDC(hdc);   
	hTemp   = CreateCompatibleDC(hdc);
	// 选入位图
	SelectObject(hTemp, hBitmap);   
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&m_bm);
	//显示位图宽高
	POINT      ptSize;
	// 取得位图的宽度
	ptSize.x = m_bm.bmWidth;     
    // 取得位图的该度
	ptSize.y = m_bm.bmHeight;           
	// 转换为逻辑点值
	DPtoLP(hTemp, &ptSize, 1);   
	
	// 创建临时位图
	HBITMAP    bmBack, bmObject, bmMem, bmSave;
	// 单色位图
	bmBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);    
	bmObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	// 与设备兼容位图
	bmMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	
	// 将创建的临时位图选入临时DC中
	HBITMAP    OldbmBack, OldbmObject, OldbmMem, OldbmSave;
	OldbmBack   = (HBITMAP)SelectObject(hBack, bmBack);
	OldbmObject = (HBITMAP)SelectObject(hObject, bmObject);
	OldbmMem    = (HBITMAP)SelectObject(hMem, bmMem);
	OldbmSave   = (HBITMAP)SelectObject(hSave, bmSave);
	
	// 设置映射模式
	SetMapMode(hTemp, GetMapMode(hdc));
	// 先保留原始位图
	BitBlt(hSave, 0, 0, ptSize.x, ptSize.y, hTemp, 0, 0, SRCCOPY);
	// 将背景颜色设置为需透明的颜色
	cColor = SetBkColor(hTemp, cTransparentColor);
	// 创建目标屏蔽码
	BitBlt(hObject, 0, 0, ptSize.x, ptSize.y, hTemp, 0, 0, SRCCOPY);
	// 恢复源DC的原始背景色
	SetBkColor(hTemp, cColor);
	
	// 创建反转的目标屏蔽码
	BitBlt(hBack, 0, 0, ptSize.x, ptSize.y, hObject, 0, 0, NOTSRCCOPY);
	// 拷贝主DC的背景到目标DC
	BitBlt(hMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart, SRCCOPY);
	// 屏蔽位图的显示区
	BitBlt(hMem, 0, 0, ptSize.x, ptSize.y, hObject, 0, 0, SRCAND);
	// 屏蔽位图中的透明色
	BitBlt(hTemp, 0, 0, ptSize.x, ptSize.y, hBack, 0, 0, SRCAND);
	// 将位图与目标DC的背景左异或操作
	BitBlt(hMem, 0, 0, ptSize.x, ptSize.y, hTemp, 0, 0, SRCPAINT);
	// 拷贝目标到屏幕上 
	StretchBlt(hdc, xStart, yStart, ptSize.x+xadd, ptSize.y+yadd, hMem, 0, 0, ptSize.x, ptSize.y,SRCCOPY);
	// 恢复原始位图
	BitBlt(hTemp, 0, 0, ptSize.x, ptSize.y, hSave, 0, 0, SRCCOPY);
	
	// 删除临时内存位图
	DeleteObject(SelectObject(hBack, OldbmBack));
	DeleteObject(SelectObject(hObject, OldbmObject));
	DeleteObject(SelectObject(hMem, OldbmMem));
	DeleteObject(SelectObject(hSave, OldbmSave));
	
	// 删除临时内存DC
	DeleteDC(hMem);
	DeleteDC(hBack);
	DeleteDC(hObject);
	DeleteDC(hSave);
	DeleteDC(hTemp);
}

BOOL CCrossOceanView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

void CCrossOceanView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	switch(nIDEvent)    //选择哪一个Timer
	{
	case 1:
		{
			for (int i = 0;i<m_fishnum;i++)
			{
				if(freeFish[i].isAlive)         //如果鱼是活的就游动
					freeFish[i].freeMove();
				myFish[myFish->m_size].EatFish(freeFish[i]);   //吃鱼的实现
			}
			break;
		}
		// 	case 2:
		// 		{
		// 			for (int i = 0;i<m_fishnum;i++)
		// 			{
		// 				if(freeFish[i].isAlive)         //如果鱼是活的就游动
		// 					freeFish[i].freeMove();
		// 				myFish[myFish->m_size].EatFish(freeFish[i]);   //吃鱼的实现
		// 			}
		// 			break;
		// 		}
	}
	OnDraw(GetDC());     //绘图
	CView::OnTimer(nIDEvent);
}


/*游戏暂停*/
void CCrossOceanView::OnPause() 
{
	// TODO: Add your command handler code here
    PlaySound(NULL,NULL,SND_FILENAME);    //暂停音乐
	KillTimer(1);      //实现游戏的暂停
}



/*游戏开始*/
void CCrossOceanView::OnStart() 
{
	// TODO: Add your command handler code here
	PlaySound("./musics/bkmusic.wav",NULL,SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_LOOP);    //播放背景音乐
	
	//	freeFish = new CFreeFish[m_fishnum];
	SetTimer(1,200 - m_level*40,NULL);       //设置计时器1，时间间隔为跟难度有关毫秒
	
	/*载入我控制的鱼*/
    for (int j = 1;j<4;j++)
    {
		myFish[j].m_size = j;
		
		myFish[1].m_image[0].LoadBitmap(IDB_BITMAPMYL);
		myFish[1].m_image[1].LoadBitmap(IDB_BITMAPMYR);
		
		myFish[2].m_image[0].LoadBitmap(IDB_BITMAPMIDL);
		myFish[2].m_image[1].LoadBitmap(IDB_BITMAPMIDR);
		
		myFish[3].m_image[0].LoadBitmap(IDB_BITMAPBIGL);
		myFish[3].m_image[1].LoadBitmap(IDB_BITMAPBIGR);
		
		
    }
	
	
	/*载入自由鱼*/
	for (int i = 0;i<m_fishnum;i++)
	{
		int startX = rand()%2;
		(startX == 0)?freeFish[i].m_curPos.x = 0:freeFish[i].m_curPos.x = 744;  //随机化自由鱼的X坐标且只能在两边
		
		freeFish[i].m_curPos.y = rand()%447;      //自由鱼的y坐标随机化
		freeFish[i].isAlive = true;              //每条鱼的isAlive设为true
		freeFish[i].m_size = rand()%4;             //随机每条自由鱼的大小
		if (freeFish[i].m_size == 1)        //由于自由鱼的size不能和我的鱼一样，故size为1就减一
		{
			freeFish[i].m_size --;
		}

		//对应size载入自由鱼的图片
		switch(freeFish[i].m_size)
		{
		case 0:
			freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPSMALLL);
			freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPSMALLR);
			break;
		case 2:
			freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPMIDL);
			freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPMIDR);
			break;
		case 3:
			freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPBIGL);
			freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPBIGR);
			break;
		}
		
		(rand()%2 == 1)?freeFish[i].m_moveDirection = 1:freeFish[i].m_moveDirection = -1;//随机化每条鱼的游戏开始时的游动方向
	}
	
	
    
}

/*绘制分数和等级*/
void CCrossOceanView::OnDrawScore(CDC *pDC, long dx, long dy, int score)
{
    int nOldDC=pDC->SaveDC();     
	//设置字体
	CFont font;    
	if(0==font.CreatePointFont(180,"Comic Sans MS"))	
	{
		AfxMessageBox("Can't Create Font");	
	}
	pDC->SelectObject(&font);
	//设置字体颜色及其背景颜色
	//CString str;
	pDC->SetTextColor(RGB(255,255,0));
	//pDC->SetBkColor(RGB(0,0,0));
	pDC->SetBkMode(TRANSPARENT);
	//输出数字
	CString str;
	str.Format("%d",score);  
	//pDC->TextOut(690,5,str);
	pDC->TextOut(dx, dy, str);
	pDC->RestoreDC(nOldDC);
}

/*鼠标响应*/
void CCrossOceanView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	myFish[curSize].m_curPos.x = point.x;       //当前鱼的坐标等于鼠标的当前坐标
	myFish[curSize].m_curPos.y = point.y;
	myFish[curSize].Move();         //响应鼠标坐标实现鱼控制我的鱼的游动
	OnDraw(GetDC());               //绘图
	CView::OnMouseMove(nFlags, point);
}


/*弹出游戏设置对话框*/
void CCrossOceanView::OnGameset() 
{
	// TODO: Add your command handler code here
	GAMESET dialog = new GAMESET();
	KillTimer(1);
	if(dialog.DoModal() == IDOK)
	{
		m_fishnum = dialog.m_num;
		m_level = dialog.m_difficulty;
		/*载入自由鱼*/
		PlaySound("./musics/bkmusic.wav",NULL,SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_LOOP);    //播放背景音乐
		
		//	freeFish = new CFreeFish[m_fishnum];
		SetTimer(1,100,NULL);       //设置计时器1，时间间隔为100毫秒
		
		/*载入我控制的鱼*/
		for (int j = 1;j<4;j++)
		{
			myFish[j].m_size = j;
			
			myFish[1].m_image[0].LoadBitmap(IDB_BITMAPMYL);
			myFish[1].m_image[1].LoadBitmap(IDB_BITMAPMYR);
			
			myFish[2].m_image[0].LoadBitmap(IDB_BITMAPMIDL);
			myFish[2].m_image[1].LoadBitmap(IDB_BITMAPMIDR);
			
			myFish[3].m_image[0].LoadBitmap(IDB_BITMAPBIGL);
			myFish[3].m_image[1].LoadBitmap(IDB_BITMAPBIGR);
			
			
		}
		

		/*每当重新设置游戏后重新开局，即重新载入游戏素材*/
		for (int i = 0;i<m_fishnum;i++)
		{
			int startX = rand()%2;
			(startX == 0)?freeFish[i].m_curPos.x = 0:freeFish[i].m_curPos.x = 744;
			
			freeFish[i].m_curPos.y = rand()%447;
			freeFish[i].isAlive = true; 
			freeFish[i].m_size = rand()%4;
			if (freeFish[i].m_size == 1)
			{
				freeFish[i].m_size --;
			}
			switch(freeFish[i].m_size)
			{
			case 0:
				freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPSMALLL);
				freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPSMALLR);
				break;
			case 2:
				freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPMIDL);
				freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPMIDR);
				break;
			case 3:
				freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPBIGL);
				freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPBIGR);
				break;
			}
			
			(rand()%2 == 1)?freeFish[i].m_moveDirection = 1:freeFish[i].m_moveDirection = -1;//随机化每条鱼的游戏开始时的游动方向
		}
	}
}

void CCrossOceanView::OnPlayagain() 
{
	// TODO: Add your command handler code here
	m_fishnum = 10;
	total_score = 0;
	curSize = 1;
	/*载入自由鱼*/
	PlaySound("./musics/bkmusic.wav",NULL,SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_LOOP);    //播放背景音乐
	
	//	freeFish = new CFreeFish[m_fishnum];
	SetTimer(1,200 - m_level*40,NULL);;       //设置计时器1，时间间隔为100毫秒
	
	/*载入我控制的鱼*/
	for (int j = 1;j<4;j++)
	{
		myFish[j].m_size = j;
		
		myFish[1].m_image[0].LoadBitmap(IDB_BITMAPMYL);
		myFish[1].m_image[1].LoadBitmap(IDB_BITMAPMYR);
		
		myFish[2].m_image[0].LoadBitmap(IDB_BITMAPMIDL);
		myFish[2].m_image[1].LoadBitmap(IDB_BITMAPMIDR);
		
		myFish[3].m_image[0].LoadBitmap(IDB_BITMAPBIGL);
		myFish[3].m_image[1].LoadBitmap(IDB_BITMAPBIGR);
		
		
	}
	
	for (int i = 0;i<m_fishnum;i++)
	{
		int startX = rand()%2;
		(startX == 0)?freeFish[i].m_curPos.x = 0:freeFish[i].m_curPos.x = 744;
		
		freeFish[i].m_curPos.y = rand()%447;
		freeFish[i].isAlive = true; 
		freeFish[i].m_size = rand()%4;
		if (freeFish[i].m_size == 1)
		{
			freeFish[i].m_size --;
		}
		switch(freeFish[i].m_size)
		{
		case 0:
			freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPSMALLL);
			freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPSMALLR);
			break;
		case 2:
			freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPMIDL);
			freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPMIDR);
			break;
		case 3:
			freeFish[i].m_image[0].LoadBitmap(IDB_BITMAPBIGL);
			freeFish[i].m_image[1].LoadBitmap(IDB_BITMAPBIGR);
			break;
		}
		
		(rand()%2 == 1)?freeFish[i].m_moveDirection = 1:freeFish[i].m_moveDirection = -1;//随机化每条鱼的游戏开始时的游动方向
	}
}

void CCrossOceanView::OnSave() 
{
	// TODO: Add your command handler code here
	CStdioFile gameFile;   //以可读写方式打开文件
	CFileException fileException;
	if (gameFile.Open("gameinfo.txt",CFile::modeCreate|CFile::typeText|CFile::modeReadWrite,&fileException))  //以读写方式打开文件，若不存在这个文件新建一个
	{
		//写入我的鱼的信息
		LPTSTR strMyFishInfo = new TCHAR[128]; 
		wsprintf(strMyFishInfo,"难度:%d\n我的鱼的信息\n大小:%d\nX:%d\nY:%d\n得分:%d\n\n",
			m_level,curSize,myFish[curSize].m_curPos.x,myFish[curSize].m_curPos.y,total_score);
		gameFile.WriteString(strMyFishInfo);
		
		
		//写入自由鱼的信息
		LPTSTR * freeFishInfo = new LPTSTR[m_fishnum];
		for (int i = 0;i<m_fishnum;i++)
		{
			freeFishInfo[i] = new TCHAR[128];
			if(freeFish[i].isAlive)
			{
				
				wsprintf(freeFishInfo[i],"第%d条鱼的信息\n大小:%d\nX:%d\nY:%d\n\n",i+1,
					freeFish[i].m_size,freeFish[i].m_curPos.x,freeFish[i].m_curPos.y);
				gameFile.WriteString(freeFishInfo[i]);
				
			}
		}
		delete freeFishInfo;
	}
    else
	{
		TRACE("Can't open file gameifo.txt,error=%u\n",fileException.m_cause);
	}
}
