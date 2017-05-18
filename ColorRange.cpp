/////////////////////////////////////////////////////////////////////
//CColorRange.cpp 
//implementation of CColorRange
#include "StdAfx.h"
#define HONOR_REQUEST_ONLY 0
#define PRESERVE_LAYOUT 1
#define HONOR_RANGE_ASPECT 2

CColorRange::CColorRange()
{
	m_topsMove = FALSE;
	m_rangeReqOffset = TRUE;
	m_startChangeMoreDrastic = TRUE;
}

CColorRange::~CColorRange()
{

}

extern CCalc scratchPad;

void CColorRange::InitializeColorRange(UINT range,UINT iRequestBotVal,
		UINT iRequestTopVal,int whoIsKing,BOOL kingIncrs,UINT botColor,
		UINT topColor,BOOL startClrLock,BOOL endClrLock,CProgressMgr * mgr)
{
	UINT eChange,sChange;
	m_startColorIsFree = FALSE;
	m_curRange = range;
	m_curStartColor = botColor;
	m_curEndColor = topColor;
	m_origStartColor = botColor;
	m_origEndColor = topColor;
	m_startLock = startClrLock;
	m_endLock = endClrLock;
	m_idealEndColor = iRequestTopVal;
	m_idealStartColor = iRequestBotVal;
	if(topColor>=botColor)m_normal = TRUE;
	else m_normal = FALSE;
	if(iRequestBotVal>botColor && iRequestTopVal>topColor)
		m_rangeReqOffset = TRUE;
	if(iRequestBotVal<botColor && iRequestTopVal<topColor)
		m_rangeReqOffset = TRUE;
	if(whoIsKing==1)
	{
		if(!startClrLock)SetNewStartColor(iRequestBotVal,mgr);
		if(!endClrLock)SetNewEndColor(iRequestTopVal,mgr);
	}
	if(m_curStartColor>=m_origStartColor)sChange = 
		m_curStartColor - m_origStartColor;
	else sChange = m_origStartColor - m_curStartColor;
	if(m_curEndColor>=m_origEndColor)eChange = 
		m_curEndColor - m_origEndColor;
	else eChange = m_origEndColor - m_curEndColor;
	if(sChange>=eChange)m_startChangeMoreDrastic = TRUE;
	else m_startChangeMoreDrastic = FALSE;
	if(sChange>0 && eChange>0)m_singleRequest = FALSE;
	else
	{
		m_singleRequest = TRUE;
		if(sChange==0)m_startColorIsFree = TRUE;
		else m_startColorIsFree = FALSE;
	}
	m_startLock = startClrLock;
	m_endLock = endClrLock;
	m_rangeIsKing = TRUE;
	m_increase = kingIncrs;
	UINT maxInc,maxDec;
	maxInc = GetMaxRangeIncrease();
	maxDec = GetMaxRangeDecrease();
	if(whoIsKing==2)//count is king...m_increase important if freqLck
	{
		m_rangeIsKing = FALSE;
		m_increase = kingIncrs;
		if(!mgr->IsFrequencyLocked())
		{
			double nuC = mgr->GetCount();
			double quo;
			if(nuC>0)quo = m_curRange / (nuC - 1);
			if((quo - (UINT)quo)>0.5)m_increase = TRUE;
			else m_increase = FALSE;

			if((mgr->GetFrequency()*(quo - (UINT)quo))>=maxInc)
				m_increase = FALSE;
			if((mgr->GetFrequency()*(1 - (quo - (UINT)quo)))>=maxDec)
				m_increase = TRUE;
		}
	}
	if(whoIsKing==3)//frequency is king
	{
		m_rangeIsKing = FALSE;
		m_increase = kingIncrs;
		double nuF = mgr->GetFrequency();
		double quo;
		if(nuF!=0)quo = m_curRange / nuF;
		if((quo - (UINT)quo)>0.5)m_increase = TRUE;
		else m_increase = FALSE;

		if((mgr->GetCount()*(quo - (UINT)quo))>=maxInc)
			m_increase = FALSE;
		if((mgr->GetCount()*(1 - (quo - (UINT)quo)))>=maxDec)
			m_increase = TRUE;
	}
}

UINT CColorRange::GetPheasibleRange(int index,CProgressMgr * mgr)
{
	UINT startColor,endColor;
	int flag = 0;
	CRegAspect* sLine = ::scratchPad.m_reg[mgr->GetStartID()];
	CRegAspect* eLine = ::scratchPad.m_reg[mgr->GetEndID()];
	startColor = m_curStartColor;
	endColor = m_curEndColor;
	if(startColor>255){startColor = 255;flag = 15;}
	if(startColor<0){startColor = 1;flag = 15;}
	if(endColor>255){endColor = 255;flag = 15;}
	if(endColor<0){endColor = 1;flag = 15;}
	if(sLine->m_locked && (startColor!=sLine->m_nNuCount))
	{
		if(sLine->m_instigating)
		{
			int lockFlag = 18;
			mgr->SetFlag(lockFlag);
		}
		startColor = sLine->m_nNuCount;
	}
	if(eLine->m_locked && (endColor!=eLine->m_nNuCount))
	{
		if(eLine->m_instigating)
		{
			int lockFlag = 18;
			mgr->SetFlag(lockFlag);
		}
		endColor = eLine->m_nNuCount;
	}
	if(startColor!=m_curStartColor)SetNewStartColor(startColor,mgr);
	if(endColor!=m_curEndColor)SetNewEndColor(endColor,mgr);
	UINT pheasibleRange = m_curRange;
	if(flag!=0)mgr->SetFlag(flag);

	return pheasibleRange;
}

BOOL CColorRange::RelaxKingRangeRequest(CProgressMgr * mgr)
{
	BOOL contin = FALSE;

	int approach = mgr->GetCalculationIntent();

	if(approach==HONOR_REQUEST_ONLY)
		contin = AdvanceToNextRequestOnlyStep(mgr);
	if(approach==PRESERVE_LAYOUT)
		contin = FindPreserveLayoutValues(mgr);
	if(approach==HONOR_RANGE_ASPECT)
		contin = AdvanceToNextRangeAspectStep(mgr);

	return contin;
}

BOOL CColorRange::ModifyQueenRange(CProgressMgr * mgr)
{
	BOOL move = FALSE,tortoiseAtImpass=FALSE,hareAtImpass=FALSE;
	BOOL moveHare=FALSE;
	BOOL normal = TRUE;
	BOOL tortoiseMoves = m_topsMove;
	UINT tortoise = m_curEndColor;//last drawn (not always high value)
	UINT hare = m_curStartColor;//first drawn (not always low value)
	int flag  = 0;

	if(!::scratchPad.m_rangeInvolve)
	{
		flag = 19;
		mgr->SetFlag(flag);
		return FALSE;
	}
	if(m_startLock && m_endLock)
	{
		flag = 18;
		mgr->SetFlag(flag);
		return FALSE;
	}
	
	if(tortoise>=hare)normal = TRUE;
	else normal = FALSE;

	if(tortoiseMoves)
	{
		moveHare = FALSE;
		if(normal)
		{
			if(m_increase && tortoise==255)moveHare = TRUE;
		}
		else if(m_increase && tortoise==0)moveHare = TRUE;
		if(m_endLock)moveHare = TRUE;
	}
	else
	{
		moveHare = TRUE;
		if(normal)
		{
			if(m_increase && hare==0)moveHare = FALSE;
		}
		else if(m_increase && hare==255)moveHare = FALSE;
		if(m_startLock)moveHare = FALSE;
	}
	if(!moveHare)//try to move tortoise
	{
		if(!m_endLock)
		{
			if((m_increase && normal) || (!m_increase && !normal))
			{
				if((normal && tortoise<255)||(!normal && tortoise<hare))tortoise++;
				else tortoiseAtImpass = TRUE;
			}
			else 
			{
				if((normal && tortoise>hare)||(!normal && tortoise>0))tortoise--;
				else tortoiseAtImpass = TRUE;
			}
			if(tortoise!=m_curEndColor)
			{
				SetNewEndColor(tortoise,mgr);
				move = TRUE;
			}
		}
	}
	if(!move)//try to move hare
	{
		if(!m_startLock)
		{
			if((m_increase && normal) || (!m_increase && !normal))
			{
				if((normal && hare>0)||(!normal && hare>tortoise))hare--;
				else hareAtImpass = TRUE;
			}
			else 
			{
				if((normal && hare<tortoise)||(!normal && hare<0))hare++;
				else hareAtImpass = TRUE;
			}
			if(hare!=m_curStartColor)
			{
				SetNewStartColor(hare,mgr);
				move = TRUE;
			}
		}
	}
	//set pertinant flags
	if(m_increase && (m_endLock || m_startLock))flag = 18;
	if(!m_increase && m_endLock && m_startLock)flag = 18;
	if(!move)
	{
		if(flag!=0)mgr->SetFlag(flag);
		mgr->QueenIsExhausted();
	}
	if(m_topsMove)m_topsMove = FALSE;
	else m_topsMove = TRUE;

	return move;
}

BOOL CColorRange::AdjustJackRange(CProgressMgr * mgr)
{
	BOOL cando = FALSE,toppedOut=FALSE;
	int flag = 0;
	UINT needed = mgr->GetCount() * mgr->GetFrequency();
	UINT dif,curTop=m_curEndColor,curBot=m_curStartColor;
	if(needed==m_curRange)return cando;
	if(m_endLock && m_startLock){flag=18;mgr->SetFlag(flag);}
	if(needed>=m_curRange)
	{
		dif = needed - m_curRange;
		if(!m_endLock)
		{
			if(curTop!=255)
			{
				if(dif>=(255 - curTop))
				{
					dif = dif - (255 - curTop);
					curTop = 255;
				}
				else
				{
					curTop += dif;
					dif = 0;
				}
			}
			else toppedOut = TRUE;
		}
		if(!m_startLock && dif!=0)
		{
			if(curBot!=0)
			{
				if(dif>=curBot)
				{
					dif = dif - curBot;
					curBot = 0;
				}
				else
				{
					curBot -= dif;
					dif = 0;
				}
			}
			else m_bottomedOut = TRUE;
		}
	}
	if(m_curRange>=needed)
	{
		dif = m_curRange - needed;
		if(!m_endLock)
		{
			curTop -= dif;
			dif = 0;
		}
		if(!m_startLock)
		{
			curBot += dif;
			dif = 0;
		}
	}

	if(dif!=0)cando = FALSE;
	else 
	{
		m_curRange = needed;
		m_curEndColor = curTop;
		m_curStartColor = curBot;
		SetNewStartColor(m_curStartColor,mgr);
		SetNewEndColor(m_curEndColor,mgr);
		cando = TRUE;
	}

	return cando;
}

BOOL CColorRange::AdvanceToNextRequestOnlyStep(CProgressMgr * mgr)
{
	BOOL advance = FALSE;
	BOOL altered = FALSE;
	BOOL recycle = FALSE;
	BOOL queenExhausted = mgr->IsQueenExhausted();
	BOOL endCycle = TRUE;
	UINT nuColor;
	if(m_startChangeMoreDrastic)
	{
		if(m_curStartColor>m_origStartColor)
		{
			nuColor = m_curStartColor - 1;
			altered = SetNewStartColor(nuColor,mgr);
		}
		if(m_curStartColor<m_origStartColor)
		{
			nuColor = m_curStartColor + 1;
			altered = SetNewStartColor(nuColor,mgr);
		}
	}
	if(!m_startChangeMoreDrastic || !altered)
	{
		if(m_curEndColor>m_origEndColor)
		{
			nuColor = m_curEndColor - 1;
			altered = SetNewEndColor(nuColor,mgr);
		}
		if(m_curEndColor<m_origEndColor)
		{
			nuColor = m_curEndColor + 1;
			altered = SetNewEndColor(nuColor,mgr);
		}
	}
	if(altered)endCycle = FALSE;
	else
	{
		m_curEndColor = m_idealEndColor;
		nuColor = m_curEndColor;
		SetNewEndColor(nuColor,mgr);
	}
	if(recycle && !queenExhausted)advance = TRUE;
	if(!endCycle)advance = TRUE;

	return advance;
}

BOOL CColorRange::FindPreserveLayoutValues(CProgressMgr * mgr)
{
	BOOL cando = FALSE;
	BOOL freqLock = mgr->IsFrequencyLocked();
	BOOL qExhausted = mgr->IsQueenExhausted();
	BOOL atop=FALSE,atBot=FALSE;
	BOOL startColorMoves=((m_idealStartColor==m_origStartColor)||qExhausted);
	BOOL endColorMoves=((m_idealEndColor==m_origEndColor)||qExhausted);
	UINT minRange,maxRange;
	UINT nuStartColor=m_curStartColor,nuEndColor=m_curEndColor;
	UINT nuRange = mgr->GetRange();
	UINT offSet = 0;
	UINT curCount = mgr->GetCount();
	UINT testVal;
	double curFreq = mgr->GetFrequency();
	if(!freqLock)testVal = (UINT)curFreq;
	else testVal = curCount;

	//establish range of valid ranges
	if(m_startLock && m_endLock)
	{
		minRange = nuRange;
		maxRange = nuRange;
	}
	else
	{
		minRange = nuRange;
		maxRange = nuRange;
		if(!m_startLock && startColorMoves)
		{
			maxRange += m_curStartColor;
			minRange = 0;
		}
		if(!m_endLock && endColorMoves)
		{
			maxRange += (255 - m_curEndColor);
			minRange = 0;
		}
	}
	CRange validRange;
	validRange.InitializeRange(minRange,maxRange);
	
	//find valid range
	int i;
	for(i=0;i<1000;i++)
	{
		if(atBot && atop)break;
		if(i%2==0)
		{
			if(freqLock)testVal = curCount + offSet;
			else testVal = curFreq + offSet;
		}
		else 
		{
			if(freqLock)testVal = curCount - offSet;
			else testVal = curFreq - offSet;
		}
		if((freqLock && curCount<=offSet)||(!freqLock && curFreq<=offSet))
			{atBot=TRUE;continue;}
		if(testVal>256){atop = TRUE;continue;}
		if(testVal<2){atBot = TRUE;continue;}

		if(freqLock)nuRange = (testVal - 1) * curFreq;
		else nuRange = (curCount - 1) * testVal;

		cando = validRange.DoesValueFallWithinRange(nuRange);
		if(cando)
		{
			if(freqLock)mgr->SendHintToCount(testVal);
			break;
		}

		if(i%2==0)offSet++;
	}

	if(m_singleRequest)
	{
		if(m_startColorIsFree)nuStartColor = nuEndColor - nuRange;
		else nuEndColor = nuStartColor + nuRange;
	}

	mgr->KingHasMadeHisBid();

	BOOL continueCycle = TRUE;
	if(cando)
	{
		SetNewEndColor(nuEndColor,mgr);
		SetNewStartColor(nuStartColor,mgr);
	}
	else if(qExhausted)continueCycle = FALSE;

	return continueCycle;
}

	
BOOL CColorRange::AdvanceToNextRangeAspectStep(CProgressMgr * mgr)
{
	BOOL advance = FALSE;
	return advance;
}

void CColorRange::ResetRange(CProgressMgr * mgr)
{
	m_curStartColor = m_origStartColor;
	m_curEndColor = m_origEndColor;
	if(m_normal)m_curRange = m_curEndColor - m_curStartColor;
	else m_curRange = m_curStartColor - m_curEndColor;
	mgr->SetNewStartColor(m_curStartColor);
	mgr->SetNewEndColor(m_curEndColor);
}

BOOL CColorRange::SetNewStartColor(UINT nuColor,CProgressMgr * mgr)
{
	BOOL cando = FALSE;
	int flag = 0;
	if(nuColor<256 && nuColor>=0)cando = TRUE;
	else {flag = 15;mgr->SetFlag(flag);}
	if(m_startLock){flag = 12;mgr->SetFlag(flag);cando = FALSE;}
	if(cando)
	{
		m_curStartColor = nuColor;
		if(m_curEndColor>=m_curStartColor)m_curRange = m_curEndColor - 
			m_curStartColor;
		else m_curRange = m_curStartColor - m_curEndColor;
		mgr->SetNewStartColor(m_curStartColor);
	}
			
	return cando;
}

BOOL CColorRange::SetNewEndColor(UINT nuColor, CProgressMgr * mgr)
{
	BOOL cando = FALSE;
	int flag = 0;
	if(nuColor<256 && nuColor>=0)cando = TRUE;
	else {flag = 15;mgr->SetFlag(flag);}
	if(m_endLock){flag = 12;mgr->SetFlag(flag);cando = FALSE;}
	if(cando)
	{
		m_curEndColor = nuColor;
		if(m_curEndColor>=m_curStartColor)m_curRange = m_curEndColor - 
			m_curStartColor;
		else m_curRange = m_curStartColor - m_curEndColor;
		mgr->SetNewEndColor(m_curEndColor);
	}
	return FALSE;
}

UINT CColorRange::GetMaxRangeIncrease()
{
	UINT maxInc = 0;
	if(!m_startLock)maxInc = m_curStartColor;
	if(!m_endLock)maxInc += (255 - m_curEndColor);
	return maxInc;
}

UINT CColorRange::GetMaxRangeDecrease()
{
	UINT maxDec = 0;
	if(!m_startLock || !m_endLock)
	{
		if(m_curEndColor>=m_curStartColor)maxDec = m_curEndColor - 
			m_curStartColor;
		else maxDec = m_curStartColor - m_curEndColor;
	}
	return maxDec;
}

UINT CColorRange::GetOriginalRange()
{
	UINT oRange;
	if(m_origStartColor>=m_origEndColor)
		oRange = m_origStartColor - m_origEndColor;
	else oRange = m_origEndColor - m_origStartColor;
	return oRange;
}