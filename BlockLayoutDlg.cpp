// BlockLayoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "BlockLayoutDlg.h"
#include "SerioDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlockLayoutDlg dialog


CBlockLayoutDlg::CBlockLayoutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlockLayoutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBlockLayoutDlg)
	m_blockCols = 0;
	m_blockRows = 0;
	m_frameH = 0.0f;
	m_frameW = 0.0f;
	m_blockH = 0.0f;
	m_blockW = 0.0f;
	m_colSpace = 0.0f;
	m_rowSpace = 0.0f;
	//}}AFX_DATA_INIT

}


void CBlockLayoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBlockLayoutDlg)
	DDX_Control(pDX, IDC_FRAME_W_EDIT, m_trapDec6);
	DDX_Control(pDX, IDC_FRAME_H_EDIT, m_trapDec5);
	DDX_Control(pDX, IDC_B_ROWSPACE_EDIT, m_trapDec4);
	DDX_Control(pDX, IDC_B_COLSPACE_EDIT, m_trapDec3);
	DDX_Control(pDX, IDC_BLOCKH_EDIT, m_trapDec2);
	DDX_Control(pDX, IDC_BLOCKW_EDIT, m_trapDec);
	DDX_Control(pDX, IDC_BLK_LAYOUT_STATIC, m_drag);
	DDX_Text(pDX, IDC_BCOLS_EDIT, m_blockCols);
	DDX_Text(pDX, IDC_BROWS_EDIT, m_blockRows);
	DDX_Text(pDX, IDC_FRAME_H_EDIT, m_frameH);
	DDX_Text(pDX, IDC_FRAME_W_EDIT, m_frameW);
	DDX_Text(pDX, IDC_BLOCKH_EDIT, m_blockH);
	DDX_Text(pDX, IDC_BLOCKW_EDIT, m_blockW);
	DDX_Text(pDX, IDC_B_COLSPACE_EDIT, m_colSpace);
	DDX_Text(pDX, IDC_B_ROWSPACE_EDIT, m_rowSpace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBlockLayoutDlg, CDialog)
	//{{AFX_MSG_MAP(CBlockLayoutDlg)
	ON_EN_CHANGE(IDC_BCOLS_EDIT, OnChangeBcolsEdit)
	ON_EN_CHANGE(IDC_BROWS_EDIT, OnChangeBrowsEdit)
	ON_EN_CHANGE(IDC_FRAME_H_EDIT, OnChangeFrameHEdit)
	ON_EN_CHANGE(IDC_FRAME_W_EDIT, OnChangeFrameWEdit)
	ON_EN_CHANGE(IDC_BLOCKH_EDIT, OnChangeBlockhEdit)
	ON_EN_CHANGE(IDC_BLOCKW_EDIT, OnChangeBlockwEdit)
	ON_EN_CHANGE(IDC_B_COLSPACE_EDIT, OnChangeBColspaceEdit)
	ON_EN_CHANGE(IDC_B_ROWSPACE_EDIT, OnChangeBRowspaceEdit)
	ON_BN_CLICKED(IDC_BL_RESET_BN, OnBlockLayResetBn)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlockLayoutDlg message handlers


void CBlockLayoutDlg::OnChangeBcolsEdit() 
{
	BOOL valid, sgn = FALSE;
	unsigned val = GetDlgItemInt(IDC_BCOLS_EDIT,&valid,sgn);
	valid = m_drag.ChangeIntValue(val,1);
	m_drag.InitializeGraphicComponants(TRUE);
	m_drag.Invalidate();
	InductNewValues();
	UpdateData(FALSE);
}

void CBlockLayoutDlg::OnChangeBrowsEdit() 
{
	BOOL valid, sgn = FALSE;
	unsigned val = GetDlgItemInt(IDC_BROWS_EDIT,&valid,sgn);
	m_drag.ChangeIntValue(val,2);
	m_drag.InitializeGraphicComponants(TRUE);
	m_drag.Invalidate();
	InductNewValues();
	UpdateData(FALSE);
}

void CBlockLayoutDlg::OnChangeFrameHEdit() 
{
	BOOL valid = FALSE;
	//CString str = GetDlgItemText(IDC_FRAME_H_EDIT,
	BOOL go = m_trapDec5.m_go;//test for "decimal" char
	//if(m_trapDec5.m_nChar==48)go = TRUE;//zero 
	if(go)
	{
		float buffer = m_frameH;
		UpdateData(TRUE);
		float val = m_frameH;
		valid = m_drag.ChangeFloatValue(val,1);
		if(valid)
		{
			m_drag.InitializeGraphicComponants(TRUE);
			m_drag.Invalidate();	
			InductNewValues();
		}
		if(!valid) m_frameH = buffer;
		UpdateData(FALSE);
	}
}

void CBlockLayoutDlg::OnChangeFrameWEdit() 
{
	BOOL valid;
	BOOL go = m_trapDec6.m_go;
	if(go)
	{
		float buffer = m_frameW;
		UpdateData(TRUE);
		float val = m_frameW;
		valid = m_drag.ChangeFloatValue(val,2);
		if(valid)
		{
			m_drag.InitializeGraphicComponants(TRUE);
			m_drag.Invalidate();
			InductNewValues();
		}
		if(!valid) m_frameW = buffer;
		UpdateData(FALSE);
	}
}

void CBlockLayoutDlg::OnChangeBlockhEdit() 
{
	BOOL valid;
	BOOL go = m_trapDec2.m_go;
	if(go)
	{
		float buffer = m_blockH;
		UpdateData(TRUE);
		float val = m_blockH;
		valid = m_drag.ChangeFloatValue(val,3);
		if(valid)
		{
			m_drag.InitializeGraphicComponants(TRUE);
			m_drag.Invalidate();
			InductNewValues();
		}
		if(!valid) m_blockH = buffer;
		UpdateData(FALSE);
	}
}

void CBlockLayoutDlg::OnChangeBlockwEdit() 
{
	BOOL valid;
	BOOL go = m_trapDec.m_go;
	if(go)
	{
		BOOL go = m_trapDec.m_go;
		if(go)
		{
			float buffer = m_blockW;
			UpdateData(TRUE);
			float val = m_blockW;
			valid = m_drag.ChangeFloatValue(val,4);
			if(valid)
			{
				m_drag.InitializeGraphicComponants(TRUE);
				m_drag.Invalidate();
				InductNewValues();
			}
			if(!valid) m_blockW = buffer;
			UpdateData(FALSE);
		}
	}
}

void CBlockLayoutDlg::OnChangeBColspaceEdit() 
{
	BOOL valid;
	BOOL go = m_trapDec3.m_go;
	if(go)
	{
		float buffer = m_colSpace;
		UpdateData(TRUE);
		float val = m_colSpace;
		valid = m_drag.ChangeFloatValue(val,5);
		if(valid)
		{
			m_drag.InitializeGraphicComponants(TRUE);
			m_drag.Invalidate();
			InductNewValues();
		}
		if(!valid) m_colSpace = buffer;
		UpdateData(FALSE);
	}
}

void CBlockLayoutDlg::OnChangeBRowspaceEdit() 
{
	BOOL valid;
	BOOL go = m_trapDec4.m_go;
	if(go)
	{
		float buffer = m_rowSpace;
		UpdateData(TRUE);
		float val = m_rowSpace;
		valid = m_drag.ChangeFloatValue(val,6);
		if(valid)
		{
			m_drag.InitializeGraphicComponants(TRUE);
			m_drag.Invalidate();
			InductNewValues();
		}
		if(!valid) m_rowSpace;
		UpdateData(FALSE);	
	}
}

void CBlockLayoutDlg::InductNewValues()
{
	m_blockH = m_drag.GetBlockHeight();
	m_blockW = m_drag.GetBlockWidth();
	m_blockCols = m_drag.GetBlockCols();
	m_blockRows = m_drag.GetBlockRows();
	m_frameH = m_drag.GetFrameH();
	m_frameW = m_drag.GetFrameW();
	m_colSpace = m_drag.GetColSpace();
	m_rowSpace = m_drag.GetRowSpace();
}

void CBlockLayoutDlg::OnBlockLayResetBn() 
{
	m_blockH = m_bufBlockH;
	m_blockW = m_bufBlockW;
	m_blockCols = m_bufBlockCols;
	m_blockRows = m_bufBlockRows;
	m_frameH = m_bufFrameH;
	m_frameW = m_bufFrameW;
	m_colSpace = m_bufColSpace;
	m_rowSpace = m_bufRowSpace;

	UpdateData(FALSE);

	m_drag.SetBlockHeight(m_blockH);
	m_drag.SetBlockWidth(m_blockW);
	m_drag.SetCols(m_blockCols);
	m_drag.SetRows(m_blockRows);
	m_drag.SetFrameHeight(m_frameH);
	m_drag.SetFrameWidth(m_frameW);
	//m_drag.SetColSpace(m_colSpace);
	//m_drag.SetRowSpace(m_rowSpace);

	m_drag.InitializeGraphicComponants(TRUE);
	m_drag.Invalidate();
}

BOOL CBlockLayoutDlg::OnInitDialog() 
{
	m_drag.m_calledByDlg = byDlg;
	m_drag.extra = extra;

	CDialog::OnInitDialog();
	
	m_bufBlockCols = m_blockCols;
	m_bufBlockH = m_blockH;
	m_bufBlockW = m_blockW;
	m_bufBlockCols = m_blockCols;
	m_bufBlockRows = m_blockRows;
	m_bufFrameH = m_frameH;
	m_bufFrameW = m_frameW;

	//only needed to obtain colSpace and rowSpace (in this case)
	//m_drag.InitializeGraphicComponants(TRUE);
	InductNewValues(); 

	m_bufColSpace = m_colSpace;
	m_bufRowSpace = m_rowSpace;
	//UpdateData here would put the proper spacing values in the edits
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBlockLayoutDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	AfxMessageBox("ondrawItem");
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CBlockLayoutDlg::OnOK() 
{
	BOOL nuf = TRUE;
	UINT avail = m_drag.GetBlockTotal();
	if(m_blocksNeeded>avail)nuf = FALSE;
	if(!nuf)
	{
		CString m_addStr = "Please add more columns or rows to the format so that it may accomodate the intended number of blocks.";
		int response = ::MessageBox(
			NULL,m_addStr,"Prompt Box",MB_OKCANCEL);
		if(response==IDCANCEL)OnCancel();
	}
	
	if(nuf)CDialog::OnOK();
}
