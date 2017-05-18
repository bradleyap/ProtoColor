// QuickLayout.h : header file
//
#include "ClickStatic.h"
/////////////////////////////////////////////////////////////////////////////
// CQuickLayout dialog



class CQuickLayout : public CDialog
{
	
// Construction
	
public:
	BOOL ExtractValue(int cntlID);
	double GetDenom(int expon,BOOL mult);
	UINT GetNumericValue(int val);
	double MemberFloatLUT(int cntlID);

	int m_xPic;
	int m_yPic;
	int m_saveMult;
	int m_origUnits;//0=inches 1=pixels 2=centimeters
	UINT m_pageC;
	float m_pageW;
	float m_pageH;
	float m_leftM;
	float m_rightM;
	float m_topM;
	float m_botM;
	BOOL m_pageCchange;
	BOOL m_pageWchange;
	BOOL m_pageHchange;
	BOOL m_leftMchange;
	BOOL m_rightMchange;
	BOOL m_topMchange;
	BOOL m_botMchange;
	BOOL m_Bn7;
	BOOL m_Bn6;
	BOOL m_Bn5;
	BOOL m_Bn4;
	BOOL m_Bn3;
	BOOL m_Bn2;
	BOOL m_Bn;

	BOOL m_next;
	CString m_origStr;
	void UnifyCBs(int nBoxID);
	
	UINT m_MargRatResult;
	BOOL m_tl7;
	BOOL m_tl6;
	BOOL m_tl5;
	BOOL m_tl4;
	BOOL m_tl3;
	BOOL m_tl2;
	BOOL m_tl;

	BOOL m_TogLock7;
	BOOL m_TogLock6;
	BOOL m_TogLock5;
	BOOL m_TogLock4;
	BOOL m_TogLock3;
	BOOL m_TogLock2;
	BOOL m_TogLock;
	CBitmapButton m_LockBn7;
	CBitmapButton m_LockBn6;
	CBitmapButton m_LockBn5;
	CBitmapButton m_LockBn4;
	CBitmapButton m_LockBn3;
	CBitmapButton m_LockBn2;
	CBitmapButton m_LockBn;
	CSerioDoc* pDcmt;
	
	
	float m_nBogus;
	CQuickLayout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQuickLayout)
	enum { IDD = IDD_PAGE_LAYOUT };
	CMyEdit	m_upMgCtl;
	CMyEdit	m_rightMgCtl;
	CMyEdit	m_pgWthCtl;
	CMyEdit	m_pgHtCtl;
	CMyEdit	m_lowMgCtl;
	CMyEdit	m_leftMgCtl;
	CIntsEdit	m_pageCountCtl;
	CClickStatic	m_Click;
	float	m_nLeftMarg;
	float	m_nLowerMarg;
	int		m_nPageCount;
	float	m_nPageHeight;
	float	m_nPageWidth;
	BOOL	m_nShowPage;
	float	m_nRightMarg;
	float	m_nUpperMarg;
	CString	m_nUnits;
	CString	m_nUnits1;
	CString	m_nUnits2;
	CString	m_nUnits3;
	CString	m_nUnits4;
	CString	m_nUnits5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuickLayout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBitmap m_bitmap;

	// Generated message map functions
	//{{AFX_MSG(CQuickLayout)
	virtual BOOL OnInitDialog();
	afx_msg void OnLocked10();
	afx_msg void OnLocked12();
	afx_msg void OnLocked13();
	afx_msg void OnLocked14();
	afx_msg void OnLocked15();
	afx_msg void OnLocked9();
	virtual void OnOK();
	afx_msg void OnSelchangeUnitComb();
	afx_msg void OnSelchangeUnitComb2();
	afx_msg void OnSelchangeUnitComb3();
	afx_msg void OnSelchangeUnitComb4();
	afx_msg void OnSelchangeUnitComb5();
	afx_msg void OnSelchangeUnitComb6();
	afx_msg void OnCompute();
	afx_msg void OnLayoutJump();
	afx_msg void OnChangeLeftMEdit();
	afx_msg void OnChangeLowerMEdit();
	afx_msg void OnChangePageCount();
	afx_msg void OnChangePagehEdit();
	afx_msg void OnChangePagewEdit();
	afx_msg void OnChangeRightMEdit();
	afx_msg void OnChangeUpperMEdit();
	virtual void OnCancel();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

