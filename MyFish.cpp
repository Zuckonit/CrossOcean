// MyFish.cpp: implementation of the CMyFish class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrossOcean.h"
#include "MyFish.h"
#include <mmsystem.h>

#include <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMyFish::CMyFish()
{
	m_curPos.x = 744/2;
	m_curPos.y = 447/2;
	m_size = 1;
	m_life = 3;
}

CMyFish::~CMyFish()
{
	
}

extern int curSize;
extern int total_score;


void CMyFish::EatFish(CFreeFish &freeFish)
{
	srand((unsigned)time(NULL));
	if (isAlive&&freeFish.isAlive&&m_size > freeFish.m_size&&abs(freeFish.m_curPos.y - m_curPos.y) <= 18)
	{
		switch (freeFish.m_size)
		{
		case 0:
			{
				
				
				if ((m_curPos.x + 81 >= freeFish.m_curPos.x) &&(m_curPos.x + 81 <= freeFish.m_curPos.x + 62) )
				{
					mciSendString("play ./musics/bite1.wav"," ",0,0);
					freeFish.isAlive = false;
					m_score += 10;
					total_score += 10;
					if(m_score >= 60)
					{
						if(m_size < 4)
							m_size++;
						m_score = 0;
					}
				}
				break;
			}
		case 2:
			{
				
				if ((m_curPos.x + 81 >= freeFish.m_curPos.x) &&(m_curPos.x + 81 <= freeFish.m_curPos.x + 123) )
				{
					mciSendString("play ./musics/bite2.wav"," ",0,0);
					freeFish.isAlive = false;
					m_score += 15;
					total_score += 15;
					if(m_score >= 60)
					{
						if(m_size < 4)
							m_size++;
						m_score = 0;
					}
				}
				break;
			}
		case 3:
			{
				if ((m_curPos.x + 81 >= freeFish.m_curPos.x) &&(m_curPos.x + 81 <= freeFish.m_curPos.x + 198) )
				{
					mciSendString("play ./musics/bite3.wav"," ",0,0);
					freeFish.isAlive = false;
					m_score += 20;
					total_score += 20;
					if(m_score >= 60)
					{
						if(m_size < 4)
							m_size++;
						m_score = 0;
					}
				}
				break;
			}
			
		}
		curSize = m_size;
		if (!freeFish.isAlive)  //每有一条鱼被吃就另外产生一条新的鱼
		{
			srand((unsigned)time(NULL));
			freeFish.isAlive = true;
			
			
			(rand()%2 == 1)?freeFish.m_moveDirection = 1:freeFish.m_moveDirection = -1;
			(rand()%744 >= 744/2)?freeFish.m_curPos.x = 744:freeFish.m_curPos.x = 0;
		}
	}
}
