// MyOtherEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyOtherEdit

CMyOtherEdit::CMyOtherEdit()
{
	m_go = TRUE;
}

CMyOtherEdit::~CMyOtherEdit()
{
}


BEGIN_MESSAGE_MAP(CMyOtherEdit, CEdit)
	//{{AFX_MSG_MAP(CMyOtherEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyOtherEdit message handlers

void CMyOtherEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	

	CString str;
	int id = GetDlgCtrlID();
	CDialog* dlg = (CDialog*)GetParent();
	dlg->GetDlgItemText(id,str);
	int lineLen = LineLength(-1);
	BOOL weHaveDecimal = FALSE;

	int i;
	int len = str.GetLength();
	for(i=0;i<len;i++)
	{
		if(str.GetAt(i)=='.')weHaveDecimal = TRUE;
	}
	m_go = TRUE;
	m_nChar = nChar;
	int charIndx = CharFromPos(GetCaretPos());
	if(nChar==46 && !weHaveDecimal)m_go = FALSE;	
	if(nChar==48)
	{
		//does the zero precede everything?
		if(charIndx==0)
			m_go = FALSE;
		//is the zero last
		if(len<=charIndx)
		{
			//if so, is there a decimal
			if(weHaveDecimal)m_go = FALSE;
			//otherwise
			else m_go = TRUE;
		}
	}
	CEdit::OnChar(nChar, nRepCnt, nFlags);

}
