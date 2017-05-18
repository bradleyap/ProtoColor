// PanelStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "PanelStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanelStatic

CPanelStatic::CPanelStatic()
{
}

CPanelStatic::~CPanelStatic()
{
}


BEGIN_MESSAGE_MAP(CPanelStatic, CStatic)
	//{{AFX_MSG_MAP(CPanelStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanelStatic message handlers

void CPanelStatic::SetPenColor(COLORREF color)
{
	m_pColor = color;

}
void CPanelStatic::SetBrushColor(COLORREF color)
{
	m_bColor = color;
}

void CPanelStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CPen* pOldPen;
	CPen pen;
	CBrush* oldBr;
	CBrush br;
	if(br.CreateSolidBrush(m_bColor))
	{
		oldBr = dc.SelectObject(&br);
	}
	if(pen.CreatePen(PS_SOLID,2,m_pColor))
	{
		pOldPen = dc.SelectObject(&pen);
	}
	CRect r;
	GetClientRect(r);
	dc.Rectangle(r);
	dc.SelectObject(pOldPen);
	dc.SelectObject(oldBr);

	
	// Do not call CStatic::OnPaint() for painting messages
}
