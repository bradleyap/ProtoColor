// SerioView.h : interface of the CSerioView class
//
/////////////////////////////////////////////////////////////////////////////
#include "PenObject.h"
class CColorTag;
class CRegAspect;
class CSerioView : public CScrollView
{
protected: // create from serialization only
	CSerioView();
	DECLARE_DYNCREATE(CSerioView)

// Attributes
public:
	CSize m_size;
	int m_cFontHeight;
	int m_bFontHeight;
	int m_cbFontHeight;
	int m_safeReduct; //applied to m_cFontHeight to cause reasonable
					//amount of decrease for readablility of indices
					//ie, especially when columns are crowded together
	int m_ax3HtReduct; //adjustment to bounding rect for readability
	int m_cellIndexSpaceHoriz;
	int m_xAxisDexSpace;
	int m_yAxisDexSpace;
	int m_smallestMarginVertically;//cell indice size conforms to smallest of all marg space
	int m_smallestMarginHorizontally;
	int m_blockY; 
	double m_horzStartColr;
	double m_vertStartColr;
	double m_blockStartColr;
	double m_cBlockStartColr;
	double m_bRowSpAvail;
	double m_bColSpAvail;
	double m_ax3DexPercent;//c'block index spacing taken from whats left 
							//to work with
	unsigned long m_bColSpace;
	unsigned long m_colSpace;
	unsigned long m_rowSpace;
	unsigned long m_leftMarg;
	unsigned long m_topMarg;
	unsigned long m_botMarg;
	unsigned long m_rightMarg;
	unsigned long m_axis4_x;
	unsigned long m_axis4_x2;
	unsigned long m_bDex_sideNearBlock;
	unsigned long m_bDex_farSide;
	unsigned long m_cBDex_sideNearBlock;
	unsigned long m_cBDex_farSide;
	unsigned long m_cBFrameX;
	unsigned long m_cellIndexHorExtent;

	UINT m_horzCounter;
	UINT m_vertCounter;
	UINT m_blockCounter;
	UINT m_cBlockCounter;
	UINT m_hCountC;
	UINT m_hCountB;
	UINT m_hCountCB;
	UINT m_vCountC;
	UINT m_vCountB;
	UINT m_vCountCB;
	BOOL m_ouldy;
	BOOL m_abb;
	BOOL m_lineBr;//if newline "\n" char is placed in indice
	BOOL m_ax1LineBr;//if newline "\n" char is placed in indice
	BOOL m_ax2LineBr;//if newline "\n" char is placed in indice
	BOOL m_ax3LineBr;//if newline "\n" char is placed in indice
	BOOL m_ax4LineBr;//if newline "\n" char is placed in indice

	BOOL m_perc; //whether to display the percent sign
	BOOL m_percent; //whether to convert values to percentages
	BOOL m_hex; //whether hexadecimal indices are displayed
	BOOL m_horizCrowd; //if space between columns hurt readability
	BOOL m_rowEnd;
	BOOL m_colEnd;
	BOOL m_bRowEnd;
	BOOL m_bColEnd;
	BOOL m_cBRowEnd;
	BOOL m_cBColEnd;
	BOOL m_firstCall2prn; //ellimanates redundant inquiries about printer
	BOOL m_initialOnDrawCell;//to promt one time functions per OnDraw() call
	BOOL m_ps; //indicates a Post-Script device
	BOOL m_userIsDragging;//signals when re-drawing should be postponed
	BOOL m_scrollBarInitDraw;//test to avoid drawing background often
	BOOL m_userInteruptsDraw;//click on scroll bar stops OnDraw
	UINT m_pageView;
	UINT m_page;
	UINT m_startPrnPage;
	int m_colorModel;
	int m_top;
	int m_bottom;
	int m_left;
	int m_right;
	double m_horzColr;
	double m_vertColr;
	double m_blockColr;
	double m_cBlockColr;
	double m_cBlockInc;
	double m_blockInc;
	double m_vertInc;
	double m_horzInc;
	int m_RedAxis;
	int m_GreenAxis;
	int m_BlueAxis;
	int m_MagentaAxis;
	int m_CyanAxis;
	int m_YellowAxis;
	int m_BlackAxis;
	int GetRedIntensity();
	int GetGrnIntensity();
	int GetBluIntensity();
	void ResetColorVal(int axis,UINT count);
	void IncrementColor(UINT page);
	void StoreAxisColors();
	void TakeCoordinateSnapShot();
	BOOL DetectBumperToBumperCells();
	void DrawPaper(CDC* pdc,CRect r);
	void DrawBackground(CDC * pdc,CRect bkR,CRect pgR);
	int RegionLUT(int colorID, int cfgCode);
	enum colorType{red = 0, green, blue};
	void InitializeColorItems(UINT page);
	void UpdateColorItems(UINT page);
	int GetRGBColorVal(int nColor, int cellCount, int cell, colorType c);
	void SetIndexFormatCodes(CSerioDoc* pD);
	void DrawIndex(int asp, CDC* pDC, UINT count);
	void DecideOnStyleAndFormatSizes();
	void PlugInHorizontalCoords(int* x,int* x2,int asp,BOOL forceLBr);
	void PlugInVerticalCoords(int* y,int* y2,int asp,BOOL forceLBr);
	CString GetIndexString(int col);
	CString AddIndexValString(CString str,int codeAx);
	int GetRounded(float f);
	CPenObject* m_bic;
	void OnCMYKPrint(CDC* pDC, CPrintInfo* pInfo);
	LOGCOLORSPACE *pOldLcs;
	void GetNewCoords();
	BOOL GetLeftMargFlags(int i);
	CSerioDoc* GetDocument();
	CArray<int,int>m_Coords;
	double CalcMaxPointSize();
	CRect CalcPointSize(CRect rect,LOGFONT logfont,CFont* font,
		CDC * pDC,double maxPtSz,UINT fmt,BOOL forAx3,int* largHt);
	void CalcBlockPointSize(int asp);
	void ComputeIndexPositionRegion(CDC* pDC,BOOL printg);
	void ComputeBlockIndexPositioning(CDC* pDC);
	void ComputeCBlockIndexPositioning();

// Operations
public:
	//static CSerioView* GetView();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerioView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSerioView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSerioView)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SerioView.cpp
inline CSerioDoc* CSerioView::GetDocument()
   { return (CSerioDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CColorTag command target

class CColorTag : public CCmdTarget
{
	DECLARE_DYNCREATE(CColorTag)

	CColorTag();           // protected constructor used by dynamic creation

// Attributes
public:
	int red;
	int grn;
	int blu;
	int cyn;
	int mag;
	int yel;
	int blk;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorTag)
	//}}AFX_VIRTUAL

// Implementation
	virtual ~CColorTag();
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CColorTag)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
