// StrikeStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStrikeStatic window

class CStrikeStatic : public CStatic
{
// Construction
public:
	BOOL m_retry;
	BOOL m_panelCall;
	void IndicateRetry();
	void IndicateRemove();
	void EnableText(BOOL text);
	BOOL m_noText;
	COLORREF m_pColor;
	COLORREF m_bColor;
	void SetPenColor(COLORREF color);
	void SetBrushColor(COLORREF color);
	CStrikeStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrikeStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStrikeStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStrikeStatic)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
