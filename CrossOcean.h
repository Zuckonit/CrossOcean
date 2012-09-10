// CrossOcean.h : main header file for the CROSSOCEAN application
//

#if !defined(AFX_CROSSOCEAN_H__20DEBD67_304C_4E3B_83BD_6A7BDE9A9547__INCLUDED_)
#define AFX_CROSSOCEAN_H__20DEBD67_304C_4E3B_83BD_6A7BDE9A9547__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanApp:
// See CrossOcean.cpp for the implementation of this class
//

class CCrossOceanApp : public CWinApp
{
public:
	CCrossOceanApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrossOceanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCrossOceanApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CROSSOCEAN_H__20DEBD67_304C_4E3B_83BD_6A7BDE9A9547__INCLUDED_)
