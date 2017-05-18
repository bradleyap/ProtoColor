// Serio.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ProtoColor.h"


#include "MainFrm.h"
#include "ChildFrm.h"
#include "SerioDoc.h"
#include "SerioView.h"
#include "EulaDlg.h"
#include "AuthorizeDlg.h"
#include "Flash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerioApp

BEGIN_MESSAGE_MAP(CSerioApp, CWinApp)
	//{{AFX_MSG_MAP(CSerioApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerioApp construction

CSerioApp::CSerioApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSerioApp object

CSerioApp theApp;
CCalc scratchPad;

/////////////////////////////////////////////////////////////////////////////
// CSerioApp initialization

BOOL CSerioApp::InitInstance()
{
	scratchPad.m_firstInit = FALSE;
	m_noRegFile = FALSE;

	//AfxEnableControlContainer();
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	//CMultiDocTemplate* pDocTemplate;
	m_pDocTemplate = new CMultiDocTemplate(
		IDR_PROCOTYPE,
		RUNTIME_CLASS(CSerioDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSerioView));
	AddDocTemplate(m_pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();


	CFile regFile;
	CFileException e;
	
	int eula = 0;
	int freeFiles = 0;
	int freePrintouts = 0;
	int reg = 0;
	SetRegistryKey("Highway 65 Software, Inc.");

	CFlash flashDlg;
	flashDlg.DoModal();
	ShowCursor(TRUE);

	eula = GetProfileInt("ProtoColor1.0","agreed",0);
	if(eula==0)
	{
		CEulaDlg dlg;
		if(dlg.DoModal()==IDOK)
		{
			WriteProfileInt("ProtoColor1.0","agreed",1);
		}
		else return FALSE;
	}
/* 
	This software is now Open Source .. 5-18-2017 -Brad Pliam	
	Keeping this code around only for reference, and as example of how to work with
	registry keys etc....

	reg = GetProfileInt("ProtoColor1.0","authorizationCode",0);
	if(reg!=77712)
	{
		CAuthorizeDlg dlg;
		if(dlg.DoModal()==IDOK)
		{
			if(dlg.m_codeValid)
			{
				WriteProfileInt("ProtoColor1.0", "authorizationCode",77712);
				scratchPad.m_registered = TRUE;
			}
			else
			{
				//exit if trial period has expired
				SYSTEMTIME st;
				GetSystemTime(&st);
				int runPreviously = 0;
				runPreviously = GetProfileInt("ProtoColor1.0", "runPreviously", 99);
				if(runPreviously==1)
				{
					int launchMo = 99;
					int launchDay = 99;
					int launchYear = 99;
					launchMo = GetProfileInt("ProtoColor1.0", "launchMonth", 99);
					launchDay = GetProfileInt("ProtoColor1.0", "launchDay", 99);
					launchYear = GetProfileInt("ProtoColor1.0", "launchYear", 99);
					if(NumberOfDays(launchDay,launchMo, launchYear, st.wDay, st.wMonth, st.wYear)>15)
					{
						AfxMessageBox("The Trial Period for this software has expired.  Please see User's.doc for information about enabling ProtoColor 1.0"); 	
						return FALSE;
					}
				}
				else 
				{
					//this is first launch of ProtoColor
					WriteProfileInt("ProtoColor1.0", "runPreviously", 1);
					WriteProfileInt("ProtoColor1.0", "launchMonth", st.wMonth);
					WriteProfileInt("ProtoColor1.0", "launchYear", st.wYear);
					WriteProfileInt("ProtoColor1.0", "launchDay", st.wDay);
				}
				
				//set up to run under evaluation period constraints
				scratchPad.m_registered = FALSE;
				freeFiles = GetProfileInt("ProtoColor1.0","testFiles",99);
				if(freeFiles!=99)scratchPad.m_freeFiles = freeFiles;
				else freeFiles = 0;
				if(freeFiles>9)AfxMessageBox("WARNING:  The number of 'save' operations allowed for this evaluation period has reached the maximum.  You will not be able to save your work!");
				freePrintouts = GetProfileInt("ProtoColor1.0", "testCharts",99);
				if(freePrintouts!=99)scratchPad.m_freePrintouts = freePrintouts;
				else freePrintouts = 0;
				if(freePrintouts>9)AfxMessageBox("WARNING:  The number of 'print' operations allowed for this evaluation period has reached the maximum.  You will no longer be able to generate 'printed' output.");
			}
		}
		else return FALSE;
	}
*/
	else scratchPad.m_registered = TRUE;

	return TRUE;
}


long CSerioApp::NumberOfDays(int initialDay, int initialMo, int initialYr,
							int finalDay, int finalMo, int finalYr)
{
	#define PRE_JAN 0//31
	#define PRE_FEB 31//28
	#define PRE_MAR 59//31
	#define PRE_APR 90//30
	#define PRE_MAY 120//31
	#define PRE_JUN 151//30
	#define PRE_JUL 181//31
	#define PRE_AUG 212//31
	#define PRE_SEP 243//30
	#define PRE_OCT 273//31
	#define PRE_NOV 304//30
	#define PRE_DEC 334//31
	long count = 0;
	long beginDate = 0;
	long endDate;
	long monthTally = 0;
	long firstLeapDay = 0;
	if(initialMo==1)monthTally = PRE_JAN;
	if(initialMo==2)monthTally = PRE_FEB;
	if(initialMo==3)monthTally = PRE_MAR;
	if(initialMo==4)monthTally = PRE_APR;
	if(initialMo==5)monthTally = PRE_MAY;
	if(initialMo==6)monthTally = PRE_JUN;
	if(initialMo==7)monthTally = PRE_JUL;
	if(initialMo==8)monthTally = PRE_AUG;
	if(initialMo==9)monthTally = PRE_SEP;
	if(initialMo==10)monthTally = PRE_OCT;
	if(initialMo==11)monthTally = PRE_NOV;
	if(initialMo==12)monthTally = PRE_DEC;
	beginDate = monthTally;
	beginDate += initialDay;

	int yr2Leap = 4 - ((initialYr - 2000) % 4);
	yr2Leap += (initialYr - 2000) / 4;
	int days2Leap1 = (365 - beginDate) + ((yr2Leap - 1) * 365) + 59;
	

	endDate = (finalYr - initialYr) * 365;
	if(finalMo==1)monthTally = PRE_JAN;
	if(finalMo==2)monthTally = PRE_FEB;
	if(finalMo==3)monthTally = PRE_MAR;
	if(finalMo==4)monthTally = PRE_APR;
	if(finalMo==5)monthTally = PRE_MAY;
	if(finalMo==6)monthTally = PRE_JUN;
	if(finalMo==7)monthTally = PRE_JUL;
	if(finalMo==8)monthTally = PRE_AUG;
	if(finalMo==9)monthTally = PRE_SEP;
	if(finalMo==10)monthTally = PRE_OCT;
	if(finalMo==11)monthTally = PRE_NOV;
	if(finalMo==12)monthTally = PRE_DEC;
	endDate += monthTally;
	endDate += finalDay;
	count = endDate - beginDate;
	int add = 0;
	if(count>days2Leap1)
	{
		add++;
		add += (count - days2Leap1) / (365 * 4);
	}
	count += add;
	return count;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSerioApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSerioApp commands

