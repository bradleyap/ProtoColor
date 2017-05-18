// ToggleManager.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "ToggleManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CYCLE 1
#define FEED_VALUE 1
#define TRACK_VALUE 2

/////////////////////////////////////////////////////////////////////////////
// CToggleManager

IMPLEMENT_DYNCREATE(CToggleManager, CCmdTarget)

CToggleManager::CToggleManager()
{
	m_count = 0;
	m_lastTimeToggled = 0;
	m_lastTimeStaggered = 0;
}

CToggleManager::~CToggleManager()
{
}


BEGIN_MESSAGE_MAP(CToggleManager, CCmdTarget)
	//{{AFX_MSG_MAP(CToggleManager)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToggleManager message handlers

void CToggleManager::SetStaggerInterval(UINT interVal)
{
	m_staggerInterval = interVal;
}

void CToggleManager::SetToggleInterval(UINT togVal)
{
	m_toggleInterval = togVal;
}

void CToggleManager::SetTrackBasis(int basis)
{
	m_eventBasis = basis;	
}

BOOL CToggleManager::Report(UINT optionalCueValue)
{
	BOOL toggleCode = 0;
	if(m_eventBasis==FEED_VALUE)
	{
		if(optionalCueValue==m_toggleCue)toggleCode = TRUE;
		if(optionalCueValue==m_staggerCue)
		{
			if(!toggleCode)toggleCode = TRUE;
			else toggleCode = FALSE;
		}
	}
	if(m_eventBasis==TRACK_VALUE)
	{
		if(m_count%m_toggleInterval==m_toggleOffsetValue)toggleCode = TRUE;
		if(m_count%m_staggerInterval==m_staggerOffsetValue)
		{
			if(!toggleCode)toggleCode = TRUE;
			else toggleCode = FALSE;
		}
	}
	m_count++;

	return toggleCode;
}

void CToggleManager::SetUpForCueMonitoring(UINT togVal,UINT staggerVal)
{
	m_toggleCue = togVal;
	m_staggerCue = staggerVal;
	m_eventBasis = FEED_VALUE;
}

void CToggleManager::SetUpForAutoTracking(UINT togVal,UINT togOffset,UINT stagVal,
		UINT stagOffsetVal)
{
	m_toggleInterval = togVal;
	m_toggleOffsetValue = togOffset;
	if(togOffset>=togVal)m_toggleOffsetValue = togOffset%togVal;

	m_staggerInterval = stagVal;
	m_staggerOffsetValue = stagOffsetVal;
	if(stagOffsetVal>=stagVal)m_staggerOffsetValue = stagOffsetVal%stagVal;

	m_eventBasis = TRACK_VALUE;
}

void CToggleManager::Reset(UINT nuCount)
{
	m_count = nuCount;
}

void CToggleManager::DestroyToggler()
{
	delete this;
}
