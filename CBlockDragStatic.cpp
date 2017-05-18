// CBlockDragStatic.cpp : implementation file
//

#include "stdafx.h"
#include "SerioDoc.h"
#include "ProtoColor.h"
#include "CBlockDragStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCBlockDragStatic

CCBlockDragStatic::CCBlockDragStatic()
{
}

CCBlockDragStatic::~CCBlockDragStatic()
{
}


BEGIN_MESSAGE_MAP(CCBlockDragStatic, CStatic)
	//{{AFX_MSG_MAP(CCBlockDragStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBlockDragStatic message handlers

void CCBlockDragStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnLButtonDown(nFlags, point);
}

void CCBlockDragStatic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnLButtonUp(nFlags, point);
}

void CCBlockDragStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMouseMove(nFlags, point);
}

void CCBlockDragStatic::OnPaint() 
{
	CPaintDC dc(this);	
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	CRect r;
	GetClientRect(&r);
	CBrush* olbr;
	olbr = dc.SelectObject(&brush);
	dc.Rectangle(r);

	if(m_calledByDlg)
	{
		BOOL stopLoop;
		for( stopLoop=FALSE;stopLoop==FALSE; )
		{
			int response = AfxMessageBox("Add 2 rows or 3 columns",MB_OKCANCEL);
//			if(dlg.DoModal()==IDOK)
//			{
//				if(dlg.m_yes)ans = 1;
//				if(dlg.m_no)ans = 2;
//				canDo = TRUE;
//			}
			if(response==IDCANCEL)stopLoop = TRUE;
		}
		m_calledByDlg = FALSE;

	}

	// Do not call CStatic::OnPaint() for painting messages
}

float CCBlockDragStatic::GetBlockHeight()
{
	float bh;
	return bh;
}

float CCBlockDragStatic::GetBlockWidth()
{
	float bw;
	return bw;
}

float CCBlockDragStatic::GetFrameW()
{
	float fw;
	return fw;
}

float CCBlockDragStatic::GetFrameH()
{
	float fh;
	return fh;
}
