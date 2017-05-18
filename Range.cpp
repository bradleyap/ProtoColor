//CRange 
//Implementation
#include "StdAfx.h"

CRange::CRange()
{

}

CRange::~CRange()
{

}

void CRange::InitializeRange(UINT loVal,UINT hiVal)
{
	m_curLowVal = loVal;
	m_curHighVal = hiVal;
	m_curRangeVal = hiVal - loVal;
}

BOOL CRange::DoesValueFallWithinRange(UINT val)
{
	BOOL isContained = FALSE;
	if((val>=m_curLowVal)&&(val<=m_curHighVal))isContained = TRUE;
	return isContained;
}

BOOL CRange::SetNewUpperBound(UINT val)
{
	BOOL cando = FALSE;
	if(m_curLowVal<=val)
	{
		m_curHighVal = val;
		cando = TRUE;
	}
	return cando;
}

BOOL CRange::SetNewLowerBound(UINT val)
{
	BOOL cando = FALSE;
	if(m_curHighVal>=val)
	{
		m_curLowVal = val;
		cando = TRUE;
	}
	return cando;
}
