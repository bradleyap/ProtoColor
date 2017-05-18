// EulaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "EulaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEulaDlg dialog


CEulaDlg::CEulaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEulaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEulaDlg)
	m_text = _T("");
	//}}AFX_DATA_INIT
}


void CEulaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEulaDlg)
	DDX_Text(pDX, IDC_EULA_EDIT, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEulaDlg, CDialog)
	//{{AFX_MSG_MAP(CEulaDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEulaDlg message handlers

BOOL CEulaDlg::OnInitDialog() 
{
	CString lb = "lb";
	lb.SetAt(0,13);
	lb.SetAt(1,10);
	m_text = "This software is free to use, copy and modify as users see fit, with the following provisions:";
	m_text += lb;
	m_text += lb;
	m_text += "Proper compliance with all Microsoft MFC licensing should be observed";
	m_text += lb;
	m_text += "Coders and contributors to code, who are not writing intentionally malicious code, insofar as it is with the paramters of unambiguous law, shall in no wise be held responsible for damages arising out of the use or misuse of this software";
	m_text += lb;
	m_text += lb;
	/*	

	CEdit* ed = (CEdit*)GetDlgItem(IDC_EULA_EDIT);
	ed->SetReadOnly();*/
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
