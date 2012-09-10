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
	m_level = total_score/60;    //��Ϸ�Ѷ����ŷ��������Ӷ�����
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
	//��ͼ
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

/*���̷������Ӧ*/
void CCrossOceanView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_LEFT:
		myFish[curSize].m_moveDirection = -1;     //�����ϼ���m_moveDirection = -1
		break;
	case VK_RIGHT:
		myFish[curSize].m_moveDirection = 1;      //�����ϼ���m_moveDirection = 1
		break;
	case VK_UP:
		myFish[curSize].m_moveDirection = -2;     //�����ϼ���m_moveDirection = -2
		break;
	case VK_DOWN:
		myFish[curSize].m_moveDirection = 2;     //�����ϼ���m_moveDirection = 2
		break;
	}
	myFish[curSize].Move();        //��Ӧ�������ʵ������ζ�
	OnDraw(GetDC());               //��ͼ
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCrossOceanView::TransparentBitmap(HDC hdc, HBITMAP hBitmap, short xStart, short yStart, short xadd, short yadd, COLORREF cTransparentColor)
{
    BITMAP     m_bm;
	COLORREF   cColor;  
	
	// ������ʱDC
	HDC     hMem, hBack, hObject, hTemp, hSave;
	hBack   = CreateCompatibleDC(hdc);
	hObject = CreateCompatibleDC(hdc);
	hMem    = CreateCompatibleDC(hdc);
	hSave   = CreateCompatibleDC(hdc);   
	hTemp   = CreateCompatibleDC(hdc);
	// ѡ��λͼ
	SelectObject(hTemp, hBitmap);   
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&m_bm);
	//��ʾλͼ���
	POINT      ptSize;
	// ȡ��λͼ�Ŀ��
	ptSize.x = m_bm.bmWidth;     
    // ȡ��λͼ�ĸö�
	ptSize.y = m_bm.bmHeight;           
	// ת��Ϊ�߼���ֵ
	DPtoLP(hTemp, &ptSize, 1);   
	
	// ������ʱλͼ
	HBITMAP    bmBack, bmObject, bmMem, bmSave;
	// ��ɫλͼ
	bmBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);    
	bmObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	// ���豸����λͼ
	bmMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	
	// ����������ʱλͼѡ����ʱDC��
	HBITMAP    OldbmBack, OldbmObject, OldbmMem, OldbmSave;
	OldbmBack   = (HBITMAP)SelectObject(hBack, bmBack);
	OldbmObject = (HBITMAP)SelectObject(hObject, bmObject);
	OldbmMem    = (HBITMAP)SelectObject(hMem, bmMem);
	OldbmSave   = (HBITMAP)SelectObject(hSave, bmSave);
	
	// ����ӳ��ģʽ
	SetMapMode(hTemp, GetMapMode(hdc));
	// �ȱ���ԭʼλͼ
	BitBlt(hSave, 0, 0, ptSize.x, ptSize.y, hTemp, 0, 0, SRCCOPY);
	// ��������ɫ����Ϊ��͸������ɫ
	cColor = SetBkColor(hTemp, cTransparentColor);
	// ����Ŀ��������
	BitBlt(hObject, 0, 0, ptSize.x, ptSize.y, hTemp, 0, 0, SRCCOPY);
	// �ָ�ԴDC��ԭʼ����ɫ
	SetBkColor(hTemp, cColor);
	
	// ������ת��Ŀ��������
	BitBlt(hBack, 0, 0, ptSize.x, ptSize.y, hObject, 0, 0, NOTSRCCOPY);
	// ������DC�ı�����Ŀ��DC
	BitBlt(hMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart, SRCCOPY);
	// ����λͼ����ʾ��
	BitBlt(hMem, 0, 0, ptSize.x, ptSize.y, hObject, 0, 0, SRCAND);
	// ����λͼ�е�͸��ɫ
	BitBlt(hTemp, 0, 0, ptSize.x, ptSize.y, hBack, 0, 0, SRCAND);
	// ��λͼ��Ŀ��DC�ı�����������
	BitBlt(hMem, 0, 0, ptSize.x, ptSize.y, hTemp, 0, 0, SRCPAINT);
	// ����Ŀ�굽��Ļ�� 
	StretchBlt(hdc, xStart, yStart, ptSize.x+xadd, ptSize.y+yadd, hMem, 0, 0, ptSize.x, ptSize.y,SRCCOPY);
	// �ָ�ԭʼλͼ
	BitBlt(hTemp, 0, 0, ptSize.x, ptSize.y, hSave, 0, 0, SRCCOPY);
	
	// ɾ����ʱ�ڴ�λͼ
	DeleteObject(SelectObject(hBack, OldbmBack));
	DeleteObject(SelectObject(hObject, OldbmObject));
	DeleteObject(SelectObject(hMem, OldbmMem));
	DeleteObject(SelectObject(hSave, OldbmSave));
	
	// ɾ����ʱ�ڴ�DC
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
	
	switch(nIDEvent)    //ѡ����һ��Timer
	{
	case 1:
		{
			for (int i = 0;i<m_fishnum;i++)
			{
				if(freeFish[i].isAlive)         //������ǻ�ľ��ζ�
					freeFish[i].freeMove();
				myFish[myFish->m_size].EatFish(freeFish[i]);   //�����ʵ��
			}
			break;
		}
		// 	case 2:
		// 		{
		// 			for (int i = 0;i<m_fishnum;i++)
		// 			{
		// 				if(freeFish[i].isAlive)         //������ǻ�ľ��ζ�
		// 					freeFish[i].freeMove();
		// 				myFish[myFish->m_size].EatFish(freeFish[i]);   //�����ʵ��
		// 			}
		// 			break;
		// 		}
	}
	OnDraw(GetDC());     //��ͼ
	CView::OnTimer(nIDEvent);
}


/*��Ϸ��ͣ*/
void CCrossOceanView::OnPause() 
{
	// TODO: Add your command handler code here
    PlaySound(NULL,NULL,SND_FILENAME);    //��ͣ����
	KillTimer(1);      //ʵ����Ϸ����ͣ
}



/*��Ϸ��ʼ*/
void CCrossOceanView::OnStart() 
{
	// TODO: Add your command handler code here
	PlaySound("./musics/bkmusic.wav",NULL,SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_LOOP);    //���ű�������
	
	//	freeFish = new CFreeFish[m_fishnum];
	SetTimer(1,200 - m_level*40,NULL);       //���ü�ʱ��1��ʱ����Ϊ���Ѷ��йغ���
	
	/*�����ҿ��Ƶ���*/
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
	
	
	/*����������*/
	for (int i = 0;i<m_fishnum;i++)
	{
		int startX = rand()%2;
		(startX == 0)?freeFish[i].m_curPos.x = 0:freeFish[i].m_curPos.x = 744;  //������������X������ֻ��������
		
		freeFish[i].m_curPos.y = rand()%447;      //�������y���������
		freeFish[i].isAlive = true;              //ÿ�����isAlive��Ϊtrue
		freeFish[i].m_size = rand()%4;             //���ÿ��������Ĵ�С
		if (freeFish[i].m_size == 1)        //�����������size���ܺ��ҵ���һ������sizeΪ1�ͼ�һ
		{
			freeFish[i].m_size --;
		}

		//��Ӧsize�����������ͼƬ
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
		
		(rand()%2 == 1)?freeFish[i].m_moveDirection = 1:freeFish[i].m_moveDirection = -1;//�����ÿ�������Ϸ��ʼʱ���ζ�����
	}
	
	
    
}

/*���Ʒ����͵ȼ�*/
void CCrossOceanView::OnDrawScore(CDC *pDC, long dx, long dy, int score)
{
    int nOldDC=pDC->SaveDC();     
	//��������
	CFont font;    
	if(0==font.CreatePointFont(180,"Comic Sans MS"))	
	{
		AfxMessageBox("Can't Create Font");	
	}
	pDC->SelectObject(&font);
	//����������ɫ���䱳����ɫ
	//CString str;
	pDC->SetTextColor(RGB(255,255,0));
	//pDC->SetBkColor(RGB(0,0,0));
	pDC->SetBkMode(TRANSPARENT);
	//�������
	CString str;
	str.Format("%d",score);  
	//pDC->TextOut(690,5,str);
	pDC->TextOut(dx, dy, str);
	pDC->RestoreDC(nOldDC);
}

/*�����Ӧ*/
void CCrossOceanView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	myFish[curSize].m_curPos.x = point.x;       //��ǰ�������������ĵ�ǰ����
	myFish[curSize].m_curPos.y = point.y;
	myFish[curSize].Move();         //��Ӧ�������ʵ��������ҵ�����ζ�
	OnDraw(GetDC());               //��ͼ
	CView::OnMouseMove(nFlags, point);
}


/*������Ϸ���öԻ���*/
void CCrossOceanView::OnGameset() 
{
	// TODO: Add your command handler code here
	GAMESET dialog = new GAMESET();
	KillTimer(1);
	if(dialog.DoModal() == IDOK)
	{
		m_fishnum = dialog.m_num;
		m_level = dialog.m_difficulty;
		/*����������*/
		PlaySound("./musics/bkmusic.wav",NULL,SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_LOOP);    //���ű�������
		
		//	freeFish = new CFreeFish[m_fishnum];
		SetTimer(1,100,NULL);       //���ü�ʱ��1��ʱ����Ϊ100����
		
		/*�����ҿ��Ƶ���*/
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
		

		/*ÿ������������Ϸ�����¿��֣�������������Ϸ�ز�*/
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
			
			(rand()%2 == 1)?freeFish[i].m_moveDirection = 1:freeFish[i].m_moveDirection = -1;//�����ÿ�������Ϸ��ʼʱ���ζ�����
		}
	}
}

void CCrossOceanView::OnPlayagain() 
{
	// TODO: Add your command handler code here
	m_fishnum = 10;
	total_score = 0;
	curSize = 1;
	/*����������*/
	PlaySound("./musics/bkmusic.wav",NULL,SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_LOOP);    //���ű�������
	
	//	freeFish = new CFreeFish[m_fishnum];
	SetTimer(1,200 - m_level*40,NULL);;       //���ü�ʱ��1��ʱ����Ϊ100����
	
	/*�����ҿ��Ƶ���*/
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
		
		(rand()%2 == 1)?freeFish[i].m_moveDirection = 1:freeFish[i].m_moveDirection = -1;//�����ÿ�������Ϸ��ʼʱ���ζ�����
	}
}

void CCrossOceanView::OnSave() 
{
	// TODO: Add your command handler code here
	CStdioFile gameFile;   //�Կɶ�д��ʽ���ļ�
	CFileException fileException;
	if (gameFile.Open("gameinfo.txt",CFile::modeCreate|CFile::typeText|CFile::modeReadWrite,&fileException))  //�Զ�д��ʽ���ļ���������������ļ��½�һ��
	{
		//д���ҵ������Ϣ
		LPTSTR strMyFishInfo = new TCHAR[128]; 
		wsprintf(strMyFishInfo,"�Ѷ�:%d\n�ҵ������Ϣ\n��С:%d\nX:%d\nY:%d\n�÷�:%d\n\n",
			m_level,curSize,myFish[curSize].m_curPos.x,myFish[curSize].m_curPos.y,total_score);
		gameFile.WriteString(strMyFishInfo);
		
		
		//д�����������Ϣ
		LPTSTR * freeFishInfo = new LPTSTR[m_fishnum];
		for (int i = 0;i<m_fishnum;i++)
		{
			freeFishInfo[i] = new TCHAR[128];
			if(freeFish[i].isAlive)
			{
				
				wsprintf(freeFishInfo[i],"��%d�������Ϣ\n��С:%d\nX:%d\nY:%d\n\n",i+1,
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
