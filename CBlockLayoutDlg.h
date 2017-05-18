// CBlockLayoutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCBlockLayoutDlg dialog


class CCBlockLayoutDlg : public CDialog
{
// Construction
public:
	BOOL extra;
	UINT m_blocksNeeded;
	BOOL byDlg;
	int m_color;
	CCBlockLayoutDlg(CWnd* pParent = NULL);   // standard constructor
	void InductNewValues();
	float m_bufBlockH;
	float m_bufBlockW;
	float m_bufBlockCols;
	float m_bufBlockRows;
	float m_bufFrameH;
	float m_bufFrameW;
	float m_bufColSpace;
	float m_bufRowSpace;

// Dialog Data
	//{{AFX_DATA(CCBlockLayoutDlg)
	enum { IDD = IDD_CBLOCK_LAYOUT };
	CMyOtherEdit	m_trapDec;
	CMyOtherEdit	m_trapDec2;
	CMyOtherEdit	m_trapDec3;
	CMyOtherEdit	m_trapDec4;
	CMyOtherEdit	m_trapDec5;
	CMyOtherEdit	m_trapDec6;
	CBlockDragStatic	m_drag;
	float	m_colSpace;
	float	m_blockH;
	float	m_rowSpace;
	float	m_frameH;
	UINT	m_blockCols;
	UINT	m_blockRows;
	float	m_frameW;
	float	m_blockW;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBlockLayoutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCBlockLayoutDlg)
	afx_msg void OnCblResetBn();
	afx_msg void OnChangeCbWEdit();
	afx_msg void OnChangeCbHEdit();
	afx_msg void OnChangeCblkColsEdit();
	afx_msg void OnChangeCblkRowsEdit();
	afx_msg void OnChangeVFrmWEdit();
	afx_msg void OnChangeVFrmHEdit();
	afx_msg void OnChangeCbColspEdit();
	afx_msg void OnChangeCbRowspEdit();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
