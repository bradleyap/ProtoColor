// MessDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessDlg dialog

class CMessDlg : public CDialog
{
// Construction
public:
	CString str;
	BOOL m_yes;
	BOOL m_no;
	CMessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessDlg)
	enum { IDD = IDD_MESSAGE_BOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessDlg)
	afx_msg void OnNoBn();
	afx_msg void OnYesBn();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
