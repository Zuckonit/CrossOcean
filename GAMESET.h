#if !defined(AFX_GAMESET_H__3511A854_BA21_4988_9141_11E786D48F47__INCLUDED_)
#define AFX_GAMESET_H__3511A854_BA21_4988_9141_11E786D48F47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GAMESET.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GAMESET dialog

class GAMESET : public CDialog
{
// Construction
public:
	GAMESET(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GAMESET)
	enum { IDD = IDD_DIALOG1 };
	int		m_difficulty;
	int		m_num;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GAMESET)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GAMESET)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMESET_H__3511A854_BA21_4988_9141_11E786D48F47__INCLUDED_)
