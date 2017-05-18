// ConstrainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConstrainDlg dialog

class CConstrainDlg : public CDialog
{
// Construction
public:
	CConstrainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConstrainDlg)
	enum { IDD = IDD_DIALOG4 };
	BOOL	m_nBlockHeight;
	BOOL	m_nBlockRatio;
	BOOL	m_nBlockWidth;
	BOOL	m_nBottomMarg;
	BOOL	m_nBot2Right;
	BOOL	m_nCBlockHeight;
	BOOL	m_nCBlockRatio;
	BOOL	m_nCBlockWidth;
	BOOL	m_nCellCount;
	BOOL	m_nCellHeight;
	BOOL	m_nCellRatio;
	BOOL	m_nCellWidth;
	BOOL	m_nLeftMarg;
	BOOL	m_nLeft2Right;
	BOOL	m_nPageCount;
	BOOL	m_nRightMarg;
	BOOL	m_nTopMarg;
	BOOL	m_nTop2Bot;
	BOOL	m_nTop2Left;
	CString	m_nConstrMode;
	CString	m_nModeContext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstrainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConstrainDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
