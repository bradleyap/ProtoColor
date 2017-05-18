// RetractDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRetractDlg dialog
#include "PanelStatic.h"
#include "StrikeStatic.h"
class CRetractDlg : public CDialog
{
// Construction
public:
	void SetItems(CString str);
	void SetInitialRequest(CString s);
	void SetResultingValue(CString s);
	CRetractDlg(CWnd* pParent = NULL);   // standard constructor
private:
	CString m_itemStr;
	CString m_itemStr2;
	CString m_itemStr3;
	CString m_itemStr4;
	CString m_itemStr5;
	CString m_itemStr6;
	CString m_reqStr;
	CString m_reqStr2;
	CString m_reqStr3;
	CString m_reqStr4;
	CString m_reqStr5;
	CString m_reqStr6;
	CString m_resStr;
	CString m_resStr2;
	CString m_resStr3;
	CString m_resStr4;
	CString m_resStr5;
	CString m_resStr6;

	int m_line;
public:
// Dialog Data
	//{{AFX_DATA(CRetractDlg)
	enum { IDD = IDD_RETRACT_REQ };
	CStrikeStatic	m_strike6;
	CStrikeStatic	m_strike5;
	CStrikeStatic	m_strike4;
	CStrikeStatic	m_strike3;
	CStrikeStatic	m_strike2;
	CStrikeStatic	m_strike1;
	CPanelStatic	m_panel4;
	CPanelStatic	m_panel3;
	CPanelStatic	m_panel2;
	CPanelStatic	m_panel1;
	CStrikeStatic	m_strike;
	BOOL	m_chk1;
	BOOL	m_chk3;
	BOOL	m_chk2;
	BOOL	m_chk4;
	BOOL	m_chk5;
	BOOL	m_chk6;
	BOOL	m_strikeAll;
	CString	m_asp;
	CString	m_asp2;
	CString	m_asp3;
	CString	m_asp4;
	CString	m_asp5;
	CString	m_asp6;
	CString	m_req;
	CString	m_val;
	CString	m_val2;
	CString	m_val3;
	CString	m_val4;
	CString	m_val5;
	CString	m_val6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRetractDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRetractDlg)
	afx_msg void OnPaint();
	afx_msg void OnRetractCheck1();
	afx_msg void OnRetractCheck2();
	afx_msg void OnRetractCheck3();
	afx_msg void OnRetractCheck4();
	afx_msg void OnRetractCheck5();
	afx_msg void OnRetractCheck6();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
