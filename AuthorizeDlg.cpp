// AuthorizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "AuthorizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuthorizeDlg dialog


CAuthorizeDlg::CAuthorizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAuthorizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAuthorizeDlg)
	m_key = _T("");
	//}}AFX_DATA_INIT
	m_codeValid = FALSE;
}


void CAuthorizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuthorizeDlg)
	DDX_Text(pDX, IDC_KEY_EDIT, m_key);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuthorizeDlg, CDialog)
	//{{AFX_MSG_MAP(CAuthorizeDlg)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuthorizeDlg message handlers

void CAuthorizeDlg::OnClose() 
{		
	CDialog::OnClose();
}

void CAuthorizeDlg::OnDestroy() 
{
	if(m_key=="77712")m_codeValid = TRUE;
	CDialog::OnDestroy();
}
