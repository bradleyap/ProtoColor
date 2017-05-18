// ColorFormDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "SerioDoc.h"
#include "ColorFormDlg.h"
#include "afxext.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorFormDlg dialog


CColorFormDlg::CColorFormDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorFormDlg::IDD, pParent)
{
	m_next = FALSE;
	m_resetCall = FALSE;
	//{{AFX_DATA_INIT(CColorFormDlg)
	m_nMaxSteps = _T("");
	m_StartL2R = 0;
	m_StartT2B = 0;
	m_StartF2L = 0;
	m_EndF2B = 0;
	m_EndF2L = 0;
	m_EndL2R = 0;
	m_EndT2B = 0;
	m_StartF2B = 0;
	m_nOutLineClr = _T("");
	m_autoLock = FALSE;
	m_calcIntent = -1;
	//}}AFX_DATA_INIT

}


void CColorFormDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorFormDlg)
	DDX_Control(pDX, IDC_START_RA_T2B, m_8);
	DDX_Control(pDX, IDC_START_RA_L2R, m_7);
	DDX_Control(pDX, IDC_START_RA_F2L, m_6);
	DDX_Control(pDX, IDC_START_RA_F2B, m_5);
	DDX_Control(pDX, IDC_END_RA_T2B, m_4);
	DDX_Control(pDX, IDC_END_RA_L2R, m_3);
	DDX_Control(pDX, IDC_END_RA_F2L, m_2);
	DDX_Control(pDX, IDC_END_RA_F2B, m_1);
	DDX_Radio(pDX, IDC_RADIO_RGB, m_nColorMode);
	DDX_CBString(pDX, IDC_MAX_STEPS, m_nMaxSteps);
	DDX_Text(pDX, IDC_START_RA_L2R, m_StartL2R);
	DDX_Text(pDX, IDC_START_RA_T2B, m_StartT2B);
	DDX_Text(pDX, IDC_START_RA_F2L, m_StartF2L);
	DDX_Text(pDX, IDC_END_RA_F2B, m_EndF2B);
	DDX_Text(pDX, IDC_END_RA_F2L, m_EndF2L);
	DDX_Text(pDX, IDC_END_RA_L2R, m_EndL2R);
	DDX_Text(pDX, IDC_END_RA_T2B, m_EndT2B);
	DDX_Text(pDX, IDC_START_RA_F2B, m_StartF2B);
	DDX_CBString(pDX, IDC_OUTL_COLR, m_nOutLineClr);
	DDX_Check(pDX, IDC_AUTO_LOCK_RANGE, m_autoLock);
	DDX_Radio(pDX, IDC_HONOR_REQ, m_calcIntent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorFormDlg, CDialog)
	//{{AFX_MSG_MAP(CColorFormDlg)
	ON_BN_CLICKED(IDC_LOCKED, OnLocked)
	ON_BN_CLICKED(IDC_LOCKED2, OnLocked2)
	ON_BN_CLICKED(IDC_LOCKED3, OnLocked3)
	ON_BN_CLICKED(IDC_LOCKED4, OnLocked4)
	ON_BN_CLICKED(IDC_LOCKED5, OnLocked5)
	ON_BN_CLICKED(IDC_LOCKED6, OnLocked6)
	ON_BN_CLICKED(IDC_LOCKED7, OnLocked7)
	ON_BN_CLICKED(IDC_LOCKED8, OnLocked8)
	ON_BN_CLICKED(IDC_COLOR_JUMP, OnColorJump)
	ON_BN_CLICKED(IDC_RADIO_RGB, OnRadioRgb)
	ON_BN_CLICKED(IDC_RADIO_CMYK, OnRadioCmyk)
	ON_BN_CLICKED(IDC_RADIO_CMY, OnRadioCmy)
	ON_CBN_SELCHANGE(IDC_MAX_STEPS, OnSelchangeMaxSteps)
	ON_EN_CHANGE(IDC_END_RA_F2B, OnChangeEndRaF2b)
	ON_EN_CHANGE(IDC_END_RA_F2L, OnChangeEndRaF2l)
	ON_EN_CHANGE(IDC_END_RA_L2R, OnChangeEndRaL2r)
	ON_EN_CHANGE(IDC_END_RA_T2B, OnChangeEndRaT2b)
	ON_EN_CHANGE(IDC_START_RA_F2B, OnChangeStartRaF2b)
	ON_EN_CHANGE(IDC_START_RA_F2L, OnChangeStartRaF2l)
	ON_EN_CHANGE(IDC_START_RA_L2R, OnChangeStartRaL2r)
	ON_EN_CHANGE(IDC_START_RA_T2B, OnChangeStartRaT2b)
	ON_CBN_SELCHANGE(IDC_OUTL_COLR, OnSelchangeOutlColr)
	ON_BN_CLICKED(IDC_COLOR_RESET, OnColorReset)
	ON_BN_CLICKED(IDC_COMPUTE_COLOR, OnComputeColorRange)
	ON_BN_CLICKED(IDC_AUTO_LOCK_RANGE, OnAutoLockRange)
	ON_BN_CLICKED(IDC_HONOR_REQ, OnHonorReq)
	ON_BN_CLICKED(IDC_PRESERVE_LAY, OnPreserveLay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorFormDlg message handlers

BOOL CColorFormDlg::OnInitDialog() 
{
	//initialize combo boxes
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	int color = pDoc->m_dColorMode;	

	m_next = FALSE;


	CComboBox *pOutlCmbo = 
		(CComboBox*)GetDlgItem(IDC_OUTL_COLR);
	ASSERT(pOutlCmbo != NULL);

	pOutlCmbo->AddString("white");
	pOutlCmbo->AddString("black");
	pOutlCmbo->AddString("gray");
	pOutlCmbo->AddString("same as cell");


	CComboBox *pStepCmbo = 
		(CComboBox*)GetDlgItem(IDC_MAX_STEPS);
	ASSERT(pStepCmbo != NULL);

	pStepCmbo->AddString("steps (0 to 255)");
	pStepCmbo->AddString("hexadecimal (00 to FF)");
	pStepCmbo->AddString("percent (0 to 100)");


	if(color!=1)
	{
		CBitmapButton* bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED);
		bn->EnableWindow(FALSE);
		bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED2);
		bn->EnableWindow(FALSE);
	}
	m_LockBn.AutoLoad(IDC_LOCKED,this);
	if(!m_TogLock)m_LockBn.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,IDB_LOCKEDX);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
		pEd->EnableWindow(FALSE);
		m_LockBn.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,IDB_LOCKEDX);
	}
	m_LockBn.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn2.AutoLoad(IDC_LOCKED2,this);
	if(!m_TogLock2)m_LockBn2.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,IDB_LOCKEDX);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
		pEd->EnableWindow(FALSE);
		m_LockBn2.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,IDB_LOCKEDX);
	}
	m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn3.AutoLoad(IDC_LOCKED3,this);	
	if(!m_TogLock3)m_LockBn3.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2L);
		pEd->EnableWindow(FALSE);
		m_LockBn3.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn3.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn4.AutoLoad(IDC_LOCKED4,this);
	if(!m_TogLock4)m_LockBn4.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2L);
		pEd->EnableWindow(FALSE);
		m_LockBn4.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn5.AutoLoad(IDC_LOCKED5,this);
	if(!m_TogLock5)m_LockBn5.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_T2B);
		pEd->EnableWindow(FALSE);
		m_LockBn5.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn6.AutoLoad(IDC_LOCKED6,this);
	if(!m_TogLock6)m_LockBn6.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_T2B);
		pEd->EnableWindow(FALSE);
		m_LockBn6.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn7.AutoLoad(IDC_LOCKED7,this);
	if(!m_TogLock7)m_LockBn7.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_L2R);
		pEd->EnableWindow(FALSE);
		m_LockBn7.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);


	m_LockBn8.AutoLoad(IDC_LOCKED8,this);
	if(!m_TogLock8)m_LockBn8.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_L2R);
		pEd->EnableWindow(FALSE);
		m_LockBn8.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn8.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_tl = m_TogLock;
	m_tl2 = m_TogLock2;
	m_tl3 = m_TogLock3;
	m_tl4 = m_TogLock4;
	m_tl5 = m_TogLock5;
	m_tl6 = m_TogLock6;
	m_tl7 = m_TogLock7;
	m_tl8 = m_TogLock8;

	m_lockChange = FALSE;
	m_lock2Change = FALSE;
	m_lock3Change = FALSE;
	m_lock4Change = FALSE;
	m_lock5Change = FALSE;
	m_lock6Change = FALSE;
	m_lock7Change = FALSE;
	m_lock8Change = FALSE;


	m_startL2RChange = FALSE;
	m_startT2BChange = FALSE;
	m_startF2LChange = FALSE;
	m_startF2BChange = FALSE;
	m_endL2RChange = FALSE;
	m_endT2BChange = FALSE;
	m_endF2LChange = FALSE;
	m_endF2BChange = FALSE;

	m_origCalcIntent = m_calcIntent;

	CDialog::OnInitDialog();

	if(color!=1)
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
		pEd->EnableWindow(FALSE);
		pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
		pEd->EnableWindow(FALSE);
	}
	//CSerioDoc* pDoc = CSerioDoc::GetDoc();
	int colorMode = pDoc->m_dColorMode;
	int oCode;
	if(colorMode==0)oCode = pDoc->m_dOrientation_0;
	if(colorMode==1)oCode = pDoc->m_dOrientation_1;
	if(colorMode==2)oCode = pDoc->m_dOrientation_2;


	CString axis1Str = GetAxisString(oCode,1);
	CString axis2Str = GetAxisString(oCode,2);
	CString axis3Str = GetAxisString(oCode,3);
	CString axis4Str = GetAxisString(oCode,4);

	m_ax1str = axis1Str;
	m_ax2str = axis2Str;
	m_ax3str = axis3Str;
	m_ax4str = axis4Str;

	SetDlgItemText(IDC_DYN_L2R,axis3Str);
	SetDlgItemText(IDC_DYN_T2B,axis1Str);
	SetDlgItemText(IDC_DYN_F2L,axis2Str);
	SetDlgItemText(IDC_DYN_F2B,axis4Str);

	m_origModel = m_nColorMode;
	m_origSteps = m_nMaxSteps;
	m_out = m_nOutLineClr;
	m_autoLock = FALSE;
	//m_sBasis = m_StepBas;


	//for OnSelchangeMaxSteps()
	m_start1prec = (float)m_StartL2R;
	m_start2prec = (float)m_StartT2B;
	m_start3prec = (float)m_StartF2L;
	m_start4prec = (float)m_StartF2B;
	m_end1prec = (float)m_EndL2R;
	m_end2prec = (float)m_EndT2B;
	m_end3prec = (float)m_EndF2L;
	m_end4prec = (float)m_EndF2B;
	if(m_nMaxSteps=="hexadecimal (00 to FF)")
		{m_lastSel = 0;m_resetSel = m_lastSel;}
	if(m_nMaxSteps=="percent (0 to 100)")
		{m_lastSel = 3;m_resetSel = m_lastSel;}//temp code value
	if(m_nMaxSteps=="steps (0 to 255)")
		{m_lastSel = 2;m_resetSel = m_lastSel;}

	if(m_lastSel==3)ConvertRangeValues(TRUE,TRUE);



	m_efb = m_EndF2B;
	m_efl = m_EndF2L;
	m_etb = m_EndT2B;
	m_elr = m_EndL2R;
	m_sfb = m_StartF2B;
	m_sfl = m_StartF2L;
	m_stb = m_StartT2B;
	m_slr = m_StartL2R;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CColorFormDlg::OnLocked() 
{
	if(m_TogLock)
	{
		m_LockBn.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,IDB_UNLOCKEDX);
		m_LockBn.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock = FALSE;
		if(!m_resetCall)
		{
			CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
			pEd->EnableWindow(TRUE);
		}
		
	}
	else if(!m_TogLock)
	{
		m_LockBn.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,IDB_LOCKEDX);
		m_LockBn.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock = TRUE;
		if(!m_resetCall)
		{
			CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
			pEd->EnableWindow(FALSE);
		}
	}
	m_lockChange = TRUE;
}

void CColorFormDlg::OnLocked2() 
{
	if(m_TogLock2)
	{
		m_LockBn2.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,IDB_UNLOCKEDX);
		m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock2 = FALSE;
		if(!m_resetCall)
		{
			CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
			pEd->EnableWindow(TRUE);
		}
	}
	else if(!m_TogLock2)
	{
		m_LockBn2.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,IDB_LOCKEDX);
		m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock2 = TRUE;
		if(!m_resetCall)
		{
			CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
			pEd->EnableWindow(FALSE);
		}
	}
	m_lock2Change = TRUE;
}

void CColorFormDlg::OnLocked3() 
{
	if(m_TogLock3)
	{
		m_LockBn3.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn3.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock3 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2L);
		pEd->EnableWindow(TRUE);
	}
	else if(!m_TogLock3)
	{
		m_LockBn3.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn3.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock3 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2L);
		pEd->EnableWindow(FALSE);
	}
	m_lock3Change = TRUE;
}

void CColorFormDlg::OnLocked4() 
{
	if(m_TogLock4)
	{
		m_LockBn4.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock4 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2L);
		pEd->EnableWindow(TRUE);
	}
	else if(!m_TogLock4)
	{
		m_LockBn4.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock4 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2L);
		pEd->EnableWindow(FALSE);
	}
	m_lock4Change = TRUE;
}

void CColorFormDlg::OnLocked5() 
{
	if(m_TogLock5)
	{
		m_LockBn5.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock5 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_T2B);
		pEd->EnableWindow(TRUE);
	}
	else if(!m_TogLock5)
	{
		m_LockBn5.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock5 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_T2B);
		pEd->EnableWindow(FALSE);
	}
	m_lock5Change = TRUE;
}

void CColorFormDlg::OnLocked6() 
{
	if(m_TogLock6)
	{
		m_LockBn6.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock6 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_T2B);
		pEd->EnableWindow(TRUE);
	}
	else if(!m_TogLock6)
	{
		m_LockBn6.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock6 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_T2B);
		pEd->EnableWindow(FALSE);
	}
	m_lock6Change = TRUE;
}

void CColorFormDlg::OnLocked7() 
{
	if(m_TogLock7)
	{
		m_LockBn7.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock7 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_L2R);
		pEd->EnableWindow(TRUE);
	}
	else if(!m_TogLock7)
	{
		m_LockBn7.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,IDB_LOCKEDX);
		m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock7 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_L2R);
		pEd->EnableWindow(FALSE);
	}
	m_lock7Change = TRUE;
}

void CColorFormDlg::OnLocked8() 
{
	if(m_TogLock8)
	{
		m_LockBn8.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn8.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock8 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_L2R);
		pEd->EnableWindow(TRUE);
	}
	else if(!m_TogLock8)
	{
		m_LockBn8.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn8.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock8 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_L2R);
		pEd->EnableWindow(FALSE);
	}
	m_lock8Change = TRUE;
}

void CColorFormDlg::OnColorJump() 
{	
	m_next = TRUE;
	UpdateData(TRUE);
	if(m_lastSel==0)
	{
		ConvertRangeValues(FALSE,TRUE);
		UpdateData(FALSE);
	}

	CDialog::OnOK();
}

void CColorFormDlg::PostNcDestroy() 
{
	
//	CSerioDoc* pDcmt = CSerioDoc::GetDoc();	
		
//	if(pDcmt->GetNextVal())pDcmt->CallDialog(2);
	
	CDialog::PostNcDestroy();
}

void CColorFormDlg::OnRadioRgb() 
{
	CBitmapButton* bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED);
	bn->EnableWindow(FALSE);
	bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED2);
	bn->EnableWindow(FALSE);

	CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
	pEd->EnableWindow(FALSE);
	pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
	pEd->EnableWindow(FALSE);

	SetDlgItemText(IDC_DYN_L2R,"RED");
	SetDlgItemText(IDC_DYN_T2B,"BLUE");
	SetDlgItemText(IDC_DYN_F2L,"GREEN");
	SetDlgItemText(IDC_DYN_F2B,"");
	UpdateData(TRUE);
}

void CColorFormDlg::OnRadioCmy() 
{
	CBitmapButton* bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED);
	bn->EnableWindow(FALSE);
	bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED2);
	bn->EnableWindow(FALSE);

	CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
	pEd->EnableWindow(FALSE);
	pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
	pEd->EnableWindow(FALSE);

	SetDlgItemText(IDC_DYN_L2R,"MAGENTA");
	SetDlgItemText(IDC_DYN_T2B,"CYAN");
	SetDlgItemText(IDC_DYN_F2L,"YELLOW");
	SetDlgItemText(IDC_DYN_F2B,"");

	UpdateData(TRUE);
}

void CColorFormDlg::OnRadioCmyk() 
{
	CBitmapButton* bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED);
	bn->EnableWindow(TRUE);
	bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED2);
	bn->EnableWindow(TRUE);

	if(m_TogLock)
	{
		m_LockBn.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,IDB_LOCKEDX);
		m_LockBn.SetButtonStyle(BS_OWNERDRAW,TRUE);
	}
	if(!m_TogLock)
	{
		m_LockBn.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,IDB_UNLOCKEDX);
		m_LockBn.SetButtonStyle(BS_OWNERDRAW,TRUE);
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
		pEd->EnableWindow(TRUE);
	}
	if(m_TogLock2)
	{
		m_LockBn2.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,IDB_LOCKEDX);
		m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);
	}
	if(!m_TogLock2)
	{
		m_LockBn2.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,IDB_UNLOCKEDX);
		m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
		pEd->EnableWindow(TRUE);
	}

	SetDlgItemText(IDC_DYN_L2R,"MAGENTA");
	SetDlgItemText(IDC_DYN_T2B,"CYAN");
	SetDlgItemText(IDC_DYN_F2L,"YELLOW");
	SetDlgItemText(IDC_DYN_F2B,"BLACK");

	UpdateData(TRUE);
}


void CColorFormDlg::OnSelchangeMaxSteps() 
{
	BOOL toPercent = FALSE;
	int index;
	CComboBox* pBo =
		(CComboBox*)GetDlgItem(IDC_MAX_STEPS);
	ASSERT(pBo != NULL);
	index = pBo->GetCurSel();
	if(index < 0) AfxMessageBox("CB ERR");
	if(index==0)m_nMaxSteps = "hexadecimal (00 to FF)";
	if(index==1)
	{
		m_nMaxSteps = "percent (0 to 100)";
		toPercent = TRUE;
	}
	if(index==2)m_nMaxSteps = "steps (0 to 255)";
	BOOL convert = FALSE;
	convert = ConvertRangeValues(toPercent,FALSE);
	if(convert)UpdateData(FALSE);
	m_lastSel = index;
}

BOOL CColorFormDlg::ConvertRangeValues(BOOL toPer,BOOL final)
{
	float rate;
	BOOL go = FALSE,init = FALSE;
	if(toPer && m_lastSel!=1 && m_lastSel!=3 )
	{
		go = TRUE;
		rate = 0.392156;
		//if(!final)m_nMaxSteps = "percent (0 to 100)";
	}
	if(!toPer && m_lastSel==1)
	{
		go = TRUE;
		rate = 2.55;
		//if(!final)m_nMaxSteps = "steps (0 to 255)";
	}
	if(toPer && m_lastSel==3)
	{
		go = TRUE;
		rate = 0.392156;
		m_lastSel = 1;
		m_resetSel = 1;
		init = TRUE;
	}
	if(go)
	{
		ConvertToFromPercent(rate);
	}
	if(init)UpdateData(FALSE);
	return go;
}

void CColorFormDlg::ConvertToFromPercent(double rate)
{
		m_StartL2R = GetRounded(m_start1prec * rate);
		m_StartT2B = GetRounded(m_start2prec * rate);
		m_StartF2L = GetRounded(m_start3prec * rate);
		m_StartF2B = GetRounded(m_start4prec * rate);
		m_EndL2R = GetRounded(m_end1prec * rate);
		m_EndT2B = GetRounded(m_end2prec * rate);
		m_EndF2L = GetRounded(m_end3prec * rate);
		m_EndF2B = GetRounded(m_end4prec * rate);
		m_start1prec = m_start1prec * rate;
		m_start2prec = m_start2prec * rate;
		m_start3prec = m_start3prec * rate;
		m_start4prec = m_start4prec * rate;
		m_end1prec = m_end1prec * rate;
		m_end2prec = m_end2prec * rate;
		m_end3prec = m_end3prec * rate;
		m_end4prec = m_end4prec * rate;
}

int CColorFormDlg::GetRounded(float fig)
{
	float f = fig;
	int val;
	for( ;f>=1; )
	{
		f = f - 1;
	}
	val = (int)fig;
	if(f>=0.5)val++;

	return val;
}

void CColorFormDlg::OnChangeEndRaF2b() 
{
	if(m_TogLock2) UpdateData(FALSE);
	int test = GetDlgItemInt(IDC_END_RA_F2B,NULL,TRUE);
	if(m_nMaxSteps=="percent (0 to 100)" && test > 100)UpdateData(FALSE);
	if(m_nMaxSteps=="steps (0 to 255)" && test > 255)UpdateData(FALSE);
	if(test<0)UpdateData(FALSE);
	if(!m_TogLock2)
	{
		UpdateData(TRUE);
		m_end4prec = (float)GetDlgItemInt(IDC_END_RA_F2B,NULL,TRUE);
		m_endF2BChange = TRUE;
	}
}

void CColorFormDlg::OnChangeEndRaF2l() 
{
	if(m_TogLock4) UpdateData(FALSE);
	int test = GetDlgItemInt(IDC_END_RA_F2L,NULL,TRUE);
	if(m_nMaxSteps=="percent (0 to 100)" && test > 100)UpdateData(FALSE);
	if(m_nMaxSteps=="steps (0 to 255)" && test > 255)UpdateData(FALSE);
	if(test<0)UpdateData(FALSE);
	if(!m_TogLock4)
	{
		UpdateData(TRUE);
		m_end3prec = (float)GetDlgItemInt(IDC_END_RA_F2L,NULL,TRUE);
		m_endF2LChange = TRUE;
	}
}

void CColorFormDlg::OnChangeEndRaL2r() 
{
	if(m_TogLock8) UpdateData(FALSE);
	int test = GetDlgItemInt(IDC_END_RA_L2R,NULL,TRUE);
	if(m_nMaxSteps=="percent (0 to 100)" && test > 100)UpdateData(FALSE);
	if(m_nMaxSteps=="steps (0 to 255)" && test > 255)UpdateData(FALSE);
	if(test<0)UpdateData(FALSE);
	if(!m_TogLock8)
	{
		UpdateData(TRUE);
		m_end1prec = (float)GetDlgItemInt(IDC_END_RA_L2R,NULL,TRUE);
		m_endL2RChange = TRUE;
	}
}

void CColorFormDlg::OnChangeEndRaT2b() 
{
	if(m_TogLock6) UpdateData(FALSE);
	int test = GetDlgItemInt(IDC_END_RA_T2B,NULL,TRUE);
	if(m_nMaxSteps=="percent (0 to 100)" && test > 100)UpdateData(FALSE);
	if(m_nMaxSteps=="steps (0 to 255)" && test > 255)UpdateData(FALSE);
	if(test<0)UpdateData(FALSE);
	if(!m_TogLock6)
	{
		UpdateData(TRUE);
		m_end2prec = (float)GetDlgItemInt(IDC_END_RA_T2B,NULL,TRUE);
		m_endT2BChange = TRUE;
	}
}

void CColorFormDlg::OnChangeStartRaF2b() 
{
	if(m_TogLock) UpdateData(FALSE);
	int test = GetDlgItemInt(IDC_START_RA_F2B,NULL,TRUE);
	if(m_nMaxSteps=="percent (0 to 100)" && test > 100)UpdateData(FALSE);
	if(m_nMaxSteps=="steps (0 to 255)" && test > 255)UpdateData(FALSE);
	if(test<0)UpdateData(FALSE);
	if(!m_TogLock)
	{
		UpdateData(TRUE);
		m_start4prec = (float)GetDlgItemInt(IDC_START_RA_F2B,NULL,TRUE);
		m_startF2BChange = TRUE;
	}
}

void CColorFormDlg::OnChangeStartRaF2l() 
{
	if(m_TogLock3) UpdateData(FALSE);
	int test = GetDlgItemInt(IDC_START_RA_F2L,NULL,TRUE);
	if(m_nMaxSteps=="percent (0 to 100)" && test > 100)UpdateData(FALSE);
	if(m_nMaxSteps=="steps (0 to 255)" && test > 255)UpdateData(FALSE);
	if(test<0)UpdateData(FALSE);
	if(!m_TogLock3)
	{
		UpdateData(TRUE);
		m_start3prec = (float)GetDlgItemInt(IDC_START_RA_F2L,NULL,TRUE);
		m_startF2LChange = TRUE;
	}
}

void CColorFormDlg::OnChangeStartRaL2r() 
{
	if(m_TogLock7) UpdateData(FALSE);
	int test = GetDlgItemInt(IDC_START_RA_L2R,NULL,TRUE);
	if(m_nMaxSteps=="percent (0 to 100)" && test > 100)UpdateData(FALSE);
	if(m_nMaxSteps=="steps (0 to 255)" && test > 255)UpdateData(FALSE);
	if(test<0)UpdateData(FALSE);
	if(!m_TogLock7)
	{
		UpdateData(TRUE);
		m_start1prec = (float)GetDlgItemInt(IDC_START_RA_L2R,NULL,TRUE);
		m_startL2RChange = TRUE;
	}
}

void CColorFormDlg::OnChangeStartRaT2b() 
{
	if(m_TogLock5) UpdateData(FALSE);
	int test = GetDlgItemInt(IDC_START_RA_T2B,NULL,TRUE);
	if(m_nMaxSteps=="percent (0 to 100)" && test > 100)UpdateData(FALSE);
	if(m_nMaxSteps=="steps (0 to 255)" && test > 255)UpdateData(FALSE);
	if(test<0)UpdateData(FALSE);
	if(!m_TogLock5)
	{
		UpdateData(TRUE);
		m_start2prec = (float)GetDlgItemInt(IDC_START_RA_T2B,NULL,TRUE);
		m_startT2BChange = TRUE;
	}
}

void CColorFormDlg::OnOK() 
{
	OnComputeColorRange();

	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	CString curStart;
	BOOL startMax = FALSE;
	int i = 0;
	int val[8];
	val[i] = GetDlgItemInt(IDC_START_RA_F2B,NULL,TRUE);
	val[++i] = GetDlgItemInt(IDC_END_RA_F2B,NULL,TRUE);
	val[++i] = GetDlgItemInt(IDC_START_RA_F2L,NULL,TRUE);
	val[++i] = GetDlgItemInt(IDC_END_RA_F2L,NULL,TRUE);
	val[++i] = GetDlgItemInt(IDC_START_RA_T2B,NULL,TRUE);
	val[++i] = GetDlgItemInt(IDC_END_RA_T2B,NULL,TRUE);
	val[++i] = GetDlgItemInt(IDC_START_RA_L2R,NULL,TRUE);
	val[++i] = GetDlgItemInt(IDC_END_RA_L2R,NULL,TRUE);
	for(i=0;i<8;i++)
	{
		int val1,val2;
		val1 = val[i];
		val2 = val[++i];
		if(val1>val2)startMax = TRUE;
		if(val1<=val2)startMax = FALSE;
		if(i==1)curStart = pDoc->m_strArray[19];
		if(i==3)curStart = pDoc->m_strArray[20];
		if(i==5)curStart = pDoc->m_strArray[30];
		if(i==7)curStart = pDoc->m_strArray[29];
		if(curStart=="the MINIMUM value" && startMax)
		{
			if(i==1)pDoc->m_strArray[19] = "the MAXIMUM value";
			if(i==3)pDoc->m_strArray[20] = "the MAXIMUM value";
			if(i==5)pDoc->m_strArray[30] = "the MAXIMUM value";
			if(i==7)pDoc->m_strArray[29] = "the MAXIMUM value";
		}
		if(curStart=="the MAXIMUM value" && !startMax)
		{
			if(i==1)pDoc->m_strArray[19] = "the MINIMUM value";
			if(i==3)pDoc->m_strArray[20] = "the MINIMUM value";
			if(i==5)pDoc->m_strArray[30] = "the MINIMUM value";
			if(i==7)pDoc->m_strArray[29] = "the MINIMUM value";
		}
	}
	if(m_lastSel==1)
	{
		UpdateData(TRUE);
		ConvertRangeValues(FALSE,TRUE);
		UpdateData(FALSE);
	}
	
	CDialog::OnOK();
}


void CColorFormDlg::OnCancel() 
{

	CDialog::OnCancel();
}

void CColorFormDlg::OnSelchangeOutlColr() 
{
	int index;
	CComboBox* pBo =
		(CComboBox*)GetDlgItem(IDC_OUTL_COLR);
	ASSERT(pBo != NULL);
	index = pBo->GetCurSel();
	if(index < 0) AfxMessageBox("CB ERR");
	if(index==0)m_nOutLineClr = "black";
	if(index==1)m_nOutLineClr = "gray";
	if(index==2)m_nOutLineClr = "same as cell";
	if(index==3)m_nOutLineClr = "white";
	UpdateData(FALSE);
}

extern CCalc scratchPad;

void CColorFormDlg::OnColorReset() 
{
	BOOL box1On=FALSE, box1Off=FALSE, box2On=FALSE, box2Off=FALSE;
	BOOL sameModel = TRUE;
	BOOL disable = FALSE;
	BOOL enable = FALSE;
	if(m_origModel!=m_nColorMode)
	{
		sameModel = FALSE;
		if(m_origModel==1)enable = TRUE;
		if(m_nColorMode==1)disable = TRUE;
	}
	if(enable)//back to CMYK
	{
		if(!m_tl)box1On = TRUE;
		if(!m_tl2)box2On = TRUE;
		CBitmapButton* bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED);
		bn->EnableWindow(TRUE);
		bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED2);
		bn->EnableWindow(TRUE);
	}
	if(disable)//leaving CMYK
	{
		if(!m_TogLock)box1Off = TRUE;
		if(!m_TogLock2)box2Off = TRUE;
		CBitmapButton* bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED);
		bn->EnableWindow(FALSE);
		bn = (CBitmapButton*)GetDlgItem(IDC_LOCKED2);
		bn->EnableWindow(FALSE);
	}
	if(sameModel && m_origModel==1)//neither leaving nor returning to a model 
	{
		if(m_tl && !m_TogLock)box1Off = TRUE;
		if(!m_tl && m_TogLock)box1On = TRUE;
		if(m_tl2 && !m_TogLock2)box2Off = TRUE;
		if(!m_tl2 && m_TogLock2)box2On = TRUE;
	}
	CEdit* pEd;
	if(box1Off)
	{
		pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
		pEd->EnableWindow(FALSE);
	}
	if(box1On)
	{
		pEd = (CEdit*)GetDlgItem(IDC_START_RA_F2B);
		pEd->EnableWindow(TRUE);
	}
	if(box2Off)
	{
		pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
		pEd->EnableWindow(FALSE);
	}
	if(box2On)
	{
		pEd = (CEdit*)GetDlgItem(IDC_END_RA_F2B);
		pEd->EnableWindow(TRUE);
	}

	m_resetCall = TRUE;				  //redundant? see OnLockedX()
	if(m_TogLock8!=m_tl8){OnLocked8();m_TogLock8 = m_tl8;}
	if(m_TogLock7!=m_tl7){OnLocked7();m_TogLock7 = m_tl7;}
	if(m_TogLock6!=m_tl6){OnLocked6();m_TogLock6 = m_tl6;}
	if(m_TogLock5!=m_tl5){OnLocked5();m_TogLock5 = m_tl5;}
	if(m_TogLock4!=m_tl4){OnLocked4();m_TogLock4 = m_tl4;}
	if(m_TogLock3!=m_tl3){OnLocked3();m_TogLock3 = m_tl3;}
	if(m_TogLock2!=m_tl2){OnLocked2();m_TogLock2 = m_tl2;}
	if(m_TogLock!=m_tl){OnLocked();m_TogLock = m_tl;}

	m_lockChange = FALSE;
	m_lock2Change = FALSE;
	m_lock3Change = FALSE;
	m_lock4Change = FALSE;
	m_lock5Change = FALSE;
	m_lock6Change = FALSE;
	m_lock7Change = FALSE;
	m_lock8Change = FALSE;


	SetDlgItemText(IDC_DYN_L2R,m_ax3str);
	SetDlgItemText(IDC_DYN_T2B,m_ax1str);
	SetDlgItemText(IDC_DYN_F2L,m_ax2str);
	SetDlgItemText(IDC_DYN_F2B,m_ax4str);

	UpdateData(TRUE);
	m_EndF2B = m_efb;
	m_EndF2L = m_efl;
	m_EndT2B = m_etb;
	m_EndL2R = m_elr;
	m_StartF2B = m_sfb;
	m_StartF2L = m_sfl;
	m_StartT2B = m_stb;
	m_StartL2R = m_slr;

	m_end4prec = (float)m_efb;
	m_end3prec = (float)m_efl;
	m_end2prec = (float)m_etb;
	m_end1prec = (float)m_elr;
	m_start4prec = (float)m_sfb;
	m_start3prec = (float)m_sfl;
	m_start2prec = (float)m_stb;
	m_start1prec = (float)m_slr;

	m_nColorMode = m_origModel;
	m_nMaxSteps = m_origSteps;
	m_nOutLineClr = m_out;
	m_calcIntent = m_origCalcIntent;
	//m_StepBas = m_sBasis;
	m_autoLock = FALSE;
	m_lastSel = m_resetSel;
	m_resetCall = FALSE;

	UpdateData(FALSE);	

	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	pDoc->RegisterAspects();
	::scratchPad.LoadCalcMembers();

	m_startL2RChange = FALSE;
	m_startT2BChange = FALSE;
	m_startF2LChange = FALSE;
	m_startF2BChange = FALSE;
	m_endL2RChange = FALSE;
	m_endT2BChange = FALSE;
	m_endF2LChange = FALSE;
	m_endF2BChange = FALSE;
}

CString CColorFormDlg::GetAxisString(int oCode,int axis)
{
	CString str;
	if(oCode<7)
	{
		if(oCode==1)
		{
			if(axis==1)str = "RED";
			if(axis==2)str = "GREEN";
			if(axis==3)str = "BLUE";
			if(axis==4)str = "";
		}
		if(oCode==2)
		{
			if(axis==1)str = "RED";
			if(axis==2)str = "BLUE";
			if(axis==3)str = "GREEN";
			if(axis==4)str = "";
		}
		if(oCode==3)
		{
			if(axis==1)str = "GREEN";
			if(axis==2)str = "BLUE";
			if(axis==3)str = "RED";
			if(axis==4)str = "";

		}
		if(oCode==4)
		{
			if(axis==1)str = "GREEN";
			if(axis==2)str = "RED";
			if(axis==3)str = "BLUE";
			if(axis==4)str = "";
		}
		if(oCode==5)
		{
			if(axis==1)str = "BLUE";
			if(axis==2)str = "RED";
			if(axis==3)str = "GREEN";
			if(axis==4)str = "";
		}
		if(oCode==6)
		{
			if(axis==1)str = "BLUE";
			if(axis==2)str = "GREEN";
			if(axis==3)str = "RED";
			if(axis==4)str = "";
		}
	}
	if(oCode>=7 && oCode<=12)
	{
		if(oCode==7)
		{
			if(axis==1)str = "CYAN";
			if(axis==2)str = "MAGENTA";
			if(axis==3)str = "YELLOW";
			if(axis==4)str = "";
		}
		if(oCode==8)
		{
			if(axis==1)str = "CYAN";
			if(axis==2)str = "YELLOW";
			if(axis==3)str = "MAGENTA";
			if(axis==4)str = "";
		}
		if(oCode==9)
		{
			if(axis==1)str = "MAGENTA";
			if(axis==2)str = "CYAN";
			if(axis==3)str = "YELLOW";
			if(axis==4)str = "";

		}
		if(oCode==10)
		{
			if(axis==1)str = "MAGENTA";
			if(axis==2)str = "YELLOW";
			if(axis==3)str = "CYAN";
			if(axis==4)str = "";
		}
		if(oCode==11)
		{
			if(axis==1)str = "YELLOW";
			if(axis==2)str = "CYAN";
			if(axis==3)str = "MAGENTA";
			if(axis==4)str = "";
		}
		if(oCode==12)
		{
			if(axis==1)str = "YELLOW";
			if(axis==2)str = "MAGENTA";
			if(axis==3)str = "CYAN";
			if(axis==4)str = "";
		}

	}
	if(oCode>12)
	{
		if(oCode==13)
		{
			if(axis==1)str = "CYAN";
			if(axis==2)str = "MAGENTA";
			if(axis==3)str = "YELLOW";
			if(axis==4)str = "BLACK";
		}
		if(oCode==14)
		{
			if(axis==1)str = "CYAN";
			if(axis==2)str = "YELLOW";
			if(axis==3)str = "MAGENTA";
			if(axis==4)str = "BLACK";
		}
		if(oCode==15)
		{
			if(axis==1)str = "MAGENTA";
			if(axis==2)str = "YELLOW";
			if(axis==3)str = "CYAN";
			if(axis==4)str = "BLACK";
		}
		if(oCode==16)
		{
			if(axis==1)str = "MAGENTA";
			if(axis==2)str = "CYAN";
			if(axis==3)str = "YELLOW";
			if(axis==4)str = "BLACK";
		}
		if(oCode==17)
		{
			if(axis==1)str = "YELLOW";
			if(axis==2)str = "CYAN";
			if(axis==3)str = "MAGENTA";
			if(axis==4)str = "BLACK";
		}
		if(oCode==18)
		{
			if(axis==1)str = "YELLOW";
			if(axis==2)str = "MAGENTA";
			if(axis==3)str = "CYAN";
			if(axis==4)str = "BLACK";
		}
		if(oCode==19)
		{
			if(axis==1)str = "CYAN";
			if(axis==2)str = "MAGENTA";
			if(axis==3)str = "BLACK";
			if(axis==4)str = "YELLOW";
		}
		if(oCode==20)
		{
			if(axis==1)str = "CYAN";
			if(axis==2)str = "BLACK";
			if(axis==3)str = "MAGENTA";
			if(axis==4)str = "YELLOW";
		}
		if(oCode==21)
		{
			if(axis==1)str = "MAGENTA";
			if(axis==2)str = "CYAN";
			if(axis==3)str = "BLACK";
			if(axis==4)str = "YELLOW";
		}
		if(oCode==22)
		{
			if(axis==1)str = "MAGENTA";
			if(axis==2)str = "BLACK";
			if(axis==3)str = "CYAN";
			if(axis==4)str = "YELLOW";
		}
		if(oCode==23)
		{
			if(axis==1)str = "BLACK";
			if(axis==2)str = "MAGENTA";
			if(axis==3)str = "CYAN";
			if(axis==4)str = "YELLOW";
		}
		if(oCode==24)
		{
			if(axis==1)str = "BLACK";
			if(axis==2)str = "CYAN";
			if(axis==3)str = "MAGENTA";
			if(axis==4)str = "YELLOW";
		}
		if(oCode==25)
		{
			if(axis==1)str = "CYAN";
			if(axis==2)str = "BLACK";
			if(axis==3)str = "YELLOW";
			if(axis==4)str = "MAGENTA";
		}
		if(oCode==26)
		{
			if(axis==1)str = "CYAN";
			if(axis==2)str = "YELLOW";
			if(axis==3)str = "BLACK";
			if(axis==4)str = "MAGENTA";
		}
		if(oCode==27)
		{
			if(axis==1)str = "YELLOW";
			if(axis==2)str = "CYAN";
			if(axis==3)str = "BLACK";
			if(axis==4)str = "MAGENTA";
		}
		if(oCode==28)
		{
			if(axis==1)str = "YELLOW";
			if(axis==2)str = "BLACK";
			if(axis==3)str = "CYAN";
			if(axis==4)str = "MAGENTA";
		}
		if(oCode==29)
		{
			if(axis==1)str = "BLACK";
			if(axis==2)str = "YELLOW";
			if(axis==3)str = "CYAN";
			if(axis==4)str = "MAGENTA";
		}
		if(oCode==30)
		{
			if(axis==1)str = "BLACK";
			if(axis==2)str = "CYAN";
			if(axis==3)str = "YELLOW";
			if(axis==4)str = "MAGENTA";
		}
		if(oCode==31)
		{
			if(axis==1)str = "MAGENTA";
			if(axis==2)str = "YELLOW";
			if(axis==3)str = "BLACK";
			if(axis==4)str = "CYAN";

		}
		if(oCode==32)
		{
			if(axis==1)str = "MAGENTA";
			if(axis==2)str = "BLACK";
			if(axis==3)str = "YELLOW";
			if(axis==4)str = "CYAN";
		}
		if(oCode==33)
		{
			if(axis==1)str = "YELLOW";
			if(axis==2)str = "MAGENTA";
			if(axis==3)str = "BLACK";
			if(axis==4)str = "CYAN";
		}
		if(oCode==34)
		{
			if(axis==1)str = "YELLOW";
			if(axis==2)str = "BLACK";
			if(axis==3)str = "MAGENTA";
			if(axis==4)str = "CYAN";
		}
		if(oCode==35)
		{
			if(axis==1)str = "BLACK";
			if(axis==2)str = "YELLOW";
			if(axis==3)str = "MAGENTA";
			if(axis==4)str = "CYAN";
		}
		if(oCode==36)
		{
			if(axis==1)str = "BLACK";
			if(axis==2)str = "MAGENTA";
			if(axis==3)str = "YELLOW";
			if(axis==4)str = "CYAN";
		}
	}
	return str;

}

void CColorFormDlg::OnComputeColorRange() 
{
	double rate = 2.55;
	if(m_lastSel==1)ConvertToFromPercent(rate);

	if(m_lockChange)
		::scratchPad.ChangeLocksAndFlags(33,m_TogLock);
	if(m_lock2Change)
		::scratchPad.ChangeLocksAndFlags(34,m_TogLock2);
	if(m_lock3Change)
		::scratchPad.ChangeLocksAndFlags(31,m_TogLock3);
	if(m_lock4Change)
		::scratchPad.ChangeLocksAndFlags(32,m_TogLock4);
	if(m_lock5Change)
		::scratchPad.ChangeLocksAndFlags(29,m_TogLock5);
	if(m_lock6Change)
		::scratchPad.ChangeLocksAndFlags(30,m_TogLock6);
	if(m_lock7Change)
		::scratchPad.ChangeLocksAndFlags(27,m_TogLock7);
	if(m_lock8Change)
		::scratchPad.ChangeLocksAndFlags(28,m_TogLock8);

	if(m_startL2RChange)::scratchPad.InstigateChange((UINT)m_StartL2R,27);
	if(m_startT2BChange)::scratchPad.InstigateChange((UINT)m_StartT2B,29);
	if(m_startF2LChange)::scratchPad.InstigateChange((UINT)m_StartF2L,31);
	if(m_startF2BChange)::scratchPad.InstigateChange((UINT)m_StartF2B,33);
	if(m_endL2RChange)::scratchPad.InstigateChange((UINT)m_EndL2R,28);
	if(m_endT2BChange)::scratchPad.InstigateChange((UINT)m_EndT2B,30);
	if(m_endF2LChange)::scratchPad.InstigateChange((UINT)m_EndF2L,32);
	if(m_endF2BChange)::scratchPad.InstigateChange((UINT)m_EndF2B,34);

	CSerioDoc * pDoc = CSerioDoc::GetDoc();
	int intentBuf = pDoc->m_dCalcIntent;
	pDoc->m_dCalcIntent = m_calcIntent;
	::scratchPad.m_calcIntent = m_calcIntent;
	
	::scratchPad.ProcessChangeRequests();

	pDoc->m_dCalcIntent = intentBuf;
	::scratchPad.m_calcIntent = intentBuf;
	
	CRegAspect * line;
	line = ::scratchPad.m_reg[27];
	m_start1prec = (double)line->m_nNuCount;
	line = ::scratchPad.m_reg[29];
	m_start2prec = (double)line->m_nNuCount;
	line = ::scratchPad.m_reg[31];
	m_start3prec = (double)line->m_nNuCount;
	line = ::scratchPad.m_reg[33];
	m_start4prec = (double)line->m_nNuCount;
	line = ::scratchPad.m_reg[28];
	m_end1prec = (double)line->m_nNuCount;
	line = ::scratchPad.m_reg[30];
	m_end2prec = (double)line->m_nNuCount;
	line = ::scratchPad.m_reg[32];
	m_end3prec = (double)line->m_nNuCount;
	line = ::scratchPad.m_reg[34];
	m_end4prec = (double)line->m_nNuCount;

	m_StartL2R = (UINT)m_start1prec;
	m_StartT2B = (UINT)m_start2prec;
	m_StartF2L = (UINT)m_start3prec;
	m_StartF2B = (UINT)m_start4prec;
	m_EndL2R = (UINT)m_end1prec;
	m_EndT2B = (UINT)m_end2prec;
	m_EndF2L = (UINT)m_end3prec;
	m_EndF2B = (UINT)m_end4prec;

	rate = 0.392156;
	if(m_lastSel==1)ConvertToFromPercent(rate);

	m_startL2RChange = FALSE;
	m_startT2BChange = FALSE;
	m_startF2LChange = FALSE;
	m_startF2BChange = FALSE;
	m_endL2RChange = FALSE;
	m_endF2LChange = FALSE;
	m_endF2BChange = FALSE;
	m_endT2BChange = FALSE;

	UpdateData(FALSE);
}

void CColorFormDlg::OnAutoLockRange() 
{
	m_autoLock = TRUE;
	
}

void CColorFormDlg::OnHonorReq() 
{
	m_calcIntent = 0;	
}

void CColorFormDlg::OnPreserveLay() 
{
	m_calcIntent = 1;	
}