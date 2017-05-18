//CCellCount 
//Implementation
#include "StdAfx.h"
#define HONOR_REQUEST_ONLY 0
#define PRESERVE_LAYOUT 1

CCellCount::CCellCount()
{
	m_bottomedOut = FALSE;
	m_raiseCount = TRUE;
}

CCellCount::~CCellCount()
{

}

void CCellCount::InitializeCellCount(UINT count,UINT iRequestVal,
									 BOOL whoIsKing,BOOL kingIncrs,
									 BOOL cLock)
{
	m_curCount = count;
	m_origCount = count;
	m_curHighCount = count;
	m_curLowCount = count;
	m_bottomedOut = FALSE;
	m_toppedOut = FALSE;
	if(m_curCount==1)m_bottomedOut = TRUE;
	m_idealCount = iRequestVal;
	m_increase = kingIncrs;
	m_countIsKing = TRUE;
	if(whoIsKing==1)
	{
		m_countIsKing = FALSE;
		m_increase = kingIncrs;
	}
	if(whoIsKing==2)
	{
		m_curCount = m_idealCount;
	}
	if(whoIsKing==3)
	{
		m_countIsKing = FALSE;
		m_increase = !kingIncrs;
	}
	m_countLock = cLock;
	m_increaseRelaxes = !m_increase;
}

extern CCalc scratchPad;

//evaluates/modifies initial request
UINT CCellCount::GetPheasibleCount(int index,CProgressMgr * mgr)
{
	CRegAspect* cLine = ::scratchPad.m_reg[mgr->GetCountID()];
	UINT pheasibleCount = m_curCount;
	int flag = 0;
	if(cLine->m_origReqCount>256)
	{flag = 15;mgr->SetFlag(flag);pheasibleCount = 256;}
	if(cLine->m_origReqCount<=0)
	{flag = 15;mgr->SetFlag(flag);pheasibleCount = 1;}
	if(cLine->m_locked)
	{
		flag = 12;
		mgr->SetFlag(flag);
		pheasibleCount = cLine->m_nNuSize;
	}
	if(pheasibleCount!=m_curCount)SetNewCount(pheasibleCount,mgr);

	return pheasibleCount;
}

BOOL CCellCount::RelaxKingCountRequest(CProgressMgr * mgr)
{
	BOOL contin = FALSE;
	BOOL flag = 0;
	if(m_countLock)
	{
		flag = 12;
		mgr->SetFlag(flag);
		return FALSE;
	}
	if(m_curCount!=m_origCount)
	{
		if(m_increaseRelaxes)m_curCount++;
		else m_curCount--;
		SetNewCount(m_curCount,mgr);
		contin = TRUE;
	}

	return contin;
}

BOOL CCellCount::ModifyQueenCount(CProgressMgr * mgr)
{
	BOOL contin = TRUE;
	BOOL countChange = FALSE;
	int flag = 0;
	if(m_countLock)
	{
		flag = 12;
		mgr->SetFlag(flag);
		return FALSE;
	}
	BOOL greenLight = mgr->IsQueenAuthorizedToAdapt();
	if(!greenLight)return FALSE;


	int intent = mgr->GetCalculationIntent();

	if(intent==HONOR_REQUEST_ONLY)contin = 
		AdvanceToNextRequestOnlyStep(mgr);
	if(intent==PRESERVE_LAYOUT)contin = 
		AdvanceToNextPreserveLayoutStep(mgr);
	
	return contin;
}

BOOL CCellCount::AdjustJackCount(CProgressMgr * mgr)
{
	BOOL cando = FALSE;
	int flag = 0;
	if(m_countLock)
	{
		flag = 12; 
		mgr->SetFlag(flag);
		return FALSE;
	}
	UINT range = mgr->GetRange();
	double freq = mgr->GetFrequency();
	double needed;
	if(freq!=0)needed = (range / freq) + 1;
	else return FALSE;
	if(range==0)return FALSE;
	if(needed==(UINT)needed && needed>=1)
	{
		SetNewCount((UINT)needed,mgr);
		cando = TRUE;
	}
	//else burden is on Queen to flag problem

	return cando;
}

BOOL CCellCount::AdvanceToNextRequestOnlyStep(CProgressMgr * mgr)
{
	BOOL contin = TRUE;
	BOOL countChange = FALSE;
	UINT nuCount = m_curCount;
	int flag = 0;

	if(m_raiseCount || m_bottomedOut)
	{
		if(m_curHighCount==256)m_toppedOut = TRUE;
		else
		{
			m_curHighCount++;
			nuCount = m_curHighCount;
			countChange = TRUE;
		}
	}
	if(!m_raiseCount || !countChange)
	{
		if(m_curLowCount==1)m_bottomedOut = TRUE;
		else
		{
			if(m_curLowCount>1)
			{
				m_curLowCount--;
				nuCount = m_curLowCount;
				countChange = TRUE;
			}
		}
	}
	if(m_raiseCount)m_raiseCount = FALSE;
	else m_raiseCount = TRUE;

	if(!countChange)
	{
		if(m_toppedOut && m_bottomedOut)
		{
			flag = 0;
			mgr->QueenIsExhausted();
			contin = FALSE;
		}
		if(flag!=0)mgr->SetFlag(flag);
	}
	else SetNewCount(nuCount,mgr);

	return contin;
}

BOOL CCellCount::AdvanceToNextPreserveLayoutStep(CProgressMgr * mgr)
{
	BOOL contin = FALSE;
	double curFreq = mgr->GetFrequency();
	double nuFreq;
	UINT curRange = mgr->GetRange();
	UINT nuCount = m_curCount;
	UINT offset = 0;
	BOOL freqLock = mgr->IsFrequencyLocked();
	BOOL raiseCountOnly = FALSE;
	BOOL lowerCountOnly = FALSE;

	int i;
	for(i=0;i<10000;i++)
	{
		if(offset>m_origCount)raiseCountOnly = TRUE;
		if(curRange==0 && m_origCount==1)break;
		if(curRange==0 && m_origCount>1)lowerCountOnly = TRUE;
		if(curRange>0 && (offset+1)>=m_origCount)raiseCountOnly = TRUE;
		if(raiseCountOnly && lowerCountOnly)break;
		if((i%2==0 && !raiseCountOnly)||lowerCountOnly)
			nuCount = m_origCount - offset;	
		else nuCount = m_origCount + offset;
		if(!freqLock)
		{
			if(nuCount>1)nuFreq = curRange / (nuCount - 1);
			else nuFreq = curRange;
		}
		if(!freqLock && (nuFreq==(UINT)nuFreq))
		{
			contin = TRUE;
			break;
		}
		if(freqLock && curFreq==(curRange /(nuCount-1)))
		{
			contin = TRUE;
			break;
		}
		if(i%2==0)offset++;
	}
	if(nuCount!=m_curCount && contin)SetNewCount(nuCount,mgr);
	else mgr->QueenIsExhausted();

	return contin;
}

BOOL CCellCount::SetNewCount(UINT nuCount,CProgressMgr * mgr)
{
	BOOL cando = TRUE;
	int flag = 0;
	if(!m_countLock){m_curCount = nuCount;cando = TRUE;}
	else {flag = 12;mgr->SetFlag(flag);}
	if(cando)mgr->SetNewCount(nuCount);

	return cando;
}

void CCellCount::ResetCount(CProgressMgr* mgr)
{
	m_curCount = m_origCount;
	mgr->SetNewCount(m_curCount);
	
}
