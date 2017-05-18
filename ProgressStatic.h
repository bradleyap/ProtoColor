// ProgressStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressStatic window

class CProgressStatic : public CStatic
{
// Construction
public:
	void ExplicitWrite();
	void UpdateStatusRegion(unsigned long nuPixLen);
	void GetStatusIndicatorArea(CRect* clientArea);
	void SetStartColor(COLORREF clr);
	void SetProgressColor(COLORREF  clr);
	CProgressStatic();
	BOOL firstTimeThrough;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgressStatic();

	// Generated message map functions
protected:
	unsigned long m_prevPixelWidth;
	unsigned long m_currentPixelWidth;
	COLORREF m_progressColor;
	COLORREF m_backGround;
	//{{AFX_MSG(CProgressStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
