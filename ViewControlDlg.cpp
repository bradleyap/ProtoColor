// ViewControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "SerioDoc.h"
#include "ViewControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define REFUSE_FOCUS_CODE 2222

/////////////////////////////////////////////////////////////////////////////
// CViewControlDlg dialog


CViewControlDlg::CViewControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewControlDlg)
	m_curPage = 0;
	//}}AFX_DATA_INIT
	m_refuseFocus = 0;
	m_closePromptedByMenu = FALSE;
}


void CViewControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewControlDlg)
	DDX_Text(pDX, IDC_CUR_PAGE_EDIT, m_curPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewControlDlg, CDialog)
	//{{AFX_MSG_MAP(CViewControlDlg)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_CUR_PAGE_EDIT, OnChangeCurPageEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewControlDlg message handlers

void CViewControlDlg::OnClose() 
{
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	if(pDoc!=NULL)
	{
		if(pDoc->m_viewDlg==this)
		{
			if(pDoc->IsViewDlgOn())
			{
				if(!pDoc->m_dViewDlgCloseIsSimulated)
					
				{
					if(!m_closePromptedByMenu)
						pDoc->ToggleViewDlg();
				}
			}
		}
	}
	CDialog::OnClose();
}

void CViewControlDlg::PostNcDestroy() 
{
	delete this;

	CDialog::PostNcDestroy();
}

void CViewControlDlg::OnOK()
{
	DestroyWindow();
}

void CViewControlDlg::OnCancel()
{
	DestroyWindow();
}

void CViewControlDlg::ShutDown()
{
	SendMessage(WM_CLOSE);
}

void CViewControlDlg::OnChangeCurPageEdit() 
{
	UINT nuPage = GetDlgItemInt(IDC_CUR_PAGE_EDIT,NULL,FALSE);
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	if(pDoc->ValidateNewPageView(nuPage))
	{
		m_curPageBuf = m_curPage;
		if(m_curPage!=0)UpdateData(TRUE);
	}
	else UpdateData(FALSE);
	
}

void CViewControlDlg::SignifyCloseByMenu(BOOL startProcess)
{
	if(startProcess)m_closePromptedByMenu = TRUE;
	else m_closePromptedByMenu = FALSE;
}