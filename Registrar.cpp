// Registrar.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "Registrar.h"
#include "Bellows.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CELL_LEVEL 1

/////////////////////////////////////////////////////////////////////////////
// CRegistrar

IMPLEMENT_DYNCREATE(CRegistrar, CCmdTarget)

CRegistrar::CRegistrar()
{
}

CRegistrar::~CRegistrar()
{
}


BEGIN_MESSAGE_MAP(CRegistrar, CCmdTarget)
	//{{AFX_MSG_MAP(CRegistrar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistrar message handlers

extern CCalc scratchPad;

void CRegistrar::InitializeRegistry(int index,unsigned long nuCount,int colorMode,
									UINT * cols,UINT * rows,
									CBellows * bellows)
{
	m_requestIndex = index;
	m_bellows = bellows;

	if(index==13){m_colID=19;m_rowID=20;m_level=2;m_widthID=1;m_heightID=8;}
	if(index==14){m_colID=21;m_rowID=22;m_level=3;m_widthID=2;m_heightID=9;}
	if(index==5 || index==12)
	{
		m_colID=5;m_rowID=12;m_level=CELL_LEVEL;m_widthID=0;m_heightID=7;
		m_outLevel=2;
		m_levelOneRequest = TRUE;
		if(index==5)m_requestImpactIsHorizontal = TRUE;
		else m_requestImpactIsHorizontal = FALSE;
	}
	else
	{
		m_levelOneRequest = FALSE;
		m_requestImpactIsHorizontal = TRUE;
	}

	m_requestedCount = nuCount;

	if(m_level==2 && colorMode!=1)m_outLevel = 4;
	if(m_level==2 && colorMode==1)m_outLevel = 3;
	if(m_level==3)m_outLevel = 4;
	m_colorMode = colorMode;

	CRegAspect* aspLine = ::scratchPad.m_reg[m_colID];
	*cols = aspLine->m_nNuCount;
	aspLine = ::scratchPad.m_reg[m_rowID];
	*rows = aspLine->m_nNuCount;

	//m_curColCountPtr = cols;
	//m_curRowCountPtr = rows;
}

void CRegistrar::DestroyRegistry()
{
	delete this;
}

void CRegistrar::SetColumnInfo(CRegAspect * colLine)
{
	m_columnLine = colLine;
	SetCurrentColumnCount((UINT)colLine->m_nNuCount);
}

void CRegistrar::SetRowInfo(CRegAspect * rLine)
{
	m_rowLine = rLine;
	SetCurrentRowCount((UINT)rLine->m_nNuCount);
}

void CRegistrar::ChangeAxisMode(BOOL curAspectIsHoriz)
{
	if(curAspectIsHoriz)
	{
		m_curRequestID = m_colID;
		//m_curAspectID = m_
	}
	else
	{
		m_curRequestID = m_rowID;
	}
}

BOOL CRegistrar::IsRequestLevelOne()
{
	return m_levelOneRequest;
}

UINT CRegistrar::GetRequestedCount()
{
	//return m_requestLine->m_origReqCount;
	return m_requestedCount;

}

void CRegistrar::SetRequestInfo(CRegAspect * reqLine)
{
	m_requestLine = reqLine;
}

void CRegistrar::SetPageTotal(UINT total)
{
	m_totalPages = total;
}

UINT CRegistrar::GetCurrentColumnCount()
{	
	return m_curColumns;
}

UINT CRegistrar::GetCurrentRowCount()
{
	return m_curRows;
}

void CRegistrar::SetCurrentRowCount(UINT rows)
{
	m_curRows = rows;
	//*m_curRowCountPtr = rows;
}

void CRegistrar::SetCurrentColumnCount(UINT cols)
{
	m_curColumns = cols;
	//*m_curColCountPtr = cols;
}

UINT CRegistrar::GetCurrentCount()
{
	return m_requestLine->m_nNuCount;
}

CRegAspect * CRegistrar::GetEntryLine(int entryID)
{
	return ::scratchPad.m_reg[entryID];
}

void CRegistrar::SendPlugID(int plugID)
{
	m_bellows->SetPlugID(plugID);
}

void CRegistrar::SetCurrentCount(UINT nuCount)
{
	m_requestLine->m_nNuCount = nuCount;
}
