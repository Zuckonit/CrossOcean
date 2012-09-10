// MyFish.h: interface for the CMyFish class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFISH_H__96140F38_6C77_46DE_8705_E756206CADC7__INCLUDED_)
#define AFX_MYFISH_H__96140F38_6C77_46DE_8705_E756206CADC7__INCLUDED_
#include "FreeFish.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Fish.h"

class CMyFish : public CFish
{
public:
	int m_life;
	void EatFish(CFreeFish &freeFish);
	CMyFish();
	virtual ~CMyFish();

};

#endif // !defined(AFX_MYFISH_H__96140F38_6C77_46DE_8705_E756206CADC7__INCLUDED_)
