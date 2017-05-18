// IndexDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIndexDlg dialog

class CIndexDlg : public CDialog
{
// Construction
public:
	CIndexDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIndexDlg)
	enum { IDD = IDD_DIALOG7 };
	BOOL	m_Bot;
	BOOL	m_Left;
	BOOL	m_Right;
	CString	m_Anchor;
	BOOL	m_Top;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIndexDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIndexDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
