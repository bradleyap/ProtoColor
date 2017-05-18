// ClickStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "SerioDoc.h"
#include "ClickStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

	/////////////////////////////////////////////////////////////////////////////
// CClickStatic



CClickStatic::CClickStatic()
{
	CSerioDoc* pDcmt = CSerioDoc::GetDoc();
	mult = pDcmt->m_dMargRat;
	m_saveMult = mult;
	InitializeData(mult);
}

CClickStatic::~CClickStatic()
{


}


BEGIN_MESSAGE_MAP(CClickStatic, CStatic)
	//{{AFX_MSG_MAP(CClickStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClickStatic message handlers

void CClickStatic::OnPaint() 
{
	CPaintDC dc(this);
	CBitmap bmp,*obmp;
	CDC memdc;
	bmp.LoadBitmap(m_idbCur);
	memdc.CreateCompatibleDC(&dc);
	obmp = memdc.SelectObject(&bmp);
	dc.BitBlt(0,0,87,62,&memdc,0,0,SRCCOPY);
	memdc.SelectObject(obmp);
}

void CClickStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	int factorchk;
	factorchk = factors;
	UINT multbegin = mult;
	UINT idbbegin = m_idbCur;
	UINT newmult = 1;
	BOOL reset = FALSE;
	CRect rectTL(5,1,36,23);
	if(rectTL.PtInRect(point))
	{
		//Top Left--TL
		CPoint pt1(29,3),pt2(35,3),pt3(35,9),pt4(35,9),pt5(13,22),
		pt6(13,22),pt7(6,22),pt8(6,15),pt9(6,15),pt10(29,3);
/*		
before fattening alteration:
		CPoint pt1(29,3),pt2(35,3),pt3(35,9),pt4(32,8),pt5(13,20),
		pt6(13,22),pt7(6,22),pt8(6,15),pt9(9,16),pt10(29,4);

		*/
		CPoint path[10];
		path[0] = pt1;
		path[1] = pt2;
		path[2] = pt3;
		path[3] = pt4;
		path[4] = pt5;
		path[5] = pt6;
		path[6] = pt7;
		path[7] = pt8;
		path[8] = pt9;
		path[9] = pt10;

		CRgn rgnTL;
		rgnTL.CreatePolygonRgn((tagPOINT*)&path,10,WINDING);
		BOOL yn = 0;
		yn = rgnTL.PtInRegion(point);
	
		if(yn!=0)							//prime number 17 
		{									//used to indicate TL;
			if((mult%17)==0)		
			{	newmult = mult/17;
				factors--;
				reduce = TRUE;
			}
			else if((mult%17)!=0) 
			{
				newmult = mult*17;
				factors++;
			}
	
		}
	}

	CRect rectTR(51,0,80,23);
	if(rectTR.PtInRect(point))
	{
		//Top Right--TR
		CPoint pt1(52,2),pt2(59,2),pt3(59,2),pt4(80,15),pt5(80,15),
		pt6(80,22),pt7(73,22),pt8(73,22),pt9(52,9),pt10(52,9);

		/*
		CPoint pt1(52,2),pt2(59,2),pt3(58,4),pt4(77,16),pt5(80,15),
		pt6(80,22),pt7(73,22),pt8(73,20),pt9(55,8),pt10(52,9);
		*/

		CPoint path[10];
		path[0] = pt1;
		path[1] = pt2;
		path[2] = pt3;
		path[3] = pt4;
		path[4] = pt5;
		path[5] = pt6;
		path[6] = pt7;
		path[7] = pt8;
		path[8] = pt9;
		path[9] = pt10;

		CRgn rgnTR;
		rgnTR.CreatePolygonRgn((tagPOINT*)&path,10,WINDING);
		BOOL yn = 0;
		yn = rgnTR.PtInRegion(point);

		if(yn!=0)
		{
			if((mult%13)==0)		//prime number 13; 
			{						//used to indicate TR;
				newmult = mult/13;		
				reduce = TRUE;
				factors--;
			}
			else if((mult%13)!=0) 
			{
				newmult = mult*13;
				factors++;
			}
		}

	}

	CRect rectTB(38,1,49,60);
		if(rectTB.PtInRect(point))
	{
		//Top Bottom--TB
		CPoint pt1(39,6),pt2(43,1),pt3(48,7),pt4(48,7),pt5(48,55),
		pt6(48,55),pt7(43,60),pt8(39,54),pt9(39,54),pt10(39,6);
		/*
		CPoint pt1(39,6),pt2(43,1),pt3(48,7),pt4(46,7),pt5(46,54),
		pt6(48,55),pt7(43,60),pt8(39,54),pt9(41,54),pt10(41,7);
		*/


		CPoint path[10];
		path[0] = pt1;
		path[1] = pt2;
		path[2] = pt3;
		path[3] = pt4;
		path[4] = pt5;
		path[5] = pt6;
		path[6] = pt7;
		path[7] = pt8;
		path[8] = pt9;
		path[9] = pt10;

		CRgn rgnTB;
		rgnTB.CreatePolygonRgn((tagPOINT*)&path,10,WINDING);
		BOOL yn = 0;
		yn = rgnTB.PtInRegion(point);
	
		if(yn!=0) 
		{
			if((mult%11)==0)		//prime number 11 
			{						//used to indicate TB;
				newmult = mult/11;
				factors--;
				reduce = TRUE;
			}
			else if((mult%11)!=0) 
			{
				newmult = mult * 11;
				factors++;
			}
		}

	}


	CRect rectLR(2,25,84,36);
		if(rectLR.PtInRect(point))
	{

		//AfxMessageBox("Made it into the specific region test, point must be valid");
		//Left Right--L
		CPoint pt1(2,30),pt2(7,26),pt3(7,26),pt4(39,26),pt5(39,35),
		pt6(8,35),pt7(7,35);
		/*
		CPoint pt1(2,30),pt2(7,26),pt3(8,28),pt4(40,28),pt5(40,33),
		pt6(8,33),pt7(7,35);
		*/


		CPoint path1[7];
		path1[0] = pt1;
		path1[1] = pt2;
		path1[2] = pt3;
		path1[3] = pt4;
		path1[4] = pt5;
		path1[5] = pt6;
		path1[6] = pt7;


		CRgn rgnL;
		rgnL.CreatePolygonRgn((tagPOINT*)&path1,7,WINDING);
		BOOL yn = 0;
		yn = rgnL.PtInRegion(point);
	
		//if(yn!=0)

				//LEFT RIGHT--R
		CPoint pt1b(48,25),pt2b(77,25),pt3b(79,25),pt4b(83,30),pt5b(79,35),
		pt6b(78,35),pt7b(48,35);
		/*
		CPoint pt1b(47,27),pt2b(77,28),pt3b(79,25),pt4b(83,30),pt5b(79,35),
		pt6b(78,33),pt7b(47,33);
		*/
		CPoint path2[7];
		path2[0] = pt1b;
		path2[1] = pt2b;
		path2[2] = pt3b;
		path2[3] = pt4b;
		path2[4] = pt5b;
		path2[5] = pt6b;
		path2[6] = pt7b;


		CRgn rgnR;
		rgnR.CreatePolygonRgn((tagPOINT*)&path2,7,WINDING);
		BOOL ny = 0;
		ny = rgnR.PtInRegion(point);
	
		if(ny!=0||yn!=0)
		{
			if((mult%7)==0)		//prime number 7 
			{					//used to indicate LR
				newmult = mult/7;
				factors--;
				reduce = TRUE;
			}
			else if((mult%7)!=0) 
			{
				newmult = mult*7;
				factors++;
			}
		}
	}


	CRect rectLB(5,38,36,60);
		if(rectLB.PtInRect(point))
	{
		//Left Bottom--LB
		CPoint pt1(6,39),pt2(13,39),pt3(13,39),pt4(35,52),pt5(35,52),
		pt6(35,59),pt7(28,59),pt8(28,59),pt9(6,46),pt10(6,46);
		/*
		CPoint pt1(6,39),pt2(13,39),pt3(13,42),pt4(32,52),pt5(35,52),
		pt6(35,59),pt7(28,59),pt8(28,57),pt9(9,46),pt10(6,46);
		*/
		CPoint path[10];
		path[0] = pt1;
		path[1] = pt2;
		path[2] = pt3;
		path[3] = pt4;
		path[4] = pt5;
		path[5] = pt6;
		path[6] = pt7;
		path[7] = pt8;
		path[8] = pt9;
		path[9] = pt10;

		CRgn rgnLB;
		rgnLB.CreatePolygonRgn((tagPOINT*)&path,10,WINDING);
		BOOL yn = 0;
		yn = rgnLB.PtInRegion(point);
	
		if(yn!=0)
		{
			if((mult%5)==0)		//prime number 5 
			{					//used to indicate LB;
				newmult = mult/5;
				factors--;
				reduce = TRUE;
			}
			else if((mult%5)!=0) 
			{
				newmult = mult * 5;
				factors++;
			}
				
		}

	}


	CRect rectBR(51,38,81,60);
		if(rectBR.PtInRect(point))
	{
		//Bottom Right--BR
		CPoint pt1(52,52),pt2(52,52),pt3(73,39),pt4(73,39),pt5(80,39),
		pt6(80,46),pt7(80,46),pt8(59,59),pt9(59,59),pt10(52,59);
		/*
		CPoint pt1(52,52),pt2(56,52),pt3(73,42),pt4(73,39),pt5(80,39),
		pt6(80,46),pt7(77,46),pt8(60,57),pt9(59,59),pt10(52,59);
		*/
		CPoint path[10];
		path[0] = pt1;
		path[1] = pt2;
		path[2] = pt3;
		path[3] = pt4;
		path[4] = pt5;
		path[5] = pt6;
		path[6] = pt7;
		path[7] = pt8;
		path[8] = pt9;
		path[9] = pt10;

		CRgn rgnBR;
		rgnBR.CreatePolygonRgn((tagPOINT*)&path,10,WINDING);
		BOOL yn = 0;
		yn = rgnBR.PtInRegion(point);
	
		if(yn!=0)
		{
			if((mult%3)==0)	
			{						//prime number 3
				newmult = mult/3;		//used to indicate BR;
				factors--;
				reduce = TRUE;
			}
			else if((mult%3)!=0) 
			{
				newmult = mult*3;
				factors++;
			}
		}

	}

if(factors==factorchk)				//test for unhandled clicks
	reset = TRUE;

UINT newidb;

switch(factors)
{

case 0:

	newidb = IDB_AR;//157;
	mult = newmult;
	reduce = FALSE;
	break;

case 1:

	if(newmult==17)	newidb = IDB_AR_TL;//158;
	if(newmult==11) newidb = IDB_AR_TB;//159;
	if(newmult==13) newidb = IDB_AR_TR;//162;
	if(newmult==3) newidb = IDB_AR_BR;//163;
	if(newmult==7) newidb = IDB_AR_LR;//165;
	if(newmult==5) newidb = IDB_AR_LB;//166;

	mult = newmult;
	reduce = FALSE;
	break;

case 2:
	
	if(!reduce)
	{
		if(newmult==65) newidb = IDB_AR_TR_LB;//169;
		if(newmult==51) newidb = IDB_AR_TL_RB;//170;
		if(newmult==77) newidb = IDB_AR_TB_LR;//171;
		if(newmult==187||newmult==55||newmult==85)
		{
			newmult = 935;
			newidb = IDB_AR_TLB;//160;
			factors++;
		}
		if(newmult==33||newmult==143||newmult==39)
		{
			newmult = 429;
			newidb = IDB_AR_TBR;//164;
			factors++;
		}
		if(newmult==21||newmult==35||newmult==15)
		{
			newmult = 105;
			newidb = IDB_AR_RLB;//167;
			factors++;
		}
		if(newmult==119||newmult==221||newmult==91)
		{
			newmult = 1547;
			newidb = IDB_AR_TLR;//168;
			factors++;
		}

	}
	if(reduce)
	{
		newidb = IDB_AR;//157;
		newmult = 1;
		factors = 0;
	}
	mult = newmult;
	reduce = FALSE;
	break;

case 3:

	if(!reduce)
	{
		newidb = IDB_AR_TLBR;//161;
		newmult = 255255;
		factors = 4;//symbolic of a promotion to seven
	}
	if(reduce)
	{
		newidb = IDB_AR;//157;
		newmult = 1;
		factors = 0;
	}
	mult = newmult;
	reduce = FALSE;
	break;

case 4:

	newidb = IDB_AR_TLBR;//161;
	newmult = 255255;
	factors = 4;

	reduce = FALSE;
	mult = newmult;
	break;


default:
	reduce = FALSE;
	AfxMessageBox("Invalid settings: \n Start new docmument ");
	break;

}

	if(m_idbCur!=newidb)
		InvalidateRect(NULL,FALSE);


	m_idbCur = newidb;

	if(reset==TRUE)
	{
		factors = factorchk;
		mult = multbegin;
		m_idbCur = idbbegin;
		reset = FALSE;
	}


	CStatic::OnLButtonDown(nFlags, point);
}

void CClickStatic::Reset()
{
	mult = m_saveMult;
	InitializeData(mult);
	InvalidateRect(NULL,FALSE);
}

void CClickStatic::InitializeData(UINT mult)
{
	if(mult==1){m_idbCur = IDB_AR; factors = 0;}// 157
	if(mult==17){m_idbCur = IDB_AR_TL; factors = 1;}//158
	if(mult==11){m_idbCur = IDB_AR_TB; factors = 1;}//159
	if(mult==935){m_idbCur = IDB_AR_TLB; factors = 3;}//160
	if(mult==255255){m_idbCur = IDB_AR_TLBR; factors = 4;}//161		//4is code for 6
	if(mult==13){m_idbCur = IDB_AR_TR; factors = 1;}//162
	if(mult==3){m_idbCur = IDB_AR_BR; factors = 1;}//163
	if(mult==429){m_idbCur = IDB_AR_TBR; factors = 3;}//164
	if(mult==7){m_idbCur = IDB_AR_LR; factors = 1;}//165
	if(mult==5){m_idbCur = IDB_AR_LB; factors = 1;}//166
	if(mult==105){m_idbCur = IDB_AR_RLB; factors = 3;}//167
	if(mult==1547){m_idbCur = IDB_AR_TLR; factors = 3;}//168
	if(mult==65){m_idbCur = IDB_AR_TR_LB; factors = 2;}//169
	if(mult==51){m_idbCur = IDB_AR_TL_RB; factors = 2;}//170
	if(mult==77){m_idbCur = IDB_AR_TB_LR; factors = 2;}//171


		
	reduce = FALSE;

}
