// ProgressBar.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressBar dialog


CProgressBar::CProgressBar(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressBar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressBar)
	//}}AFX_DATA_INIT
}


void CProgressBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressBar)
	DDX_Control(pDX, IDC_PROGRESS_STATIC, m_progressStatic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressBar, CDialog)
	//{{AFX_MSG_MAP(CProgressBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressBar message handlers

BOOL CProgressBar::OnInitDialog() 
{
	m_curMinutes = 0;
	m_curPixelWidth = 0;
	

	CDialog::OnInitDialog();

	CRect clientRect;
	m_progressStatic.GetStatusIndicatorArea(&clientRect);

	m_fullPixelWidth = clientRect.right - clientRect.left;
	m_fullPixelHeight = clientRect.bottom - clientRect.top;

	/*
		m_expectedGrandTotalMinutes		 m_fullPixelWidth
		---------------------------  =  ------------------
		      m_curMinutes				 m_curPixelWidth
	*/
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgressBar::UpdateProgressBar(UINT hoursProgressed, UINT minutesProgressed)
{
	m_curHours = hoursProgressed;
	m_curMinutes = (m_curHours * m_minutesPerHour) + minutesProgressed;

	unsigned long nuPixelLength;
	if(m_expectedGrandTotalMinutes!=0)nuPixelLength = 
		(m_fullPixelWidth * m_curMinutes) / m_expectedGrandTotalMinutes;
	else nuPixelLength = m_fullPixelWidth;

	if(nuPixelLength>m_fullPixelWidth)nuPixelLength = m_fullPixelWidth;

	if(nuPixelLength>m_curPixelWidth)
	{
		CRect changeArea;
		changeArea.left = m_curPixelWidth;
		changeArea.right = nuPixelLength;
		changeArea.top = 0;
		changeArea.bottom = m_fullPixelHeight;
		m_progressStatic.UpdateStatusRegion(nuPixelLength);
		//InvalidateRect(&changeArea,FALSE);
		//m_progressStatic.InvalidateRect(&changeArea,FALSE);
		//m_progressStatic.InvalidateRect(NULL,FALSE);
		//m_progressStatic.UpdateWindow();
		m_progressStatic.ExplicitWrite();
	}
}

void CProgressBar::InitializeProgressBar(unsigned long totalHours,
										 unsigned long totalMinutes)
{
	m_expectedHours = totalHours;
	m_minutesPerHour = totalMinutes;
	m_expectedGrandTotalMinutes = totalHours * totalMinutes;
}