// MyEdit.cpp : implementation file
//
#include "stdafx.h"
#include "ProtoColor.h"
#include "SerioDoc.h"
#include "CellAspectsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit
class CCellAspects;

IMPLEMENT_DYNCREATE(CMyEdit,CEdit)


CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	ON_WM_GETDLGCODE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

UINT CMyEdit::OnGetDlgCode() 
{
	return DLGC_WANTCHARS;//DLGC_WANTALLKEYS|DLGC_WANTCHARS;
}

void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( (nChar < 0x20) || ( (nChar >= '0') && (nChar <= '9'))
		|| nChar==46 || nChar==9)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		::MessageBeep(0xFFFFFFFF);
	}
}
