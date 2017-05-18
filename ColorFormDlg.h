// ColorFormDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorFormDlg dialog


class CColorFormDlg : public CDialog
{
// Construction
public:
	//backup variables for reset
	BOOL m_resetCall;
	//locks
	BOOL m_tl;
	BOOL m_tl2;
	BOOL m_tl3;
	BOOL m_tl4;
	BOOL m_tl5;
	BOOL m_tl6;
	BOOL m_tl7;
	BOOL m_tl8;

	//to flag changes
	BOOL m_startL2RChange;
	BOOL m_startT2BChange;
	BOOL m_startF2LChange;
	BOOL m_startF2BChange;
	BOOL m_endL2RChange;
	BOOL m_endT2BChange;
	BOOL m_endF2LChange;
	BOOL m_endF2BChange;

	BOOL m_lockChange;
	BOOL m_lock2Change;
	BOOL m_lock3Change;
	BOOL m_lock4Change;
	BOOL m_lock5Change;
	BOOL m_lock6Change;
	BOOL m_lock7Change;
	BOOL m_lock8Change;

	CString m_ax1str;
	CString m_ax2str;
	CString m_ax3str;
	CString m_ax4str;
	int m_origModel;
	int m_resetSel;
	CString m_origSteps;
	CString m_out;
	BOOL m_sBasis;

	//working variables
	int m_lastSel;
	float m_start1prec;
	float m_start2prec;
	float m_start3prec;
	float m_start4prec;
	float m_end1prec;
	float m_end2prec;
	float m_end3prec;
	float m_end4prec;
	BOOL m_next;
	BOOL  m_origCalcIntent;
	CBitmapButton m_LockBn;
	CBitmapButton m_LockBn2;
	CBitmapButton m_LockBn3;
	CBitmapButton m_LockBn4;
	CBitmapButton m_LockBn5;
	CBitmapButton m_LockBn6;
	CBitmapButton m_LockBn7;
	CBitmapButton m_LockBn8;
	int m_efb;
	int m_efl;
	int m_etb;
	int m_elr;
	int m_sfb;
	int m_sfl;
	int m_stb;
	int m_slr;

	BOOL m_TogLock8;
	BOOL m_TogLock7;
	BOOL m_TogLock6;
	BOOL m_TogLock5;
	BOOL m_TogLock4;
	BOOL m_TogLock3;
	BOOL m_TogLock2;
	BOOL m_TogLock;
	int GetRounded(float fig);	
	BOOL ConvertRangeValues(BOOL toPer,BOOL final);
	void ConvertToFromPercent(double rate);
	CColorFormDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CColorFormDlg)
	enum { IDD = IDD_COLOR_FORMAT };
	CIntsEdit	m_8;
	CIntsEdit	m_7;
	CIntsEdit	m_6;
	CIntsEdit	m_5;
	CIntsEdit	m_4;
	CIntsEdit	m_3;
	CIntsEdit	m_2;
	CIntsEdit	m_1;
	int		m_nColorMode;
	CString	m_nMaxSteps;
	int		m_StartL2R;
	int		m_StartT2B;
	int		m_StartF2L;
	int		m_EndF2B;
	int		m_EndF2L;
	int		m_EndL2R;
	int		m_EndT2B;
	int		m_StartF2B;
	CString	m_nOutLineClr;
	BOOL	m_autoLock;
	int		m_calcIntent;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorFormDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	//CSerioDoc* pDoc;
	// Generated message map functions
	//{{AFX_MSG(CColorFormDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLocked();
	afx_msg void OnLocked2();
	afx_msg void OnLocked3();
	afx_msg void OnLocked4();
	afx_msg void OnLocked5();
	afx_msg void OnLocked6();
	afx_msg void OnLocked7();
	afx_msg void OnLocked8();
	afx_msg void OnColorJump();
	afx_msg void OnRadioRgb();
	afx_msg void OnRadioCmyk();
	afx_msg void OnRadioCmy();
	afx_msg void OnSelchangeMaxSteps();
	afx_msg void OnChangeEndRaF2b();
	afx_msg void OnChangeEndRaF2l();
	afx_msg void OnChangeEndRaL2r();
	afx_msg void OnChangeEndRaT2b();
	afx_msg void OnChangeStartRaF2b();
	afx_msg void OnChangeStartRaF2l();
	afx_msg void OnChangeStartRaL2r();
	afx_msg void OnChangeStartRaT2b();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeOutlColr();
	afx_msg void OnColorReset();
	afx_msg void OnComputeColorRange();
	afx_msg void OnAutoLockRange();
	afx_msg void OnHonorReq();
	afx_msg void OnPreserveLay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
CString GetAxisString(int oCode,int axis);
};

