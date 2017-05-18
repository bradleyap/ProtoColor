// Bellows.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "Bellows.h"
#include "Maestro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBellows

IMPLEMENT_DYNCREATE(CBellows, CCmdTarget)

CBellows::CBellows()
{
}

CBellows::~CBellows()
{
}

extern CCalc scratchPad;

void CBellows::SetUpManipulations(CMaestro* maestro)
{
	m_conductor = maestro;
}

BEGIN_MESSAGE_MAP(CBellows, CCmdTarget)
	//{{AFX_MSG_MAP(CBellows)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBellows message handlers

void CBellows::DestroyBellows()
{
	delete this;
}

BOOL CBellows::ExploreChartAspectResize()
{
	BOOL attack = TRUE;
	attack = GetCueFromConductor();
	if(attack)::scratchPad.RequestRect(m_plugID,FALSE);

	return attack;

}

double CBellows::GetTargetSize()
{
	//m_targetSize = ;
	return m_targetSize;
}

BOOL CBellows::GetCueFromConductor()
{
	BOOL  attack = FALSE;
	attack = m_conductor->Conduct();
	return attack;
}

BOOL CBellows::PreImplantNewCount()
{
	BOOL timeToPlant = FALSE;
	return timeToPlant;
}

void CBellows::SetPlugID(int plugID)
{
	m_plugID = plugID;
}
