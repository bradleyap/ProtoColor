// Maestro.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "Maestro.h"
#include "Registrar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TWO_BARS 16


/////////////////////////////////////////////////////////////////////////////
// CMaestro

IMPLEMENT_DYNCREATE(CMaestro, CCmdTarget)

CMaestro::CMaestro()
{
}

CMaestro::~CMaestro()
{
}

void CMaestro::InitializeMaestro(CRegistrar* registry)
{
	m_regInfo = registry;
	m_baton = 1;
	m_failureCount = 0;
	m_decreaseGiven = FALSE;
	m_beginningOfBar = TRUE;
	m_aTimeToGrow = FALSE;
	m_concernsAreHorizontal = TRUE;
	m_pendingCountLoaded = FALSE;
	m_abortRequestRect = FALSE;
	m_ultimateCountDesired = m_regInfo->GetRequestedCount();
	if(m_ultimateCountDesired>=m_regInfo->GetCurrentCount())
		m_desiredCountIsIncrease = TRUE;
	else m_desiredCountIsIncrease = FALSE;
	DetermineUltimateCountChange();
}

BEGIN_MESSAGE_MAP(CMaestro, CCmdTarget)
	//{{AFX_MSG_MAP(CMaestro)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaestro message handlers

extern CCalc scratchPad;

BOOL CMaestro::Conduct()
{
	BOOL play = FALSE;
	m_pendingCountLoaded = FALSE;
	//if(m_beginningOfBar)
	PrepareForNewMeasure();
	LoadRequestValues();
	SendPlugID();
	if(m_pendingCountLoaded)play = TRUE;
	if(m_abortRequestRect)
	{
		play = FALSE;
		m_abortRequestRect = FALSE;
	}
	return play;
}


void CMaestro::LoadRequestValues()
{
	int nID = m_plugID;
	int lev = m_regInfo->GetRequestLevel();
	BOOL countIncrs = m_desiredCountIsIncrease;
	BOOL forCells = m_regInfo->IsRequestLevelOne();
	int colorMode = m_regInfo->GetColorMode();
	UINT cols = m_regInfo->GetCurrentColumnCount();
	UINT rows = m_regInfo->GetCurrentRowCount();
	double nuSize = 1.0;
	double minAspSize,maxAspSize;
	double outAspSz;
	CRegAspect * line;
	CRegAspect * cLine;
	CRegAspect * inLine;
	CRegAspect * outLine;

	if(!countIncrs && ((forCells && m_pendingCountLoaded)||!forCells))
	{
		line = m_regInfo->GetEntryLine(m_plugID);
		if((m_concernsAreHorizontal && cols==1)||
			(!m_concernsAreHorizontal && rows==1))
		{
			//determine index and nuSize
			//initialize nuSize on the way
			line = m_regInfo->GetEntryLine(nID);
			nuSize = line->m_nNuSize;
			m_plugID = GetEnclosingAspectID(nID);
			if(colorMode!=1 && lev==2)m_plugID = 
				GetEnclosingAspectID(m_plugID);
			if(m_aTimeToGrow) 
			{
				line = m_regInfo->GetEntryLine(m_plugID);
				nuSize = line->m_nNuSize;
				m_plugID = nID;
			}
			//implement new count
			cLine = m_regInfo->GetEntryLine(GetAssociatedCountID(nID));
			cLine->m_nNuCount = 1;
		}
		else 
		{
			m_decreaseGiven = TRUE;
			nuSize = line->m_nNuSize;
		}
		m_pendingCountLoaded = TRUE;
	}//(!countIncrs && m_pendingCountLoaded)
	if(countIncrs && m_pendingSpatialFormatLoaded)
	{
		//determine index and nuSize
		line = m_regInfo->GetEntryLine(nID);
		double aspSize = line->m_nNuSize;
		double outAspSz;
		BOOL aspLck = FALSE;
		aspLck = line->m_locked;
		if(line->m_minSet && !m_aTimeToGrow)aspLck = TRUE;
		if(m_aTimeToGrow)
		{
			if(lev!=1)
			{
				int inID = GetEnclosedAspectID(nID);
				inLine = m_regInfo->GetEntryLine(inID);
				cLine = m_regInfo->GetEntryLine(GetAssociatedCountID(inID));
				minAspSize = inLine->m_nNuSize * cLine->m_nNuCount;
			}
			else minAspSize = aspSize; //0.0001;
			//if(aspLck)minAspSize = aspSize;
			unsigned long count = rows;
			if(m_concernsAreHorizontal)count = cols;
			m_plugID = GetEnclosingAspectID(nID);
			if(colorMode!=1 && lev==2)
				m_plugID = GetEnclosingAspectID(m_plugID);
			outLine = m_regInfo->GetEntryLine(m_plugID);
			outAspSz = outLine->m_nNuSize;
			if(outAspSz<(count * minAspSize))
				nuSize = count * minAspSize;
			else nuSize = outAspSz;
		}	
		else 
		{
			int outID = GetEnclosingAspectID(nID);
			if(colorMode!=1 && lev==2) 
				outID = GetEnclosingAspectID(outID);
			outLine = m_regInfo->GetEntryLine(outID);
			if(m_concernsAreHorizontal)
				maxAspSize = outLine->m_nNuSize / cols;
			else maxAspSize = outLine->m_nNuSize / rows;
			if(aspLck)maxAspSize = aspSize;
			if(aspSize>maxAspSize)nuSize = maxAspSize;
			else nuSize = aspSize;
		}
		cLine = m_regInfo->GetEntryLine(GetAssociatedCountID(nID));
		if(m_concernsAreHorizontal)cLine->m_nNuCount = cols;
		else cLine->m_nNuCount = rows;
		m_pendingCountLoaded = TRUE;
	}//(countIncrs && m_pendingCountLoaded)

	//install request value
	if(!m_pendingCountLoaded)
	{
		line = m_regInfo->GetEntryLine(nID);
		if(!line->m_instigating)line->m_origReqSize = line->m_nNuSize;
	}
	else
	{
		line = m_regInfo->GetEntryLine(m_plugID);
		if(!line->m_instigating)line->m_origReqSize = nuSize;
		else m_abortRequestRect = TRUE;
	}

}


void CMaestro::PrepareForNewMeasure()
{
	unsigned long countChange;
	m_decreaseGiven = FALSE;
	m_pendingSpatialFormatLoaded = FALSE;
	BOOL adjustCount = FALSE;
	if(m_regInfo->IsInitialRequestImpactHorizontal() && m_concernsAreHorizontal)
		adjustCount = TRUE;
	if(!m_regInfo->IsInitialRequestImpactHorizontal() && !m_concernsAreHorizontal)
		adjustCount = TRUE;
	if(adjustCount || !m_regInfo->IsRequestLevelOne())
	{
		if(m_regInfo->IsRequestLevelOne())//cell level
		{
			{
				m_pendingSpatialFormatLoaded = 
					NextStepAutoAdjustCellCount();
			}
		}
		else m_pendingSpatialFormatLoaded = NextStepAutoAdjustCount();
		m_pendingCountLoaded = m_pendingSpatialFormatLoaded;
	}
	m_plugID = InitializeRootID();
}


int CMaestro::InitializeRootID()
{

	int plugID = 99;
	if(m_concernsAreHorizontal)plugID = m_regInfo->GetRootWidthID();
	else plugID = m_regInfo->GetRootHeightID();
	return plugID;
}


void CMaestro::DestroyMaestro()
{
	delete this;
}


void CMaestro::ToggleAxisConcerns()
{
	if(m_concernsAreHorizontal)
	{
		m_concernsAreHorizontal = FALSE;
		m_beginningOfBar = FALSE;
	}
	else 
	{
		m_concernsAreHorizontal = TRUE;
		m_beginningOfBar = TRUE;
	}
	m_regInfo->ChangeAxisMode(m_concernsAreHorizontal);
}


void CMaestro::ToggleRequestSize()
{
	if(m_aTimeToGrow)m_aTimeToGrow = FALSE;
	else m_aTimeToGrow = TRUE;
}


BOOL CMaestro::TestForAnsweredRequest()
{
	//if(m_changeYetNeeded==0)return TRUE;
	BOOL colorMode = m_regInfo->GetColorMode();
	BOOL intermediateCountWasAchieved = FALSE;
	BOOL countIncrs = m_desiredCountIsIncrease;
	BOOL idealCountWasAchieved = FALSE;
	UINT count;
	UINT cols = m_regInfo->GetCurrentColumnCount();
	UINT rows = m_regInfo->GetCurrentRowCount();
	int outID,nID = InitializeRootID();
	outID = GetEnclosingAspectID(nID);
	CRegAspect *outLine,*line;
	line = m_regInfo->GetEntryLine(nID);

	outID = GetEnclosingAspectID(nID);
	if(colorMode!=1 && (outID==2 || outID==9))outID = 
		GetEnclosingAspectID(outID);
	outLine = m_regInfo->GetEntryLine(outID);
	if(!countIncrs)
	{
		if(m_decreaseGiven)intermediateCountWasAchieved = TRUE;
		else
		{
			if(line->m_nNuSize==outLine->m_nNuSize)
				intermediateCountWasAchieved = TRUE;
			else 
			{
				intermediateCountWasAchieved = FALSE;
				ReloadPreviousValues();
			}
		}
	}
	if(countIncrs)
	{
		if(m_concernsAreHorizontal)count = cols;
		else count = rows;
		BOOL normalFit = FALSE;
		float dif = 1.0;
		if((line->m_nNuSize * count)>=outLine->m_nNuSize)
			dif = (line->m_nNuSize * count) - outLine->m_nNuSize;
		else normalFit = TRUE;
		if(dif<0.00001 || normalFit)
			intermediateCountWasAchieved = TRUE;
		else 
		{
			intermediateCountWasAchieved = FALSE;
			ReloadPreviousValues();
		}
	}
	if(intermediateCountWasAchieved)
	{
		m_storeRegistryValues = TRUE;
		if(m_failureCount>0 && m_pendingCountLoaded)
			m_failureCount = 0;
	}
	else m_storeRegistryValues = FALSE;
	if(!m_pendingCountLoaded || !m_storeRegistryValues)m_failureCount++;
	if(m_changeYetNeeded==0)idealCountWasAchieved = TRUE;

	return idealCountWasAchieved;
}


void CMaestro::DetermineUltimateCountChange()
{
	int colorMode = m_regInfo->GetColorMode();
	int index = m_regInfo->GetRequestIndex();
	UINT totalPages = m_regInfo->GetTotalPages();
	UINT cols = m_regInfo->GetCurrentColumnCount();
	m_colBuf = cols;
	UINT rows = m_regInfo->GetCurrentRowCount();
	m_rowBuf = rows;
	UINT nuCount = m_ultimateCountDesired;
	UINT reduct;
	UINT addAmt;

	if(!m_desiredCountIsIncrease)
	{
		if((index==14 && colorMode==1)||(index==13 && colorMode!=1))
		{
			UINT c,shrinkBy;
			c = (cols * rows * totalPages);
			shrinkBy = c - nuCount;
			reduct = 0;
			if(c>=nuCount)
			{
				for(;totalPages<(shrinkBy+1); )
				{
					shrinkBy -= totalPages;
					reduct++;
				}
			}
		}
		else reduct = (cols * rows) - nuCount;
		if(index==5)reduct = cols - nuCount;
		if(index==12)reduct = rows - nuCount;
	}
	else 
	{
		UINT c;
		if((index==14 && colorMode==1)||(index==13 && colorMode!=1))
			c = cols * rows * totalPages;
		else c = cols * rows;
		if(nuCount>=c)
		{
			if((index==14 && colorMode==1)||(index==13 && colorMode!=1))
			{
				UINT growBy = nuCount - c;
				addAmt = 0;
				for(;totalPages<=growBy;)
				{
					growBy -= totalPages;
					addAmt++;
				}
			}
			else addAmt = nuCount - (cols * rows);
		}
		else addAmt = 0;
		if(index==5)addAmt = nuCount - cols;
		if(index==12)addAmt = nuCount - rows;
	}
	if(!m_desiredCountIsIncrease)m_ultimateCountChange = reduct;
	else m_ultimateCountChange = addAmt;
	m_changeYetNeeded = m_ultimateCountChange;
	m_changeYetNeededBuf = m_changeYetNeeded;
}


BOOL CMaestro::NextStepAutoAdjustCellCount()
{
	BOOL nuAmt = FALSE;
	UINT cols = m_regInfo->GetCurrentColumnCount();
	m_colBuf = cols;
	UINT rows = m_regInfo->GetCurrentRowCount();
	m_rowBuf = rows;
	m_changeYetNeededBuf = m_changeYetNeeded;

	if(m_desiredCountIsIncrease)
	{
		if(m_concernsAreHorizontal)
		{
			if(m_changeYetNeeded>0)
			{
				cols = cols + 1;
				nuAmt =TRUE;
				m_changeYetNeeded--;
			}
		}
		else if(m_changeYetNeeded>0)
		{
			rows = rows + 1;
			nuAmt = TRUE;
			m_changeYetNeeded--;
		}			
	}
	else
	{
		if(m_concernsAreHorizontal)
		{
			if(cols>1 && m_changeYetNeeded>0)
			{
				cols = cols - 1;
				nuAmt = TRUE;
				m_changeYetNeeded--;
			}
		}
		else if(rows>1 && m_changeYetNeeded>0)
		{
			rows = rows - 1;
			nuAmt = TRUE;
			m_changeYetNeeded--;
		}
	}


	if(nuAmt)
	{
		//if(m_changeYetNeeded>0)m_changeYetNeeded--;
		m_regInfo->SetCurrentRowCount(rows);
		m_regInfo->SetCurrentColumnCount(cols);
	}
	return nuAmt;
}


BOOL CMaestro::NextStepAutoAdjustCount()
{
	BOOL nuAmt = FALSE;
	UINT cols = m_regInfo->GetCurrentColumnCount();
	m_colBuf = cols;
	UINT rows = m_regInfo->GetCurrentRowCount();
	m_rowBuf = rows;
	m_changeYetNeededBuf = m_changeYetNeeded;
	unsigned long reduct,addAmt;

	BOOL nuFormat = TRUE;
	if(m_desiredCountIsIncrease)
	{
		addAmt = m_changeYetNeeded;
		if(addAmt==0)nuFormat = FALSE;
		if(addAmt>0)
		{
			if(m_concernsAreHorizontal)
			{
				cols = cols + 1;
				if(addAmt>=rows)addAmt = addAmt - rows;
				else addAmt = 0;
			}
			else
			{
				rows = rows + 1;
				if(addAmt>=cols)addAmt = addAmt - cols;
				else addAmt = 0;
			}
		}
		m_changeYetNeeded = addAmt;
	}
	else
	{
		reduct = m_changeYetNeeded;
		if(reduct==0)nuFormat = FALSE;
		if(reduct>0)
		{
			if(m_concernsAreHorizontal)
			{
				if(reduct>=rows && cols>1)
				{
					reduct = reduct - rows;
					cols = cols - 1;
				}
				else nuFormat = FALSE;
			}
			else
			{
				if(reduct>=cols && rows>1)
				{
					reduct = reduct - cols;
					rows = rows - 1;
				}
				else nuFormat = FALSE;
			}
		}

		//enable auto-decrease format for release 1.0
		m_changeYetNeeded = reduct;
		//nuFormat = FALSE;

	}
	if(nuFormat)
	{
		//if(m_changeYetNeeded>0)m_changeYetNeeded = m_changeYetNeeded - 1;
		m_regInfo->SetCurrentRowCount(rows);
		m_regInfo->SetCurrentColumnCount(cols);
	}
	return nuFormat;
}


int CMaestro::GetEnclosingAspectID(int id)
{
	int outID;
	if(id==0) outID = 1;
	if(id==1) outID = 2;
	if(id==2) outID = 17;
	if(id==3) outID = 6;
	if(id==4) outID = 6;
	if(id==5) outID = 1;
	if(id==6) outID = 6;
	if(id==7) outID = 8;
	if(id==8) outID = 9;
	if(id==9) outID = 18;
	if(id==10) outID = 16;
	if(id==11) outID = 16;
	if(id==12) outID = 8;
	if(id==16) outID = 16;
	if(id==17) outID = 6;
	if(id==18) outID = 16;
	if(id==19) outID = 2;
	if(id==20) outID = 8;
	if(id==21) outID = 21;
	if(id==22) outID = 22;
	return outID;
}


int CMaestro::GetEnclosedAspectID(int id)
{
	int inID;
	if(id==0) inID = 0;
	if(id==1) inID = 0;
	if(id==2) inID = 1;
	if(id==3) inID = 17;
	if(id==4) inID = 17;
	if(id==5) inID = 0;
	if(id==6) inID = 17;
	if(id==7) inID = 7;
	if(id==8) inID = 7;
	if(id==9) inID = 8;
	if(id==10) inID = 18;
	if(id==11) inID = 18;
	if(id==12) inID = 7;
	if(id==16) inID = 18;
	if(id==17) inID = 2;
	if(id==18) inID = 9;
	if(id==19) inID = 0;
	if(id==20) inID = 7;
	if(id==21) inID = 1;
	if(id==22) inID = 8;
	return inID;
}


int CMaestro::GetAssociatedCountID(int id)
{
	int cID = 99;
	if(id==0)cID = 5; 
	if(id==1)cID = 19;
	if(id==2)cID = 21;
	if(id==7)cID = 12;
	if(id==8)cID = 20;
	if(id==9)cID = 22;

	return cID;
}


void CMaestro::SendPlugID()
{
	m_regInfo->SendPlugID(m_plugID);
}

void CMaestro::ReloadPreviousValues()
{
	m_changeYetNeeded = m_changeYetNeededBuf;
	m_regInfo->SetCurrentColumnCount(m_colBuf);
	m_regInfo->SetCurrentRowCount(m_rowBuf);
}
