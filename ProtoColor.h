// Serio.h : main header file for the SERIO application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CSerioApp:
// See Serio.cpp for the implementation of this class
//

class CSerioApp : public CWinApp
{
public:
	long NumberOfDays(int initialDay, int initialMo, int initialYr,
							int finalDay, int finalMo, int finalYr);
	BOOL m_noRegFile;
	CSerioApp();
	CMultiDocTemplate* m_pDocTemplate;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerioApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
