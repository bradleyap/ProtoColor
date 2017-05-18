// OrientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "OrientDlg.h"
#include "SerioDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrientDlg dialog
class CDragStatic;

COrientDlg::COrientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COrientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COrientDlg)
	m_DirFB = _T("");
	m_DirFL = _T("");
	m_DirLR = _T("");
	m_DirTB = _T("");
	//}}AFX_DATA_INIT



	
}


void COrientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrientDlg)
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Control(pDX, IDC_T2B_STATIC, m_T2B);
	DDX_Control(pDX, IDC_F2B_STATIC, m_F2B);
	DDX_Control(pDX, IDC_F2L_STATIC, m_F2L);
	DDX_Control(pDX, IDC_L2R_STATIC, m_L2R);
	DDX_Control(pDX, IDC_ORIENT, m_Drag);
	DDX_CBString(pDX, IDC_DIR_F2B, m_DirFB);
	DDX_CBString(pDX, IDC_DIR_F2L, m_DirFL);
	DDX_CBString(pDX, IDC_DIR_L2R, m_DirLR);
	DDX_CBString(pDX, IDC_DIR_T2B, m_DirTB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrientDlg, CDialog)
	//{{AFX_MSG_MAP(COrientDlg)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// COrientDlg message handlers



BOOL COrientDlg::OnInitDialog() 
{
	//CSpinButtonCtrl m_spin;
	//CRect rect(50,40,80,80);
	//m_spin.Create(UDS_ARROWKEYS|WS_VISIBLE|UDS_WRAP,rect,GetParent(),IDC_SPIN1);

	m_sync = 4;
	m_track = 0;

	SetDlgItemText(IDC_T2B_STATIC,m_Drag.axis1Str);
	SetDlgItemText(IDC_F2L_STATIC,m_Drag.axis2Str);
	SetDlgItemText(IDC_L2R_STATIC,m_Drag.axis3Str);
	SetDlgItemText(IDC_F2B_STATIC,m_Drag.axis4Str);

	CComboBox *pLRCmbo = 
			(CComboBox*)GetDlgItem(IDC_DIR_L2R);
		ASSERT(pLRCmbo != NULL);

		pLRCmbo->AddString("the MAXIMUM value");
		pLRCmbo->AddString("the MINIMUM value");

	CComboBox *pTBCmbo = 
			(CComboBox*)GetDlgItem(IDC_DIR_T2B);
		ASSERT(pTBCmbo != NULL);

		pTBCmbo->AddString("the MAXIMUM value");
		pTBCmbo->AddString("the MINIMUM value");

	CComboBox *pFLCmbo = 
			(CComboBox*)GetDlgItem(IDC_DIR_F2L);
		ASSERT(pFLCmbo != NULL);

		pFLCmbo->AddString("the MAXIMUM value");
		pFLCmbo->AddString("the MINIMUM value");
	
	CComboBox *pFBCmbo = 
			(CComboBox*)GetDlgItem(IDC_DIR_F2B);
		ASSERT(pFBCmbo != NULL);

		pFBCmbo->AddString("the MAXIMUM value");
		pFBCmbo->AddString("the MINIMUM value");
	
	if(m_colorMode!=1)pFBCmbo->EnableWindow(FALSE);
		
	//m_Drag.SubclassDlgItem(IDC_ORIENT, this);
//	CWnd* pWnd = GetDlgItem(IDC_ORIENT); // or use some other method to get
                                      // a pointer to the window you wish
                                      // to subclass
//	ASSERT( pWnd && pWnd->GetSafeHwnd() );
//	m_Drag.SubclassWindow(pWnd->GetSafeHwnd());
	
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void COrientDlg::OnOK() 
{
	UpdateData(TRUE);
	int val1,val2;
	BOOL swap = FALSE;
	CString start;
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	int val[8];
	int i = 0;
	val[i] = pDoc->m_dSF2B;
	val[++i] = pDoc->m_dEF2B;
	val[++i] = pDoc->m_dSF2L;
	val[++i] = pDoc->m_dEF2L;
	val[++i] = pDoc->m_dST2B;
	val[++i] = pDoc->m_dET2B;
	val[++i] = pDoc->m_dSL2R;
	val[++i] = pDoc->m_dEL2R;
	for(i=0;i<8;i++)
	{
		swap = FALSE;
		val1 = val[i];
		val2 = val[++i];
		if(i==1)start = m_DirFB;
		if(i==3)start = m_DirFL;
		if(i==5)start = m_DirTB;
		if(i==7)start = m_DirLR;
		if(start=="the MINIMUM value" && val1>val2)swap = TRUE;
		if(start=="the MAXIMUM value" && val1<=val2)swap = TRUE;
		if(swap)
		{
			int buf = val[i];
			val[i] = val[i-1];
			val[i-1] = buf;
		}
	}
	i--;
	pDoc->m_dEL2R = val[i];
	pDoc->m_dSL2R = val[--i];
	pDoc->m_dET2B = val[--i];
	pDoc->m_dST2B = val[--i];
	pDoc->m_dEF2L = val[--i];
	pDoc->m_dSF2L = val[--i];
	pDoc->m_dEF2B = val[--i];
	pDoc->m_dSF2B = val[--i];

	m_tempOrient = m_Drag.m_orientation;
	CDialog::OnOK();
}


void COrientDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{	
	if((pScrollBar != NULL) && (pScrollBar->GetDlgCtrlID()
		==IDC_SPIN1))
	{
		m_curPos = m_Drag.Revolve(nPos,TRUE);

		if(nPos==100 && m_track==0)m_track = 101;
		if(nPos==0 && m_track==100)m_track = -1;

		signed p;	//because of 'integral promotion' -1 was not holding  
		p = nPos;	// its value next to the relational operator 

		if(m_curPos==1 && m_track < p) m_Drag.Revolve(2,FALSE);
		if(m_curPos==1 && m_track > p) m_Drag.Revolve(3,FALSE);
		if(m_curPos==2 && m_track < p) m_Drag.Revolve(3,FALSE);
		if(m_curPos==2 && m_track > p) m_Drag.Revolve(1,FALSE);
		if(m_curPos==3 && m_track < p) m_Drag.Revolve(1,FALSE);//AfxMessageBox("m_t < nPos");}
		if(m_curPos==3 && m_track > p) m_Drag.Revolve(2,FALSE);//AfxMessageBox("m_t > nPos");}

		m_track = nPos;
		m_reset = FALSE;
	}
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

