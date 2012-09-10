// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CrossOcean.h"

#include "MainFrm.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_COMMAND(IDB_PLAY, OnPlay)
	ON_COMMAND(IDB_MUSICPAUSE, OnMusicpause)
	ON_COMMAND(IDM_BLOG, OnBlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.dwExStyle = cs.dwExStyle|WS_EX_TOPMOST;
	cs.style = WS_SYSMENU|WS_OVERLAPPED|WS_MINIMIZEBOX;
	//设置窗口大小744*447
	cs.cx = 744;
	cs.cy = 500;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers






void CMainFrame::OnExit() 
{
	// TODO: Add your command handler code here
	exit(0);
}

void CMainFrame::OnPlay() 
{
	// TODO: Add your command handler code here
	//播放背景音乐
	PlaySound("./musics/bkmusic.wav",NULL,SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_LOOP);
}

void CMainFrame::OnMusicpause() 
{
	// TODO: Add your command handler code here
	PlaySound(NULL,NULL,SND_FILENAME);
}

void CMainFrame::OnBlog() 
{
	// TODO: Add your command handler code here
	CString myBlog = "http://hi.baidu.com/lsin30";
	ShellExecute(0,"open",myBlog,"","",SW_SHOWNORMAL);
}
