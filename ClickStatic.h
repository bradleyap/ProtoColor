// ClickStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClickStatic window



class CClickStatic : public CStatic
{
// Construction
	CSerioDoc* pDcmt;
	int factors;
	BOOL reduce;
public:
	void InitializeData(UINT mult);
	UINT m_saveMult;
	void Reset();
	UINT mult;
	UINT m_idbCur;
	CClickStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClickStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClickStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClickStatic)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
