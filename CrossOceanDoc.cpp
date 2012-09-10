// CrossOceanDoc.cpp : implementation of the CCrossOceanDoc class
//

#include "stdafx.h"
#include "CrossOcean.h"

#include "CrossOceanDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanDoc

IMPLEMENT_DYNCREATE(CCrossOceanDoc, CDocument)

BEGIN_MESSAGE_MAP(CCrossOceanDoc, CDocument)
	//{{AFX_MSG_MAP(CCrossOceanDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanDoc construction/destruction

CCrossOceanDoc::CCrossOceanDoc()
{
	// TODO: add one-time construction code here

}

CCrossOceanDoc::~CCrossOceanDoc()
{
}

BOOL CCrossOceanDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCrossOceanDoc serialization

void CCrossOceanDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanDoc diagnostics

#ifdef _DEBUG
void CCrossOceanDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCrossOceanDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCrossOceanDoc commands
