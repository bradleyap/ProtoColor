// QuickLayout.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"

#include "SerioDoc.h"
#include "QuickLayout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuickLayout dialog


CQuickLayout::CQuickLayout(CWnd* pParent /*=NULL*/)
	: CDialog(CQuickLayout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuickLayout)
	m_nLeftMarg = 0.0f;
	m_nLowerMarg = 0.0f;
	m_nPageCount = 0;
	m_nPageHeight = 0.0f;
	m_nPageWidth = 0.0f;
	m_nShowPage = FALSE;
	m_nRightMarg = 0.0f;
	m_nUpperMarg = 0.0f;
	m_nUnits = _T("inches");
	m_nUnits1 = _T("inches");
	m_nUnits2 = _T("inches");
	m_nUnits3 = _T("inches");
	m_nUnits4 = _T("inches");
	m_nUnits5 = _T("inches");
	//}}AFX_DATA_INIT

	m_leftMchange = FALSE;
	m_rightMchange = FALSE;
	m_topMchange = FALSE;
	m_botMchange = FALSE;
	m_pageWchange = FALSE;
	m_pageHchange = FALSE;
	m_pageCchange = FALSE;

	m_Bn7 = FALSE;
	m_Bn6 = FALSE;
	m_Bn5 = FALSE;
	m_Bn4 = FALSE;
	m_Bn3 = FALSE;
	m_Bn2 = FALSE;
	m_Bn = FALSE;
	
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	m_saveMult = pDoc->m_dMargRat;

}


void CQuickLayout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuickLayout)
	DDX_Control(pDX, IDC_UPPER_M_EDIT, m_upMgCtl);
	DDX_Control(pDX, IDC_RIGHT_M_EDIT, m_rightMgCtl);
	DDX_Control(pDX, IDC_PAGEW_EDIT, m_pgWthCtl);
	DDX_Control(pDX, IDC_PAGEH_EDIT, m_pgHtCtl);
	DDX_Control(pDX, IDC_LOWER_M_EDIT, m_lowMgCtl);
	DDX_Control(pDX, IDC_LEFT_M_EDIT, m_leftMgCtl);
	DDX_Control(pDX, IDC_PAGE_COUNT, m_pageCountCtl);
	DDX_Control(pDX, IDC_CLICKABLE_STATIC, m_Click);
	DDX_Text(pDX, IDC_LEFT_M_EDIT, m_nLeftMarg);
	DDX_Text(pDX, IDC_LOWER_M_EDIT, m_nLowerMarg);
	DDX_Text(pDX, IDC_PAGE_COUNT, m_nPageCount);
	DDV_MinMaxInt(pDX, m_nPageCount, 1, 10000);
	DDX_Text(pDX, IDC_PAGEH_EDIT, m_nPageHeight);
	DDX_Text(pDX, IDC_PAGEW_EDIT, m_nPageWidth);
	DDX_Check(pDX, IDC_PAGINATE_CHK, m_nShowPage);
	DDX_Text(pDX, IDC_RIGHT_M_EDIT, m_nRightMarg);
	DDX_Text(pDX, IDC_UPPER_M_EDIT, m_nUpperMarg);
	DDX_CBString(pDX, IDC_UNIT_COMB2, m_nUnits);
	DDX_CBString(pDX, IDC_UNIT_COMB3, m_nUnits1);
	DDX_CBString(pDX, IDC_UNIT_COMB4, m_nUnits2);
	DDX_CBString(pDX, IDC_UNIT_COMB5, m_nUnits3);
	DDX_CBString(pDX, IDC_UNIT_COMB6, m_nUnits4);
	DDX_CBString(pDX, IDC_UNIT_COMB, m_nUnits5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuickLayout, CDialog)
	//{{AFX_MSG_MAP(CQuickLayout)
	ON_BN_CLICKED(IDC_LOCKED12, OnLocked12)
	ON_BN_CLICKED(IDC_LOCKED13, OnLocked13)
	ON_BN_CLICKED(IDC_LOCKED14, OnLocked14)
	ON_BN_CLICKED(IDC_LOCKED15, OnLocked15)
	ON_CBN_SELCHANGE(IDC_UNIT_COMB, OnSelchangeUnitComb)
	ON_CBN_SELCHANGE(IDC_UNIT_COMB2, OnSelchangeUnitComb2)
	ON_CBN_SELCHANGE(IDC_UNIT_COMB3, OnSelchangeUnitComb3)
	ON_CBN_SELCHANGE(IDC_UNIT_COMB4, OnSelchangeUnitComb4)
	ON_CBN_SELCHANGE(IDC_UNIT_COMB5, OnSelchangeUnitComb5)
	ON_CBN_SELCHANGE(IDC_UNIT_COMB6, OnSelchangeUnitComb6)
	ON_BN_CLICKED(IDC_COMPUTE, OnCompute)
	ON_BN_CLICKED(IDC_LAYOUT_JUMP, OnLayoutJump)
	ON_EN_CHANGE(IDC_LEFT_M_EDIT, OnChangeLeftMEdit)
	ON_EN_CHANGE(IDC_LOWER_M_EDIT, OnChangeLowerMEdit)
	ON_EN_CHANGE(IDC_PAGE_COUNT, OnChangePageCount)
	ON_EN_CHANGE(IDC_PAGEH_EDIT, OnChangePagehEdit)
	ON_EN_CHANGE(IDC_PAGEW_EDIT, OnChangePagewEdit)
	ON_EN_CHANGE(IDC_RIGHT_M_EDIT, OnChangeRightMEdit)
	ON_EN_CHANGE(IDC_UPPER_M_EDIT, OnChangeUpperMEdit)
	ON_BN_CLICKED(IDC_LAYOUT_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuickLayout message handlers

BOOL CQuickLayout::OnInitDialog() 
{	
	int i;
	int arrayID[] = {IDC_UNIT_COMB,IDC_UNIT_COMB2,IDC_UNIT_COMB3,
		IDC_UNIT_COMB4, IDC_UNIT_COMB5, IDC_UNIT_COMB6};
	for(i=0; i<6; i++)
	{

		CComboBox * pUnitCmbo =
			(CComboBox*)GetDlgItem(arrayID[i]);
		ASSERT(pUnitCmbo != NULL);

		pUnitCmbo->AddString("inches");
		pUnitCmbo->AddString("centimeters");
		//pUnitCmbo->AddString("pixels");
	}
	m_LockBn4.AutoLoad(IDC_LOCKED12,this);
	if(!m_TogLock4)m_LockBn4.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_UPPER_M_EDIT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB3);
		pCmbx->EnableWindow(FALSE);
		m_LockBn4.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn5.AutoLoad(IDC_LOCKED13,this);
	if(!m_TogLock5)m_LockBn5.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_LEFT_M_EDIT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB4);
		pCmbx->EnableWindow(FALSE);
		m_LockBn5.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn6.AutoLoad(IDC_LOCKED14,this);
	if(!m_TogLock6)m_LockBn6.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_LOWER_M_EDIT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB5);
		pCmbx->EnableWindow(FALSE);
		m_LockBn6.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}
	m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_LockBn7.AutoLoad(IDC_LOCKED15,this);
	if(!m_TogLock7)m_LockBn7.LoadBitmaps(IDB_UNLOCKED_DN,IDB_UNLOCKED_UP,0,0);
	else
	{
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_RIGHT_M_EDIT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB6);
		pCmbx->EnableWindow(FALSE);
		m_LockBn7.LoadBitmaps(IDB_LOCKED_DN,IDB_LOCKED_UP,0,0);
	}	
	m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);

	m_origStr = CString(m_nUnits);
	double rate = 1.0;
	if(m_nUnits=="centimeters")rate = 2.54;


	m_nPageWidth = m_nPageWidth * rate;
	m_nPageHeight = m_nPageHeight * rate;
	m_nLeftMarg = m_nLeftMarg * rate;
	m_nRightMarg = m_nRightMarg * rate;
	m_nUpperMarg = m_nUpperMarg * rate;
	m_nLowerMarg = m_nLowerMarg * rate;

	m_pageC = m_nPageCount;
	m_pageW = m_nPageWidth;
	m_pageH = m_nPageHeight;
	m_leftM = m_nLeftMarg;
	m_rightM = m_nRightMarg;
	m_topM = m_nUpperMarg;
	m_botM = m_nLowerMarg;

	m_tl7 = m_TogLock7;
	m_tl6 = m_TogLock6;
	m_tl5 = m_TogLock5;
	m_tl4 = m_TogLock4;
	m_tl3 = m_TogLock3;
	m_tl2 = m_TogLock2;
	m_tl = m_TogLock;


	CDialog::OnInitDialog();
	
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


////////////////////////////////////////////////////////////////////////
//LockButton handlers

void CQuickLayout::OnLocked9() 
{
	m_Bn = TRUE;
	if(m_TogLock==TRUE)
	{
		m_LockBn.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock = FALSE;
		
	}
	else if(m_TogLock==FALSE)
	{
		m_LockBn.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock = TRUE;
	}
}
void CQuickLayout::OnLocked10() 
{	
	m_Bn2 = TRUE;
	if(m_TogLock2==TRUE)
	{
		m_LockBn2.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock2 = FALSE;
	}
	else if(m_TogLock2==FALSE)
	{
		m_LockBn2.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn2.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock2 = TRUE;
	}
	
}
void CQuickLayout::OnLocked12() 
{
	m_Bn4 = TRUE;
	if(m_TogLock4)
	{
		m_LockBn4.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock4 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_UPPER_M_EDIT);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB3);
		pCmbx->EnableWindow(TRUE);
	}
	else if(!m_TogLock4)
	{
		m_LockBn4.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn4.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock4 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_UPPER_M_EDIT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB3);
		pCmbx->EnableWindow(FALSE);
	}
	
}

void CQuickLayout::OnLocked13() 
{
	m_Bn5 = TRUE;
	if(m_TogLock5)
	{
		m_LockBn5.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock5 = FALSE;	
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_LEFT_M_EDIT);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB4);
		pCmbx->EnableWindow(TRUE);

	}
	else if(!m_TogLock5)
	{
		m_LockBn5.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn5.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock5 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_LEFT_M_EDIT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB4);
		pCmbx->EnableWindow(FALSE);
	}
	
}

void CQuickLayout::OnLocked14() 
{
	m_Bn6 = TRUE;
	if(m_TogLock6)
	{
		m_LockBn6.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock6 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_LOWER_M_EDIT);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB5);
		pCmbx->EnableWindow(TRUE);
	}
	else if(!m_TogLock6)
	{
		m_LockBn6.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn6.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock6 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_LOWER_M_EDIT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB5);
		pCmbx->EnableWindow(FALSE);
	}
	
}

void CQuickLayout::OnLocked15() 
{
	m_Bn7 = TRUE;
	if(m_TogLock7)
	{
		m_LockBn7.LoadBitmaps(IDB_UNLOCKED_UP,IDB_UNLOCKED_DN,0,0);
		m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock7 = FALSE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_RIGHT_M_EDIT);
		pEd->EnableWindow(TRUE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB6);
		pCmbx->EnableWindow(TRUE);
	}
	else if(!m_TogLock7)
	{
		m_LockBn7.LoadBitmaps(IDB_LOCKED_UP,IDB_LOCKED_DN,0,0);
		m_LockBn7.SetButtonStyle(BS_OWNERDRAW,TRUE);
		m_TogLock7 = TRUE;
		CEdit* pEd = (CEdit*)GetDlgItem(IDC_RIGHT_M_EDIT);
		pEd->EnableWindow(FALSE);
		CComboBox* pCmbx = (CComboBox*)GetDlgItem(
			IDC_UNIT_COMB6);
		pCmbx->EnableWindow(FALSE);
	}
	
}

void CQuickLayout::OnOK() 
{
	m_MargRatResult = m_Click.mult; 

	OnCompute();
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	pDoc->InductNewValues();

	CComboBox* pBo =
		(CComboBox*)GetDlgItem(IDC_UNIT_COMB);
	ASSERT(pBo != NULL);

	char string[15];
	char* str = &string[0];
	int i;
	i = pBo->GetCurSel();
	pBo->GetLBText(i,str);

	m_nUnits = str;

	double rate = 0.39370075;
	if(m_nUnits=="centimeters")
	{
		m_nLeftMarg = m_nLeftMarg * rate;
		m_nRightMarg = m_nRightMarg * rate;
		m_nUpperMarg = m_nUpperMarg * rate;
		m_nLowerMarg = m_nLowerMarg * rate;
		m_nPageHeight = m_nPageHeight * rate;
		m_nPageWidth = m_nPageWidth * rate;
	}
	
	UpdateData(FALSE);

	CDialog::OnOK();
}


void CQuickLayout::OnSelchangeUnitComb() 
{
	UnifyCBs(1043);
}

void CQuickLayout::UnifyCBs(int nBoxID)
{
	//CString* in, pix, cm;
	//instigator = nBoxID;
	int index;
	double rate = 1.0;
	CComboBox* pBo =
		(CComboBox*)GetDlgItem(nBoxID);
	ASSERT(pBo != NULL);
	index = pBo->GetCurSel();

	if(index!=0 && index < 0) AfxMessageBox("CB ERR");

	int i;
	int arrayID[] = {IDC_UNIT_COMB,IDC_UNIT_COMB2,IDC_UNIT_COMB3,
		IDC_UNIT_COMB4, IDC_UNIT_COMB5, IDC_UNIT_COMB6};
	for(i=0; i<6; i++)
	{
		LPCTSTR lpIn ("inches");//if(index==0)
		LPCTSTR lpCm ("centimeters");//if(index==1)
		LPCTSTR lpPic ("pixels");//if(index==2) 

		CComboBox * pUnitCmbo =
		(CComboBox*)GetDlgItem(arrayID[i]);
		ASSERT(pUnitCmbo != NULL);

		if(index==0)pUnitCmbo->SelectString(-1,lpIn);
		if(index==1)pUnitCmbo->SelectString(-1,lpCm);
		if(index==2)pUnitCmbo->SelectString(-1,lpPic);
	}


	if(index==0)
	{
		if(m_nUnits=="centimeters")rate = 0.39370075;
		//if(m_nUnits=="pixels")rate = 1 / ::scratchPad.m_xppi;
	}
	if(index==1)
	{
		if(m_nUnits=="inches")rate = 2.54;
		//if(m_nUnits=="pixels")rate = ;
	}
	if(index==2)
	{
	}

	UpdateData(TRUE);

	m_nPageWidth = m_nPageWidth * rate;
	m_nPageHeight = m_nPageHeight * rate;
	m_nLeftMarg = m_nLeftMarg * rate;
	m_nRightMarg = m_nRightMarg * rate;
	m_nUpperMarg = m_nUpperMarg * rate;
	m_nLowerMarg = m_nLowerMarg * rate;


	UpdateData(FALSE);
}

void CQuickLayout::OnSelchangeUnitComb2() 
{
	UnifyCBs(1065);	
}

void CQuickLayout::OnSelchangeUnitComb3() 
{
	UnifyCBs(1066);	
}

void CQuickLayout::OnSelchangeUnitComb4() 
{
	UnifyCBs(1067);	
}

void CQuickLayout::OnSelchangeUnitComb5() 
{
	UnifyCBs(1068);	
}

void CQuickLayout::OnSelchangeUnitComb6() 
{
	UnifyCBs(1069);	
}

extern CCalc scratchPad;

void CQuickLayout::OnReset() 
{
	int intArray[6] = {IDC_UNIT_COMB,IDC_UNIT_COMB2,IDC_UNIT_COMB3,
		IDC_UNIT_COMB4,IDC_UNIT_COMB5,IDC_UNIT_COMB6};
	int i;
	for(i=0;i<6;i++)
	{

		CComboBox * pUnitCmbo =
			(CComboBox*)GetDlgItem(intArray[i]);

		ASSERT(pUnitCmbo != NULL);

		pUnitCmbo->SelectString(-1,m_origStr);
	}

	UpdateData(TRUE);

	m_Bn7 = FALSE;
	m_Bn6 = FALSE;
	m_Bn5 = FALSE;
	m_Bn4 = FALSE;
	m_Bn3 = FALSE;
	m_Bn2 = FALSE;
	m_Bn = FALSE;

	if(m_TogLock7!=m_tl7){OnLocked15();m_TogLock7 = m_tl7;}
	if(m_TogLock6!=m_tl6){OnLocked14();m_TogLock6 = m_tl6;}
	if(m_TogLock5!=m_tl5){OnLocked13();m_TogLock5 = m_tl5;}
	if(m_TogLock4!=m_tl4){OnLocked12();m_TogLock4 = m_tl4;}
	if(m_TogLock2!=m_tl2){OnLocked10();m_TogLock2 = m_tl2;}
	if(m_TogLock!=m_tl){OnLocked9();m_TogLock = m_tl;}

	m_TogLock4 = m_tl4;
	m_TogLock3 = m_tl3;
	m_TogLock2 = m_tl2;
	m_TogLock = m_tl;


	m_nPageCount = m_pageC;
	m_nPageWidth = m_pageW;
	m_nPageHeight = m_pageH;
	m_nLeftMarg = m_leftM;
	m_nRightMarg = m_rightM;
	m_nUpperMarg = m_topM;
	m_nLowerMarg = m_botM;
	UpdateData(FALSE);

	m_Click.Reset();
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	pDoc->m_dMargRat = m_saveMult;
	pDoc->RegisterAspects();
	::scratchPad.LoadCalcMembers();
}
/*
void CQuickLayout::OnLayoutReset() 
{

}

*/
void CQuickLayout::OnLayoutJump() 
{
	m_MargRatResult = m_Click.mult;
	OnCompute();
	m_next = TRUE;
	UpdateData(TRUE);

	CDialog::OnOK();
}

void CQuickLayout::OnCompute() 
{	
	UpdateData(TRUE);

	BOOL result = 0;
	if(m_Bn7)::scratchPad.ChangeLocksAndFlags(4,m_TogLock7);
	if(m_Bn6)::scratchPad.ChangeLocksAndFlags(11,m_TogLock6);
	if(m_Bn5)::scratchPad.ChangeLocksAndFlags(3,m_TogLock5);
	if(m_Bn4)::scratchPad.ChangeLocksAndFlags(10,m_TogLock4);
	if(m_Bn3)::scratchPad.ChangeLocksAndFlags(15,m_TogLock3);
	if(m_Bn2)::scratchPad.ChangeLocksAndFlags(16,m_TogLock2);
	if(m_Bn)::scratchPad.ChangeLocksAndFlags(6,m_TogLock);

	m_Bn7 = FALSE;
	m_Bn6 = FALSE;
	m_Bn5 = FALSE;
	m_Bn4 = FALSE;
	m_Bn3 = FALSE;
	m_Bn2 = FALSE;
	m_Bn = FALSE;

	double rate = 0.39370075;
	if(m_nUnits=="centimeters")
	{
		m_nLeftMarg = m_nLeftMarg * rate;
		m_nRightMarg = m_nRightMarg * rate;
		m_nUpperMarg = m_nUpperMarg * rate;
		m_nLowerMarg = m_nLowerMarg * rate;
		m_nPageHeight = m_nPageHeight * rate;
		m_nPageWidth = m_nPageWidth * rate;
	}

	if(m_leftMchange)result =
		::scratchPad.InstigateChange(m_nLeftMarg,3);
	if(m_rightMchange)result = 
		::scratchPad.InstigateChange(m_nRightMarg,4);
	if(m_topMchange)result = 
		::scratchPad.InstigateChange(m_nUpperMarg,10);
	if(m_botMchange)result = 
		::scratchPad.InstigateChange(m_nLowerMarg,11);
	if(m_pageHchange)result = 
		::scratchPad.InstigateChange(m_nPageHeight,16);
	if(m_pageWchange)result = 
		::scratchPad.InstigateChange(m_nPageWidth,6);
	if(m_pageCchange)result = 
		::scratchPad.InstigateChange((UINT)m_nPageCount,15);

	CSerioDoc* pDoc = CSerioDoc::GetDoc();

	pDoc->m_dMargRat = m_Click.mult;
	

	BOOL boom = ::scratchPad.ProcessChangeRequests();

	m_leftMchange = FALSE;
	m_rightMchange = FALSE;
	m_topMchange = FALSE;
	m_botMchange = FALSE;
	m_pageWchange = FALSE;
	m_pageHchange = FALSE;
	m_pageCchange = FALSE;
	
	BOOL change = ::scratchPad.m_change;

	CRegAspect* line;
	line = scratchPad.m_reg[3];
	m_nLeftMarg = line->m_nSize;
	line = scratchPad.m_reg[4];
	m_nRightMarg = line->m_nSize;
	line = scratchPad.m_reg[10];
	m_nUpperMarg = line->m_nSize;
	line = scratchPad.m_reg[11];
	m_nLowerMarg = line->m_nSize;
	line = scratchPad.m_reg[6];
	m_nPageWidth = line->m_nSize;
	line = scratchPad.m_reg[16];
	m_nPageHeight = line->m_nSize;
	line = scratchPad.m_reg[15];
	m_nPageCount = line->m_nCount;

	if(m_nUnits=="centimeters")
	{
		rate = 2.54;
		m_nLeftMarg = m_nLeftMarg * rate;
		m_nRightMarg = m_nRightMarg * rate;
		m_nUpperMarg = m_nUpperMarg * rate;
		m_nLowerMarg = m_nLowerMarg * rate;
		m_nPageHeight = m_nPageHeight * rate;
		m_nPageWidth = m_nPageWidth * rate;
	}


	UpdateData(FALSE);

}

void CQuickLayout::OnChangeLeftMEdit() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_LEFT_M_EDIT);
	if(change) m_leftMchange = TRUE;
}

void CQuickLayout::OnChangeLowerMEdit() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_LOWER_M_EDIT);
	if(change) m_botMchange = TRUE;
}

void CQuickLayout::OnChangePageCount() 
{
	m_pageCchange = TRUE;
}

void CQuickLayout::OnChangePagehEdit() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_PAGEH_EDIT);
	if(change) m_pageHchange = TRUE;
}

void CQuickLayout::OnChangePagewEdit() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_PAGEW_EDIT);
	if(change) m_pageWchange = TRUE;
}

void CQuickLayout::OnChangeRightMEdit() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_RIGHT_M_EDIT);
	if(change) m_rightMchange = TRUE;
}

void CQuickLayout::OnChangeUpperMEdit() 
{
	BOOL change = FALSE;
	change = ExtractValue(IDC_UPPER_M_EDIT);
	if(change) m_topMchange = TRUE;
}

BOOL CQuickLayout::ExtractValue(int cntlID)
{
	BOOL noDec = TRUE;
	CString str;
	GetDlgItemText(cntlID,str);
	int len = str.GetLength();
	int place;
	for(place=0;place<len;place++)
	{
		if(str[place]==46)noDec = FALSE;
	}
	if(noDec)
	{
		str +=".0";
		len += 2;
	}
	double rack[20];
	int decPos;
	int num;
	for(num=0;num<len;num++)
	{
		if(str[num]==46)	//	str[num];//'0'=48, '.'=46
		{
			decPos = num;
			break;
		}
	}
	for(num=0;num<len;num++)//integer part
	{
		int multTenDigits = decPos;
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
	return change;
}

double CQuickLayout::GetDenom(int expon,BOOL mult)
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

UINT CQuickLayout::GetNumericValue(int val)
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

double CQuickLayout::MemberFloatLUT(int cntlID)
{
	double val = 0;
	if(cntlID==IDC_LEFT_M_EDIT) val = m_nLeftMarg;
	if(cntlID==IDC_LOWER_M_EDIT) val = m_nLowerMarg;
	if(cntlID==IDC_PAGE_COUNT) val = m_nPageCount;
	if(cntlID==IDC_PAGEH_EDIT) val = m_nPageHeight;
	if(cntlID==IDC_PAGEW_EDIT) val = m_nPageWidth;
	if(cntlID==IDC_RIGHT_M_EDIT) val = m_nRightMarg;
	if(cntlID==IDC_UPPER_M_EDIT) val = m_nUpperMarg;
	return val;
}

void CQuickLayout::OnCancel() 
{
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	pDoc->m_dMargRat = m_saveMult;

	
	CDialog::OnCancel();
}

