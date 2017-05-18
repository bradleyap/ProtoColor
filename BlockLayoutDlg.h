// BlockLayoutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlockLayoutDlg dialog

class CBlockLayoutDlg : public CDialog
{
// Construction
public:
	//CBlockLayoutDlg* m_blockDlg;
	BOOL extra;
	BOOL m_blocksNeeded;
	BOOL byDlg;
	void InductNewValues();
	CBlockLayoutDlg(CWnd* pParent = NULL);   // standard constructor
	float m_bufBlockH;
	float m_bufBlockW;
	float m_bufBlockCols;
	float m_bufBlockRows;
	float m_bufFrameH;
	float m_bufFrameW;
	float m_bufColSpace;
	float m_bufRowSpace;

// Dialog Data
	//{{AFX_DATA(CBlockLayoutDlg)
	enum { IDD = IDD_BLOCK_LAYOUT };
	CMyOtherEdit	m_trapDec6;
	CMyOtherEdit	m_trapDec5;
	CMyOtherEdit	m_trapDec4;
	CMyOtherEdit	m_trapDec3;
	CMyOtherEdit	m_trapDec2;
	CMyOtherEdit	m_trapDec;
	CBlockDragStatic	m_drag;
	UINT	m_blockCols;
	UINT	m_blockRows;
	float	m_frameH;
	float	m_frameW;
	float	m_blockH;
	float	m_blockW;
	float	m_colSpace;
	float	m_rowSpace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlockLayoutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBlockLayoutDlg)
	afx_msg void OnChangeBcolsEdit();
	afx_msg void OnChangeBrowsEdit();
	afx_msg void OnChangeFrameHEdit();
	afx_msg void OnChangeFrameWEdit();
	afx_msg void OnChangeBlockhEdit();
	afx_msg void OnChangeBlockwEdit();
	afx_msg void OnChangeBColspaceEdit();
	afx_msg void OnChangeBRowspaceEdit();
	afx_msg void OnBlockLayResetBn();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
