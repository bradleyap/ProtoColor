// ViewControlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewControlDlg dialog

class CViewControlDlg : public CDialog
{
// Construction
public:
	CViewControlDlg(CWnd* pParent = NULL);   // standard constructor
	int m_refuseFocus;
	UINT m_curPageBuf;
	//LRESULT CViewControlDlg::DefWindowProc(UINT message,WPARAM wparam,LPARAM lparam );

// Dialog Data
	//{{AFX_DATA(CViewControlDlg)
	enum { IDD = IDD_VIEW_PAGE };
	UINT	m_curPage;
	//}}AFX_DATA

	void ShutDown();
	void SignifyCloseByMenu(BOOL startProc);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_closePromptedByMenu;
	// Generated message map functions
	//{{AFX_MSG(CViewControlDlg)
	afx_msg void OnClose();
	afx_msg void OnChangeCurPageEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
