// DragStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "SerioDoc.h"
#include "DragStatic.h"
#include "math.h"
#include "ArrowSpin.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragStatic

CDragStatic::CDragStatic()
{
	CSerioDoc* pDcmt;
	pDcmt = CSerioDoc::GetDoc();
	ColorMode = pDcmt->m_dColorMode;

	if(ColorMode==0) m_orientation = pDcmt->m_dOrientation_0;

	if(ColorMode==1) m_orientation = pDcmt->m_dOrientation_1;

	if(ColorMode==2) m_orientation = pDcmt->m_dOrientation_2;

	int c;
	for(c=1; c<8; c++)
	{	
		int axis;
		axis = RegionLUT(c,m_orientation);

		if(axis==1) { axis1Color = c; axis1Str = LoadStr(c);}
		if(axis==2) { axis2Color = c; axis2Str = LoadStr(c);}
		if(axis==3) { axis3Color = c; axis3Str = LoadStr(c);}
		if(axis==4) { axis4Color = c; axis4Str = LoadStr(c);}
	}

}


CDragStatic::~CDragStatic()
{
}


BEGIN_MESSAGE_MAP(CDragStatic, CStatic)
	//{{AFX_MSG_MAP(CDragStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////

void CDragStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	#ifdef _DEBUG
	CMemoryState start;
	start.Checkpoint();
	#endif

	validDrag = FALSE;
	int i;
	CRgn* r;
	for(i=1; i<8; i++)
	{	
		r = GetRegion(i);
		if(r->PtInRegion(point))
		{		
			origClick = i;
			if(i!=4)validDrag = TRUE;
			if(i==4 && ColorMode==1) validDrag = TRUE;	
		}
	delete r;
	}
	
	
	SetCapture();
	
	if(validDrag)
	{
		int quadrant;
		if(point.x >= 58 && point.y < 50) quadrant = 1;
		if(point.x >= 58 && point.y >= 50) quadrant = 4;
		if(point.x < 58 && point.y < 50) quadrant = 2;
		if(point.x < 58 && point.y >= 50) quadrant = 3;		
		origQuad = quadrant;

		//determine original click position for m_angleClick
		int x, y;
		if(quadrant==1)
		{
			x = point.x - 58;
			y = 50 - point.y;
			if((x + y)==0) x++;
			m_angleOff = (90 * y) / (x + y);
			
		}
				
		if(quadrant==2)
		{	
			x = 58 - point.x;
			y = 50 - point.y;
			if((x + y)==0) y++;
			m_angleOff = (90 * x) / (y + x);
		}
	
		if(quadrant==3)
		{
			x = 58 - point.x;
			y = point.y - 50;
			if((x + y)==0) x++;
			m_angleOff = (90 * y) / (x + y);
		}

		if(quadrant==4)
		{
			x = point.x - 58;
			y = point.y - 50;
			if((x + y)==0) y++;
			m_angleOff = (90 * x) / (y + x);
		}
	}
	//if(origClick==1) m_angleOff =  
	eraseCycle = FALSE;
	noMove = TRUE;
	
	CStatic::OnLButtonDown(nFlags, point);

	#ifdef _DEBUG
	CMemoryState end;
	end.Checkpoint();
	CMemoryState diff;
	if(diff.Difference(start,end))
	{
		TRACE("leak\n");
		diff.DumpStatistics();
		//start.DumpAllObjectsSince();
	}
	else TRACE("no leak\n");

	#endif


}


////////////////////////////////////////////////////////////////////


void CDragStatic::OnPaint() 
{	
#ifdef _DEBUG
	CMemoryState start;
	start.Checkpoint();
#endif

	CPaintDC dc(this);
	CBitmap bmp,*obmp;
	CDC memdc;

	if(ColorMode==0)bmp.LoadBitmap(IDB_CO_RGB);
	if(ColorMode==2)bmp.LoadBitmap(IDB_CO_CMY);
	if(ColorMode==1)bmp.LoadBitmap(IDB_CO_CMYK);

	memdc.CreateCompatibleDC(&dc);
	obmp = memdc.SelectObject(&bmp);

	if(m_orientation != 6 && m_orientation != 8 && m_orientation != 14)
	{

		
		int i, i2;
		for(i=1; i<5;i++)
		{
			i2 = i + 4;
			int c;
			if(i==1) c = axis1Color;
			if(i==2) c = axis2Color;
			if(i==3) c = axis3Color;
			if(i==4) c = axis4Color;

			CPen* pOldPen;
			CBrush* oldBr;
			CPen pen;
			if(pen.CreatePen(PS_SOLID, 2,RGB(
				GetColorVal(c,1),
				GetColorVal(c,2),
				GetColorVal(c,3))))
			{
				pOldPen = 
				memdc.SelectObject(&pen);
			}

			CBrush br;
			if(br.CreateSolidBrush(RGB(GetColorVal(c,1),
				GetColorVal(c,2),
				GetColorVal(c,3))))
			{
				oldBr = memdc.SelectObject(&br);
			}
			
			CRgn* r = GetRegion(i);
			if(i!=4)memdc.PaintRgn(r);
			
			if(i==4 && ColorMode==1)memdc.PaintRgn(GetRegion(i));

			CRgn* r2 = GetRegion(i2);
			if(i!=4) memdc.PaintRgn(r2);

			memdc.SelectObject(&pOldPen);
			memdc.SelectObject(&oldBr);

			delete r;
			delete r2;

		}

	}
	
	dc.BitBlt(0,0,131,109,&memdc,0,0,SRCCOPY);
	memdc.SelectObject(obmp);

	bmp.DeleteObject();

#ifdef _DEBUG
	CMemoryState end;
	end.Checkpoint();
	CMemoryState diff;
	if(diff.Difference(start,end))
	{
		TRACE("leak");
		diff.DumpStatistics();
		//start.DumpAllObjectsSince();
	}
	else TRACE("no leak");

#endif



}



////////////////////////////////////////////////////////////////////

void CDragStatic::OnLButtonUp(UINT nFlags, CPoint point) 
{	

	CClientDC dc(this);
	int rCode;

	if(noMove==FALSE && validDrag==TRUE)			
	{
						//Get rid of R2_NOT arrow
		dc.SetROP2(R2_NOT);

		int i;
		for(i=1; i<10; i++)
		{
			dc.MoveTo(array_x[i-1], array_y[i-1]);
			dc.LineTo(array_x[i], array_y[i]);
		}
		dc.MoveTo(array_x[9], array_y[9]);
		dc.LineTo(array_x[0], array_y[0]);
		
	}

	if(GetCapture()==this)
	ReleaseCapture();

	if(validDrag==TRUE)
	{
		CString toAxisStr;
		CString fromAxisStr;
		int i;
		for(i=1; i<8; i++)
		{	
			CRgn* r = GetRegion(i);
			if(r->PtInRegion(point))
			{	
				if(ColorMode!=1 && i==4) break;
				int fromAxis;

				if(origClick==1 || origClick==5) 
				{fromAxis = 1; fromAxisStr = axis1Str;}

				if(origClick==2 || origClick==6) 
				{fromAxis = 2; fromAxisStr = axis2Str;}

				if(origClick==3 || origClick==7) 
				{fromAxis = 3; fromAxisStr = axis3Str;}

				if(origClick==4)
				{fromAxis = 4; fromAxisStr = axis4Str;}

				int axis;
				int c;		//current color 1-7 for all primaries & black
				for(c=1; c<8; c++)
				{
					axis = RegionLUT(c,m_orientation);
					if(axis==fromAxis) break;
				}
				

				fromAxisColor = c;
				CPen* pOldPen;

				int i2;					//id of both clicked (i)
				if(i < 4) i2 = i + 4;	//and related region (i2)
				if(i > 4) i2 = i - 4;	//needed
				rCode = i;
				if(origClick!=i)
				{	
					CPen pen;
					CBrush* oldBr;
					if(pen.CreatePen(PS_SOLID, 2,RGB(
						GetColorVal(c,1),
						GetColorVal(c,2),
						GetColorVal(c,3))))
					{
						pOldPen = 
						dc.SelectObject(&pen);
					}
	
					dc.SetROP2(R2_COPYPEN);
			
					CBrush br;
					if(br.CreateSolidBrush(RGB(GetColorVal(c,1),
						GetColorVal(c,2),
						GetColorVal(c,3))))
					{
	
						oldBr = dc.SelectObject(&br);
					}
	
					//dc.SelectObject();
					
					dc.PaintRgn(GetRegion(i));
					if(i!=4)
					{
						dc.PaintRgn(GetRegion(i2));
					}
					dc.SelectObject(&pOldPen);
					dc.SelectObject(&oldBr);

					int reg2;
					if(origClick < 4) reg2 = origClick + 4;
					if(origClick > 4) reg2 = origClick - 4;

					//paint 'color from' axis
					
					if(i==1 || i==5) 
					{ 
						toAxisColor = axis1Color;
						axis1Color = c;
						toAxisStr = axis1Str;
						axis1Str = fromAxisStr;
						if(fromAxis==2) m_swap = 12;
						if(fromAxis==3) m_swap = 13;
						if(fromAxis==4) m_swap = 14;
					}

					if(i==2 || i==6) 
					{ 
						toAxisColor = axis2Color;
						axis2Color = c;
						toAxisStr = axis2Str;
						axis2Str = fromAxisStr;
						if(fromAxis==1) m_swap = 12;
						if(fromAxis==3) m_swap = 23;
						if(fromAxis==4) m_swap = 24;
					}

					if(i==3 || i==7) 
					{
						toAxisColor = axis3Color;
						axis3Color = c;
						toAxisStr = axis3Str;
						axis3Str = fromAxisStr;
						if(fromAxis==1) m_swap = 13;
						if(fromAxis==2) m_swap = 23;
						if(fromAxis==4) m_swap = 34;
					}

					if(i==4) 
					{
						toAxisColor = axis4Color;
						axis4Color = c;
						toAxisStr = axis4Str;
						axis4Str = fromAxisStr;
						if(fromAxis==1) m_swap = 14;
						if(fromAxis==2) m_swap = 24;
						if(fromAxis==3) m_swap = 34;
					}

					CPen p;
					if(p.CreatePen(PS_SOLID, 2,RGB(
						GetColorVal(toAxisColor,1),
						GetColorVal(toAxisColor,2),
						GetColorVal(toAxisColor,3))))
					{
						CPen* pOldP;
						pOldP = 
						dc.SelectObject(&p);
					
	
					dc.SetROP2(R2_COPYPEN);
			
					CBrush b;
					if(b.CreateSolidBrush(RGB(GetColorVal(toAxisColor,1),
						GetColorVal(toAxisColor,2),
						GetColorVal(toAxisColor,3))))
					{
	
						CBrush* pOldB = dc.SelectObject(&b);
					

						//get original color from this region
						dc.PaintRgn(GetRegion(origClick));
						if(origClick!=4)
						{
							dc.PaintRgn(GetRegion(reg2));
						}
						dc.SelectObject(&pOldP);
						dc.SelectObject(&pOldB);

						if(fromAxis==1)	{axis1Color = toAxisColor; axis1Str = toAxisStr;}
						if(fromAxis==2) {axis2Color = toAxisColor; axis2Str = toAxisStr;}
						if(fromAxis==3) {axis3Color = toAxisColor; axis3Str = toAxisStr;}
						if(fromAxis==4) {axis4Color = toAxisColor; axis4Str = toAxisStr;}

						int tmpO;
						if(ColorMode==0 || ColorMode==2)
						{
							tmpO = OrientationLUT(axis1Color,
								axis2Color,axis3Color);
						}

						if(ColorMode==1)
						{
							tmpO = OrientationLUT();
						} 
						
						m_orientation = tmpO;
					}}

					GetParent()->SetDlgItemText(
						IDC_L2R_STATIC, axis3Str);
					GetParent()->SetDlgItemText(
						IDC_T2B_STATIC, axis1Str);
					GetParent()->SetDlgItemText(
						IDC_F2L_STATIC, axis2Str);
					GetParent()->SetDlgItemText(
						IDC_F2B_STATIC, axis4Str);

					m_reset = TRUE; //spin control sync flag for COrientDlg

				}//if  stay inside if(origClick!=i) to avoid processing 
	//	unnecessarily		break;
				
			}//if value of 'i' outside this 'if' is invalid

			delete r;

		}//for
	}
//	char s[200];
//	ostrstream ostr(s,200);
//	ostr << test<<ends;
//	MessageBox("# of cycles:",ostr);

	CStatic::OnLButtonUp(nFlags, point);
}


////////////////////////////////////////////////////////////////////

void CDragStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	#ifdef _DEBUG
	CMemoryState start;
	start.Checkpoint();
	#endif

	if(validDrag==TRUE)
	{
		if(GetCapture()==this)
		{
		CClientDC dc(this);
		dc.SetROP2(R2_NOT);
		//if(eraseCycle==TRUE)
		//	int i;
		//	for(i=1; i<10; i++)
		//	{test++;
		//		dc.MoveTo(array_x[i-1], array_y[i-1]);
		//		dc.LineTo(array_x[i], array_y[i]);
		//	}
		//	dc.MoveTo(array_x[9], array_y[9]);
		//	dc.LineTo(array_x[0], array_y[0]);
		//}

			int angle;
			int quadrant;
			if(point.x >= 58 && point.y < 50) quadrant = 1;
			if(point.x >= 58 && point.y >= 50) quadrant = 4;
			if(point.x < 58 && point.y < 50) quadrant = 2;
			if(point.x < 58 && point.y >= 50) quadrant = 3; 

			if(quadrant==1)
			{
				int x, y;
				x = point.x - 58;
				y = 50 - point.y;
				if((x + y)!=0)
				{
					m_angleClick = (90 * y) / (x + y);
					angle = m_angleClick + 270 - m_angleOff;
				}
			}


			if(quadrant==2)
			{	
				int x, y;
				x = 58 - point.x;
				y = 50 - point.y;
				if((x + y)!=0)
				{
					m_angleClick = (90 * x) / (y + x);
					angle = m_angleClick - m_angleOff;
				}
			}

			if(quadrant==3)
			{
				int x, y;
				x = 58 - point.x;
				y = point.y - 50;
				if((x + y)!=0)
				{
					m_angleClick = (90 * y) / (x + y);
					angle = m_angleClick + 90 - m_angleOff;
				}

			}

			if(quadrant==4)
			{
				int x, y;
				x = point.x - 58;
				y = point.y - 50;
				if((x + y)!=0)
				{
					m_angleClick = (90 * x) / (y + x);
					angle = m_angleClick + 180 - m_angleOff;
				}
			}

			BOOL GoRound = TRUE;
			CRgn* r = GetRegion(8);
			CRgn* r2 = GetRegion(9);
	
			if(!r->PtInRegion(point)) GoRound = FALSE;
			if(r2->PtInRegion(point)) GoRound = FALSE;

			delete r;
			delete r2;

			if(eraseCycle==TRUE)
			{
				//CClientDC dc(this);
				//dc.SetROP2(R2_NOT);
				int i;
				for(i=1; i<10; i++)
				{
					dc.MoveTo(array_x[i-1], array_y[i-1]);
					dc.LineTo(array_x[i], array_y[i]);
				}
			dc.MoveTo(array_x[9], array_y[9]);
			dc.LineTo(array_x[0], array_y[0]);
			}

			if(!GoRound)
			{
				int n = 4;
				CArrowSpin loader;
				loader.Load_X_Coords(n);
				loader.Load_Y_Coords(n);
				int i;
				for(i=0; i<10; i++)
				{	
					array_x[i] = loader.AsIs_X(i);
					array_x[i] = array_x[i] + point.x;
				}
	
				for(i=0; i<10; i++)
				{
					array_y[i] = loader.AsIs_Y(i);
					array_y[i] = array_y[i] + point.y;
				}

		
			}

			if(GoRound)
			{
				int select;
				if(origClick!=4) select = origClick;
				if(origQuad==1 && origClick!=2) angle = angle + 90;
				if(origQuad==3 && origClick!=6) angle = angle + 90;
				if(origClick==4) angle = angle + 94;

				CArrowSpin spinner;
				spinner.Load_X_Coords(origClick);
				spinner.Load_Y_Coords(origClick);
				int i;
				for(i=0; i<10; i++)
				{	
	
					array_x[i] = spinner.Rotate(angle,select,i,TRUE);
					array_x[i] = array_x[i] + 58;
				}
	
				for(i=0; i<10; i++)
				{
	
					array_y[i] = spinner.Rotate(angle,select,i,FALSE);
					array_y[i] = array_y[i] + 50;
				}	
			
			}//if(GoRound)

			int i;
			for(i=1; i<10; i++)//display new object
			{
				dc.MoveTo(array_x[i-1], array_y[i-1]);
				dc.LineTo(array_x[i], array_y[i]);
			}
			dc.MoveTo(array_x[9], array_y[9]);
			dc.LineTo(array_x[0], array_y[0]);

			noMove = FALSE;
			eraseCycle = TRUE;

		//dc.FillRgn(&rgnTL,CBrush::FromHandle((HBRUSH)
		//GetStockObject(WHITE_BRUSH)));

		}//if capture

	}//if validDrag
	#ifdef _DEBUG
	CMemoryState end;
	end.Checkpoint();
	CMemoryState diff;
	if(diff.Difference(start,end))
	{
		TRACE("leak\n");
		diff.DumpStatistics();
		//start.DumpAllObjectsSince();
	}
	else TRACE("no leak\n");

	#endif



	CStatic::OnMouseMove(nFlags, point);
}



////////////////////////////////////////////////////////////////////

CRgn* CDragStatic::GetRegion(int rgnCode)
{	
	CRgn* y;
	int currentReg = rgnCode;
	if(currentReg==1)
	{
		
		CPoint pt1(58,7),pt2(67,16),pt3(62,16),pt4(62,47),pt5(59,50);
		CPoint pt6(57,47),pt7(55,47),pt8(55,16),pt9(49,16);


		CPoint paths[9];
		paths[0] = pt1;
		paths[1] = pt2;
		paths[2] = pt3;
		paths[3] = pt4;
		paths[4] = pt5;
		paths[5] = pt6;
		paths[6] = pt7;
		paths[7] = pt8;
		paths[8] = pt9;

		y = new CRgn();
		int i;
		BOOL validRgn = FALSE;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreatePolygonRgn((tagPOINT*)&paths,9,WINDING);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreatePolygonRgn() for arrows");
	}

	if(currentReg==2)
	{		
		CPoint pt1(77,21),pt2(89,21),pt3(89,33),pt4(85,29),pt5(67,47);
		CPoint pt6(62,47),pt7(62,42),pt8(80,24);


		CPoint paths[8];
		paths[0] = pt1;
		paths[1] = pt2;
		paths[2] = pt3;
		paths[3] = pt4;
		paths[4] = pt5;
		paths[5] = pt6;
		paths[6] = pt7;
		paths[7] = pt8;


		y = new CRgn();
		int i;
		BOOL validRgn = FALSE;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreatePolygonRgn((tagPOINT*)&paths,8,WINDING);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreatePolygonRgn() for arrows");
	}
	
	if(currentReg==3)
	{
		CPoint pt1(93,42),pt2(101,50),pt3(93,58),pt4(93,54),pt5(62,54);
		CPoint pt6(59,50),pt7(62,47),pt8(93,47);


		CPoint paths[8];
		paths[0] = pt1;
		paths[1] = pt2;
		paths[2] = pt3;
		paths[3] = pt4;
		paths[4] = pt5;
		paths[5] = pt6;
		paths[6] = pt7;
		paths[7] = pt8;
		
		y = new CRgn();
		int i;
		BOOL validRgn = FALSE;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreatePolygonRgn((tagPOINT*)&paths,8,WINDING);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreatePolygonRgn() for arrows");
	}

	if(currentReg==4)
	{
		CPoint pt1(105,68),pt2(116,68),pt3(116,79),pt4(113,77),pt5(113,77);
		CPoint pt6(97,93),pt7(97,93),pt8(100,96),pt9(87,96),pt10(87,84);
		CPoint pt11(90,86),pt12(90,87),pt13(107,70),pt14(106,70);


		CPoint paths[14];
		paths[0] = pt1;
		paths[1] = pt2;
		paths[2] = pt3;
		paths[3] = pt4;
		paths[4] = pt5;
		paths[5] = pt6;
		paths[6] = pt7;
		paths[7] = pt8;
		paths[8] = pt9;
		paths[9] = pt10;
		paths[10] = pt11;
		paths[11] = pt12;
		paths[12] = pt13;
		paths[13] = pt14;


		y = new CRgn();
		int i;
		BOOL validRgn = FALSE;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreatePolygonRgn((tagPOINT*)&paths,14,WINDING);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreatePolygonRgn() for arrows");
	}

	if(currentReg==5)
	{
		CPoint pt1(62,53),pt2(62,85),pt3(66,85),pt4(58,93),pt5(50,85);
		CPoint pt6(55,85),pt7(55,58),pt8(60,53),pt9(61,53);

		CPoint paths[9];
		paths[0] = pt1;
		paths[1] = pt2;
		paths[2] = pt3;
		paths[3] = pt4;
		paths[4] = pt5;
		paths[5] = pt6;
		paths[6] = pt7;
		paths[7] = pt8;
		paths[8] = pt9;

		y = new CRgn();
		int i;
		BOOL validRgn = FALSE;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreatePolygonRgn((tagPOINT*)&paths,9,WINDING);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreatePolygonRgn() for arrows");
	}

	if(currentReg==6)
	{
		CPoint pt1(57,47),pt2(62,53),pt3(38,77),pt4(38,77),pt5(40,81);
		CPoint pt6(29,81),pt7(29,69),pt8(32,71),pt9(32,72);

		CPoint paths[9];
		paths[0] = pt1;
		paths[1] = pt2;
		paths[2] = pt3;
		paths[3] = pt4;
		paths[4] = pt5;
		paths[5] = pt6;
		paths[6] = pt7;
		paths[7] = pt8;
		paths[8] = pt9;

		y = new CRgn();
		int i;
		BOOL validRgn = FALSE;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreatePolygonRgn((tagPOINT*)&paths,9,WINDING);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreatePolygonRgn() for arrows");
	}

	if(currentReg==7)
	{
		CPoint pt1(24,43),pt2(24,47),pt3(56,47),pt4(56,48),pt5(50,54);
		CPoint pt6(24,54),pt7(24,58),pt8(16,50),pt9(24,42);

		CPoint paths[9];
		paths[0] = pt1;
		paths[1] = pt2;
		paths[2] = pt3;
		paths[3] = pt4;
		paths[4] = pt5;
		paths[5] = pt6;
		paths[6] = pt7;
		paths[7] = pt8;
		paths[8] = pt9;

		y = new CRgn();
		int i;
		BOOL validRgn = FALSE;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreatePolygonRgn((tagPOINT*)&paths,9,WINDING);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreatePolygonRgn() for arrows");
	}

	if(currentReg==8)
	{
		y = new CRgn();
		BOOL validRgn = FALSE;
		int i;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreateEllipticRgn(16,7,100,91);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreateEllipticRgn()");
	}

	if(currentReg==9)
	{
		CPoint pt1(106,55),pt2(123,55),pt3(123,105),pt4(80,105),pt5(80,82),
			 pt6(94,74);

		CPoint paths[6];
		paths[0] = pt1;
		paths[1] = pt2;
		paths[2] = pt3;
		paths[3] = pt4;
		paths[4] = pt5;
		paths[5] = pt6;

		y = new CRgn();
		BOOL validRgn = FALSE;
		int i;
		for(i=0;i<50;i++)
		{
			validRgn = y->CreatePolygonRgn((tagPOINT*)&paths,6,WINDING);
			if(validRgn)break;
			delete y;
		}
		if(!validRgn)AfxMessageBox("Failed CreatePolygonRgn()");
	}

	//CRgn* r; //member

	return y;

}



////////////////////////////////////////////////////////////////////

/* 
The following chart was used to organize the RegionLUT() and 
OrientationLUT() functions:

  m_orientation		red/axis   green/axis   blue/axis
		1				r1			g2			b3
		2				r1			g3			b2
		3				r3			g1			b2
		4				r2			g1			b3
		5				r2			g3			b1
		6				r3			g2			b1

  m_orientation		cyan/axis	magenta/ax	yellow/axis	
		7				c1			m2			y3
		8				c1			m3			y2
		9				c2			m1			y3
		10				c3			m1			y2
		11				c2			m3			y1
		12				c3			m2			y1

  m_orientation		group 1		group 2		group 3		group 4
 "section" 1 
		13				c1			m2			y3			k4
		14				c1			m3			y2			k4
		15				c3			m1			y2			k4
		16				c2			m1			y3			k4
		17				c2			m3			y1			k4
		18				c3			m2			y1			k4

  "section" 2
		19				c1			m2			y4			k3
		20				c1			m3			y4			k2
		21				c2			m1			y4			k3
		22				c3			m1			y4			k2
		23				c3			m2			y4			k1
		24				c2			m3			y4			k1
 
   "section" 3
		25				c1			m4			y3			k2
		26				c1			m4			y2			k3
		27				c2			m4			y1			k3
		28				c3			m4			y1			k2
		29				c3			m4			y2			k1
		30				c2			m4			y3			k1

  "section" 4
		31				c4			m1			y2			k3
		32				c4			m1			y3			k2
		33				c4			m2			y1			k3
		34				c4			m3			y1			k2
		35				c4			m3			y2			k1
		36				c4			m2			y3			k1
		
*/

int CDragStatic::RegionLUT(int colorID, int cfgCode)
{
	int currentAxis = 0;
	switch(colorID)
	{

	case 1 :						//Red

			if(cfgCode==1 || cfgCode==2) currentAxis = 1;
			if(cfgCode==3 || cfgCode==6) currentAxis = 3;
			if(cfgCode==4 || cfgCode==5) currentAxis = 2;
			break;
		
	case 2 :							//GREEN

			if(cfgCode==1 || cfgCode==6) currentAxis = 2;
			if(cfgCode==3 || cfgCode==4) currentAxis = 1;
			if(cfgCode==5 || cfgCode==2) currentAxis = 3;
			break;

	case 3 :							//BLUE
		
			if(cfgCode==1 || cfgCode==4) currentAxis = 3;
			if(cfgCode==2 || cfgCode==3) currentAxis = 2;
			if(cfgCode==5 || cfgCode==6) currentAxis = 1;
			break;

	case 4:								//CYAN

			if(cfgCode==7 || cfgCode==8) currentAxis = 1;
			if(cfgCode==9 || cfgCode==11) currentAxis = 2;
			if(cfgCode==10 || cfgCode==12) currentAxis = 3;

			if(cfgCode==13 || cfgCode==14) currentAxis = 1;
			if(cfgCode==19 || cfgCode==20) currentAxis = 1;
			if(cfgCode==25 || cfgCode==26) currentAxis = 1;
			if(cfgCode==16 || cfgCode==17) currentAxis = 2;
			if(cfgCode==21 || cfgCode==24) currentAxis = 2;
			if(cfgCode==27 || cfgCode==30) currentAxis = 2;
			if(cfgCode==15 || cfgCode==18) currentAxis = 3;
			if(cfgCode==22 || cfgCode==23) currentAxis = 3;
			if(cfgCode==28 || cfgCode==29) currentAxis = 3;
			if(cfgCode==31 || cfgCode==32) currentAxis = 4;
			if(cfgCode==33 || cfgCode==34) currentAxis = 4;
			if(cfgCode==35 || cfgCode==36) currentAxis = 4;
			break;

	case 5:								//MAGENTA

			if(cfgCode==7 || cfgCode==12) currentAxis = 2;
			if(cfgCode==8 || cfgCode==11) currentAxis = 3;
			if(cfgCode==9 || cfgCode==10) currentAxis = 1;

			if(cfgCode==15 || cfgCode==16) currentAxis = 1;
			if(cfgCode==21 || cfgCode==22) currentAxis = 1;
			if(cfgCode==31 || cfgCode==32) currentAxis = 1;
			if(cfgCode==13 || cfgCode==18) currentAxis = 2;
			if(cfgCode==19 || cfgCode==23) currentAxis = 2;
			if(cfgCode==33 || cfgCode==36) currentAxis = 2;
			if(cfgCode==14 || cfgCode==17) currentAxis = 3;
			if(cfgCode==20 || cfgCode==24) currentAxis = 3;
			if(cfgCode==34 || cfgCode==35) currentAxis = 3;
			if(cfgCode==25 || cfgCode==26) currentAxis = 4;
			if(cfgCode==27 || cfgCode==28) currentAxis = 4;
			if(cfgCode==29 || cfgCode==30) currentAxis = 4;

			break;

	case 6:								//YELLOW

			if(cfgCode==7 || cfgCode==9) currentAxis = 3;
			if(cfgCode==8 || cfgCode==10) currentAxis = 2;
			if(cfgCode==11 || cfgCode==12) currentAxis = 1;

			if(cfgCode==17 || cfgCode==18) currentAxis = 1;
			if(cfgCode==27 || cfgCode==28) currentAxis = 1;
			if(cfgCode==33 || cfgCode==34) currentAxis = 1;
			if(cfgCode==14 || cfgCode==15) currentAxis = 2;
			if(cfgCode==26 || cfgCode==29) currentAxis = 2;
			if(cfgCode==31 || cfgCode==35) currentAxis = 2;
			if(cfgCode==13 || cfgCode==16) currentAxis = 3;
			if(cfgCode==25 || cfgCode==30) currentAxis = 3;
			if(cfgCode==32 || cfgCode==36) currentAxis = 3;
			if(cfgCode==19 || cfgCode==20) currentAxis = 4;
			if(cfgCode==21 || cfgCode==22) currentAxis = 4;
			if(cfgCode==23 || cfgCode==24) currentAxis = 4;
			break;

	case 7:							//BLACK

			if(cfgCode==23 || cfgCode==24) currentAxis = 1;
			if(cfgCode==29 || cfgCode==30) currentAxis = 1;
			if(cfgCode==35 || cfgCode==36) currentAxis = 1;
			if(cfgCode==20 || cfgCode==22) currentAxis = 2;
			if(cfgCode==25 || cfgCode==28) currentAxis = 2;
			if(cfgCode==32 || cfgCode==34) currentAxis = 2;
			if(cfgCode==19 || cfgCode==21) currentAxis = 3;
			if(cfgCode==26 || cfgCode==27) currentAxis = 3;
			if(cfgCode==31 || cfgCode==33) currentAxis = 3;
			if(cfgCode==13 || cfgCode==14) currentAxis = 4;
			if(cfgCode==15 || cfgCode==16) currentAxis = 4;
			if(cfgCode==17 || cfgCode==18) currentAxis = 4;

			break;
	}

	return currentAxis;
}


////////////////////////////////////////////////////////////////////

int CDragStatic::GetColorVal(int color,int primary)
{	
	//constructor initialized counter to 3;
	int clr;

	if(color==1)		//red
		{	uno = 255;	dos = 0;	tres = 0;}
		

	if(color==2)		//green
		{	uno = 0;	dos = 255;	tres = 0;}

	if(color==3)		//blue
		{	uno = 0;	dos = 0;	tres = 255;}
	
	if(color==4)			//cyan
		{	uno = 0;	dos = 255;	tres = 255;}
		
	if(color==5)			//magenta
		{	uno = 255;	dos = 0;	tres = 255;}
	
	if(color==6)			//yellow
		{	uno = 255;	dos = 255;	tres = 0;}
	
	if(color==7)			//black
		{	uno = 0;	dos = 0;	tres = 0;}
		
	if(primary==1) clr = uno;
	if(primary==2) clr = dos;
	if(primary==3) clr = tres;

	return clr;

}/////////////////////////////////////////////////////////////////////////////
// COrientStatic

COrientStatic::COrientStatic()
{
}

COrientStatic::~COrientStatic()
{
}


BEGIN_MESSAGE_MAP(COrientStatic, CStatic)
	//{{AFX_MSG_MAP(COrientStatic)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrientStatic message handlers

int CDragStatic::OrientationLUT()
{
	int oCode = 0;
	int section;

	if(m_orientation >= 13 && m_orientation <= 18)
	{
		section = 1;
		if(fromAxisColor==7 || toAxisColor==7)
		{
			if(fromAxisColor==6||toAxisColor==6) section = 2;
			if(fromAxisColor==5||toAxisColor==5) section = 3;
			if(fromAxisColor==4||toAxisColor==4) section = 4;
		}
	}

	if(m_orientation >= 19 && m_orientation <= 24)
	{
		section = 2;
		if(fromAxisColor==6 || toAxisColor==6)
		{
			if(fromAxisColor==7||toAxisColor==7) section = 1;
			if(fromAxisColor==5||toAxisColor==5) section = 3;
			if(fromAxisColor==4||toAxisColor==4) section = 4;
		}
	}

	if(m_orientation >= 25 && m_orientation <= 30)
	{
		section = 3;
		if(fromAxisColor==5 || toAxisColor==5)
		{
			if(fromAxisColor==7||toAxisColor==7) section = 1;
			if(fromAxisColor==6||toAxisColor==6) section = 2;
			if(fromAxisColor==4||toAxisColor==4) section = 4;
		}

	}

	if(m_orientation >= 31 && m_orientation <= 36)
	{
		section = 4;
		if(fromAxisColor==4 || toAxisColor==4)
		{
			if(fromAxisColor==7||toAxisColor==7) section = 1;
			if(fromAxisColor==6||toAxisColor==6) section = 2;
			if(fromAxisColor==5||toAxisColor==5) section = 3;
		}

	}

	if(section==1)
	{
		if(axis1Color==4)	//cyan
		{
			if(axis2Color==5) oCode = 13;
			else if(axis2Color!=5) oCode = 14;
		}

		if(axis1Color==5) //magenta
		{
			if(axis3Color==4) oCode = 15;
			else if(axis3Color!=4) oCode = 16;
		}

		if(axis1Color==6) //yellow
		{
			if(axis3Color==5) oCode = 17;
			else if(axis3Color!=5) oCode = 18;
		}

	}

	if(section==2)
	{
		if(axis1Color==4)	//cyan
		{
			if(axis2Color==5) oCode = 19;
			else oCode = 20;
		}

		if(axis1Color==5) //magenta
		{
			if(axis3Color==4) oCode = 22;
			else oCode = 21;
		}

		if(axis1Color==7) //black
		{
			if(axis3Color==5) oCode = 24;
			else oCode = 23;
		}

	}

	if(section==3)
	{
		if(axis1Color==4)	//cyan
		{
			if(axis2Color==7) oCode = 25;
			else oCode = 26;
		}

		if(axis1Color==6) //yellow
		{
			if(axis3Color==7) oCode = 27;
			else oCode = 28;
		}

		if(axis1Color==7) //black
		{
			if(axis3Color==4) oCode = 29;
			else return 30;
		}

	}

	if(section==4)
	{
		if(axis1Color==5)	//magenta
		{
			if(axis2Color==6) oCode = 31;
			else return 32;
		}

		if(axis1Color==6) //yellow
		{
			if(axis3Color==7) oCode = 33;
			else oCode = 34;
		}

		if(axis1Color==7) //black
		{
			if(axis3Color==5) oCode = 35;
			else oCode = 36;
		}

	}

	return oCode;
}

int CDragStatic::OrientationLUT(int ax1C, int ax2C, int ax3C)
{
	if(m_orientation <= 6)
	{
		if(ax1C==1)	//red
		{
			if(ax2C==2) return 1;
			else return 2;
		}

		if(ax1C==2) //green
		{
			if(ax3C==1) return 3;
			else return 4;
		}

		if(ax1C==3) //blue
		{
			if(ax3C==2) return 5;
			else return 6;
		}

	}

	if(m_orientation >= 7)
	{
		if(ax1C==4)	//cyan
		{
			if(ax2C==5) return 7;
			else return 8;
		}

		if(ax1C==5) //magenta
		{
			if(ax3C==6) return 9;
			else return 10;
		}

		if(ax1C==6) //yellow
		{
			if(ax3C==5) return 11;
			else return 12;
		}

	}

	return 0;
}

CString CDragStatic::LoadStr(int sCode)
{
	CString red = "(RED)";
	CString grn = "(GREEN)";
	CString blu = "(BLUE)";
	CString cyn = "(CYAN)";
	CString mag = "(MAGENTA)";
	CString ylw = "(YELLOW)";
	CString blk = "(BLACK)";

	if(sCode==1) return red;
	if(sCode==2) return grn;
	if(sCode==3) return blu;
	if(sCode==4) return cyn;
	if(sCode==5) return mag;
	if(sCode==6) return ylw;
	if(sCode==7) return blk;

	return blk;
}


int CDragStatic::Revolve(int pos, BOOL reset)
{
	//if(pos==1)AfxMessageBox("passed 1");
	//if(pos==2)AfxMessageBox("passed 2");
	//if(pos==3)AfxMessageBox("passed 3");
	int set;

	int p = pos;
	
	if(m_orientation==1 || m_orientation==3 || m_orientation==5) set = 1;
	if(m_orientation==2 || m_orientation==4 || m_orientation==6) set = 2;
	if(m_orientation==8 || m_orientation==9 || m_orientation==12) set = 3;
	if(m_orientation==7 || m_orientation==10 || m_orientation==11) set = 4;

	if(m_orientation==14 || m_orientation==16 || m_orientation==18) set = 5;
	if(m_orientation==13 || m_orientation==15 || m_orientation==17) set = 6;
	if(m_orientation==20 || m_orientation==21 || m_orientation==23) set = 7;
	if(m_orientation==19 || m_orientation==22 || m_orientation==24) set = 8;
	if(m_orientation==25 || m_orientation==27 || m_orientation==29) set = 9;
	if(m_orientation==26 || m_orientation==28 || m_orientation==30) set = 10;
	if(m_orientation==31 || m_orientation==34 || m_orientation==36) set = 11;
	if(m_orientation==32 || m_orientation==33 || m_orientation==35) set = 12;

	if(!reset)
	{
		if(pos==1 && set==1) m_orientation = 3;//AfxMessageBox("5");}
		if(pos==2 && set==1) m_orientation = 1;//AfxMessageBox("3");}
		if(pos==3 && set==1) m_orientation = 5;// AfxMessageBox("1");}
		if(pos==1 && set==2) m_orientation = 6;//AfxMessageBox("6");}
		if(pos==2 && set==2) m_orientation = 2;//AfxMessageBox("2");}
		if(pos==3 && set==2) m_orientation = 4;// AfxMessageBox("4");}
		if(pos==1 && set==3) m_orientation = 8;//AfxMessageBox("8");}
		if(pos==2 && set==3) m_orientation = 9;//AfxMessageBox("9");}
		if(pos==3 && set==3) m_orientation = 12;// AfxMessageBox("12");}
		if(pos==1 && set==4) m_orientation = 7;//AfxMessageBox("7");}
		if(pos==2 && set==4) m_orientation = 11;//AfxMessageBox("11");}
		if(pos==3 && set==4) m_orientation = 10;// AfxMessageBox("10");}
		if(pos==1 && set==5) m_orientation = 14;//AfxMessageBox("14");}
		if(pos==2 && set==5) m_orientation = 16;//AfxMessageBox("16");}
		if(pos==3 && set==5) m_orientation = 18;// AfxMessageBox("18");}
		if(pos==1 && set==6) m_orientation = 13;
		if(pos==2 && set==6) m_orientation = 17;
		if(pos==3 && set==6) m_orientation = 15; 
		if(pos==1 && set==7) m_orientation = 20;
		if(pos==2 && set==7) m_orientation = 21;
		if(pos==3 && set==7) m_orientation = 23; 
		if(pos==1 && set==8) m_orientation = 19;
		if(pos==2 && set==8) m_orientation = 24;
		if(pos==3 && set==8) m_orientation = 22; 
		if(pos==1 && set==9) m_orientation = 25;
		if(pos==2 && set==9) m_orientation = 27;
		if(pos==3 && set==9) m_orientation = 29; 
		if(pos==1 && set==10) m_orientation = 26;
		if(pos==2 && set==10) m_orientation = 30;
		if(pos==3 && set==10) m_orientation = 28; 
		if(pos==1 && set==11) m_orientation = 34;
		if(pos==2 && set==11) m_orientation = 31;
		if(pos==3 && set==11) m_orientation = 36; 
		if(pos==1 && set==12) m_orientation = 32;
		if(pos==2 && set==12) m_orientation = 33;
		if(pos==3 && set==12) m_orientation = 35; 

		int c;
		for(c=1; c<8; c++)
		{	
			int axis;
			axis = RegionLUT(c,m_orientation);
	
			if(axis==1) { axis1Color = c; axis1Str = LoadStr(c);}
			if(axis==2) { axis2Color = c; axis2Str = LoadStr(c);}
			if(axis==3) { axis3Color = c; axis3Str = LoadStr(c);}
			if(axis==4) { axis4Color = c; axis4Str = LoadStr(c);}
		}
	
		GetParent()->SetDlgItemText(IDC_L2R_STATIC, axis3Str);
		GetParent()->SetDlgItemText(IDC_T2B_STATIC, axis1Str);
		GetParent()->SetDlgItemText(IDC_F2L_STATIC, axis2Str);
		GetParent()->SetDlgItemText(IDC_F2B_STATIC, axis4Str);
			
		InvalidateRect(NULL,FALSE);

		return 1;

	}

	if(reset)
	{
		if(m_orientation==3) p = 1;
		if(m_orientation==1) p = 2;
		if(m_orientation==5) p = 3; 
		if(m_orientation==6) p = 1;
		if(m_orientation==2) p = 2;
		if(m_orientation==4) p = 3; 
		if(m_orientation==8) p = 1;
		if(m_orientation==9) p = 2;
		if(m_orientation==12) p = 3; 
		if(m_orientation==7) p = 1;
		if(m_orientation==11) p = 2;
		if(m_orientation==10) p = 3; 
		if(m_orientation==14) p = 1;
		if(m_orientation==16) p = 2;
		if(m_orientation==18) p = 3; 
		if(m_orientation==13) p = 1;
		if(m_orientation==17) p = 2;
		if(m_orientation==15) p = 3; 
		if(m_orientation==20) p = 1;
		if(m_orientation==21) p = 2;
		if(m_orientation==23) p = 3; 
		if(m_orientation==19) p = 1;
		if(m_orientation==24) p = 2;
		if(m_orientation==22) p = 3; 
		if(m_orientation==25) p = 1;
		if(m_orientation==27) p = 2;
		if(m_orientation==29) p = 3; 
		if(m_orientation==26) p = 1;
		if(m_orientation==30) p = 2;
		if(m_orientation==28) p = 3; 
		if(m_orientation==34) p = 1;
		if(m_orientation==31) p = 2;
		if(m_orientation==36) p = 3; 
		if(m_orientation==32) p = 1;
		if(m_orientation==33) p = 2;
		if(m_orientation==35) p = 3; 
	}		
	
	return p;
	
}
	

BOOL CDragStatic::CheckSpinReset()
{
	BOOL r;
	r = m_reset;
	m_reset = FALSE;
	return r;
}
