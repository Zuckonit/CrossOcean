// FreeFish.h: interface for the CFreeFish class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FREEFISH_H__C9122E70_547C_4267_B471_BDA0929B65BA__INCLUDED_)
#define AFX_FREEFISH_H__C9122E70_547C_4267_B471_BDA0929B65BA__INCLUDED_
#include "Fish.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFreeFish  : public CFish
{
public:
	void freeMove();
	CFreeFish();
	virtual ~CFreeFish();
};

#endif // !defined(AFX_FREEFISH_H__C9122E70_547C_4267_B471_BDA0929B65BA__INCLUDED_)
