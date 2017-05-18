// StrikeStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "StrikeStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrikeStatic

CStrikeStatic::CStrikeStatic()
{
	m_noText = TRUE;
	m_panelCall = FALSE;
}

CStrikeStatic::~CStrikeStatic()
{
}


BEGIN_MESSAGE_MAP(CStrikeStatic, CStatic)
	//{{AFX_MSG_MAP(CStrikeStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStrikeStatic message handlers

void CStrikeStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CPen* pOldPen;
	CPen pen;
	CBrush* oldBr;
	CBrush br;
	if(br.CreateSolidBrush(GetSysColor(COLOR_3DFACE)))
	{
		oldBr = dc.SelectObject(&br);
	}
	if(!m_panelCall)
	{
		if(pen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DFACE)))
		{
			pOldPen = dc.SelectObject(&pen);
		}
	}
	if(m_panelCall)
	{
		if(pen.CreatePen(PS_SOLID,2,GetSysColor(COLOR_BACKGROUND)))
		{
			pOldPen = dc.SelectObject(&pen);
		}
	}
	CRect r;
	GetClientRect(r);
	dc.Rectangle(r);
	dc.SelectObject(pOldPen);
	dc.SelectObject(oldBr);

	CString str;
	if(!m_noText && !m_retry)str = CString("REMOVE");
	if(!m_noText && m_retry)str = CString("RETRY");
	if(m_noText)str = CString("");
	dc.SetBkColor(GetSysColor(COLOR_3DFACE));//(m_bColor);
	if(!m_retry)dc.SetTextColor(RGB(255,0,0));//(m_pColor);
	if(m_retry)dc.SetTextColor(RGB(75,75,75));
	//if(!m_noText)dc.DrawText(str,-1,r,DT_CALCRECT);
	if(!m_panelCall)dc.DrawText(str,r,DT_SINGLELINE);
	// Do not call CStatic::OnPaint() for painting messages

}

void CStrikeStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnLButtonDown(nFlags, point);
}

void CStrikeStatic::SetBrushColor(COLORREF color)
{
	m_bColor = color;
}

void CStrikeStatic::SetPenColor(COLORREF color)
{
	m_pColor = color;
}

void CStrikeStatic::EnableText(BOOL text)
{
	if(text)m_noText = FALSE;
	if(!text)m_noText = TRUE;
}

void CStrikeStatic::IndicateRemove()
{
	m_retry = FALSE;
	InvalidateRect(NULL,FALSE);
}

void CStrikeStatic::IndicateRetry()
{
	m_retry = TRUE;
	InvalidateRect(NULL,FALSE);
}
