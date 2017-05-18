//CFrequency
//Implementation

#include "StdAfx.h"

CFrequency::CFrequency()
{
	m_toppedOut = FALSE;
	m_bottomedOut = FALSE;
}

CFrequency::~CFrequency()
{

}

void CFrequency::InitializeFrequency(double freq,double dRequestVal,
									 int whoIsKing,BOOL kingIncrs,
									 BOOL fLock)
{
	m_origFrequency = freq;
	m_curFrequency = freq;
	m_idealFreq = dRequestVal;
	m_fractionalPart = dRequestVal - (UINT)dRequestVal;
	m_oddCall = TRUE;
	m_frequencyIsKing = TRUE;
	m_increase = kingIncrs;
	if(whoIsKing!=3)
	{
		m_frequencyIsKing = FALSE;
		m_increase = !kingIncrs;
	}
	else m_curFrequency = m_idealFreq;
	m_incrsRelaxes = !m_increase;
	m_freqLock = fLock;
}

extern CCalc scratchPad;

double CFrequency::GetPheasibleFrequency(int index,CProgressMgr * mgr)
{

	int flag = 0;
	double pheasibleFreq = m_curFrequency;
	CRegAspect* fLine = ::scratchPad.m_reg[mgr->GetFreqID()];
	if(fLine->m_locked)
	{
		if(fLine->m_instigating){flag = 13;mgr->SetFlag(flag);}
		pheasibleFreq = fLine->m_nNuSize;
	}
	else
	{
		if(m_idealFreq>256 || m_idealFreq<1)
		{
			flag = 13;
			mgr->SetFlag(flag);
		}
		else pheasibleFreq = m_idealFreq;
		if(::scratchPad.m_intSync && pheasibleFreq!=(UINT)pheasibleFreq)
		{
			pheasibleFreq = (UINT)pheasibleFreq;
			flag = 17;
			mgr->SetFlag(flag);
		}
		else
		{
			pheasibleFreq = pheasibleFreq * 100000;
			pheasibleFreq = (UINT)pheasibleFreq;
			pheasibleFreq = pheasibleFreq * 0.1;
			if((pheasibleFreq - (UINT)pheasibleFreq)>0.5)
				pheasibleFreq = ((UINT)pheasibleFreq + 1) * 0.0001;
			else pheasibleFreq = (UINT)pheasibleFreq * 0.0001;

			double origDif = pheasibleFreq - ((UINT)pheasibleFreq);
			double testF = origDif;
			double dif = 0;
			int max = 256,i;
			for(i=0 ;i<max;i++ )
			{
				dif = testF - (UINT)testF;
				if(dif<0.00001)break;
				testF = testF + origDif;
			}
			dif = (UINT)testF - testF;
			if(dif>0.00001)pheasibleFreq = (UINT)pheasibleFreq;
		}
	}
	if(pheasibleFreq!=m_curFrequency)SetNewFrequency(pheasibleFreq,mgr);

		
	return pheasibleFreq;
}


BOOL CFrequency::RelaxKingFrequencyRequest(CProgressMgr * mgr)
{
	BOOL contin=FALSE;
	BOOL toppedOut=FALSE;
	int flag = 0;
	double changeAmt;
	double nuFreq;
	if(m_freqLock)
	{
		flag = 12;
		mgr->SetFlag(flag);
		return FALSE;
	}
	if(m_curFrequency!=m_origFrequency)
	{
		if(mgr->IsThereAHint(mgr->GetQueenID()))
		{

		}
		else
		{
			if(m_incrsRelaxes && !m_toppedOut)
			{			
				if(m_oddCall)changeAmt = 1 - m_fractionalPart;
				if(!m_oddCall)changeAmt = m_fractionalPart;
				if(m_fractionalPart==0)changeAmt = 1;
				nuFreq = m_curFrequency + changeAmt;
				if(nuFreq<=256)
				{
					m_curFrequency = nuFreq;
					contin = TRUE;
				}
				else m_toppedOut = TRUE;
			}
			if(!m_incrsRelaxes && !m_bottomedOut)
			{				
				if(m_oddCall)changeAmt = m_fractionalPart;
				else changeAmt = 1 - m_fractionalPart;
				if(m_curFrequency>(changeAmt + 1))
				{
					m_curFrequency = (changeAmt + 1);
					contin = TRUE;
				}
				else 
				{
					m_curFrequency = 1;
					m_bottomedOut = TRUE;
					contin = TRUE;
				}
			}
		}
	}
	if(m_oddCall)m_oddCall = FALSE;
	else m_oddCall = TRUE;
	if(contin)mgr->SetNewFrequency(m_curFrequency);

	return contin;
}


BOOL CFrequency::ModifyQueenFrequency(CProgressMgr * mgr)
{
	BOOL contin = FALSE;
	AfxMessageBox("CFrequency was not designed to handle a queen's position");
	return contin;
}

BOOL CFrequency::AdjustJackFrequency(CProgressMgr * mgr)
{
	BOOL cando = FALSE;
	int flag = 0;
	double count;
	double needed;
	if(m_freqLock)
	{
		flag = 13;
		mgr->SetFlag(flag);
		return FALSE;
	}
	else
	{
		count = (double)mgr->GetCount();
		if(count>1)needed = mgr->GetRange() / (count-1);
		else needed = mgr->GetRange();
		if(needed==(UINT)needed)cando = TRUE;
		else 
		{
			if(!::scratchPad.m_intSync)cando = TRUE;
			else flag = 17;
		}
		if(cando)
		{
			m_curFrequency = needed;
			mgr->SetNewFrequency(needed);
		}
		else mgr->SetFlag(flag);
	}
	return cando;
}

BOOL CFrequency::SetNewFrequency(double nuFreq, CProgressMgr * mgr)
{
	BOOL cando = TRUE;
	m_curFrequency = nuFreq;
	mgr->SetNewFrequency(nuFreq);
	return cando;
}

void CFrequency::ResetFrequency(CProgressMgr * mgr)
{
	m_curFrequency = m_origFrequency;
	mgr->SetNewFrequency(m_curFrequency);
}
