// CrossOceanView.h : interface of the CCrossOceanView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CROSSOCEANVIEW_H__167F43ED_45DD_405A_A0A8_B613FBCD1623__INCLUDED_)
#define AFX_CROSSOCEANVIEW_H__167F43ED_45DD_405A_A0A8_B613FBCD1623__INCLUDED_

#include "MyFish.h"	// Added by ClassView
#include "Fish.h"	// Added by ClassView
#include "FreeFish.h"	// Added by ClassView
#include "GAMESET.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCrossOceanView : public CView
{
protected: // create from serialization only
	CCrossOceanView();
	DECLARE_DYNCREATE(CCrossOceanView)

// Attributes
public:
	CCrossOceanDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrossOceanView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_level;
	int m_fishnum;
	void OnDrawScore(CDC *pDC, long dx, long dy, int score);
	CBitmap m_scorebmp;
	CMyFish myFish[4];
	CFreeFish freeFish[20];
	void TransparentBitmap(HDC hdc, HBITMAP hBitmap,short xStart, short yStart, short xadd,short yadd, COLORREF cTransparentColor);
	CBitmap m_bkimg;
	virtual ~CCrossOceanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCrossOceanView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPause();
	afx_msg void OnStart();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnGameset();
	afx_msg void OnPlayagain();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CrossOceanView.cpp
inline CCrossOceanDoc* CCrossOceanView::GetDocument()
   { return (CCrossOceanDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CROSSOCEANVIEW_H__167F43ED_45DD_405A_A0A8_B613FBCD1623__INCLUDED_)
