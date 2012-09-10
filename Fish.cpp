// Fish.cpp: implementation of the CFish class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrossOcean.h"
#include "Fish.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFish::CFish()
{
   isAlive = true;
   m_score = 0;
}

CFish::~CFish()
{

}


void CFish::Move()
{
	//鱼游动的函数实现，鱼越大速度越慢
	switch(m_moveDirection)
	{
	case -1:
		if(m_curPos.x > 0)
			m_curPos.x -= (15-m_size*2);
		break;
	case 1:
		if(m_curPos.x < 744)
			m_curPos.x += (15-m_size*2);
		break;
	case -2:
		if(m_curPos.y>0)
			m_curPos.y -= (15-m_size*2);
		break;
	case 2:
		if(m_curPos.y < 447)
			m_curPos.y += (15-m_size*2);
		break;
	}

}
