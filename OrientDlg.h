// OrientDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrientDlg dialog
#include "DragStatic.h"
#include "ArrowSpin.h"
class COrientDlg : public CDialog
{	

// Construction
public:
	signed int m_track;
	int m_sync;
	int m_curPos;
	BOOL m_reset;
	int m_tempOrient;
	int m_orientCode;
	int m_colorMode;
	//CClientDC* GetDC();
	COrientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COrientDlg)
	enum { IDD = IDD_COLOR_ORIENTATION };
	CSpinButtonCtrl	m_spin;
	COrientStatic	m_T2B;
	COrientStatic	m_F2B;
	COrientStatic	m_F2L;
	COrientStatic	m_L2R;
	CDragStatic	m_Drag;
	CString	m_DirFB;
	CString	m_DirFL;
	CString	m_DirLR;
	CString	m_DirTB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPoint m_anchor;
	// Generated message map functions
	//{{AFX_MSG(COrientDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
