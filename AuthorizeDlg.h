// AuthorizeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuthorizeDlg dialog

class CAuthorizeDlg : public CDialog
{
// Construction
public:
	BOOL m_codeValid;
	CAuthorizeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAuthorizeDlg)
	enum { IDD = IDD_AUTHORIZE };
	CString	m_key;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuthorizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAuthorizeDlg)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
