// InsertObDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertObDlg dialog

class CInsertObDlg : public CDialog
{
// Construction
public:
	CInsertObDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertObDlg)
	enum { IDD = IDD_DIALOG5 };
	BOOL	m_nBoth;
	BOOL	m_nDisabIndex;
	CString	m_nFontSel;
	CString	m_nHdr;
	CString	m_nLab;
	BOOL	m_Per;
	int		m_PosEd;
	BOOL	m_NoSym;
	BOOL	m_IDBlock;
	BOOL	m_IDCBlock;
	BOOL	m_IDCell;
	BOOL	m_IDCol;
	BOOL	m_IDRow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertObDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertObDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
