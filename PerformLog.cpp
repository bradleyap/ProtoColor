/////////////////////////////////////////////////////////////////////////////
// CPerformLog
#include "StdAfx.h"

IMPLEMENT_DYNCREATE(CPerformLog, CCmdTarget)

CPerformLog::CPerformLog()
{
	gaugeByInt = TRUE;
	gaugeByDouble = FALSE;
}

CPerformLog::~CPerformLog()
{
}

void CPerformLog::InitializeLog(BOOL byInt,UINT iGoal,
								UINT iCurrent,double dGoal,double dCurrent)
{
	iBest = iCurrent;
	iIdeal = iGoal;
	iStart = iCurrent;
	dBest = dCurrent;
	dIdeal = dGoal;
	dStart = dCurrent;
	dBestInVal = dCurrent;
	iBestInVal = iCurrent;
	if(byInt)
	{
		gaugeByInt = TRUE;
		gaugeByDouble = FALSE;
	}
	else 
	{
		gaugeByDouble = TRUE;
		gaugeByInt = FALSE;
	}
}

void CPerformLog::RecordNewInputVariables(UINT ival,double dval)
{
	dNuInVal = dval;
	iNuInVal = ival;
}

BOOL CPerformLog::EnterNewResults(UINT ival,double dval)
{
	BOOL swap = FALSE;
	if(gaugeByDouble)
	{
		if(dIdeal>=dStart)
		{
			if(dval<=dIdeal && dval>dBest)swap = TRUE;
		}
		else 
		{
			if(dval>=dIdeal && dval<dBest)swap = TRUE;
		}
		if(dval==dBest)
		{
			if(iIdeal>=iStart)
			{
				if(ival <=iIdeal && ival>iBest)swap = TRUE;
			}
			else 
			{
				if(ival>=iIdeal && ival<iBest)swap = TRUE;
			}
		}
	}
	if(gaugeByInt)
	{
		if(iIdeal>=iStart)
		{
			if(ival <=iIdeal && ival>iBest)swap = TRUE;
		}
		else 
		{
			if(ival>=iIdeal && ival<iBest)swap = TRUE;
		}
		if(ival==iBest)
		{
			if(dIdeal>=dStart)
			{
				if(dval<=dIdeal && dval>dBest)swap = TRUE;
			}
			else 
			{
				if(dval>=dIdeal && dval<dBest)swap = TRUE;
			}
		}
	}
	if(swap)
	{
		dBest = dval;
		iBest = ival;
		iBestInVal = iNuInVal;
		dBestInVal = dNuInVal;
	}
	return swap;
}

UINT CPerformLog::GetIntOut()
{
	return iBest;
}

UINT CPerformLog::GetIntIn()
{
	return iBestInVal;
}

double CPerformLog::GetPrecOut()
{
	return dBest;
}

double CPerformLog::GetPrecIn()
{
	return dBestInVal;
}

BEGIN_MESSAGE_MAP(CPerformLog, CCmdTarget)
	//{{AFX_MSG_MAP(CPerformLog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
