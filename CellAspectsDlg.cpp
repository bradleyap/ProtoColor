// CellAspectsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "SerioDoc.h"
#include "CellAspectsDlg.h"
#include <sstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCellAspectsDlg dialog


CCellAspectsDlg::CCellAspectsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCellAspectsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCellAspectsDlg)
	m_nCellRatio = FALSE;
	m_nUnits = _T("inches");
	m_nUnits2 = _T("inches");
	m_nUnits3 = _T("inches");
	m_nUnits4 = _T("inches");
	m_nUnits5 = _T("inches");
	m_nUnits6 = _T("inches");
	m_CellHeightVal = 0.0f;
	m_BlockHeightVal = 0.0f;
	m_BlockWidthVal = 0.0f;
	m_CBlockHeightVal = 0.0f;
	m_CBlockWidthVal = 0.0f;
	m_nDrawOften = 0;
	m_Reflect = FALSE;
	m_nBlockCount = 0;
	m_nCBlockCount = 0;
	m_nColCount = 0;
	m_nRowCount = 0;
	m_CnsBlock = FALSE;
	m_CnsCBlock = FALSE;
	m_CnsCol = FALSE;
	m_CnsRow = FALSE;
	m_F_BLK = 0.0f;
	m_F_CBLK = 0.0f;
	m_F_COL = 0.0f;
	m_F_ROW = 0.0f;
	m_IntSync = FALSE;
	m_CellWidthVal = 0.0f;
	//}}AFX_DATA_INIT

	m_rectWchange = FALSE;
	m_rectHchange = FALSE;
	m_blockWchange = FALSE;
	m_blockHchange = FALSE;
	m_cBlockWchange = FALSE;
	m_cBlockHchange = FALSE;
	m_colsChange = FALSE;
	m_rowsChange = FALSE;
	m_bCountChange = FALSE;
	m_cBCountChange = FALSE;
	m_colCchange = FALSE;
	m_rowCchange = FALSE;
	m_rowFrqChange = FALSE;
	m_colFrqChange = FALSE;
	m_blkFrqChange = FALSE;
	m_cBlkFrqChange = FALSE;
	m_intTest = FALSE;

	m_enableRowFreqWindow = FALSE;
	m_enableColFreqWindow = FALSE;
	m_enableBlockFreqWindow = FALSE;
	m_enableCBlockFreqWindow = FALSE;

	
	m_Bn = FALSE;
	m_Bn2 = FALSE;
	m_Bn3 = FALSE;
	m_Bn4 = FALSE;
	m_Bn5 = FALSE;
	m_Bn6 = FALSE;
	m_Bn7 = FALSE;
	m_Bn8 = FALSE;
	m_Bn9 = FALSE;
	m_Bn10 = FALSE;
	m_Bn11 = FALSE;
	m_Bn12 = FALSE;
	m_Bn13 = FALSE;
	m_Bn14 = FALSE;
	m_Bn15 = FALSE;
	m_Bn16 = FALSE;

}


void CCellAspectsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCellAspectsDlg)
	DDX_Control(pDX, IDC_CELL_W, m_CellWidth);
	DDX_Control(pDX, IDC_ROW_COUNT, m_rowCountCtl);
	DDX_Control(pDX, IDC_COLUMN_COUNT, m_colCountCtl);
	DDX_Control(pDX, IDC_C_BLOCK_COUNT, m_cBlockCountCtl);
	DDX_Control(pDX, IDC_BLOCK_COUNT, m_blockCountCtl);
	DDX_Control(pDX, IDC_FRQ_ROW, m_freqRow);
	DDX_Control(pDX, IDC_FRQ_COL, m_freqCol);
	DDX_Control(pDX, IDC_FRQ_CBLK, m_freqCblock);
	DDX_Control(pDX, IDC_FRQ_BLK, m_freqBlock);
	DDX_Control(pDX, IDC_BLOCK_HEIGHT, m_BlockHeight);
	DDX_Control(pDX, IDC_CNGL_BLOCK_W, m_CBlockWidth);
	DDX_Control(pDX, IDC_CNGL_BLOCK_H, m_CBlockHeight);
	DDX_Control(pDX, IDC_BLOCK_WIDTH, m_BlockWidth);
	DDX_Control(pDX, IDC_CELL_HEIGHT, m_CellHeight);
	DDX_Check(pDX, IDC_CELL_RATIO, m_nCellRatio);
	DDX_CBString(pDX, IDC_UNIT_MEAS_COMB1, m_nUnits);
	DDX_CBString(pDX, IDC_UNIT_MEAS_COMB2, m_nUnits2);
	DDX_CBString(pDX, IDC_UNIT_MEAS_COMB3, m_nUnits3);
	DDX_CBString(pDX, IDC_UNIT_MEAS_COMB4, m_nUnits4);
	DDX_CBString(pDX, IDC_UNIT_MEAS_COMB5, m_nUnits5);
	DDX_CBString(pDX, IDC_UNIT_MEAS_COMB6, m_nUnits6);
	DDX_Text(pDX, IDC_CELL_HEIGHT, m_CellHeightVal);
	DDV_MinMaxFloat(pDX, m_CellHeightVal, 1.e-004f, 100.f);
	DDX_Text(pDX, IDC_BLOCK_HEIGHT, m_BlockHeightVal);
	DDV_MinMaxFloat(pDX, m_BlockHeightVal, 1.e-004f, 100.f);
	DDX_Text(pDX, IDC_BLOCK_WIDTH, m_BlockWidthVal);
	DDV_MinMaxFloat(pDX, m_BlockWidthVal, 1.e-004f, 100.f);
	DDX_Text(pDX, IDC_CNGL_BLOCK_H, m_CBlockHeightVal);
	DDV_MinMaxFloat(pDX, m_CBlockHeightVal, 1.e-004f, 100.f);
	DDX_Text(pDX, IDC_CNGL_BLOCK_W, m_CBlockWidthVal);
	DDV_MinMaxFloat(pDX, m_CBlockWidthVal, 1.e-004f, 100.f);
	DDX_Check(pDX, IDC_FROM_COLOR, m_Reflect);
	DDX_Text(pDX, IDC_BLOCK_COUNT, m_nBlockCount);
	DDV_MinMaxInt(pDX, m_nBlockCount, 1, 1000);
	DDX_Text(pDX, IDC_C_BLOCK_COUNT, m_nCBlockCount);
	DDV_MinMaxInt(pDX, m_nCBlockCount, 1, 1000);
	DDX_Text(pDX, IDC_COLUMN_COUNT, m_nColCount);
	DDV_MinMaxInt(pDX, m_nColCount, 1, 1000);
	DDX_Text(pDX, IDC_ROW_COUNT, m_nRowCount);
	DDX_Check(pDX, IDC_CNS_BLK, m_CnsBlock);
	DDX_Check(pDX, IDC_CNS_CBLK, m_CnsCBlock);
	DDX_Check(pDX, IDC_CNS_COL, m_CnsCol);
	DDX_Check(pDX, IDC_CNS_ROW, m_CnsRow);
	DDX_Text(pDX, IDC_FRQ_BLK, m_F_BLK);
	DDX_Text(pDX, IDC_FRQ_CBLK, m_F_CBLK);
	DDX_Text(pDX, IDC_FRQ_COL, m_F_COL);
	DDX_Text(pDX, IDC_FRQ_ROW, m_F_ROW);
	DDX_Check(pDX, IDC_INT_SYNC, m_IntSync);
	DDX_Text(pDX, IDC_CELL_W, m_CellWidthVal);
	//}}AFX_DATA_MAP
}

//	ON_BN_CLICKED(IDC_BUTTON3, OnCAspectsQuickButton)
BEGIN_MESSAGE_MAP(CCellAspectsDlg, CDialog)
	//{{AFX_MSG_MAP(CCellAspectsDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnCellAspectsHelp)
	ON_BN_CLICKED(IDC_LOCKED17, OnLocked17)
	ON_BN_CLICKED(IDC_LOCKED18, OnLocked18)
	ON_BN_CLICKED(IDC_LOCKED19, OnLocked19)
	ON_BN_CLICKED(IDC_LOCKED20, OnLocked20)
	ON_BN_CLICKED(IDC_LOCKED21, OnLocked21)
	ON_BN_CLICKED(IDC_LOCKED22, OnLocked22)
	ON_BN_CLICKED(IDC_LOCKED23, OnLocked23)
	ON_BN_CLICKED(IDC_LOCKED24, OnLocked24)
	ON_BN_CLICKED(IDC_LOCKED25, OnLocked25)
	ON_BN_CLICKED(IDC_LOCKED26, OnLocked26)
	ON_CBN_SELCHANGE(IDC_UNIT_MEAS_COMB1, OnSelchangeUnitMeasComb1)
	ON_CBN_SELCHANGE(IDC_UNIT_MEAS_COMB2, OnSelchangeUnitMeasComb2)
	ON_CBN_SELCHANGE(IDC_UNIT_MEAS_COMB3, OnSelchangeUnitMeasComb3)
	ON_CBN_SELCHANGE(IDC_UNIT_MEAS_COMB4, OnSelchangeUnitMeasComb4)
	ON_CBN_SELCHANGE(IDC_UNIT_MEAS_COMB5, OnSelchangeUnitMeasComb5)
	ON_CBN_SELCHANGE(IDC_UNIT_MEAS_COMB6, OnSelchangeUnitMeasComb6)
	ON_BN_CLICKED(IDC_JUMP, OnJump)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_CALCULATE, OnCalculate)
	ON_EN_CHANGE(IDC_BLOCK_HEIGHT, OnChangeBlockHeight)
	ON_EN_CHANGE(IDC_BLOCK_WIDTH, OnChangeBlockWidth)
	ON_EN_CHANGE(IDC_C_BLOCK_COUNT, OnChangeCBlockCount)
	ON_EN_CHANGE(IDC_BLOCK_COUNT, OnChangeBlockCount)
	ON_EN_CHANGE(IDC_CELL_HEIGHT, OnChangeCellHeight)
	ON_EN_CHANGE(IDC_CNGL_BLOCK_H, OnChangeCnglBlockH)
	ON_EN_CHANGE(IDC_CNGL_BLOCK_W, OnChangeCnglBlockW)
	ON_EN_CHANGE(IDC_COLUMN_COUNT, OnChangeColumnCount)
	ON_EN_CHANGE(IDC_ROW_COUNT, OnChangeRowCount)
	ON_EN_CHANGE(IDC_CELL_W, OnChangeCellW)
	ON_BN_CLICKED(IDC_CELL_RATIO, OnCellRatio)
	ON_EN_CHANGE(IDC_FRQ_ROW, OnChangeFrqRow)
	ON_EN_CHANGE(IDC_FRQ_COL, OnChangeFrqCol)
	ON_EN_CHANGE(IDC_FRQ_CBLK, OnChangeFrqCblk)
	ON_EN_CHANGE(IDC_FRQ_BLK, OnChangeFrqBlk)
	ON_BN_CLICKED(IDC_CNS_CBLK, OnCnsCblk)
	ON_BN_CLICKED(IDC_CNS_COL, OnCnsCol)
	ON_BN_CLICKED(IDC_CNS_ROW, OnCnsRow)
	ON_BN_CLICKED(IDC_CNS_BLK, OnCnsBlk)
	ON_BN_CLICKED(IDC_INT_SYNC, OnIntSync)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCellAspectsDlg message handlers

void CCellAspectsDlg::OnCellAspectsHelp() 
{
	// TODO: Add your control notification handler code here
	
}

void CCellAspectsDlg::OnCAspectsQuickButton() 
{
	// TODO: Add your control notification handler code here
	
}


BOOL CCellAspectsDlg::OnInitDialog() 
{
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	int color = pDoc->m_dColorMode;
	m_color = color;

	m_LockBn2.AutoLoad(IDC_LOCKED17,this);
	if(!m_TogLock2)m_LockBn2.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_ROW_COUNT);
		pCmbx->EnableWindow(FALSE);
		m_LockBn2.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn3.AutoLoad(IDC_LOCKED18,this);
	if(!m_TogLock3)m_LockBn3.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_COLUMN_COUNT);
		pCmbx->EnableWindow(FALSE);
		m_LockBn3.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn3.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn4.AutoLoad(IDC_LOCKED19,this);
	if(!m_TogLock4)m_LockBn4.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_BLOCK_COUNT);
		pCmbx->EnableWindow(FALSE);
		m_LockBn4.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn5.AutoLoad(IDC_LOCKED20,this);
	if(!m_TogLock5)m_LockBn5.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,IDB_LOCKEDX);
	else
	{
		m_LockBn5.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,IDB_LOCKEDX);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_C_BLOCK_COUNT);
		pCmbx->EnableWindow(FALSE);
	}
	m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn6.AutoLoad(IDC_LOCKED21,this);
	if(!m_TogLock6)m_LockBn6.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CELL_W);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB1);
		pCmbx->EnableWindow(FALSE);
		m_LockBn6.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn7.AutoLoad(IDC_LOCKED22,this);
	if(!m_TogLock7)m_LockBn7.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CELL_HEIGHT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB2);
		pCmbx->EnableWindow(FALSE);
		m_LockBn7.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn8.AutoLoad(IDC_LOCKED23,this);
	if(!m_TogLock8)m_LockBn8.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_BLOCK_WIDTH);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB3);
		pCmbx->EnableWindow(FALSE);
		m_LockBn8.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn8.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn9.AutoLoad(IDC_LOCKED24,this);
	if(!m_TogLock9)m_LockBn9.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_BLOCK_HEIGHT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB4);
		pCmbx->EnableWindow(FALSE);
		m_LockBn9.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn9.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn10.AutoLoad(IDC_LOCKED25,this);
	if(!m_TogLock10)m_LockBn10.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,IDB_LOCKEDX);
	else
	{
		m_LockBn10.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,IDB_LOCKEDX);
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CNGL_BLOCK_W);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB5);
		pCmbx->EnableWindow(FALSE);
	}
	m_LockBn10.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn11.AutoLoad(IDC_LOCKED26,this);
	if(!m_TogLock11)m_LockBn11.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,IDB_LOCKEDX);
	else
	{
		m_LockBn11.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,IDB_LOCKEDX);
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CNGL_BLOCK_H);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB6);
		pCmbx->EnableWindow(FALSE);
	}
	m_LockBn11.SetButtonStyle(BS_OWNERDRAW,TRUE);

	//cellCount static
	unsigned long count = m_nColCount * m_nRowCount * m_nBlockCount * 
		m_nCBlockCount;

	char s[15];
	std::stringstream ostr(s,15);
	ostr << count;// << ends;
	CString str = (CString)s;
	SetDlgItemText(IDC_CELL_COUNT_STATIC,str);

	//backup for reset button
	m_rectW = m_CellWidthVal;
	m_rectH = m_CellHeightVal;
	m_blockW = m_BlockWidthVal;
	m_blockH = m_BlockHeightVal;
	m_cBlockW = m_CBlockWidthVal;
	m_cBlockH = m_CBlockHeightVal;
	m_cols = m_nColCount;
	m_rows = m_nRowCount;
	m_blocks = m_nBlockCount;
	m_cBlocks = m_nCBlockCount;
	m_fRow = m_F_ROW;
	m_fCol = m_F_COL;
	m_fBlk = m_F_BLK;
	m_fCBlk = m_F_CBLK;
	m_intSyncOrig = m_IntSync;
	m_reflectOrig = m_Reflect;

	//backup for locks
	m_tl2 = m_TogLock2;
	m_tl3 = m_TogLock3;
	m_tl4 = m_TogLock4;
	m_tl5 = m_TogLock5;
	m_tl6 = m_TogLock6;
	m_tl7 = m_TogLock7;
	m_tl8 = m_TogLock8;
	m_tl9 = m_TogLock9;
	m_tl10 = m_TogLock10;
	m_tl11 = m_TogLock11;

	m_cnsR = m_CnsRow;
	m_cnsC = m_CnsCol;
	m_cnsB = m_CnsBlock;
	m_cnsCB = m_CnsCBlock;

	CDialog::OnInitDialog();

	if(color!=1)
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_C_BLOCK_COUNT);
		pEd->EnableWindow(FALSE);
		pEd = (CEdit*)GetDlgItem(IDC_CNGL_BLOCK_H);
		pEd->EnableWindow(FALSE);
		pEd = (CEdit*)GetDlgItem(IDC_CNGL_BLOCK_W);
		pEd->EnableWindow(FALSE);
		pEd = (CEdit*)GetDlgItem(IDC_FRQ_CBLK);
		pEd->EnableWindow(FALSE);
		CWnd* pCbx = GetDlgItem(IDC_CNS_CBLK);
		pCbx->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB5);
		pCmbx->EnableWindow(FALSE);
		pCmbx = (CComboBox*)GetDlgItem(IDC_UNIT_MEAS_COMB6);
		pCmbx->EnableWindow(FALSE);

		CBitmapButton* bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED20);
		bn->EnableWindow(FALSE);
		bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED25);
		bn->EnableWindow(FALSE);
		bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED26);
		bn->EnableWindow(FALSE);

	}

	ControlDeactivationByCountOfOne(TRUE,FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCellAspectsDlg::ControlDeactivationByCountOfOne(BOOL fromInit,BOOL fromReset)
{
	CEdit* pEd;
	if(m_rowsChange || fromInit || fromReset)
	{
		pEd = (CEdit*)GetDlgItem(IDC_FRQ_ROW);
		if((!fromReset && m_nRowCount==1)||(fromReset && m_rows==1))
			pEd->EnableWindow(FALSE);
		m_rowsChange = FALSE;
	}
	if(m_colsChange || fromInit || fromReset)
	{
		pEd = (CEdit*)GetDlgItem(IDC_FRQ_COL);
		if((!fromReset && m_nColCount==1)||(fromReset && m_cols==1))
			pEd->EnableWindow(FALSE);
		m_colsChange = FALSE;
	}
	if(m_bCountChange || fromInit || fromReset)
	{
		pEd = (CEdit*)GetDlgItem(IDC_FRQ_BLK);
		if((!fromReset && m_nBlockCount==1)||(fromReset && m_blocks==1))
			pEd->EnableWindow(FALSE);
		m_bCountChange = FALSE;
	}
	if(m_cBCountChange || fromInit || fromReset)
	{
		pEd = (CEdit*)GetDlgItem(IDC_FRQ_CBLK);
		if((!fromReset && m_nCBlockCount==1)||(fromReset && m_cBlocks==1))
			pEd->EnableWindow(FALSE);
		m_cBCountChange = FALSE;
	}
}

void CCellAspectsDlg::ControlActivationByCountOfOne(BOOL fromReset)//not called from InitDialog
{
	CEdit * pEd;

	pEd = (CEdit*)GetDlgItem(IDC_FRQ_ROW);
	if(m_rowsChange && m_rows==1 && !fromReset)pEd->EnableWindow(TRUE);
	if(m_rows!=1 && m_nRowCount==1 && fromReset)pEd->EnableWindow(TRUE);
	if(m_enableRowFreqWindow)pEd->EnableWindow(TRUE);

	pEd = (CEdit*)GetDlgItem(IDC_FRQ_COL);
	if(m_colsChange && m_cols==1 && !fromReset)pEd->EnableWindow(TRUE);
	if(m_cols!=1 && m_nColCount==1 && fromReset)pEd->EnableWindow(TRUE);
	if(m_enableColFreqWindow)pEd->EnableWindow(TRUE);

	pEd = (CEdit*)GetDlgItem(IDC_FRQ_BLK);
	if(m_bCountChange && m_blocks==1 && !fromReset)pEd->EnableWindow(TRUE);
	if(m_blocks!=1 && m_nBlockCount==1 && fromReset)pEd->EnableWindow(TRUE);
	if(m_enableBlockFreqWindow)pEd->EnableWindow(TRUE);

	if(m_color==1)
	{
		pEd = (CEdit*)GetDlgItem(IDC_FRQ_CBLK);
		if(m_cBCountChange && m_cBlocks==1 && !fromReset)pEd->EnableWindow(TRUE);
		if(m_cBlocks!=1 && m_nCBlockCount==1 && fromReset)pEd->EnableWindow(TRUE);
		if(m_enableCBlockFreqWindow)pEd->EnableWindow(TRUE);
	}
}

void CCellAspectsDlg::OnLocked17() 
{
	m_Bn2 = TRUE;
		if(m_TogLock2)
	{
		m_LockBn2.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock2 = FALSE;
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_ROW_COUNT);
		pCmbx->EnableWindow(TRUE);
	}
	else
	{
		m_LockBn2.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock2 = TRUE;
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_ROW_COUNT);
		pCmbx->EnableWindow(FALSE);
	}
	SignalFlagChangesToCalc();
}

void CCellAspectsDlg::OnLocked18() 
{
	m_Bn3 = TRUE;
		if(m_TogLock3)
	{
		m_LockBn3.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn3.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock3 = FALSE;
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_COLUMN_COUNT);
		pCmbx->EnableWindow(TRUE);
	}
	else if(!m_TogLock3)
	{
		m_LockBn3.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn3.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock3 = TRUE;
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_COLUMN_COUNT);
		pCmbx->EnableWindow(FALSE);
	}
	SignalFlagChangesToCalc();
}

void CCellAspectsDlg::OnLocked19() 
{
	m_Bn4 = TRUE;
		if(m_TogLock4)
	{
		m_LockBn4.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock4 = FALSE;
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_BLOCK_COUNT);
		pCmbx->EnableWindow(TRUE);
	}
	else
	{
		m_LockBn4.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock4 = TRUE;
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_BLOCK_COUNT);
		pCmbx->EnableWindow(FALSE);
	}	
	SignalFlagChangesToCalc();
}

void CCellAspectsDlg::OnLocked20() 
{
	m_Bn5 = TRUE;
	if(m_TogLock5)
	{
		m_LockBn5.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,IDB_UNLOCKEDX);
		m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock5 = FALSE;
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_C_BLOCK_COUNT);
		pCmbx->EnableWindow(TRUE);
	}
	else
	{
		m_LockBn5.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,IDB_LOCKEDX);
		m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock5 = TRUE;
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_C_BLOCK_COUNT);
		pCmbx->EnableWindow(FALSE);

	}
	SignalFlagChangesToCalc();	
}

void CCellAspectsDlg::OnLocked21() 
{
	m_Bn6 = TRUE;
	if(m_TogLock6)
	{
		m_LockBn6.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock6 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CELL_W);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB1);
		pCmbx->EnableWindow(TRUE);
	}
	else if(!m_TogLock6)
	{
		m_LockBn6.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock6 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CELL_W);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB1);
		pCmbx->EnableWindow(FALSE);
	}
	SignalFlagChangesToCalc();
}

void CCellAspectsDlg::OnLocked22() 
{
	m_Bn7 = TRUE;
	if(m_TogLock7)
	{
		m_LockBn7.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock7 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CELL_HEIGHT);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB2);
		pCmbx->EnableWindow(TRUE);
	}
	else
	{
		m_LockBn7.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock7 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CELL_HEIGHT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB2);
		pCmbx->EnableWindow(FALSE);
	}
	SignalFlagChangesToCalc();
}

void CCellAspectsDlg::OnLocked23() 
{
	m_Bn8 = TRUE;
	if(m_TogLock8)
	{
		m_LockBn8.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn8.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock8 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_BLOCK_WIDTH);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB3);
		pCmbx->EnableWindow(TRUE);
	}
	else
	{
		m_LockBn8.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn8.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock8 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_BLOCK_WIDTH);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB3);
		pCmbx->EnableWindow(FALSE);
	}
	SignalFlagChangesToCalc();	
}

void CCellAspectsDlg::OnLocked24() 
{
	m_Bn9 = TRUE;
		if(m_TogLock9)
	{
		m_LockBn9.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn9.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock9 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_BLOCK_HEIGHT);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB4);
		pCmbx->EnableWindow(TRUE);
	}
	else if(!m_TogLock9)
	{
		m_LockBn9.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn9.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock9 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_BLOCK_HEIGHT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB4);
		pCmbx->EnableWindow(FALSE);
	}
	SignalFlagChangesToCalc();
}

void CCellAspectsDlg::OnLocked25() 
{
	m_Bn10 = TRUE;
	if(m_TogLock10)
	{
		if(m_color==1)
			m_LockBn10.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		if(m_color!=1)
			m_LockBn10.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,IDB_UNLOCKEDX);
		m_LockBn10.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock10 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CNGL_BLOCK_W);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB5);
		pCmbx->EnableWindow(TRUE);
	}
	else
	{
		if(m_color==1)
			m_LockBn10.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		if(m_color!=1)
			m_LockBn10.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,IDB_LOCKEDX);
		m_LockBn10.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock10 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CNGL_BLOCK_W);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB5);
		pCmbx->EnableWindow(FALSE);
	}
	SignalFlagChangesToCalc();
}

void CCellAspectsDlg::OnLocked26() 
{
	m_Bn11 = TRUE;
	if(m_TogLock11)
	{
		if(m_color==1)
			m_LockBn11.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		if(m_color!=1)
			m_LockBn11.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,IDB_UNLOCKEDX);
		m_LockBn11.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock11 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CNGL_BLOCK_H);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB6);
		pCmbx->EnableWindow(TRUE);
	}
	else
	{
		if(m_color!=1)
			m_LockBn11.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,IDB_LOCKEDX);
		if(m_color==1)
			m_LockBn11.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn11.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock11 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_CNGL_BLOCK_H);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_MEAS_COMB6);
		pCmbx->EnableWindow(FALSE);
	}
	SignalFlagChangesToCalc();
}

void CCellAspectsDlg::OnSelchangeUnitMeasComb1() 
{
	UnifyCBs(1009);
}

void CCellAspectsDlg::OnSelchangeUnitMeasComb2() 
{
	UnifyCBs(1045);
}

void CCellAspectsDlg::OnSelchangeUnitMeasComb3() 
{
	UnifyCBs(1046);
}

void CCellAspectsDlg::OnSelchangeUnitMeasComb4() 
{
	UnifyCBs(1047);
}

void CCellAspectsDlg::OnSelchangeUnitMeasComb5() 
{
	UnifyCBs(1048);
}

void CCellAspectsDlg::OnSelchangeUnitMeasComb6() 
{
	UnifyCBs(1049);
}

void CCellAspectsDlg::UnifyCBs(int nBoxID)
{
	int index;
	CComboBox* pBo =
		(CComboBox*)GetDlgItem(nBoxID);
	ASSERT(pBo != NULL);
	index = pBo->GetCurSel();

	if(index<0) AfxMessageBox("CB ERR");

	int i;
	int arrayID[] = {1009,1045,1046,1047,1048,1049};
	for(i=0; i<6; i++)
	{
		if(arrayID[i]!=nBoxID)
		{
			LPCTSTR lp ("inches");//if(index==0)
			LPCTSTR lps ("pixels");//if(index==1) 
			LPCTSTR lpsz ("centimeters");//if(index==2)

			CComboBox * pUnitCmbo =
			(CComboBox*)GetDlgItem(arrayID[i]);
			ASSERT(pUnitCmbo != NULL);

			//if(index==1)pUnitCmbo->SelectString(-1,lp);
			//if(index==2)pUnitCmbo->SelectString(-1,lps);
			//if(index==0)pUnitCmbo->SelectString(-1,lpsz);
		
			if(index==2)pUnitCmbo->SelectString(-1,lp);
			if(index==1)pUnitCmbo->SelectString(-1,lpsz);
		}
	}

}

extern CCalc scratchPad;

void CCellAspectsDlg::OnOK() 
{
	CSerioDoc* pDcmt = CSerioDoc::GetDoc();
	OnCalculate();


	CComboBox* pBo =
		(CComboBox*)GetDlgItem(IDC_UNIT_MEAS_COMB1);
	ASSERT(pBo != NULL);

	char string[15];
	char* str = &string[0];
	int i;
	i = pBo->GetCurSel();
	pBo->GetLBText(i,str);

	m_nUnits = str;
	
	CDialog::OnOK();
}

void CCellAspectsDlg::PostNcDestroy() 
{
//	CSerioDoc* pDcmt = CSerioDoc::GetDoc();	
//	if(pDcmt->GetNextVal())pDcmt->CallDialog(4);

	CDialog::PostNcDestroy();
}

void CCellAspectsDlg::OnJump() 
{
	CSerioDoc* pDcmt = CSerioDoc::GetDoc();	
	BOOL next;
	next = pDcmt->ToggleNext();
	OnCalculate();

	CDialog::OnOK();
}

void CCellAspectsDlg::OnReset() 
{
	int intArray[6] = {IDC_UNIT_MEAS_COMB1,IDC_UNIT_MEAS_COMB2,
		IDC_UNIT_MEAS_COMB3,IDC_UNIT_MEAS_COMB4,
		IDC_UNIT_MEAS_COMB5,IDC_UNIT_MEAS_COMB6};
	int i;
	for(i=0;i<6;i++)
	{

		CComboBox * pUnitCmbo =
			(CComboBox*)GetDlgItem(intArray[i]);

		ASSERT(pUnitCmbo != NULL);

		pUnitCmbo->SelectString(-1,m_origStr);
	}

	UpdateData(TRUE);

	//Edits
	ControlActivationByCountOfOne(TRUE);
	ControlDeactivationByCountOfOne(FALSE,TRUE);

	m_rectWchange = FALSE;
	m_rectHchange = FALSE;
	m_blockWchange = FALSE;
	m_blockHchange = FALSE;
	m_cBlockWchange = FALSE;
	m_cBlockHchange = FALSE;
	m_colsChange = FALSE;
	m_rowsChange = FALSE;
	m_bCountChange = FALSE;
	m_cBCountChange = FALSE;
	m_cBlkFrqChange = FALSE;
	m_blkFrqChange = FALSE;
	m_rowFrqChange = FALSE;
	m_colFrqChange = FALSE;

	m_CellWidthVal = m_rectW;
	m_CellHeightVal = m_rectH;
	m_BlockWidthVal = m_blockW;
	m_BlockHeightVal = m_blockH;
	m_CBlockWidthVal = m_cBlockW;
	m_CBlockHeightVal = m_cBlockH;
	m_nColCount = m_cols;
	m_nRowCount = m_rows;
	m_nBlockCount = m_blocks;
	m_nCBlockCount = m_cBlocks;
	m_F_COL = m_fCol;
	m_F_ROW = m_fRow;
	m_F_BLK = m_fBlk;
	m_F_CBLK = m_fCBlk;

	m_enableRowFreqWindow = FALSE;
	m_enableColFreqWindow = FALSE;
	m_enableBlockFreqWindow = FALSE;
	m_enableCBlockFreqWindow = FALSE;

	m_Bn = FALSE;
	m_Bn2 = FALSE;
	m_Bn3 = FALSE;
	m_Bn4 = FALSE;
	m_Bn5 = FALSE;
	m_Bn6 = FALSE;
	m_Bn7 = FALSE;
	m_Bn8 = FALSE;
	m_Bn9 = FALSE;
	m_Bn10 = FALSE;
	m_Bn11 = FALSE;
	m_Bn12 = FALSE;
	m_Bn13 = FALSE;
	m_Bn14 = FALSE;
	m_Bn15 = FALSE;
	m_Bn16 = FALSE;

	m_CellWidthVal = m_rectW;
	m_CellHeightVal = m_rectH;
	m_BlockWidthVal = m_blockW;
	m_BlockHeightVal = m_blockH;
	m_CBlockWidthVal = m_cBlockW;
	m_CBlockHeightVal = m_cBlockH;
	m_nColCount = m_cols;
	m_nRowCount = m_rows;

	m_IntSync = m_intSyncOrig;
	m_Reflect = m_reflectOrig;

	//locks
	if(m_TogLock2!=m_tl2)OnLocked17();
	if(m_TogLock3!=m_tl3)OnLocked18();
	if(m_TogLock4!=m_tl4)OnLocked19();
	if(m_TogLock5!=m_tl5)OnLocked20();
	if(m_TogLock6!=m_tl6)OnLocked21();
	if(m_TogLock7!=m_tl7)OnLocked22();	
	if(m_TogLock8!=m_tl8)OnLocked23();
	if(m_TogLock9!=m_tl9)OnLocked24();
	if(m_TogLock10!=m_tl10)OnLocked25();
	if(m_TogLock11!=m_tl11)OnLocked26();
	m_CnsRow = m_cnsR;
	m_CnsCol = m_cnsC;
	m_CnsBlock = m_cnsB;
	m_CnsCBlock = m_cnsCB;

	//cellCount static
	unsigned long count = m_nColCount * m_nRowCount * m_nBlockCount * 
		m_nCBlockCount;
	char s[15];
	std::stringstream ostr(s,15);
	ostr << count; // end;
	CString str = (CString)s;
	SetDlgItemText(IDC_CELL_COUNT_STATIC,str);

	UpdateData(FALSE);
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	pDoc->RegisterAspects();
	::scratchPad.LoadCalcMembers();
}

void CCellAspectsDlg::OnCalculate() 
{
	//using doubles throughout also solved the problem

	UpdateData(TRUE);

	SignalFlagChangesToCalc();

	BOOL result = 0;
	if(m_rectWchange)result =
		 ::scratchPad.InstigateChange(m_CellWidthVal,0);
	if(m_rectHchange)result =
		 ::scratchPad.InstigateChange(m_CellHeightVal,7);
	if(m_blockWchange)
		result = ::scratchPad.InstigateChange(m_BlockWidthVal,1);
	if(m_blockHchange)
		result = ::scratchPad.InstigateChange(m_BlockHeightVal,8);
	if(m_cBlockWchange)
		result = ::scratchPad.InstigateChange(m_CBlockWidthVal,2);
	if(m_cBlockHchange)
		result = ::scratchPad.InstigateChange(m_CBlockHeightVal,9);
	if(m_colsChange)
		result = ::scratchPad.InstigateChange((UINT)m_nColCount,5);
	if(m_rowsChange)
		result = ::scratchPad.InstigateChange((UINT)m_nRowCount,12);
	if(m_bCountChange)
		result = ::scratchPad.InstigateChange((UINT)m_nBlockCount,13);
	if(m_cBCountChange)
		result = ::scratchPad.InstigateChange((UINT)m_nCBlockCount,14);
	if(m_colFrqChange)
		result = ::scratchPad.InstigateChange(m_F_COL,23);
	if(m_rowFrqChange)
		result = ::scratchPad.InstigateChange(m_F_ROW,24);
	if(m_blkFrqChange)
		result = ::scratchPad.InstigateChange(m_F_BLK,25);
	if(m_cBlkFrqChange)
		result = ::scratchPad.InstigateChange(m_F_CBLK,26);

	BOOL boom = ::scratchPad.ProcessChangeRequests();
	
	UpdateMembersFromCalc();

	ControlDeactivationByCountOfOne(FALSE,FALSE);
	ControlActivationByCountOfOne(FALSE);

	m_rectWchange = FALSE;
	m_rectHchange = FALSE;
	m_blockWchange = FALSE;
	m_blockHchange = FALSE;
	m_cBlockWchange = FALSE;
	m_cBlockHchange = FALSE;
	m_colsChange = FALSE;
	m_rowsChange = FALSE;
	m_bCountChange = FALSE;
	m_cBCountChange = FALSE;
	m_rowFrqChange = FALSE;
	m_colFrqChange = FALSE;
	m_blkFrqChange = FALSE;
	m_cBlkFrqChange = FALSE;

	m_enableRowFreqWindow = FALSE;
	m_enableColFreqWindow = FALSE;
	m_enableBlockFreqWindow = FALSE;
	m_enableCBlockFreqWindow = FALSE;


}

void CCellAspectsDlg::SignalFlagChangesToCalc()
{
	if(m_Bn11)
		::scratchPad.ChangeLocksAndFlags(9,m_TogLock11);
	if(m_Bn10)
		::scratchPad.ChangeLocksAndFlags(2,m_TogLock10);
	if(m_Bn9)
		::scratchPad.ChangeLocksAndFlags(8,m_TogLock9);
	if(m_Bn8)
		::scratchPad.ChangeLocksAndFlags(1,m_TogLock8);
	if(m_Bn7)
		::scratchPad.ChangeLocksAndFlags(7,m_TogLock7);
	if(m_Bn6)
		::scratchPad.ChangeLocksAndFlags(0,m_TogLock6);
	if(m_Bn5)
		::scratchPad.ChangeLocksAndFlags(14,m_TogLock5);
	if(m_Bn4) 
		::scratchPad.ChangeLocksAndFlags(13,m_TogLock4);
	if(m_Bn3)
		::scratchPad.ChangeLocksAndFlags(5,m_TogLock3);
	if(m_Bn2)
		::scratchPad.ChangeLocksAndFlags(12,m_TogLock2);
	if(m_Bn13)
		::scratchPad.ChangeLocksAndFlags(23,m_CnsCol);
	if(m_Bn14)
		::scratchPad.ChangeLocksAndFlags(24,m_CnsRow);
	if(m_Bn15)
		::scratchPad.ChangeLocksAndFlags(25,m_CnsBlock);
	if(m_Bn16)
		::scratchPad.ChangeLocksAndFlags(26,m_CnsCBlock);
	if(m_cHitch)
		::scratchPad.ChangeLocksAndFlags(52,m_nCellRatio);
	//if(m_cConform)
	//	::scratchPad.ChangeLocksAndFlags(53,m_nIsSquare);
	//::scratchPad.ChangeLocksAndFlags(54,m_uniCount);
	//::scratchPad.ChangeLocksAndFlags(55,m_nDeriveCells);
	::scratchPad.ChangeLocksAndFlags(56,m_Reflect);
	::scratchPad.ChangeLocksAndFlags(57,m_IntSync);
	//::scratchPad.ChangeLocksAndFlags(58,m_SyncAll);


	m_Bn = FALSE;
	m_Bn2 = FALSE;
	m_Bn3 = FALSE;
	m_Bn4 = FALSE;
	m_Bn5 = FALSE;
	m_Bn6 = FALSE;
	m_Bn7 = FALSE;
	m_Bn8 = FALSE;
	m_Bn9 = FALSE;
	m_Bn10 = FALSE;
	m_Bn11 = FALSE;
	m_Bn12 = FALSE;
	m_Bn13 = FALSE;
	m_Bn14 = FALSE;
	m_Bn15 = FALSE;
	m_Bn16 = FALSE;
}

void CCellAspectsDlg::UpdateMembersFromCalc()
{
	CRegAspect* line;
	line = scratchPad.m_reg[0];
	m_CellWidthVal = line->m_nSize;
	line = scratchPad.m_reg[7];
	m_CellHeightVal = line->m_nSize;
	line = scratchPad.m_reg[1];
	m_BlockWidthVal = line->m_nSize;
	line = scratchPad.m_reg[8];
	m_BlockHeightVal = line->m_nSize;
	line = scratchPad.m_reg[2];
	m_CBlockWidthVal = line->m_nSize;
	line = scratchPad.m_reg[9];
	m_CBlockHeightVal = line->m_nSize;
	line = scratchPad.m_reg[5];
	m_nColCount = line->m_nCount;
	line = scratchPad.m_reg[12];
	m_nRowCount = line->m_nCount;
	line = scratchPad.m_reg[13];
	m_nBlockCount = line->m_nCount;
	if(m_color==1)
	{
		line = scratchPad.m_reg[14];
		m_nCBlockCount = line->m_nCount;
	}
	else 
	{
		line = scratchPad.m_reg[18];
		m_CBlockHeightVal = line->m_nSize;
		line = scratchPad.m_reg[17];
		m_CBlockWidthVal = line->m_nSize;
	}
	line = scratchPad.m_reg[24];
	m_F_ROW = line->m_nSize;
	line = scratchPad.m_reg[23];
	m_F_COL = line->m_nSize;
	line = scratchPad.m_reg[25];
	m_F_BLK = line->m_nSize;
	line = scratchPad.m_reg[26];
	m_F_CBLK = line->m_nSize;

	//cellCount static
	unsigned long count = m_nColCount * m_nRowCount * m_nBlockCount * 
		m_nCBlockCount;
	char s[15];
	std::stringstream ostr(s,15);
	ostr << count;// << ends;
	CString str = (CString)s;
	SetDlgItemText(IDC_CELL_COUNT_STATIC,str);

	UpdateData(FALSE);
}

void CCellAspectsDlg::StoreRestoreChangeFlagsAndValues(CAspectsBuffer* requestBf,
													   BOOL store)
{
	if(store)
	{
		requestBf->m_cellW = m_CellWidthVal;
		requestBf->m_cellH = m_CellHeightVal;
		requestBf->m_blockW = m_BlockWidthVal;
		requestBf->m_blockH = m_BlockHeightVal;
		requestBf->m_cBlockW = m_CBlockWidthVal;
		requestBf->m_cBlockH = m_CBlockHeightVal;
		requestBf->m_cols = m_nColCount;
		requestBf->m_rows = m_nRowCount;
		requestBf->m_blocks = m_nBlockCount;
		requestBf->m_cBlocks = m_nCBlockCount;
		requestBf->m_fRow = m_F_ROW;
		requestBf->m_fCol = m_F_COL;
		requestBf->m_fBlk = m_F_BLK;
		requestBf->m_fCBlk = m_F_CBLK;
	}
	else
	{
		if(m_rectWchange)m_CellWidthVal = requestBf->m_cellW;
		if(m_rectHchange)m_CellHeightVal = requestBf->m_cellH;
		if(m_blockWchange)m_BlockWidthVal = requestBf->m_blockW;
		if(m_blockHchange)m_BlockHeightVal = requestBf->m_blockH;
		if(m_cBlockWchange)m_CBlockWidthVal = requestBf->m_cBlockW;
		if(m_cBlockHchange)m_CBlockHeightVal = requestBf->m_cBlockH;
		if(m_colsChange)m_nColCount = requestBf->m_cols;
		if(m_rowsChange)m_nRowCount = requestBf->m_rows;
		if(m_bCountChange)m_nBlockCount = requestBf->m_blocks;
		if(m_cBCountChange)m_nCBlockCount = requestBf->m_cBlocks;
		if(m_rowFrqChange)m_F_ROW = requestBf->m_fRow;
		if(m_colFrqChange)m_F_COL = requestBf->m_fCol;
		if(m_blkFrqChange)m_F_BLK = requestBf->m_fBlk;
		if(m_cBlkFrqChange)m_F_CBLK = requestBf->m_fCBlk;
	}
}

void CCellAspectsDlg::OnCancel() 
{
	::scratchPad.m_change = FALSE;
	
	CDialog::OnCancel();
}


BOOL CCellAspectsDlg::ExtractValue(int cntlID)
{
	CString str;
	GetDlgItemText(cntlID,str);
	int len = str.GetLength();
	double rack[8];
	int decPos = 99;
	int num;
	for(num=0;num<len;num++)
	{
		if(str[num]==46)	//	str[num];//'0'=48, '.'=46
		{
			decPos = num;
			break;
		}
	}
	int multTenDigits = decPos;
	if(decPos==99)multTenDigits = len;
	for(num=0;num<len;num++)//integer part
	{
		if(num!=decPos)
		{
			int val = str[num];
			val = GetNumericValue(val);
			UINT denom = (UINT) (GetDenom(multTenDigits,TRUE));
			multTenDigits--;
			rack[num] = val * denom;
		}
		else break;
	}
	num++;
	int expon = 1;
	for( ;num<len;num++)//precision part
	{
		
		int val = str[num];
		val = GetNumericValue(val);
		double denom = GetDenom(expon,FALSE);
		expon++;
		rack[num] = val * denom;
	}
	double result = 0;
	//add results
	for(num=0;num<len;)
	{
		result = result + rack[num];
		num++;
	}

	//evaluate result
	BOOL change = FALSE;
	double old = MemberFloatLUT(cntlID);
	if(old!=result)change = TRUE;
	if(m_intTest)
	{
		UINT test = (UINT)result;
		if(test==result)change = TRUE;
		else change = FALSE;
	}
	return change;
}

double CCellAspectsDlg::GetDenom(int expon,BOOL mult)
{	
	double tens = 1;
	if(!mult) tens = 0.1;
	for( ;expon>1; )
	{
		if(mult) tens = tens * 10;
		if(!mult) tens = tens / 10;
		expon--;
	}
	return tens;
}

UINT CCellAspectsDlg::GetNumericValue(int val)
{	
	UINT number = 1;
	if(val==48) number = 0;
	if(val==49) number = 1;
	if(val==50) number = 2;
	if(val==51) number = 3;
	if(val==52) number = 4;
	if(val==53) number = 5;
	if(val==54) number = 6;
	if(val==55) number = 7;
	if(val==56) number = 8;
	if(val==57) number = 9;

	return number;
}

double CCellAspectsDlg::MemberFloatLUT(int cntlID)
{
	double val = 0;
	if(cntlID==1087) val = m_CellWidthVal;
	if(cntlID==1025) val = m_CellHeightVal;
	if(cntlID==1022) val = m_BlockWidthVal;
	if(cntlID==1023) val = m_BlockHeightVal;
	if(cntlID==1024) val = m_CBlockWidthVal;
	if(cntlID==1026) val = m_CBlockHeightVal;
	//UINTS
	if(cntlID==1064) val = (double)m_nColCount;
	if(cntlID==1123) val = (double)m_nRowCount;
	if(cntlID==1122) val = (double)m_nBlockCount;
	if(cntlID==1065) val = (double)m_nCBlockCount;

	if(cntlID==1092) val = (double)m_F_ROW;
	if(cntlID==1090) val = (double)m_F_COL;
	if(cntlID==1092) val = (double)m_F_BLK;
	if(cntlID==1096) val = (double)m_F_CBLK;

	return val;
}


void CCellAspectsDlg::OnChangeBlockHeight() 
{
	BOOL change = FALSE;
	if(m_TogLock9)
	{
		UpdateData(FALSE);

	}
	if(!m_TogLock9)
	{
		BOOL change = FALSE;
		change = ExtractValue(IDC_BLOCK_HEIGHT);
		if(change) m_blockHchange = TRUE;
		UpdateData(TRUE);
	}
}

void CCellAspectsDlg::OnChangeBlockWidth() 
{
	BOOL change = FALSE;
	if(m_TogLock8)
	{
		UpdateData(FALSE);

	}
	if(!m_TogLock8)
	{
		BOOL change = FALSE;
		change = ExtractValue(IDC_BLOCK_WIDTH);
		if(change) m_blockWchange = TRUE;
		UpdateData(TRUE);
	}
}

void CCellAspectsDlg::OnChangeCBlockCount() 
{
	UINT nuCount = GetDlgItemInt(IDC_C_BLOCK_COUNT,NULL,FALSE);
	if(nuCount!=1 && m_nCBlockCount==1)m_enableCBlockFreqWindow = TRUE;
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	int code = pDoc->OnCBlockLayoutPrompt(nuCount);
	if(code==0) {m_cBCountChange = TRUE;UpdateData(TRUE);}
	if(code==1)
	{
		UpdateData(TRUE);
		m_cBCountChange = TRUE;
		UpdateMembersFromCalc();
		m_nCBlockCount = nuCount;
	}
	if(!m_cBCountChange)m_enableCBlockFreqWindow = FALSE;
	UpdateData(FALSE);
}

void CCellAspectsDlg::OnChangeBlockCount() 
{
	UINT nuCount = GetDlgItemInt(IDC_BLOCK_COUNT,NULL,FALSE);
	if(nuCount!=1 && m_nBlockCount==1)m_enableBlockFreqWindow = TRUE;
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	int code = pDoc->OnBlockLayoutPrompt(nuCount);
	if(code==0){m_bCountChange = TRUE;UpdateData(TRUE);}
	//'1' indicates calc was called
	if(code==1)
	{
		UpdateData(TRUE);
		m_bCountChange = TRUE;
		CAspectsBuffer * aspBuf = new CAspectsBuffer();
		StoreRestoreChangeFlagsAndValues(aspBuf,TRUE);
		UpdateMembersFromCalc();
		StoreRestoreChangeFlagsAndValues(aspBuf,FALSE);
		delete aspBuf;
		m_nBlockCount = nuCount;
	}
	if(!m_bCountChange)m_enableBlockFreqWindow = FALSE;
	UpdateData(FALSE);
}

void CCellAspectsDlg::OnChangeCellHeight() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_CELL_HEIGHT);
	if(change) m_rectHchange = TRUE;
	if(m_TogLock7)UpdateData(FALSE);
	if(!m_TogLock7)UpdateData(TRUE);
}

void CCellAspectsDlg::OnChangeCnglBlockH() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_CNGL_BLOCK_H);
	if(change) m_cBlockHchange = TRUE;
	if(m_TogLock11)UpdateData(FALSE);
	if(!m_TogLock11)UpdateData(TRUE);
}

void CCellAspectsDlg::OnChangeCnglBlockW() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_CELL_W);
	if(change) m_cBlockWchange = TRUE;
	if(m_TogLock10)UpdateData(FALSE);
	if(!m_TogLock10)UpdateData(TRUE);
}

void CCellAspectsDlg::OnChangeColumnCount() 
{
	UINT nuCount = GetDlgItemInt(IDC_COLUMN_COUNT,NULL,FALSE);
	BOOL change = FALSE;
	change = ExtractValue(IDC_COLUMN_COUNT);
	if(change)
	{
		m_colsChange = TRUE;
		if(m_nColCount==1 && nuCount!=1)m_enableColFreqWindow = TRUE;
	}
	if(m_TogLock3)UpdateData(FALSE);
	if(!m_TogLock3)UpdateData(TRUE);
}

void CCellAspectsDlg::OnChangeRowCount() 
{
	UINT nuCount = GetDlgItemInt(IDC_ROW_COUNT,NULL,FALSE);
	BOOL change = FALSE;
	change = ExtractValue(IDC_ROW_COUNT);
	if(change) 
	{
		m_rowsChange = TRUE;
		if(m_nRowCount==1 && nuCount!=1)m_enableRowFreqWindow = TRUE;
	}
	if(m_TogLock2)UpdateData(FALSE);
	if(!m_TogLock2)UpdateData(TRUE);
}

void CCellAspectsDlg::OnChangeCellW() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_CELL_W);
	if(change) m_rectWchange = TRUE;
	if(m_TogLock6)UpdateData(FALSE);
	if(!m_TogLock6)UpdateData(TRUE);
}

void CCellAspectsDlg::OnCellRatio() 
{
	m_cHitch = TRUE;
	UpdateData(TRUE);
}

//void CCellAspectsDlg::OnIfSquare() 
//{
//	m_cHitch = TRUE;
//	UpdateData(TRUE);
//}

void CCellAspectsDlg::OnChangeFrqRow() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_FRQ_ROW);
	if(change)
	{
		m_rowFrqChange = TRUE;
		UpdateData(TRUE);
	}
}

void CCellAspectsDlg::OnChangeFrqCol() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_FRQ_COL);
	if(change) m_colFrqChange = TRUE;
}

void CCellAspectsDlg::OnChangeFrqCblk() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_FRQ_CBLK);
	if(change) m_cBlkFrqChange = TRUE;
}

void CCellAspectsDlg::OnChangeFrqBlk() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_FRQ_BLK);
	if(change) m_blkFrqChange = TRUE;
}

void CCellAspectsDlg::OnCnsCblk() 
{
	m_Bn16 = TRUE;
	
}

void CCellAspectsDlg::OnCnsCol() 
{
	m_Bn13 = TRUE;
}

void CCellAspectsDlg::OnCnsRow() 
{
	m_Bn14 = TRUE;
}

void CCellAspectsDlg::OnCnsBlk() 
{
	m_Bn15 = TRUE;	
}

void CCellAspectsDlg::OnIntSync() 
{
	if(!m_IntSync)
	{
		//inspect frequency for integers
		BOOL freqIsInt;
		m_intTest = TRUE;
		freqIsInt = ExtractValue(IDC_FRQ_BLK);
		if(freqIsInt) freqIsInt = ExtractValue(IDC_FRQ_COL);
		if(freqIsInt) freqIsInt = ExtractValue(IDC_FRQ_ROW);
		if(freqIsInt) freqIsInt = ExtractValue(IDC_FRQ_CBLK);
		m_intTest = FALSE;
		if(!freqIsInt)
		{
			AfxMessageBox("There must currently be no fractions of steps in order to select this option");
			m_IntSync = FALSE;
			UpdateData(FALSE);
		}
	}
	UpdateData(TRUE);
}
