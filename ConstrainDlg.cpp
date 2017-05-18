// ConstrainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Serio.h"
#include "ConstrainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConstrainDlg dialog


CConstrainDlg::CConstrainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConstrainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstrainDlg)
	m_nBlockHeight = FALSE;
	m_nBlockRatio = FALSE;
	m_nBlockWidth = FALSE;
	m_nBottomMarg = FALSE;
	m_nBot2Right = FALSE;
	m_nCBlockHeight = FALSE;
	m_nCBlockRatio = FALSE;
	m_nCBlockWidth = FALSE;
	m_nCellCount = FALSE;
	m_nCellHeight = FALSE;
	m_nCellRatio = FALSE;
	m_nCellWidth = FALSE;
	m_nLeftMarg = FALSE;
	m_nLeft2Right = FALSE;
	m_nPageCount = FALSE;
	m_nRightMarg = FALSE;
	m_nTopMarg = FALSE;
	m_nTop2Bot = FALSE;
	m_nTop2Left = FALSE;
	m_nConstrMode = _T("");
	m_nModeContext = _T("");
	//}}AFX_DATA_INIT
}


void CConstrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstrainDlg)
	DDX_Check(pDX, IDC_BLOCK_HEIGHT_L, m_nBlockHeight);
	DDX_Check(pDX, IDC_BLOCK_RATIO_L, m_nBlockRatio);
	DDX_Check(pDX, IDC_BLOCK_WIDTH_L, m_nBlockWidth);
	DDX_Check(pDX, IDC_BOT_MARG_L, m_nBottomMarg);
	DDX_Check(pDX, IDC_BOT2_RIGHT_L, m_nBot2Right);
	DDX_Check(pDX, IDC_C_BLOCK_HEIGHT_L, m_nCBlockHeight);
	DDX_Check(pDX, IDC_C_BLOCK_RATIO_L, m_nCBlockRatio);
	DDX_Check(pDX, IDC_C_BLOCK_WIDTH_L, m_nCBlockWidth);
	DDX_Check(pDX, IDC_CELL_COUNT_L, m_nCellCount);
	DDX_Check(pDX, IDC_CELL_HEIGHT_L, m_nCellHeight);
	DDX_Check(pDX, IDC_CELL_RATIO_L, m_nCellRatio);
	DDX_Check(pDX, IDC_CELL_WIDTH_L, m_nCellWidth);
	DDX_Check(pDX, IDC_LEFT_MARG_L, m_nLeftMarg);
	DDX_Check(pDX, IDC_LEFT2_RIGHT_L, m_nLeft2Right);
	DDX_Check(pDX, IDC_PAGE_COUNT_L, m_nPageCount);
	DDX_Check(pDX, IDC_RIGHT_MARG_L, m_nRightMarg);
	DDX_Check(pDX, IDC_TOP_MARG_L, m_nTopMarg);
	DDX_Check(pDX, IDC_TOP2_BOT_L, m_nTop2Bot);
	DDX_Check(pDX, IDC_TOP2_LEFT_L, m_nTop2Left);
	DDX_CBString(pDX, IDC_CONSTRAIN_MODE, m_nConstrMode);
	DDX_CBString(pDX, IDC_MODE_USAGE, m_nModeContext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstrainDlg, CDialog)
	//{{AFX_MSG_MAP(CConstrainDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstrainDlg message handlers

BOOL CConstrainDlg::OnInitDialog() 
{
	CComboBox *pModeBox = (CComboBox *)GetDlgItem( IDC_CONSTRAIN_MODE);
		ASSERT(pModeBox != NULL);
	pModeBox->AddString("Proportional");
	pModeBox->AddString("Rectangle Size" );
	pModeBox->AddString("Freeze Blocks" );

	CComboBox *pUsageBox = (CComboBox *)GetDlgItem( IDC_MODE_USAGE);
		ASSERT(pUsageBox != NULL);
	pUsageBox->AddString("default");
	pUsageBox->AddString("margin resize");

	//UpdateData(TRUE);

	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
