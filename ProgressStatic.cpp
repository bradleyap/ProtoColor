// ProgressStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "ProgressStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressStatic

CProgressStatic::CProgressStatic()
{
	m_backGround = RGB(207,207,197);
	//m_progressColor = RGB(135,135,240);lavender
	m_progressColor = RGB(0,128,128);
	m_currentPixelWidth = 0;
	m_prevPixelWidth = 0;
	firstTimeThrough = TRUE;
}

CProgressStatic::~CProgressStatic()
{
}


BEGIN_MESSAGE_MAP(CProgressStatic, CStatic)
	//{{AFX_MSG_MAP(CProgressStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressStatic message handlers

void CProgressStatic::SetProgressColor(COLORREF  clr)
{
	m_progressColor = clr;
	CRect rec;
	GetClientRect(&rec);
	InvalidateRect(&rec);
}

void CProgressStatic::SetStartColor(COLORREF clr)
{
	m_backGround = clr;
	CRect rec;
	GetClientRect(&rec);
	InvalidateRect(&rec);
}

void CProgressStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	/*
	CRect rec;
	GetClientRect(&rec);

	//brush code
	CBrush bkgBr;
	bkgBr.CreateSolidBrush(m_backGround);
	CBrush* oldBr = dc.SelectObject(&bkgBr); 

	//pen code
	CPen bkgPen;
	bkgPen.CreatePen(PS_SOLID,2,m_backGround);
	CPen* oldPen = dc.SelectObject(&bkgPen);

	dc.Rectangle(rec);
	
	if(m_currentPixelWidth!=0)
	{
		CBrush progBr;
		progBr.CreateSolidBrush(m_progressColor);
		dc.SelectObject(&progBr);

		CPen progPen;
		progPen.CreatePen(PS_SOLID,2,m_progressColor);
		dc.SelectObject(&progPen);

		//adjust client rect
		rec.right = m_currentPixelWidth;
		dc.Rectangle(rec);
		
	}

	dc.SelectObject(oldBr);
	dc.SelectObject(oldPen);
*/
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CProgressStatic::GetStatusIndicatorArea(CRect* clientArea)
{
	GetClientRect(clientArea);
}

void CProgressStatic::UpdateStatusRegion(unsigned long nuPixLen)
{
	m_currentPixelWidth = nuPixLen;
	UpdateWindow();
}

void CProgressStatic::ExplicitWrite()
{
	
	CDC* dc = GetDC();
	CRect rec;
	GetClientRect(&rec);

	//brush code
	CBrush bkgBr;
	bkgBr.CreateSolidBrush(m_backGround);
	CBrush* oldBr = dc->SelectObject(&bkgBr); 

	//pen code
	CPen bkgPen;
	bkgPen.CreatePen(PS_SOLID,2,m_progressColor);
	CPen* oldPen = dc->SelectObject(&bkgPen);

	if(firstTimeThrough)dc->Rectangle(rec);
	firstTimeThrough = FALSE;

	dc->SelectObject(oldBr);
	dc->SelectObject(oldPen);


	if(m_currentPixelWidth > (m_prevPixelWidth + 0))
	{
		CBrush progBr;
		progBr.CreateSolidBrush(m_progressColor);
		oldBr = dc->SelectObject(&progBr);

		CPen progPen;
		progPen.CreatePen(PS_SOLID,2,m_progressColor);
		oldPen = dc->SelectObject(&progPen);

		//adjust client rect
		rec.left = m_prevPixelWidth;
		m_prevPixelWidth = m_currentPixelWidth;
		rec.right = m_currentPixelWidth;
		dc->Rectangle(rec);

		dc->SelectObject(oldBr);
		dc->SelectObject(oldPen);
	}

	ReleaseDC(dc);
}
