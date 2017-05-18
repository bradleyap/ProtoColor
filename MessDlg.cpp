// MessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "MessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessDlg dialog


CMessDlg::CMessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_yes = FALSE;
	m_no = FALSE;
}


void CMessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessDlg, CDialog)
	//{{AFX_MSG_MAP(CMessDlg)
	ON_BN_CLICKED(IDC_NO_BN, OnNoBn)
	ON_BN_CLICKED(IDC_YES_BN, OnYesBn)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessDlg message handlers

void CMessDlg::OnNoBn() 
{
	m_no = TRUE;
	CDialog::OnOK();
}

void CMessDlg::OnYesBn() 
{
	m_yes = TRUE;
	CDialog::OnOK();
}

void CMessDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	SetDlgItemText(IDC_MESS_STATIC,str);	
	// Do not call CDialog::OnPaint() for painting messages
}
