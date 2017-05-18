// BlockDragStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlockDragStatic window

class CBlockDragStatic : public CStatic
{
// Construction
public:
	BOOL extra;
	BOOL m_calledByDlg;
	//void SetRowSpace(float rs);
	//void SetColSpace(float cs);
	void SetFrameWidth(float w);
	void SetFrameHeight(float h);
	void SetRows(UINT nRow);
	void SetCols(UINT nCol);
	void SetBlockWidth(float bWidth);
	void SetBlockHeight(float bheight);
	float GetRowSpace();
	float GetColSpace();
	UINT GetBlockRows();
	UINT GetBlockCols();
	float GetBlockHeight();
	float GetBlockWidth();
	float GetFrameH();
	float GetFrameW();

	int m_colorMode;
	double m_colSpace;
	double m_rowSpace;
	double m_adjBlockW;
	double m_adjBlockH;
	UINT m_blockRows;
	UINT m_blockCols;
	int	m_bColCount;
	double m_blockWidth;
	double m_blockHeight;
	double m_W;
	double m_H;
	double m_top;
	double m_bottom;
	double m_left;
	double m_right;
	int m_coords[4];
	void PassToCalc();
	BOOL ChangeIntValue(int val, int item);
	BOOL ChangeFloatValue(float val, int item);
	void Invalidate();
	int TranslateVal(int element);
	void ResetX1X2();
	void IncreaseX1X2();
	void IncreaseY1Y2();
	void InitializeCoordinates();
	int GetCoordinate(int element, UINT block);
	UINT GetBlockTotal();
	CRect m_BoundingRect;
	void InitializeGraphicComponants(BOOL internal);
	CBlockDragStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlockDragStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBlockDragStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBlockDragStatic)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
