// GAMESET.cpp : implementation file
//

#include "stdafx.h"
#include "CrossOcean.h"
#include "GAMESET.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GAMESET dialog


GAMESET::GAMESET(CWnd* pParent /*=NULL*/)
	: CDialog(GAMESET::IDD, pParent)
{
	//{{AFX_DATA_INIT(GAMESET)
	m_difficulty = 0;
	m_num = 0;
	//}}AFX_DATA_INIT
}


void GAMESET::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GAMESET)
	DDX_Text(pDX, IDC_EDITDIFF, m_difficulty);
	DDV_MinMaxInt(pDX, m_difficulty, 1, 3);
	DDX_Text(pDX, IDC_EDITNUM, m_num);
	DDV_MinMaxInt(pDX, m_num, 5, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GAMESET, CDialog)
	//{{AFX_MSG_MAP(GAMESET)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GAMESET message handlers


