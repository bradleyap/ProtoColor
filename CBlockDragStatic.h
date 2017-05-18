// CBlockDragStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCBlockDragStatic window

class CCBlockDragStatic : public CStatic
{
// Construction
public:
	float GetFrameH();
	float GetFrameW();
	float GetBlockWidth();
	float GetBlockHeight();
	CCBlockDragStatic();
	BOOL m_calledByDlg;
	CString strBrief;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBlockDragStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCBlockDragStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCBlockDragStatic)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
