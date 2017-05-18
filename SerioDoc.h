// SerioDoc.h : interface of the CSerioDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CCell;
class CViewControlDlg;

/////////////////////////////////////////////////////
//CDlgStrArray object
class CDlgStrArray : public CStringArray
{
public:
	CDlgStrArray();
};

//////////////////////////////////////////////////////////////////
class CSerioDoc : public CDocument
{
protected: // create from serialization only
	CSize m_sizeDoc;
	CSerioDoc();
	DECLARE_DYNCREATE(CSerioDoc)
	UINT m_nCurMode;
	BOOL m_dNext;
	//CAspects* daspects;
public:
	void initDoc(CAspects* pasp);
	void initStrings();
	void initInts();
	void initBOOLs();
	static CSerioDoc* GetDoc();
	BOOL OnBlockLayoutPrompt(UINT count);
	BOOL OnCBlockLayoutPrompt(UINT count);
	void InductNewValues();
	int GetIDAspectCode(int entry);
	void RegisterAspects();
	BOOL GetAspectFlags(int entry, int item);
	UINT GetAspectCount(int index);
	float GetAspectSize(int index);
	int GetIDCode(int index);
	void OnViewControlDlg();
	BOOL m_dIfServCglom;
	void ToggleViewDlg();
	void CloseViewDlg();
	void ConvertToRGB(int oldc);
	void ConvertToCMY(int oldc);
	void ConvertToCMYK(int oldc);

	BOOL m_dDlgInProcess;//prevents OnDraw from flushing CCalc w/ doc data
	BOOL m_dFirstInit;//non-essential, but: tells OnNewDocument() that 
	//the CCalc object has just been loaded sub-sequent to 
	//CChildFrame::ActivateFrame() 
	BOOL m_willBeActive;
	BOOL m_preventViewDlgFocus;
	BOOL m_cancel;
	BOOL m_dExtraColsRows;
	int m_dOutlineClr;
	UINT m_dCBlocksNeeded;
	UINT m_dBlocksNeeded;
	//CCBlockLayoutDlg* m_cBlockDlg;
	//CBlockLayoutDlg* m_blockDlg;
	BOOL m_dCalledByDlg;
	UINT m_dBlockCols;
	UINT m_dBlockRows;
	UINT m_dCBlockCols;
	UINT m_dCBlockRows;

	BOOL m_dMouldy;
	POSITION pos;
	CSize GetDocSize() { return m_sizeDoc; }
	BOOL LoadCell(int x1,int y1,int x2,int y2);

	//initialization
	void InitRegObject(CSerioDoc* pDoc);
	void TidyUpPreviousDoc();

	//ViewDialog
	BOOL RestoreViewControlDlg();
	void SimulateCloseViewDlg();
	inline BOOL IsViewDlgOn(){return m_viewDlgOn;}
	void PreventViewDlgFocus();
	void GroomSuccessorWindow();
	BOOL m_dViewDlgCloseIsSimulated;
	BOOL m_dProcessingMouseActivate;
	BOOL ValidateNewPageView(UINT nuPage);
	CRect m_dViewDlgRect;

	BOOL GetNextVal();
	BOOL ToggleNext();
	BOOL m_dFormatDlgChangedView;//in case Format Dlg changes are scratched 
								//then views should be redrawn
	void CallDialog(int nDlg);
	int m_dOrientation_2;
	int m_dOrientation_1;
	int m_dOrientation_0;
	int m_dCalcIntent;
	int m_dMargRat;
	int m_dPosEd;
	float m_dFCBlock;
	float m_dFBlock;
	float m_dFCol;
	float m_dFRow;
	int m_dCBlockCount;
	int m_dBlockCount;
	int m_dColCount;
	int m_dRowCount;
	int m_dCellCount;
	int m_dEF2B;
	int m_dEF2L;
	int m_dET2B;
	int m_dEL2R;
	
	int m_dSF2B;
	int m_dSF2L;
	int m_dST2B;
	int m_dSL2R;
	CString m_dModeContext;
	CString m_dConstrMode;
	BOOL m_userLineBrkPerCol;
	BOOL m_userLineBrkPerRow;
	BOOL m_userLineBrkPerBlk;
	BOOL m_userLineBrkPerCBlk;
	BOOL m_dIsSquare;
	BOOL m_dCellRatio;
	BOOL m_dShowPage;
	BOOL m_dDerivePCnt;
	BOOL m_dBlockColLck;
	BOOL m_dBlockRowLck;
	BOOL m_dCBlockColLck;
	BOOL m_dCBlockRowLck;

	int m_dCurPage;
	int m_dColorMode;
	int m_dColRowCount;
	float m_dStepFreq;
	int m_dPageCount;
	CWnd* pwnd;
	int m_dEndRange;
	int m_dStartRange;
	float m_dVirtualPageHeight;
	float m_dVirtualPageWidth;
	float m_dCglomBlockHeight;
	float m_dCglomBlockWidth;
	float m_dBlockHeight;
	float m_dBlockWidth;
	float m_dCellHeight;
	float m_dCellWidth;
	float m_dPageHeight;
	float m_dPageWidth;
	float m_dRightMarg;
	float m_dLowerMarg;
	float m_dLeftMarg;
	float m_dUpperMarg;
	CAspects* initDims();
	CAspects* m_dasp;
	CViewControlDlg* m_viewDlg;
	void initCells();
	CString m_dPalette;
	CString m_dBitDepth;
	CString m_dUnitMeas;

	CDlgStrArray m_strArray;
	CArray<BOOL,BOOL>m_flags;
	CObList m_cellList;
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerioDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

	virtual ~CSerioDoc();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CSerioDoc)
	afx_msg void OnSpecifyColor();
	afx_msg void OnCellSpecs();
	afx_msg void OnSpecifyOrient();
	afx_msg void OnChange();
	afx_msg void OnQuickLayout();
	afx_msg void OnCBlockLayout();
	afx_msg void OnBlockLayout();
	afx_msg void OnAuto();
	afx_msg void OnUserControl();
	afx_msg void OnUpdateAuto(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUserControl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDlg(CCmdUI* pCmdUI);
	afx_msg void OnCMYKButton();
	afx_msg void OnCMYButton();
	afx_msg void OnRGBButton();
	afx_msg void OnViewPagefinder();
	afx_msg void OnUpdateViewPagefinder(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	//entries removed from messagemap:
	//	afx_msg void OnHelp();
	//	afx_msg void OnHelpFinder();

private:
	BOOL m_viewDlgOn;
	BOOL m_user;
	BOOL m_auto;
};

/////////////////////////////////////////////////////////////////////////////
class CCell : public CObject
{
public:
	BOOL DrawCell(CDC* pDC);
	//CCell(UINT nPenWidth);

	CCell();
protected:
	DECLARE_SERIAL(CCell)

	//Attributes
protected:

public:
	
	CArray<int,int> m_rect;
	
	//Operations
public:
//	virtual void Serialize(CArchive& ar);
};

////////////////////////////////////////////////////////////////////////
/*class CAspects : public CObject
{
public:
	static CString m_Units;
	CAspects();
protected:
	DECLARE_SERIAL(CAspects);
public:
	CArray<float,float> m_asp;
	//CArray<int,int> m_spec;
	//Operations
public:
	virtual void Serialize(CArchive& ar);

};*/
