// ArrowSpin.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "ArrowSpin.h"
//#include "math.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArrowSpin

CArrowSpin::CArrowSpin()
{	

}

CArrowSpin::~CArrowSpin()
{
}


BEGIN_MESSAGE_MAP(CArrowSpin, CSpinButtonCtrl)
	//{{AFX_MSG_MAP(CArrowSpin)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArrowSpin message handlers
/*
changed to inline function:
int CArrowSpin::Rotate( int nDegrees,int nSet, int index, BOOL x)
{
	int coordNew;
	double vcos;		
	double vsin;
	vsin = sin(-1 * (0.017453292 * nDegrees));
	vcos = cos(-1 * (0.017453292 * nDegrees));

	if(x==TRUE)
	{
		coordNew = x_coord[index] * vcos - y_coord[index] * vsin;
	}
	
	if(x==FALSE)
	{
		coordNew = x_coord[index] * vsin + y_coord[index] * vcos;
	}

	return coordNew;

}
*/
////////////////////////////////////////////////////////////////
/*
BOOL CArrowSpin::Load_X_Coords( int nSet)
{
	if(nSet==1 || nSet==5)
	{
		x_coord[0] = 0;
		x_coord[1] = 8;
		x_coord[2] = 4;
		x_coord[3] = 4;
		x_coord[4] = 8;
		x_coord[5] = 0;
		x_coord[6] = -8;
		x_coord[7] = -4;
		x_coord[8] = -4;
		x_coord[9] = -8;
	}

	else if(nSet==2 || nSet==6)
	{
		//x_coord[10] = {22,19,29,29,26,-22,-19,-29,-29,-26};
		x_coord[0] = -21;//29
		x_coord[1] = -18;
		x_coord[2] = -30;
		x_coord[3] = -30;
		x_coord[4] = -27;	//to 27
		x_coord[5] = 21;	//to-21
		x_coord[6] = 18;
		x_coord[7] = 30;
		x_coord[8] = 30;
		x_coord[9] = 27;//28

	}

	else if(nSet==3 || nSet==7)
	{
		//x_coord[10] = {35,35,42,35,35,-35,-35,-42,-35,-35};
		x_coord[0] = 35;
		x_coord[1] = 42;
		x_coord[2] = 35;
		x_coord[3] = 35;
		x_coord[4] = -35;
		x_coord[5] = -35;
		x_coord[6] = -42;
		x_coord[7] = -35;
		x_coord[8] = -35;
		x_coord[9] = 35;

	}

	else if(nSet==4)
	{

		//x_coord[10] = {35,35,42,35,35,-35,-35,-42,-35,-35};
		x_coord[0] = 3;			//105
		x_coord[1] = 14;		//116
		x_coord[2] = 14;		//116
		x_coord[3] = 11;		//113
		x_coord[4] = -5;		//97
		x_coord[5] = -2;		//100
		x_coord[6] = -15;		//87
		x_coord[7] = -15;		//87
		x_coord[8] = -12;		//90
		x_coord[9] = 4;			//106

	}

	return TRUE;
}


////////////////////////////////////////////////////////

BOOL CArrowSpin::Load_Y_Coords(int nSet)
{
	if(nSet==1 || nSet==5)
	{ //{-43,-34,-34,35,35,43,35,35,-34,-34};
		y_coord[0] = -43;
		y_coord[1] = -34;
		y_coord[2] = -34;
		y_coord[3] = 35;
		y_coord[4] = 35;
		y_coord[5] = 43;
		y_coord[6] = 35;
		y_coord[7] = 35;
		y_coord[8] = -34;
		y_coord[9] = -34;
	}

	else if(nSet==2 || nSet==6)
	{
		//y_coord[10] = {-26,-29,-29,-19,-22,26,30,30,20,22};
		y_coord[0] = -27;//
		y_coord[1] = -30;
		y_coord[2] = -30;
		y_coord[3] = -18;
		y_coord[4] = -21;//to-21
		y_coord[5] = 27;//to -27
		y_coord[6] = 31;
		y_coord[7] = 31;
		y_coord[8] = 19;
		y_coord[9] = 21;//21
	}

	else if(nSet==3 || nSet==7)
	{
		//y_coord[10] = {-3,-7,0,7,3,3,7,0,-7,-3};
		y_coord[0] = -7;
		y_coord[1] = 0;
		y_coord[2] = 7;
		y_coord[3] = 4;
		y_coord[4] = 4;
		y_coord[5] = 7;
		y_coord[6] = 0;
		y_coord[7] = -7;
		y_coord[8] = -4;
		y_coord[9] = -4;
	}

	if(nSet==4)
	{ 
		y_coord[0] = -14;	 //68
		y_coord[1] = -14;	 //68
		y_coord[2] = -3;	 //79
		y_coord[3] = -5;	 //77
		y_coord[4] = 11;	 //93
		y_coord[5] = 14;	 //96
		y_coord[6] = 14;	 //96
		y_coord[7] = 2;		 //84
		y_coord[8] = 4;		 //86
		y_coord[9] = -12;	 //70
	}

	return TRUE;
}
*/
//*CArrowSpin::CArrowSpin( int *array, int _size)
//{	

		
//}

int CArrowSpin::AsIs_X(int dex)
{
	return x_coord[dex];
}

int CArrowSpin::AsIs_Y(int dex)
{
	return y_coord[dex];
}

void CArrowSpin::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	AfxMessageBox("OnClick");
	
	*pResult = 0;
}
