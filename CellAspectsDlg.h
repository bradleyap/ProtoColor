// CellAspectsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCellAspectsDlg dialog

class CCellAspectsDlg : public CDialog
{
// Construction
public:
	float m_rectW;
	float m_rectH;
	float m_blockW;
	float m_blockH;
	float m_cBlockW;
	float m_cBlockH;
	float m_fRow;
	float m_fCol;
	float m_fBlk;
	float m_fCBlk;
	UINT m_cols;
	UINT m_rows;
	UINT m_blocks;
	UINT m_cBlocks;

	BOOL m_tl;
	BOOL m_tl2;
	BOOL m_tl3;
	BOOL m_tl4;
	BOOL m_tl5;
	BOOL m_tl6;
	BOOL m_tl7;
	BOOL m_tl8;
	BOOL m_tl9;
	BOOL m_tl10;
	BOOL m_tl11;
	BOOL m_cnsB;
	BOOL m_cnsCB;
	BOOL m_cnsR;
	BOOL m_cnsC;
	BOOL m_colCchange;
	BOOL m_rowCchange;
	BOOL m_colsChange;
	BOOL m_rowsChange;
	BOOL m_bCountChange;
	BOOL m_cBCountChange;
	BOOL m_cBlockHchange;
	BOOL m_cBlockWchange;
	BOOL m_blockHchange;
	BOOL m_blockWchange;
	BOOL m_rectHchange;
	BOOL m_rectWchange;
	BOOL m_blkFrqChange;
	BOOL m_cBlkFrqChange;
	BOOL m_rowFrqChange;
	BOOL m_colFrqChange;
	BOOL m_change;
	BOOL m_enableRowFreqWindow;
	BOOL m_enableColFreqWindow;
	BOOL m_enableBlockFreqWindow;
	BOOL m_enableCBlockFreqWindow;
	BOOL m_cHitch;	//indicates change in constrain check bx
	BOOL m_cConform; //indicates change in IsSq check bx
	BOOL m_intTest;
	BOOL m_Bn;
	BOOL m_Bn2;
	BOOL m_Bn3;
	BOOL m_Bn4;
	BOOL m_Bn5;
	BOOL m_Bn6;
	BOOL m_Bn7;
	BOOL m_Bn8;
	BOOL m_Bn9;
	BOOL m_Bn10;
	BOOL m_Bn11;
	BOOL m_Bn12;
	BOOL m_Bn13;
	BOOL m_Bn14;
	BOOL m_Bn15;
	BOOL m_Bn16;



	int m_color;
	void UnifyCBs(int nBoxID);
	CString m_origStr;
	CBitmapButton m_LockBn11;
	CBitmapButton m_LockBn9;
	CBitmapButton m_LockBn10;
	CBitmapButton m_LockBn8;
	CBitmapButton m_LockBn7;
	CBitmapButton m_LockBn6;
	CBitmapButton m_LockBn5;
	CBitmapButton m_LockBn4;
	CBitmapButton m_LockBn3;
	CBitmapButton m_LockBn2;
//	CBitmapButton m_LockBn; //formerly in conjunction w/ m_TogLock IDC_'16
	BOOL m_TogLock11;
	BOOL m_TogLock10;
	BOOL m_TogLock9;
	BOOL m_TogLock8;
	BOOL m_TogLock7;
	BOOL m_TogLock6;
	BOOL m_TogLock5;
	BOOL m_TogLock4;
	BOOL m_TogLock3;
	BOOL m_TogLock2;

	BOOL m_intSyncOrig;
	BOOL m_reflectOrig;
	//void NonStatTest();
	//CString GetStrForFloatMember(int nID);
	void ControlActivationByCountOfOne(BOOL fromReset);
	void ControlDeactivationByCountOfOne(BOOL fromInit,BOOL fromReset);
	void SignalFlagChangesToCalc();
	void UpdateMembersFromCalc();
	void StoreRestoreChangeFlagsAndValues(CAspectsBuffer* requestBf,
								   BOOL store);
	double MemberFloatLUT(int cntlID);
	UINT GetNumericValue(int val);
	double GetDenom(int expon, BOOL mult);
	BOOL ExtractValue(int cntlID);
	CCellAspectsDlg*  m_pCCellAsp;
	CCellAspectsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCellAspectsDlg)
	enum { IDD = IDD_CELL_ASPECTS };
	CMyEdit	m_CellWidth;
	CIntsEdit	m_rowCountCtl;
	CIntsEdit	m_colCountCtl;
	CIntsEdit	m_cBlockCountCtl;
	CIntsEdit	m_blockCountCtl;
	CMyEdit	m_freqRow;
	CMyEdit	m_freqCol;
	CMyEdit	m_freqCblock;
	CMyEdit	m_freqBlock;
	CMyEdit	m_BlockHeight;
	CMyEdit	m_CBlockWidth;
	CMyEdit	m_CBlockHeight;
	CMyEdit	m_BlockWidth;
	CMyEdit	m_CellHeight;
	BOOL	m_nCellRatio;
	CString	m_nUnits;
	CString	m_nUnits2;
	CString	m_nUnits3;
	CString	m_nUnits4;
	CString	m_nUnits5;
	CString	m_nUnits6;
	float	m_CellHeightVal;
	float	m_BlockHeightVal;
	float	m_BlockWidthVal;
	float	m_CBlockHeightVal;
	float	m_CBlockWidthVal;
	int		m_nDrawOften;
	BOOL	m_Reflect;
	int		m_nBlockCount;
	int		m_nCBlockCount;
	int		m_nColCount;
	int		m_nRowCount;
	BOOL	m_CnsBlock;
	BOOL	m_CnsCBlock;
	BOOL	m_CnsCol;
	BOOL	m_CnsRow;
	float	m_F_BLK;
	float	m_F_CBLK;
	float	m_F_COL;
	float	m_F_ROW;
	BOOL	m_IntSync;
	float	m_CellWidthVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCellAspectsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSerioDoc* pDcmt;
	// Generated message map functions
	//{{AFX_MSG(CCellAspectsDlg)
	afx_msg void OnCellAspectsHelp();
	afx_msg void OnCAspectsQuickButton();
	virtual BOOL OnInitDialog();
	afx_msg void OnLocked17();
	afx_msg void OnLocked18();
	afx_msg void OnLocked19();
	afx_msg void OnLocked20();
	afx_msg void OnLocked21();
	afx_msg void OnLocked22();
	afx_msg void OnLocked23();
	afx_msg void OnLocked24();
	afx_msg void OnLocked25();
	afx_msg void OnLocked26();
	afx_msg void OnSelchangeUnitMeasComb1();
	afx_msg void OnSelchangeUnitMeasComb2();
	afx_msg void OnSelchangeUnitMeasComb3();
	afx_msg void OnSelchangeUnitMeasComb4();
	afx_msg void OnSelchangeUnitMeasComb5();
	afx_msg void OnSelchangeUnitMeasComb6();
	virtual void OnOK();
	afx_msg void OnJump();
	afx_msg void OnReset();
	afx_msg void OnCalculate();
	virtual void OnCancel();
	afx_msg void OnChangeBlockHeight();
	afx_msg void OnChangeBlockWidth();
	afx_msg void OnChangeCBlockCount();
	afx_msg void OnChangeBlockCount();
	afx_msg void OnChangeCellHeight();
	afx_msg void OnChangeCnglBlockH();
	afx_msg void OnChangeCnglBlockW();
	afx_msg void OnChangeColumnCount();
	afx_msg void OnChangeRowCount();
	afx_msg void OnChangeCellW();
	afx_msg void OnCellRatio();
	afx_msg void OnChangeFrqRow();
	afx_msg void OnChangeFrqCol();
	afx_msg void OnChangeFrqCblk();
	afx_msg void OnChangeFrqBlk();
	afx_msg void OnCnsCblk();
	afx_msg void OnCnsCol();
	afx_msg void OnCnsRow();
	afx_msg void OnCnsBlk();
	afx_msg void OnIntSync();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CCHeightEdit: public CEdit
{
// Construction
public:
	CCHeightEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHeightEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCHeightEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCHeightEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
