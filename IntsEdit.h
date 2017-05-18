// IntsEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIntsEdit window

class CIntsEdit : public CEdit
{
// Construction
public:
	CIntsEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntsEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIntsEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIntsEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
