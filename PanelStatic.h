// PanelStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanelStatic window

class CPanelStatic : public CStatic
{
// Construction
public:
	void SetBrushColor(COLORREF color);
	void SetPenColor(COLORREF color);
	COLORREF m_bColor;
	COLORREF m_pColor;
	CPanelStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPanelStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPanelStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
