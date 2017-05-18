// MyEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyEdit window
class CSerioDoc;
class CSerioView;
class CCellAspectsDlg;

class CMyEdit : public CEdit
{
// Construction
public:
	DECLARE_DYNCREATE(CMyEdit)
	float m_val;
	CMyEdit();
	CCellAspectsDlg* pDlg;


// Attributes
public:

// Operations
public:
	CSerioDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyEdit)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
