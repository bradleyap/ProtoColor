////////////////////////////////////////////////////////////////
//Implementation of CProgressMgr


#include "stdafx.h"
#define HONOR_REQUEST_ONLY 0
#define PRESERVE_LAYOUT 1

#define JACK_FAILURE 1
#define QUEEN_FAILURE 2
#define KING_FAILURE 4
#define JACK_COUNT_IN_HOUSE_FAILURE 8

#define STRAIGHT_JACKET 0
#define STODGY 0
#define LOOSEY_GOOSEY 0

CProgressMgr::CProgressMgr()
{
	m_normal = TRUE;
	m_greenLight = FALSE;
	m_kingIsCount = FALSE;
	m_kingIsFrequency = FALSE;
	m_kingIsRange = FALSE;
	m_kingHasMadeBid = FALSE;
	m_queenIsCount = FALSE;
	m_queenIsFrequency = FALSE;
	m_queenIsRange = FALSE;
	m_jackIsCount = FALSE;
	m_jackIsFrequency = FALSE;
	m_jackIsRange = FALSE;
	m_flags = 0;
	m_failureNotices = 0;
	m_kingsMailBox = new CMailBox();
	m_queensMailBox = new CMailBox();
	m_jacksMailBox = new CMailBox();
}

CProgressMgr::~CProgressMgr()
{
	m_kingsMailBox->DestroyMailBox();
	m_queensMailBox->DestroyMailBox();
	m_jacksMailBox->DestroyMailBox();
}

extern CCalc scratchPad;

BOOL CProgressMgr::InitializeProgressMgr(int requestID,double dReqVal,
					UINT iReqVal,UINT range,UINT count,double freq,
					UINT botColor,UINT topColor,BOOL startLock,
					BOOL endLock)			
{
	BOOL goAhead = FALSE;
	kingID = requestID;
	if(requestID<23)
	{
		m_kingIsCount = TRUE;
		m_queenIsRange = TRUE;
		m_jackIsFrequency = TRUE;
	}
	if(requestID>=23 && requestID<=26)
	{
		//the less often used reqest for frequency is done from the 
		//"Cell Aspects Dialog Box".  This establishes two reasons for 
		//preserving the Range: 1)most importantly users are primarily given
		//by Protocolor an ability two hone in on specific color ranges
		//2)secondly the desire will be for most users to get in and out of
		//a dialog box quickly without having unfinished business to tend to
		m_kingIsFrequency = TRUE;
		m_queenIsRange = TRUE;
		m_jackIsCount = TRUE;
	}
	if(requestID>=27)
	{
		m_kingIsRange = TRUE;
		m_queenIsCount = TRUE;
		m_jackIsFrequency = TRUE;
	}
	m_origCount = count;
	m_origRange = range;
	m_origFreq = freq;
	m_origToZero = botColor;
	m_origToTop = topColor;
	m_curCount = count;
	m_curRange = range;
	m_curFreq = freq;
	m_curToZero = botColor;
	m_curToTop = topColor;


	m_idealRange = iReqVal;
	m_idealCount = iReqVal;
	m_idealFreq = dReqVal;

	if(m_kingIsRange)
	{
		m_curRange = m_idealRange;
		if(m_curRange>=m_origRange)m_incr = TRUE;
		else m_incr = FALSE;
	}
	if(m_kingIsCount)
	{
		m_curCount = m_idealCount;
		if(m_curCount>=m_origCount)m_incr = TRUE;
		else m_incr = FALSE;
	}
	if(m_kingIsFrequency)
	{
		m_curFreq = m_idealFreq;
		if(m_curFreq>=m_origFreq)m_incr = FALSE;
		else m_incr = FALSE;
	}

	m_startRangeLock = startLock;
	m_endRangeLock = endLock;

	m_kingHasMail = FALSE;
	m_queenHasMail = FALSE;
	m_jackHasMail = FALSE;

	m_calcIntent = ::scratchPad.m_calcIntent;
	m_kingHasMadeBid = FALSE;
	m_queenIsExhausted = FALSE;

	//m_progBar = new CProgressBar();

	return goAhead;
}

BOOL CProgressMgr::SetNewStartColor(UINT clr)
{
	BOOL doable = FALSE;
	if(!m_startRangeLock)
	{
		m_curToZero = clr;
		doable = TRUE;
		if(m_curToTop>=m_curToZero)m_curRange = m_curToTop - m_curToZero;
		else m_curRange = m_curToZero - m_curToTop;
	}

	return doable;
}

BOOL CProgressMgr::SetNewEndColor(UINT clr)
{
	BOOL doable = FALSE;
	if(!m_endRangeLock)
	{
		m_curToTop = clr;
		doable = TRUE;
		if(m_curToTop>=m_curToZero)m_curRange = m_curToTop - m_curToZero;
		else m_curRange = m_curToZero - m_curToTop;
	}

	return doable;
}

BOOL CProgressMgr::AdjustRange()
{
	BOOL greenLight = TRUE;
	return greenLight;
}

BOOL CProgressMgr::AdjustCount()
{
	BOOL greenLight = TRUE;
	return greenLight;
}

BOOL CProgressMgr::AdjustFrequency()
{
	BOOL greenLight = TRUE;
	return greenLight;
}

void CProgressMgr::SetNewCount(UINT nC)
{
	m_curCount = nC;
}

void CProgressMgr::SetNewFrequency(double nF)
{
	m_curFreq = nF;
}

double CProgressMgr::GetFrequency()
{
	return m_curFreq;
}

BOOL CProgressMgr::IsThereAHint(int subjectID)
{
	BOOL thereIsHint = FALSE;
	if(subjectID==queenID)thereIsHint = m_queenHasMail;
	if(subjectID==kingID)thereIsHint = m_kingHasMail;
	if(subjectID==jackID)thereIsHint = m_jackHasMail;
	return thereIsHint;
}
		

double CProgressMgr::TakeHint(int id)
{
	double hint = 0.0;
	if(id==countID)hint = (double)m_countMail;
	if(id==freqID)hint = m_frequencyMail;
	if(id==rangeID)hint = (double)m_startRangeMail;//startID implied
	if(id==endID)hint = (double)m_endRangeMail;
	if(id==kingID)m_kingHasMail = FALSE;
	if(id==queenID)m_queenHasMail = FALSE;
	if(id==jackID)m_jackHasMail = FALSE;
	return hint;
}

void CProgressMgr::SendHintToCount(UINT suggVal)
{
	if(m_jackIsCount)m_jackHasMail = TRUE;
	if(m_queenIsCount)m_queenHasMail = TRUE;
	if(m_kingIsCount)m_kingHasMail = TRUE;
	m_countMail = suggVal;
}

void CProgressMgr::SendHintToFrequency(double suggVal)
{
	if(m_jackIsFrequency)m_jackHasMail = TRUE;
	if(m_queenIsFrequency)m_queenHasMail = TRUE;
	if(m_kingIsFrequency)m_kingHasMail = TRUE;
	m_frequencyMail = suggVal;
}

void CProgressMgr::SendHintToRange(UINT suggStartVal,UINT suggEndVal)
{
	if(m_jackIsRange)m_jackHasMail = TRUE;
	if(m_queenIsRange)m_queenHasMail = TRUE;
	if(m_kingIsRange)m_kingHasMail = TRUE;
	m_startRangeMail = suggStartVal;
	m_endRangeMail = suggEndVal;
}

BOOL CProgressMgr::DoesTheKingRequestAnIncrease()
{
	return m_incr;
}

BOOL CProgressMgr::ResetKing()
{
	BOOL contin = TRUE;
	m_kingHasMadeBid = FALSE;
	return contin;
}

void CProgressMgr::ResetQueenJackValues()
{
	if(m_jackIsCount || m_queenIsCount)
		m_curCount = m_origCount;
	if(m_jackIsFrequency || m_queenIsFrequency)
		m_curFreq = m_origFreq;
	if(m_jackIsRange || m_queenIsRange)
	{
		m_curToZero = m_origToZero;
		m_curToTop = m_origToTop;
		m_curRange = m_origRange;
	}
}

BOOL CProgressMgr::IsQueenAuthorizedToAdapt()
{
	BOOL go = FALSE;
	if(m_kingHasMadeBid) go = TRUE;
	ResetKing();
	if(m_calcIntent==HONOR_REQUEST_ONLY) go = TRUE;
	return go;
}

BOOL CProgressMgr::IsQueenExhausted()
{
	BOOL endProcess = FALSE;
	if(m_queenIsExhausted)endProcess = TRUE;
	m_queenIsExhausted = FALSE;
	return endProcess;
}

BOOL CProgressMgr::AssessNewValues()
{
	BOOL kosher = FALSE;
	if(m_curFreq!=0 && m_curRange!=0)
	{
		if((m_curCount - 1)==m_curRange / m_curFreq)kosher = TRUE;
	}
	return kosher;
}

void CProgressMgr::NotifyOfConcern(UINT problemCode)
{
	m_failureNotices = m_failureNotices | problemCode;
}

void CProgressMgr::DetermineNatureOfProblem()
{
	int flag = 0;
	if(m_kingIsCount)flag = DecipherCountRequestNotices();
	if(m_kingIsRange)flag = DecipherRangeRequestNotices();
	if(m_kingIsFrequency)flag = DecipherFrequencyRequestNotices();
	if(flag!=0)SetFlag(flag);
}

UINT CProgressMgr::DecipherCountRequestNotices()
{
	UINT flag = 0;
	return flag;
}

UINT CProgressMgr::DecipherRangeRequestNotices()
{
	UINT flag = 0;
	return flag;
}

UINT CProgressMgr::DecipherFrequencyRequestNotices()
{
	UINT flag = 0;
	if(m_failureNotices==(m_failureNotices | 
		JACK_COUNT_IN_HOUSE_FAILURE))
	{
		if(m_failureNotices==(m_failureNotices |
		QUEEN_FAILURE))

		if(m_flags==0)flag = 512;
	}
	return flag;
}

void CProgressMgr::RestoreOriginalValues()
{
	m_curCount = m_origCount;
	m_curFreq = m_origFreq;
	m_curToZero = m_origToZero;
	m_curToTop = m_origToTop;
	m_curRange = m_origRange;
}

void CProgressMgr::SetFlag(int flag)
{
	unsigned long flipBit = 0;
	if(flag==2)flipBit = 1;
	if(flag==12)flipBit = 2;
	if(flag==13)flipBit = 4;
	if(flag==14)flipBit = 8;
	if(flag==15)flipBit = 16;
	if(flag==17)flipBit = 32;
	if(flag==18)flipBit = 64;
	if(flag==19)flipBit = 128;
	if(flag==20)flipBit = 256;
	if(flag==22)flipBit = 512;
	m_flags = m_flags | flipBit;
}

UINT CProgressMgr::GetKingsJourneyLeft()
{
	UINT miles = 0;
	if(m_kingIsCount)
	{
		if(m_origCount>=m_curCount)miles = m_origCount - m_curCount;
		else miles = m_curCount - m_origCount;
	}
	if(m_kingIsRange)
	{
		if(m_origRange>=m_curRange)miles = m_origRange - m_curRange;
		else miles = m_curRange - m_origRange;
	}
	if(m_kingIsFrequency)
	{
		if(m_origFreq>=m_curFreq)miles = m_origFreq - m_curFreq;
		else miles = m_curFreq - m_origFreq;
	}
	return miles;
}

UINT CProgressMgr::GetQueensJourneyLeft()
{
	UINT miles = 0;
	if(m_queenIsCount)
	{
		if(m_origCount>=m_curCount)miles = m_origCount - m_curCount;
		else miles = m_curCount - m_origCount;
	}
	if(m_queenIsRange)
	{
		if(m_origRange>=m_curRange)miles = m_origRange - m_curRange;
		else miles = m_curRange - m_origRange;
	}
	if(m_queenIsFrequency)
	{
		if(m_origFreq>=m_curFreq)miles = m_origFreq - m_curFreq;
		else miles = m_curFreq - m_origFreq;
	}
	return 255 - miles;
}

UINT CProgressMgr::GetKingsProgress()
{
	UINT progress = 0;
	if(m_kingIsCount)
	{
		if(m_idealCount>=m_curCount)progress = m_idealCount - m_curCount;
		else progress = m_curCount - m_idealCount;
	}
	if(m_kingIsRange)
	{
		if(m_idealRange>=m_curRange)progress = m_idealRange - m_curRange;
		else progress = m_curRange - m_idealRange;
	}
	if(m_kingIsFrequency)
	{
		if(m_idealFreq>=m_curFreq)progress = m_idealFreq - m_curFreq;
		else progress = m_curFreq - m_idealFreq;
	}
	return progress;
}

UINT CProgressMgr::GetQueensProgress()
{
	UINT miles;
	if(m_queenIsCount)
	{
		if(m_origCount>=m_curCount)miles = m_idealCount - m_curCount;
		else miles = m_curCount - m_idealCount;
	}
	if(m_queenIsRange)
	{
		if(m_origRange>=m_curRange)miles = m_origRange - m_curRange;
		else miles = m_curRange - m_origRange;
	}
	if(m_queenIsFrequency)miles = m_curFreq;
	return miles;
}
