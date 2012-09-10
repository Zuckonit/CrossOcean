// FreeFish.cpp: implementation of the CFreeFish class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrossOcean.h"
#include "FreeFish.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFreeFish::CFreeFish()
{

}

CFreeFish::~CFreeFish()
{

}

void CFreeFish::freeMove()
{
        Move();
		if(m_curPos.x <= 0||m_curPos.x >= 744)
		    m_moveDirection = -m_moveDirection;
}
