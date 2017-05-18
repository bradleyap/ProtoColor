// Flash.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "Flash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ESC 27
#define SPACE 32
#define ENTER 13

/////////////////////////////////////////////////////////////////////////////
// CFlash dialog


CFlash::CFlash(CWnd* pParent /*=NULL*/)
	: CDialog(CFlash::IDD, pParent)
{
	m_killFocus = FALSE;
	//{{AFX_DATA_INIT(CFlash)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFlash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlash)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlash, CDialog)
	//{{AFX_MSG_MAP(CFlash)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlash message handlers

void CFlash::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFlash::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap bmp,*obmp;
	CDC memdc;
	bmp.LoadBitmap(IDB_SOLDIER);
	memdc.CreateCompatibleDC(&dc);
	obmp = memdc.SelectObject(&bmp);
	dc.BitBlt(0,0,318,272,&memdc,0,0,SRCCOPY);
	memdc.SelectObject(obmp);

	//SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW));	
	ShowCursor(FALSE);

	SYSTEMTIME st;
	GetSystemTime(&st);

	int curSeconds = st.wSecond;
	int elapsedSeconds = 0;
	UINT flags = QS_KEY;
	DWORD msgs;
	MSG msg;

	while(elapsedSeconds<6)
	{
		GetSystemTime(&st);
		if(curSeconds!=st.wSecond)
		{
			curSeconds = st.wSecond;
			elapsedSeconds++;
		}
		msgs = GetQueueStatus(flags);
		if(HIWORD(msgs)==(QS_KEY | HIWORD(msgs)))
		{
			PeekMessage(&msg,this->m_hWnd,WM_KEYDOWN,WM_KEYDOWN,PM_REMOVE);
			if(msg.wParam==ESC)break;
			if(msg.wParam==SPACE)break;
			if(msg.wParam==ENTER)break;
			if(m_killFocus)break;
		}
	}

	SendMessage(WM_CLOSE);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CFlash::OnSize(UINT nType, int cx, int cy) 
{
	//CRect r;
	//GetWindowRect(r);
	//r.bottom = r.top + cy;
	//r.right = r.left + cx;
	//if(cx!=318 || cy!=272)MoveWindow(r,0);
	
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CFlash::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	m_killFocus = TRUE;
	
}
