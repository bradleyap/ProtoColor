// ProgressBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressBar dialog
#include "ProgressStatic.h"

class CProgressBar : public CDialog
{
// Construction
public:
	void InitializeProgressBar(unsigned long hrs,unsigned long mins);
	void UpdateProgressBar(UINT loop1, UINT loop2);
	CProgressBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressBar)
	enum { IDD = IDD_MY_STATUS_BAR };
	CProgressStatic	m_progressStatic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	unsigned long m_curHours;
	unsigned long m_curMinutes;
	unsigned long m_curPixelWidth;
	unsigned long m_expectedGrandTotalMinutes;
	unsigned long m_minutesPerHour;
	unsigned long m_expectedHours;
	long m_fullPixelHeight;
	long m_fullPixelWidth;

	// Generated message map functions
	//{{AFX_MSG(CProgressBar)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
