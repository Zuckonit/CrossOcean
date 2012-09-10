// Fish.h: interface for the CFish class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FISH_H__D4A37604_5DD1_43D3_879F_5E372F60E4C7__INCLUDED_)
#define AFX_FISH_H__D4A37604_5DD1_43D3_879F_5E372F60E4C7__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFish  
{
public:
	int m_score;
	void Move();
     int m_size;
	int m_moveDirection;
	CFish();
	
	virtual ~CFish();
    CBitmap m_image[2];
	CPoint m_curPos;
	bool isAlive;
};

#endif // !defined(AFX_FISH_H__D4A37604_5DD1_43D3_879F_5E372F60E4C7__INCLUDED_)
