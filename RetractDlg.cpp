// RetractDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "RetractDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRetractDlg dialog


CRetractDlg::CRetractDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRetractDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRetractDlg)
	m_chk1 = FALSE;
	m_chk3 = FALSE;
	m_chk2 = FALSE;
	m_chk4 = FALSE;
	m_chk5 = FALSE;
	m_chk6 = FALSE;
	m_asp = _T("");
	m_asp2 = _T("");
	m_asp3 = _T("");
	m_asp4 = _T("");
	m_asp5 = _T("");
	m_asp6 = _T("");
	m_req = _T("");
	m_val = _T("");
	m_val2 = _T("");
	m_val3 = _T("");
	m_val4 = _T("");
	m_val5 = _T("");
	m_val6 = _T("");
	//}}AFX_DATA_INIT
	COLORREF bc = GetSysColor(COLOR_3DFACE);
	COLORREF pc = GetSysColor(COLOR_BACKGROUND);

	m_panel1.SetBrushColor(bc);
	m_panel1.SetPenColor(pc);
	m_panel2.SetBrushColor(bc);
	m_panel2.SetPenColor(pc);
	m_panel3.SetBrushColor(bc);
	m_panel3.SetPenColor(pc);
	m_panel4.SetBrushColor(bc);
	m_panel4.SetPenColor(pc);
	m_strike1.SetBrushColor(RGB(0,0,0));
	m_strike1.SetPenColor(RGB(255,0,0));
	m_strike1.EnableText(TRUE);
	m_strike2.EnableText(TRUE);
	m_strike3.EnableText(TRUE);
	m_strike4.EnableText(TRUE);
	m_strike5.EnableText(TRUE);
	m_strike6.EnableText(TRUE);
	m_strike.m_panelCall = TRUE;

	m_chk1 = TRUE;
	m_chk2 = FALSE;
	m_chk3 = FALSE;
	m_chk4 = FALSE;
	m_chk5 = FALSE;
	m_chk6 = FALSE;
	if(m_strikeAll)
	{
		m_chk2 = TRUE;
		m_chk3 = TRUE;
		m_chk4 = TRUE;
		m_chk5 = TRUE;
		m_chk6 = TRUE;
	}
	
	m_line = 0;

	m_itemStr = "";
	m_itemStr2 = "";
	m_itemStr3 = "";
	m_itemStr4 = "";
	m_itemStr5 = "";
	m_itemStr6 = "";
	m_reqStr = "";
	m_reqStr2 = "";
	m_reqStr3 = "";
	m_reqStr4 = "";
	m_reqStr5 = "";
	m_reqStr6 = "";
	m_resStr = "";
	m_resStr2 = "";
	m_resStr3 = "";
	m_resStr4 = "";
	m_resStr5 = "";
	m_resStr6 = "";


}


void CRetractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRetractDlg)
	DDX_Control(pDX, IDC_DEL6, m_strike6);
	DDX_Control(pDX, IDC_DEL5, m_strike5);
	DDX_Control(pDX, IDC_DEL4, m_strike4);
	DDX_Control(pDX, IDC_DEL3, m_strike3);
	DDX_Control(pDX, IDC_DEL2, m_strike2);
	DDX_Control(pDX, IDC_DEL1, m_strike1);
	DDX_Control(pDX, IDC_F4_STATIC, m_panel4);
	DDX_Control(pDX, IDC_F2_STATIC, m_panel2);
	DDX_Control(pDX, IDC_F1_STATIC, m_panel1);
	DDX_Control(pDX, IDC_F5_STATIC, m_strike);
	if(m_line>0)DDX_Check(pDX, IDC_RETRACT_CHECK1, m_chk1);
	if(m_line>2)DDX_Check(pDX, IDC_RETRACT_CHECK3, m_chk3);
	if(m_line>1)DDX_Check(pDX, IDC_RETRACT_CHECK2, m_chk2);
	if(m_line>3)DDX_Check(pDX, IDC_RETRACT_CHECK4, m_chk4);
	if(m_line>4)DDX_Check(pDX, IDC_RETRACT_CHECK5, m_chk5);
	if(m_line>5)DDX_Check(pDX, IDC_RETRACT_CHECK6, m_chk6);
	DDX_Text(pDX, IDC_ITEM, m_asp);
	DDX_Text(pDX, IDC_ITEM2, m_asp2);
	DDX_Text(pDX, IDC_ITEM3, m_asp3);
	DDX_Text(pDX, IDC_ITEM4, m_asp4);
	DDX_Text(pDX, IDC_ITEM5, m_asp5);
	DDX_Text(pDX, IDC_ITEM6, m_asp6);
	DDX_Text(pDX, IDC_VAL, m_val);
	DDX_Text(pDX, IDC_VAL2, m_val2);
	DDX_Text(pDX, IDC_VAL3, m_val3);
	DDX_Text(pDX, IDC_VAL4, m_val4);
	DDX_Text(pDX, IDC_VAL5, m_val5);
	DDX_Text(pDX, IDC_VAL6, m_val6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRetractDlg, CDialog)
	//{{AFX_MSG_MAP(CRetractDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RETRACT_CHECK1, OnRetractCheck1)
	ON_BN_CLICKED(IDC_RETRACT_CHECK2, OnRetractCheck2)
	ON_BN_CLICKED(IDC_RETRACT_CHECK3, OnRetractCheck3)
	ON_BN_CLICKED(IDC_RETRACT_CHECK4, OnRetractCheck4)
	ON_BN_CLICKED(IDC_RETRACT_CHECK5, OnRetractCheck5)
	ON_BN_CLICKED(IDC_RETRACT_CHECK6, OnRetractCheck6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRetractDlg message handlers

void CRetractDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	COLORREF bc = GetSysColor(COLOR_3DFACE);
	COLORREF pc = GetSysColor(COLOR_BACKGROUND);

	m_panel1.SetBrushColor(bc);
	m_panel1.SetPenColor(pc);
	m_panel2.SetBrushColor(bc);
	m_panel2.SetPenColor(pc);
	m_panel3.SetBrushColor(bc);
	m_panel3.SetPenColor(pc);
	m_panel4.SetBrushColor(bc);
	m_panel4.SetPenColor(pc);

//	SetDlgItemText(IDC_ITEM,"block width" );
//	SetDlgItemText(IDC_VAL,"1.334445" );
	SetDlgItemText(IDC_ITEM,m_itemStr);
	SetDlgItemText(IDC_ITEM2,m_itemStr2);
	SetDlgItemText(IDC_ITEM3,m_itemStr3);
	SetDlgItemText(IDC_ITEM4,m_itemStr4);
	SetDlgItemText(IDC_ITEM5,m_itemStr5);
	SetDlgItemText(IDC_ITEM6,m_itemStr6);

	SetDlgItemText(IDC_REQ_VAL,m_reqStr);
	SetDlgItemText(IDC_REQ_VAL2,m_reqStr2);
	SetDlgItemText(IDC_REQ_VAL3,m_reqStr3);
	SetDlgItemText(IDC_REQ_VAL4,m_reqStr4);
	SetDlgItemText(IDC_REQ_VAL5,m_reqStr5);
	SetDlgItemText(IDC_REQ_VAL6,m_reqStr6);

	SetDlgItemText(IDC_VAL,m_resStr);
	SetDlgItemText(IDC_VAL2,m_resStr2);
	SetDlgItemText(IDC_VAL3,m_resStr3);
	SetDlgItemText(IDC_VAL4,m_resStr4);
	SetDlgItemText(IDC_VAL5,m_resStr5);
	SetDlgItemText(IDC_VAL6,m_resStr6);

	// Do not call CDialog::OnPaint() for painting messages
}

void CRetractDlg::OnRetractCheck1() 
{
	UpdateData(TRUE);
	if(m_chk1)m_strike1.IndicateRemove();	
	if(!m_chk1)m_strike1.IndicateRetry();
	
}

void CRetractDlg::OnRetractCheck2() 
{
	UpdateData(TRUE);
	if(m_chk2)m_strike2.IndicateRemove();
	if(!m_chk2)m_strike2.IndicateRetry();
	
}

void CRetractDlg::OnRetractCheck3() 
{
	UpdateData(TRUE);
	if(m_chk3)m_strike3.IndicateRemove();	
	if(!m_chk3)m_strike3.IndicateRetry();	
}

void CRetractDlg::OnRetractCheck4() 
{
	UpdateData(TRUE);
	if(m_chk4)m_strike4.IndicateRemove();	
	if(!m_chk4)m_strike4.IndicateRetry();
}

void CRetractDlg::OnRetractCheck5() 
{
	UpdateData(TRUE);
	if(m_chk5)m_strike5.IndicateRemove();	
	if(!m_chk5)m_strike5.IndicateRetry();
}

void CRetractDlg::OnRetractCheck6() 
{
	UpdateData(TRUE);
	if(m_chk6)m_strike6.IndicateRemove();	
	if(!m_chk6)m_strike6.IndicateRetry();
}

void CRetractDlg::SetItems(CString str)
{
	if(m_line==0)m_itemStr = str;
	if(m_line==1)m_itemStr2 = str;
	if(m_line==2)m_itemStr3 = str;
	if(m_line==3)m_itemStr4 = str;
	if(m_line==4)m_itemStr5 = str;
	if(m_line==5)m_itemStr6 = str;
}

void CRetractDlg::SetInitialRequest(CString s)
{
	if(m_line==0)m_reqStr = s;
	if(m_line==1)m_reqStr2 = s;
	if(m_line==2)m_reqStr3 = s;
	if(m_line==3)m_reqStr4 = s;
	if(m_line==4)m_reqStr5 = s;
	if(m_line==5)m_reqStr6 = s;
}

void CRetractDlg::SetResultingValue(CString s)
{
	if(m_line==0)m_resStr = s;
	if(m_line==1)m_resStr2 = s;
	if(m_line==2)m_resStr3 = s;
	if(m_line==3)m_resStr4 = s;
	if(m_line==4)m_resStr5 = s;;
	if(m_line==5)m_resStr6 = s;
	m_line++;
}

BOOL CRetractDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_strike1.IndicateRemove();
	if(m_strikeAll)
	{
		m_strike2.IndicateRemove();
		m_strike3.IndicateRemove();
		m_strike4.IndicateRemove();
		m_strike5.IndicateRemove();
		m_strike6.IndicateRemove();
	}
	
	int i;
	for(i=6;i>m_line;i--)
	{
		if(i==6)
		{
			m_strike6.EnableText(FALSE);
			SendDlgItemMessage(IDC_RETRACT_CHECK6,WM_CLOSE);
		}
		if(i==5)
		{
			m_strike5.EnableText(FALSE);
			SendDlgItemMessage(IDC_RETRACT_CHECK5,WM_CLOSE);
		}
		if(i==4)
		{
			m_strike4.EnableText(FALSE);
			SendDlgItemMessage(IDC_RETRACT_CHECK4,WM_CLOSE);
		}
		if(i==3)
		{
			m_strike3.EnableText(FALSE);
			SendDlgItemMessage(IDC_RETRACT_CHECK3,WM_CLOSE);
		}
		if(i==2)
		{
			m_strike2.EnableText(FALSE);
			SendDlgItemMessage(IDC_RETRACT_CHECK2,WM_CLOSE);
		}
		if(i==1)
		{
			m_strike1.EnableText(FALSE);
			SendDlgItemMessage(IDC_RETRACT_CHECK1,WM_CLOSE);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
