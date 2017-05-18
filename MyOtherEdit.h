// MyOtherEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyOtherEdit window

class CMyOtherEdit : public CEdit
{
// Construction
public:
	BOOL m_go;
	int m_nChar;
	CMyOtherEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyOtherEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyOtherEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyOtherEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
