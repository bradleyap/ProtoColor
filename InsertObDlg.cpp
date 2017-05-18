// InsertObDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Serio.h"
#include "InsertObDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertObDlg dialog


CInsertObDlg::CInsertObDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertObDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertObDlg)
	m_nBoth = FALSE;
	m_nDisabIndex = FALSE;
	m_nFontSel = _T("");
	m_nHdr = _T("");
	m_nLab = _T("");
	m_Per = FALSE;
	m_PosEd = -1;
	m_NoSym = FALSE;
	m_IDBlock = FALSE;
	m_IDCBlock = FALSE;
	m_IDCell = FALSE;
	m_IDCol = FALSE;
	m_IDRow = FALSE;
	//}}AFX_DATA_INIT
}


void CInsertObDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertObDlg)
	DDX_Check(pDX, IDC_BOTH_S_P, m_nBoth);
	DDX_Check(pDX, IDC_DISAB_IND, m_nDisabIndex);
	DDX_Text(pDX, IDC_FONT_INS, m_nFontSel);
	DDX_CBString(pDX, IDC_HDR_REGIS, m_nHdr);
	DDX_CBString(pDX, IDC_LABEL_REGIS, m_nLab);
	DDX_Check(pDX, IDC_PER_ONLY, m_Per);
	DDX_Radio(pDX, IDC_POS_EDIT, m_PosEd);
	DDX_Check(pDX, IDC_NO_SYM, m_NoSym);
	DDX_Check(pDX, IDC_ID_BLOCK, m_IDBlock);
	DDX_Check(pDX, IDC_ID_CBLOCK, m_IDCBlock);
	DDX_Check(pDX, IDC_ID_CELL, m_IDCell);
	DDX_Check(pDX, IDC_ID_COL, m_IDCol);
	DDX_Check(pDX, IDC_ID_ROW, m_IDRow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertObDlg, CDialog)
	//{{AFX_MSG_MAP(CInsertObDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertObDlg message handlers
