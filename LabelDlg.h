// LabelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLabelDlg dialog

class CLabelDlg : public CDialog
{
// Construction
public:
	CLabelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLabelDlg)
	enum { IDD = IDD_DIALOG8 };
	BOOL	m_Bot;
	BOOL	m_Left;
	BOOL	m_Right;
	BOOL	m_Top;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLabelDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
