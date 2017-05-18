// DragStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDragStatic window

class CDragStatic : public CStatic
{

// Construction
public:

	BOOL m_reset;
	BOOL CheckSpinReset();

	int Revolve(int pos, BOOL reset);
	CString LoadStr(int sCode);
	CString axis1Str;
	CString axis2Str;
	CString axis3Str;
	CString axis4Str;
	int fromAxisColor;
	int toAxisColor;
	int m_swap;
	int OrientationLUT();
	int OrientationLUT(int ax1C,int ax2C,int ax3C);
	int ColorMode;
	int axis4Color;
	int axis3Color;
	int axis2Color;
	int axis1Color;
	int m_orientation;
	int origQuad;
	BOOL validDrag;
	int GetColorVal(int color, int primary);
	int origClick;
	int RegionLUT(int colorID, int cfgCode);
	CRgn* GetStackRegion(int rCode);
	CRgn* GetRegion(int rgnCode);
	CDragStatic();
	int m_angleOff;
	int m_angleClick;
	int array_x[10];
	int array_y[10];
	BOOL eraseCycle;
	BOOL noMove;
	BOOL changeBmp;
	int uno;
	int dos;
	int tres;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDragStatic)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// COrientStatic window

class COrientStatic : public CStatic
{
// Construction
public:
	int m_track;
	COrientStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrientStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COrientStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(COrientStatic)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
