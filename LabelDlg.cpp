// LabelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "LabelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLabelDlg dialog


CLabelDlg::CLabelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLabelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLabelDlg)
	m_Bot = FALSE;
	m_Left = FALSE;
	m_Right = FALSE;
	m_Top = FALSE;
	//}}AFX_DATA_INIT
}


void CLabelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLabelDlg)
	DDX_Check(pDX, IDC_L_BOTTOM, m_Bot);
	DDX_Check(pDX, IDC_L_LEFT, m_Left);
	DDX_Check(pDX, IDC_L_RIGHT, m_Right);
	DDX_Check(pDX, IDC_L_TOP, m_Top);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLabelDlg, CDialog)
	//{{AFX_MSG_MAP(CLabelDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLabelDlg message handlers
