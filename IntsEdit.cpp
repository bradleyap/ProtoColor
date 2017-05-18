// IntsEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntsEdit

CIntsEdit::CIntsEdit()
{
}

CIntsEdit::~CIntsEdit()
{
}


BEGIN_MESSAGE_MAP(CIntsEdit, CEdit)
	//{{AFX_MSG_MAP(CIntsEdit)
	ON_WM_CHAR()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntsEdit message handlers

void CIntsEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( (nChar < 0x20) || ( (nChar >= '0') && (nChar <= '9'))
	|| nChar==9)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		::MessageBeep(0xFFFFFFFF);
	}
	
	//CEdit::OnChar(nChar, nRepCnt, nFlags);
}

UINT CIntsEdit::OnGetDlgCode() 
{
	return DLGC_WANTCHARS;//DLGC_WANTALLKEYS|DLGC_WANTCHARS;
}
