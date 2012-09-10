// CrossOceanDoc.h : interface of the CCrossOceanDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CROSSOCEANDOC_H__AF7506FC_95F1_4FCF_A34F_22E1DCCEE76A__INCLUDED_)
#define AFX_CROSSOCEANDOC_H__AF7506FC_95F1_4FCF_A34F_22E1DCCEE76A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCrossOceanDoc : public CDocument
{
protected: // create from serialization only
	CCrossOceanDoc();
	DECLARE_DYNCREATE(CCrossOceanDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrossOceanDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCrossOceanDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCrossOceanDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CROSSOCEANDOC_H__AF7506FC_95F1_4FCF_A34F_22E1DCCEE76A__INCLUDED_)
