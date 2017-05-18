// IndexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Serio.h"
#include "IndexDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIndexDlg dialog


CIndexDlg::CIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIndexDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIndexDlg)
	m_Bot = FALSE;
	m_Left = FALSE;
	m_Right = FALSE;
	m_Anchor = _T("");
	m_Top = FALSE;
	//}}AFX_DATA_INIT
}


void CIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIndexDlg)
	DDX_Check(pDX, IDC_BOTTOM, m_Bot);
	DDX_Check(pDX, IDC_LEFT, m_Left);
	DDX_Check(pDX, IDC_RIGHT, m_Right);
	DDX_Text(pDX, IDC_STATIC_CELL, m_Anchor);
	DDX_Check(pDX, IDC_TOP, m_Top);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIndexDlg, CDialog)
	//{{AFX_MSG_MAP(CIndexDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIndexDlg message handlers
