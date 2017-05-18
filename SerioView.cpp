// SerioView.cpp : implementation of the CSerioView class
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "SerioDoc.h"
#include "math.h"

#include "SerioView.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_FONT_HT_INCHES .35


/////////////////////////////////////////////////////////////////////////////
// CSerioView

IMPLEMENT_DYNCREATE(CSerioView, CScrollView)

BEGIN_MESSAGE_MAP(CSerioView, CScrollView)
	//{{AFX_MSG_MAP(CSerioView)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerioView construction/destruction
extern CCalc scratchPad;
CSerioView::CSerioView()
{
	m_Coords.SetSize(40,4);
	int i;
	for(i=0;i<40; i++)
	{
		m_Coords[i] = 0;
	}
	m_userIsDragging = FALSE;
}

CSerioView::~CSerioView()
{
}

BOOL CSerioView::PreCreateWindow(CREATESTRUCT& cs)
{
		// TODO: Modify the Window class or styles here by modifying
		//  the CREATESTRUCT cs
	//cs.style &= WS_CHILD|WS_OVERLAPPEDWINDOW|WS_MAXIMIZE|FWS_ADDTOTITLE;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSerioView drawing

void CSerioView::OnDraw(CDC* pDC)
{
	m_userInteruptsDraw = FALSE;
	if(m_userIsDragging)//scroll bar
	{
		return;
	}

	BOOL mouseMessagePreExisted = FALSE;
	UINT flags = QS_KEY | QS_MOUSEBUTTON;
	DWORD msgs = GetQueueStatus(flags);
	//if(HIWORD(msgs)==(QS_KEY | HIWORD(msgs)))break;
	if(HIWORD(msgs)==(QS_MOUSEBUTTON | HIWORD(msgs)))
		mouseMessagePreExisted = TRUE;


	CSerioDoc* pDoc = GetDocument();
	if(!::scratchPad.m_firstInit)
	{
		pDoc->InitRegObject(pDoc);
		::scratchPad.m_firstInit = TRUE;
	}

	BOOL cChange=FALSE,rChange=FALSE,bChange=FALSE,cBChange=FALSE;
	BOOL cellCrunch = FALSE;
	m_rowEnd=FALSE;m_colEnd=FALSE;m_bRowEnd=FALSE;m_bColEnd=FALSE;
	m_cBRowEnd=FALSE;m_cBColEnd=FALSE;
	m_percent = FALSE;m_hex = FALSE;
	m_initialOnDrawCell = TRUE;


	if(!pDoc->m_dDlgInProcess)
	{
		pDoc->RegisterAspects();
		::scratchPad.LoadCalcMembers(pDoc);
	}
	//unsigned long lpDoc = ::scratchPad.m_pDoc;
	m_colorModel = pDoc->m_dColorMode;
	if(pDoc->m_strArray[10]=="percent (0 to 100)")m_percent = TRUE;
	if(pDoc->m_strArray[10]=="hexadecimal (00 to FF)")m_hex = TRUE;
	BOOL prn = pDC->IsPrinting();
	int xPic = 0;
	int yPic = 0;
	xPic = pDC->GetDeviceCaps(LOGPIXELSX);
	yPic = pDC->GetDeviceCaps(LOGPIXELSY);
	if(xPic>0 && yPic>0) ::scratchPad.SetScale(xPic,yPic);
	BOOL firstCall = m_firstCall2prn;
	if(prn)
	{
		if(!scratchPad.m_registered)
		{
			if(scratchPad.m_freePrintouts>9)
			{
				AfxMessageBox("PRINTING HAS BEEN DISABLED.  To print more charts, you can fully enable ProtoColor by purchasing an authorization code!  See User's.doc for more information.");
				return;
			}
			else
			{
				scratchPad.m_freePrintouts++;
				CWinApp* app = AfxGetApp();
				app->WriteProfileInt("ProtoColor1.0", "testCharts",scratchPad.m_freePrintouts);
			}
		}
		m_firstCall2prn = FALSE;
		int v_offset = pDC->GetDeviceCaps(PHYSICALOFFSETY);
		int h_offset = pDC->GetDeviceCaps(PHYSICALOFFSETX);
		if(h_offset!=0)
		{
			double hoff = h_offset / (double)xPic;
			::scratchPad.m_leftM = ::scratchPad.m_leftM - hoff;
			::scratchPad.m_rightM = ::scratchPad.m_rightM - hoff;
		}
		if(v_offset!=0)
		{
			double voff = v_offset / (double)yPic;
			::scratchPad.m_topM = ::scratchPad.m_topM - voff;
			::scratchPad.m_botM = ::scratchPad.m_botM - voff;
		}
	}
	else m_page = pDoc->m_dCurPage;
	//prepare color data
	StoreAxisColors();
	InitializeColorItems(m_page);//does not account for scrolling
	SetIndexFormatCodes(pDoc);
	ComputeIndexPositionRegion(pDC,prn);
	cellCrunch = DetectBumperToBumperCells();


	//calculate page
	int l,t,r,b;
	l = 0;
	t = 0;
	r = ::scratchPad.m_pageW * ::scratchPad.m_xppi;
	b = ::scratchPad.m_pageH * ::scratchPad.m_yppi;
	CRect pgRect = CRect(l,t,r,b);
	if(!prn &&!m_scrollBarInitDraw)DrawPaper(pDC,pgRect);
	m_scrollBarInitDraw = FALSE;

	//calculate & draw background over paper (but appears behind)
	CRect bkgRect = CRect(0,0,m_size.cx,m_size.cy);
	if(!prn)DrawBackground(pDC,bkgRect,pgRect);

	int pageXCells = ::scratchPad.GetPageCellCount(m_page);
	UINT cellsPerNormalPage = ::scratchPad.GetPageCellCount(1);
	UINT priorCells = 0;
	priorCells += (cellsPerNormalPage * (m_page - 1));
	pageXCells += priorCells;

	//reduce amount of drawing work for CSerioView (: CScrollView)
	::scratchPad.PassInScrollPosition(GetDeviceScrollPosition());
	CRect viewRect;
	if(!prn)
	{
		GetClientRect(&viewRect);
		::scratchPad.PassInViewSize(viewRect);
	}
	UINT count=0;
	UINT * pCount = &count;
	::scratchPad.FastForward(pCount,m_page);
	UpdateColorItems(m_page);//accounts for scrolling

	//if(pageXCells<10)
	//	AfxMessageBox("Less than ten cells");
		
	//feed coords as one long string
	BOOL earlyOut = FALSE;
	BOOL adv = FALSE;
	for( ; count<pageXCells;count++)
	{
		int i;
		for(i=0; i<4; i++)
		{ 
			if(i==3)
			{	
				adv = FALSE;
				if(::scratchPad.m_vCountC==1)
				{
					cChange = TRUE;
					TakeCoordinateSnapShot();
				}
				if(::scratchPad.m_hCountC==::scratchPad.m_colsPer)
					adv = TRUE;
				if(adv || earlyOut)
				{
					adv = FALSE;
					TakeCoordinateSnapShot();
					rChange = TRUE;
					if(::scratchPad.m_vCountC==::scratchPad.m_rowsPer)
						adv = TRUE;
					if(adv || earlyOut)
					{
						adv = FALSE;
						bChange = TRUE;
						ComputeBlockIndexPositioning(pDC);
						if(::scratchPad.m_CountB==
							::scratchPad.m_blockCount)
							adv = TRUE;
						if(adv || earlyOut)
						{
							cBChange = TRUE;
							ComputeCBlockIndexPositioning();
						}
					}
				}
			}
			m_Coords[i] = ::scratchPad.FeedCoords(count,m_page);
		}

		if(m_colorModel==0 || m_colorModel==1 || m_colorModel==2) //any
		{	
			int curSize = 0;
			int red = GetRedIntensity();
			int grn = GetGrnIntensity();
			int blu = GetBluIntensity();

			int OutlClr = pDoc->m_dOutlineClr;
			if(prn && (OutlClr<31 || OutlClr>34))
				AfxMessageBox("Invalid outline color!");
			COLORREF outl;
			if(OutlClr==31)outl = RGB(255,255,255);
			if(OutlClr==32)outl = RGB(0,0,0);
			if(OutlClr==33)outl = RGB(200,200,200);
			if(OutlClr==34)outl = RGB(red,grn,blu);
			if(cellCrunch && OutlClr==34)outl = RGB(255,255,255);

			COLORREF cellClr = RGB(red,grn,blu);
			 
			int w = 1;
			CPenObject po;
			po.SetColor(outl);
			po.SetWidth(w);
			po.SetStyle(PS_SOLID);	
			CPen pen;
			CPen* pOldPen;
			if(pen.CreatePenIndirect(&po.penOb))
			{
				pOldPen = 
					pDC->SelectObject(&pen);
				//DeleteObject();
			}
			CBrush* oldBr;
			CBrush br;
			if(br.CreateSolidBrush(cellClr));
			{
				oldBr = pDC->SelectObject(&br);
			}
			if(cChange){cChange=FALSE;DrawIndex(3,pDC,count);}
			if(rChange){rChange=FALSE;DrawIndex(1,pDC,count);}
			if(bChange){bChange=FALSE;DrawIndex(2,pDC,count);}
			if(cBChange){cBChange=FALSE;DrawIndex(4,pDC,count);}

			pDC->Rectangle(m_Coords[0],m_Coords[1],m_Coords[2],
				m_Coords[3]);

			pDC->SelectObject(pOldPen);
			pDC->SelectObject(oldBr);

			IncrementColor(m_page);

			//check for user scroll
			UINT flags = QS_KEY | QS_MOUSEBUTTON;
			DWORD msgs = GetQueueStatus(flags);
			//if(HIWORD(msgs)==(QS_KEY | HIWORD(msgs)))break;
			if(HIWORD(msgs)==(QS_MOUSEBUTTON | HIWORD(msgs)))
			{
				if(!mouseMessagePreExisted)
				{
					break;
				}
			}

			if(earlyOut)break;
			CPoint scrollPos = GetDeviceScrollPosition();
			if(m_Coords[0]>(scrollPos.x + viewRect.right) && 
				m_Coords[1]>(scrollPos.y + viewRect.bottom))
			{
				earlyOut = TRUE;
			}

		}//if(ColorModel==)
		
	}//for(count=0;;count++)
	
	if(pDoc->m_dShowPage)
	{
		CRect pgRect;
		pgRect.left = ((::scratchPad.m_pageW * ::scratchPad.m_xppi )* .5)
			- 15;
		pgRect.right = pgRect.left + 30;
		pgRect.top = ((::scratchPad.m_pageH - (::scratchPad.m_botM * .5))
			* ::scratchPad.m_yppi) - 7;
		pgRect.bottom = pgRect.top + 14;


		CString paginationStr = CString("page ");
		CString pageNumStr = CString("");
		char pageStr[15];
		std::stringstream ostr(pageStr,15);
		ostr << m_page;// << ends;
		pageNumStr.Format("%d",m_page);
		//pageNumStr = (CString)pageStr;
		paginationStr += pageNumStr;
		
		pDC->DrawText(paginationStr,&pgRect,DT_CENTER | DT_NOCLIP);
	}

	CSerioDoc* pDocum = GetDocument();
	ASSERT_VALID(pDocum);
	//pDoc->initRegObject();
	CObList &cellList =	pDocum->m_cellList;
	POSITION pos = cellList.GetHeadPosition();
	while (pos != NULL)
	{
		CCell* pCell = (CCell*)cellList.GetNext(pos);
		pCell->DrawCell(pDC);
	}
	//pDC->Rectangle(15,80,65,140);
	m_page++;
	//	m_ouldy = FALSE;
}

BOOL CSerioView::DetectBumperToBumperCells()
{
	//activates white outline color and/or reduction of indice size
	BOOL crunch = FALSE;
	double space;
	space = ::scratchPad.m_rowSpace;
	if(space<.009)crunch = TRUE;
	space = ::scratchPad.m_colSpace;
	if(space<.009)crunch = TRUE;
	m_horizCrowd = FALSE;
	if(space<(.25 * ::scratchPad.m_rectW))
	{
		m_horizCrowd = TRUE;
		m_safeReduct = 2;
		//double aug = .05;
		//aug = aug * ::scratchPad.m_rectW;
		//m_safeReduct = m_safeReduct + ((int)aug) + 1;
		m_safeReduct = m_safeReduct + 
			(7.5 * ((int)::scratchPad.m_rectW));
	}
	
	return crunch;
}

void CSerioView::TakeCoordinateSnapShot()
{
	m_top = ::scratchPad.TransformRect(2);
	m_bottom  = ::scratchPad.TransformRect(4);
	m_left = ::scratchPad.TransformRect(1);
	m_right = ::scratchPad.TransformRect(3);
	m_rowSpace = ::scratchPad.m_rowSpace * ::scratchPad.m_yppi;
	m_colSpace = ::scratchPad.m_colSpace * ::scratchPad.m_xppi;
	m_bColSpace = ::scratchPad.m_bColSpace * ::scratchPad.m_xppi;
	m_leftMarg = ::scratchPad.m_leftM * ::scratchPad.m_xppi;
	m_cBFrameX = ::scratchPad.m_cBlockFrame.x * ::scratchPad.m_xppi;
}

void CSerioView::ComputeBlockIndexPositioning(CDC* pDC)
{
	m_blockY = ::scratchPad.m_blockFrame.y * ::scratchPad.m_yppi;
	unsigned long leftMostBound;
	unsigned long rightSide = 
		(::scratchPad.m_blockFrame.x * ::scratchPad.m_xppi) - 2;
	if(::scratchPad.m_blockFrame.x!=::scratchPad.m_leftM)
		leftMostBound = 
		(::scratchPad.m_blockFrame.x * ::scratchPad.m_xppi)
		- (m_bColSpace - m_cellIndexSpaceHoriz);
	else leftMostBound = 0;

	m_bDex_sideNearBlock = rightSide;
	m_bDex_farSide = leftMostBound;
}

void CSerioView::ComputeCBlockIndexPositioning()
{
	const double SPACER = 0.025;
	double upperMostBound;
	double bottomSide;
	double flexibleRowSp = m_bRowSpAvail;
	double ax3DexPercent = .4;
	double fontRatio = (m_cFontHeight * 0.6) / m_cbFontHeight;
	double ratioDif = 0.0;

	//the actual font sizes used may not be requiring all the space...
	if(ax3DexPercent>fontRatio)
	{
		if(!m_ax3LineBr)ratioDif = ax3DexPercent - fontRatio;
		else
		{
			if(ax3DexPercent>(fontRatio * 5.0)) ratioDif = ax3DexPercent -
				(fontRatio * 5.0);
		}
	}
	flexibleRowSp -= (m_bRowSpAvail * ratioDif) / ax3DexPercent;

	double cBStartCoordY = ((::scratchPad.m_vCountCB - 1) *
		(::scratchPad.m_cBlockH + ::scratchPad.m_cBRowSpace)) + 
		::scratchPad.m_topM;
	if(cBStartCoordY!=::scratchPad.m_topM)
	{
		upperMostBound = cBStartCoordY - ::scratchPad.m_cBRowSpace;
		bottomSide = cBStartCoordY - (flexibleRowSp + SPACER);
	}
	else 
	{
		upperMostBound = 0;
		bottomSide = cBStartCoordY - (flexibleRowSp + SPACER);
	}
	bottomSide = bottomSide - SPACER;
	if(bottomSide<0)bottomSide = 0;

	m_cBDex_sideNearBlock = bottomSide * ::scratchPad.m_yppi;
	m_cBDex_farSide = upperMostBound * ::scratchPad.m_yppi;
}

void CSerioView::ComputeIndexPositionRegion(CDC* pDC,BOOL printg)
{
	unsigned long leftMostBound;
	unsigned long upperMostBound;

	//get prelimanary info
	m_leftMarg = ::scratchPad.m_leftM * ::scratchPad.m_xppi;
	m_topMarg = ::scratchPad.m_topM * ::scratchPad.m_yppi;
	m_botMarg = ::scratchPad.m_botM * ::scratchPad.m_yppi;
	m_rightMarg = ::scratchPad.m_rightM * ::scratchPad.m_xppi;
}

void CSerioView::DrawPaper(CDC* pDC, CRect pgR)
{
	int w = 1;
	CPenObject po;
	po.SetColor(RGB(255,255,255));
	po.SetWidth(w);
	po.SetStyle(PS_SOLID);	
	CPen pen;
	CPen* pOldPen;
	if(pen.CreatePenIndirect(&po.penOb))
	{
		pOldPen = 
			pDC->SelectObject(&pen);
		//DeleteObject();
	}
	CBrush* oldBr;
	CBrush br;
	if(br.CreateSolidBrush(RGB(255,255,255)));
	{
		oldBr = pDC->SelectObject(&br);
	}
	pDC->Rectangle(pgR);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(oldBr);
}

void CSerioView::DrawBackground(CDC* pDC, CRect bkgR, CRect pgR)
{
	BOOL pageNarrow = FALSE;
	BOOL pageShort = FALSE;
	CRect bottomRect,sideRect;
	bottomRect = CRect(bkgR);
	sideRect = CRect(bkgR);

	//calculate right side background
	if(pgR.right<bkgR.right)
	{
		pageNarrow = TRUE;
		sideRect.left = pgR.right;
	}
	if(pgR.bottom<bkgR.bottom)
	{
		pageShort = TRUE;
		bottomRect.top = pgR.bottom;
	}

	int w = 1;
	CPenObject po;
	po.SetColor(RGB(55,55,55));
	po.SetWidth(w);
	po.SetStyle(PS_SOLID);	
	CPen pen;
	CPen* pOldPen;
	if(pen.CreatePenIndirect(&po.penOb))
	{
		pOldPen = 
			pDC->SelectObject(&pen);
		//DeleteObject();
	}
	CBrush* oldBr;
	CBrush br;
	if(br.CreateSolidBrush(RGB(55,55,55)));
	{
		oldBr = pDC->SelectObject(&br);
	}
	if(pageShort)pDC->Rectangle(bottomRect);
	if(pageNarrow)pDC->Rectangle(sideRect);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(oldBr);
}
/////////////////////////////////////////////////////////////////////////////
// CSerioView printing

BOOL CSerioView::OnPreparePrinting(CPrintInfo* pInfo)
{
	UINT pageCount = ::scratchPad.GetPageCount();
	pInfo->SetMaxPage(pageCount);

	::scratchPad.SetScale(0,0);
	m_firstCall2prn = TRUE;

	BOOL rslt = FALSE;
	rslt = DoPreparePrinting(pInfo);
	
	m_startPrnPage = pInfo->GetFromPage();
	m_page = m_startPrnPage;
	return rslt;
}

/////////////////////////////////////////////////////////////////////////////
// CSerioView diagnostics

#ifdef _DEBUG
void CSerioView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSerioView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSerioDoc* CSerioView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSerioDoc)));
	return (CSerioDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSerioView message handlers


void CSerioView::GetNewCoords()
{

}

void CSerioView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{	
	int ColorModel;
	CSerioDoc* pDoc = GetDocument();
	ColorModel = pDoc->m_dColorMode;
	if(ColorModel==1)OnCMYKPrint(pDC,pInfo);
	
	
	CView::OnPrint(pDC, pInfo);
}

void CSerioView::OnCMYKPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if(m_firstCall2prn)m_ps = AfxMessageBox("Is the output device a PostScript printer?",MB_YESNO);

	//if(m_ps) generate Post-Script code here

	//CScrollView::OnPrint(pDC, pInfo);
}

void CSerioView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnBeginPrinting(pDC, pInfo);
}

void CSerioView::OnInitialUpdate() 
{
	CSize size = CSize(825,1070 );
	SetScrollSizes( MM_TEXT, 
		/*GetDocument()->GetDocSize()*/size);

	CView::OnInitialUpdate();
	
}

void CSerioView::IncrementColor(UINT page)
{
	UINT nuCount,curCount;
	int i;
	for(i=1;i<5;i++)
	{
		nuCount = ::scratchPad.GetCurrentCount(i,page);
		if(i==1)curCount = m_horzCounter;
		if(i==2)curCount = m_vertCounter;
		if(i==3)curCount = m_blockCounter;
		if(i==4)curCount = m_cBlockCounter;
		if(nuCount!=curCount)//test in case start colors == end colors
		{
			if(i==1)
			{
				m_horzColr = m_horzColr + m_horzInc;
				m_horzCounter = nuCount;
			}
			if(i==2)
			{
				m_vertColr = m_vertColr + m_vertInc;
				m_vertCounter = nuCount;
			}
			if(i==3)
			{
				m_blockColr = m_blockColr + m_blockInc;
				m_blockCounter = nuCount;
			}
			if(i==4)
			{
				m_cBlockColr = m_cBlockColr + m_cBlockInc;
				m_cBlockCounter = nuCount;
			}
			if(nuCount<curCount)ResetColorVal(i,nuCount);
		}
	}
}

void CSerioView::ResetColorVal(int axis,UINT count)
{
	if(axis==1){m_horzColr = m_horzStartColr;m_horzCounter = count;}
	if(axis==2){m_vertColr = m_vertStartColr;m_vertCounter = count;}
	if(axis==3){m_blockColr = m_blockStartColr;m_blockCounter = count;}
	if(axis==4){m_cBlockColr = m_cBlockStartColr;m_cBlockCounter = count;}
}

void CSerioView::InitializeColorItems(UINT page)
{
	CSerioDoc* pDoc = GetDocument();
	int start1,start2,start3,start4;
	double horzSteps, vertSteps,blockSteps,cBlockSteps;
	int val;
	//'N is for 'Normal'
	BOOL horzN = TRUE, vertN = TRUE, bIncN = TRUE, cBIncN = TRUE;
	
	CString s = pDoc->m_strArray[29];
	if(s=="the MAXIMUM value")horzN = FALSE;
	s = pDoc->m_strArray[30];
	if(s=="the MAXIMUM value")vertN = FALSE;
	s = pDoc->m_strArray[20];
	if(s=="the MAXIMUM value")bIncN = FALSE;
	s = pDoc->m_strArray[19];
	if(s=="the MAXIMUM value")cBIncN = FALSE;
	int cycle;
	for(cycle=1;cycle<5;cycle++)
	{
		BOOL max;
		int val1,val2,highVal,lowVal;
		if(cycle==1)
		{ max = horzN;val1 = pDoc->m_dSL2R;val2 = pDoc->m_dEL2R;
			horzSteps = (double)(pDoc->m_dColCount - 1);}
		if(cycle==2)
		{ max = vertN;val1 = pDoc->m_dST2B;val2 = pDoc->m_dET2B;
			vertSteps = (double)(pDoc->m_dRowCount - 1);}
		if(cycle==3)
		{ max = bIncN;val1 = pDoc->m_dSF2L;val2 = pDoc->m_dEF2L;
			blockSteps = (double)(pDoc->m_dBlockCount - 1);}
		if(cycle==4)
		{ max = cBIncN;val1 = pDoc->m_dSF2B;val2 = pDoc->m_dEF2B;
			cBlockSteps = (double)(pDoc->m_dCBlockCount - 1);}
			
		if(val1>val2){highVal = val1; lowVal = val2;}
		if(val1<=val2){lowVal = val1; highVal = val2;}

		if(max)val = lowVal;
		if(!max)val = highVal;

		BOOL inPercent=FALSE; 
		CString steps = pDoc->m_strArray[10];
		if(steps=="percent (0 to 100)")inPercent = TRUE;
	//	if(inPercent)ConvertFromPercent(lowVal);
	//	if(inPercent)ConvertFromPercent(highVal);

		if(cycle==1)
		{
			m_horzColr = (double)val;
			if(horzSteps!=0)m_horzInc = (highVal - lowVal)
				/ horzSteps;
			else m_horzInc = 0.0;
		}
		if(cycle==2)
		{
			m_vertColr = (double)val;
			if(vertSteps!=0)m_vertInc = (highVal - lowVal)
				/ vertSteps;
			else m_vertInc = 0.0;
		}
		if(cycle==3)
		{
			m_blockColr = (double)val;
			if(blockSteps!=0)m_blockInc = (highVal - lowVal)
				/ blockSteps;
			else m_blockInc = 0.0;
		}
		if(cycle==4)
		{
			m_cBlockColr = (double)val;
			if(cBlockSteps!=0)m_cBlockInc = (highVal - lowVal)
				/ cBlockSteps;
			else m_cBlockInc = 0.0;
		}
	}
	m_horzCounter = 1;
	m_vertCounter = 1;
	m_blockCounter = 1;
	m_cBlockCounter = 1;

	//Modify IncrementValues - if starting with max, incr is negative
	if(!horzN) m_horzInc = m_horzInc - (2 * m_horzInc);
	if(!vertN) m_vertInc = m_vertInc - (2 * m_vertInc);
	if(!bIncN) m_blockInc = m_blockInc - (2 * m_blockInc);
	if(!cBIncN) m_cBlockInc = m_cBlockInc * -1;
	
	//Modify StartPointValue for block or cBlock color
	int m_colorMode = ::scratchPad.m_colorMode;
	if(m_colorMode!=1)
	{
		UINT blocksPerPage = (pDoc->m_dBlockCols * pDoc->m_dBlockRows);
		double priorBlocks = (double)((page - 1) * blocksPerPage);
		m_blockColr = m_blockColr + (priorBlocks * m_blockInc);
		m_blockCounter += priorBlocks;
	}
	if(m_colorMode==1)
	{
		UINT cBlocksPerPage = (pDoc->m_dCBlockCols * pDoc->m_dCBlockRows);
		double priorCBlocks = (double)((page - 1) * cBlocksPerPage);
		m_cBlockColr = m_cBlockColr + (priorCBlocks	* m_cBlockInc);
		m_cBlockCounter += priorCBlocks;
	}
	m_horzStartColr = m_horzColr;
	m_vertStartColr = m_vertColr;
	m_blockStartColr = m_blockColr;
	m_cBlockStartColr = m_cBlockColr;
}

void CSerioView::UpdateColorItems(UINT page)
{
	CSerioDoc* pDoc = GetDocument();
	//'N is for 'Normal'
	BOOL horzN = TRUE, vertN = TRUE, bIncN = TRUE, cBIncN = TRUE;
	
	CString s = pDoc->m_strArray[29];
	if(s=="the MAXIMUM value")horzN = FALSE;
	s = pDoc->m_strArray[30];
	if(s=="the MAXIMUM value")vertN = FALSE;
	s = pDoc->m_strArray[20];
	if(s=="the MAXIMUM value")bIncN = FALSE;
	s = pDoc->m_strArray[19];
	if(s=="the MAXIMUM value")cBIncN = FALSE;

	UINT i = 1;
	for(i=1;i<::scratchPad.m_hCountC;i++)
	{
		m_horzColr += m_horzInc;
		m_horzCounter++;
	}
	for(i=1;i<::scratchPad.m_vCountC;i++)
	{
		m_vertColr += m_vertInc;
		m_vertCounter++;
	}
	for(i=1;i<::scratchPad.m_CountB;i++)
	{
		m_blockColr += m_blockInc;
		m_blockCounter++;
	}
	for(i=1;i<::scratchPad.m_CountCB;i++)
	{
		m_cBlockColr += m_cBlockInc;
		m_cBlockCounter++;
	}
}

int CSerioView::GetRGBColorVal(int nColor, int cellCount, int cell,
							   colorType c)
{
	int val = 0, red, blue, green;
	int axisCode;
	CSerioDoc* pDoc = GetDocument();
	int bCount = pDoc->m_dBlockCount;
	int colCount = pDoc->m_dColCount;
	int cBlkCount;
	int cpb,cpCb,cpc;
	int curAx;

	if(c==0) curAx = m_RedAxis;
	if(c==1) curAx = m_GreenAxis;
	if(c==2) curAx = m_BlueAxis;

	if(nColor==1)
	{
		cBlkCount = pDoc->m_dCBlockCount;
		axisCode = pDoc->m_dOrientation_1;
	}

	if(curAx==3)	//row left to right
	{
		cpCb = cellCount / cBlkCount;
		cpb = cpCb / bCount;
		val = 155;
	}

	if(curAx==1)	//col top to bottom
	{
		val = 200;
	}

	if(curAx==2)	//block first to last
	{
//		signed int steps;
//		start = GetStartColor(c);
///		end = GetEndColor(c);
//		steps = end - start;
//		if(steps<0) steps = -1 * steps;
		val = 100;
//		bCount;
	}

	if(curAx==4)	//cblock front to back
	{

	}

//	if(c==0) val = red;
//	if(c==1) val = blue;
//	if(c==2) val = green;

	return val;
}

void CSerioView::StoreAxisColors()
{	
	int oCode;
	CSerioDoc* pDoc = GetDocument();

	if(m_colorModel==0)
	{
		oCode = pDoc->m_dOrientation_0;
		m_RedAxis = RegionLUT(1,oCode);
		m_GreenAxis = RegionLUT(2,oCode);
		m_BlueAxis = RegionLUT(3,oCode);
	}
	if(m_colorModel==1)
	{ 
		oCode = pDoc->m_dOrientation_1;
		m_CyanAxis = RegionLUT(4,oCode);
		m_MagentaAxis = RegionLUT(5,oCode);
		m_YellowAxis = RegionLUT(6,oCode);
		m_BlackAxis = RegionLUT(7,oCode);
	}
	if(m_colorModel==2)
	{ 
		oCode = pDoc->m_dOrientation_2;
		m_CyanAxis = RegionLUT(4,oCode);
		m_MagentaAxis = RegionLUT(5,oCode);
		m_YellowAxis = RegionLUT(6,oCode);
	}
}

int CSerioView::GetRedIntensity()
{
	int value;
	if(m_colorModel==0)
	{
		if(m_RedAxis==1)value = m_vertColr;
		if(m_RedAxis==2)value = m_blockColr;
		if(m_RedAxis==3)value = m_horzColr;
		if(m_RedAxis==4)value = m_cBlockColr;
	}
	if(m_colorModel==1)
	{
		int bValue;
		if(m_BlackAxis==1)bValue = m_vertColr;
		if(m_BlackAxis==2)bValue = m_blockColr;
		if(m_BlackAxis==3)bValue = m_horzColr;
		if(m_BlackAxis==4)bValue = m_cBlockColr;

		if(m_CyanAxis==1)value = 255 - m_vertColr;
		if(m_CyanAxis==2)value = 255 - m_blockColr;
		if(m_CyanAxis==3)value = 255 - m_horzColr;
		if(m_CyanAxis==4)value = 255 - m_cBlockColr;

		value = ((255 - bValue) * value) / 255;
	}
	if(m_colorModel==2)
	{
		if(m_CyanAxis==1)value = 255 - m_vertColr;
		if(m_CyanAxis==2)value = 255 - m_blockColr;
		if(m_CyanAxis==3)value = 255 - m_horzColr;
	}
	return value;
}

int CSerioView::GetGrnIntensity()
{
	int value;
	if(m_colorModel==0)
	{
		if(m_GreenAxis==1)value = m_vertColr;
		if(m_GreenAxis==2)value = m_blockColr;
		if(m_GreenAxis==3)value = m_horzColr;
		if(m_GreenAxis==4)value = m_cBlockColr;
	}
	if(m_colorModel==1)
	{
		int bValue;
		if(m_BlackAxis==1)bValue = m_vertColr;
		if(m_BlackAxis==2)bValue = m_blockColr;
		if(m_BlackAxis==3)bValue = m_horzColr;
		if(m_BlackAxis==4)bValue = m_cBlockColr;

		if(m_MagentaAxis==1)value = 255 - m_vertColr;
		if(m_MagentaAxis==2)value = 255 - m_blockColr;
		if(m_MagentaAxis==3)value = 255 - m_horzColr;
		if(m_MagentaAxis==4)value = 255 - m_cBlockColr;

		value = ((255 - bValue) * value) / 255;
	}
	if(m_colorModel==2)
	{
		if(m_MagentaAxis==1)value = 255 - m_vertColr;
		if(m_MagentaAxis==2)value = 255 - m_blockColr;
		if(m_MagentaAxis==3)value = 255 - m_horzColr;
	}

	return value;
}

int CSerioView::GetBluIntensity()
{
	int value;
	if(m_colorModel==0)
	{
		if(m_BlueAxis==1)value = m_vertColr;
		if(m_BlueAxis==2)value = m_blockColr;
		if(m_BlueAxis==3)value = m_horzColr;
		if(m_BlueAxis==4)value = m_cBlockColr;
	}
	if(m_colorModel==1)
	{
		int bValue;
		if(m_BlackAxis==1)bValue = m_vertColr;
		if(m_BlackAxis==2)bValue = m_blockColr;
		if(m_BlackAxis==3)bValue = m_horzColr;
		if(m_BlackAxis==4)bValue = m_cBlockColr;

		if(m_YellowAxis==1)value = 255 - m_vertColr;
		if(m_YellowAxis==2)value = 255 - m_blockColr;
		if(m_YellowAxis==3)value = 255 - m_horzColr;
		if(m_YellowAxis==4)value = 255 - m_cBlockColr;

		value = ((255 - bValue) * value) / 255;
	}
	if(m_colorModel==2)
	{
		if(m_YellowAxis==1)value = 255 - m_vertColr;
		if(m_YellowAxis==2)value = 255 - m_blockColr;
		if(m_YellowAxis==3)value = 255 - m_horzColr;
	}
	return value;
}

int CSerioView::RegionLUT(int colorID, int cfgCode)
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

//////////////////////////////////////////////////////////////////////////
// Indices
void CSerioView::DrawIndex(int axis,CDC* pDC,UINT count)
{
	BOOL userForceLineBrk = FALSE,forAx3=TRUE;
	CSerioDoc* pDoc = GetDocument();
	int left,top,bot,right,peakHt;
	int *px = &left;
	int *py = &top;
	int *px2 = &right;
	int *py2 = &bot;
	int pointSize = 72;
	int * htReached = &peakHt;
	UINT format = DT_NOCLIP | DT_SINGLELINE;
	UINT purpFormat = format;
	if(m_initialOnDrawCell)DecideOnStyleAndFormatSizes();
	if(axis==1)
	{
		format = format | DT_LEFT;
		if(!m_ax1LineBr)format = format | DT_VCENTER;
		pointSize = m_cFontHeight;
		if(pDoc->m_userLineBrkPerRow)userForceLineBrk = TRUE;
		if(m_ax1LineBr)m_lineBr = TRUE;
		if(m_ax3LineBr)purpFormat = purpFormat ^ DT_SINGLELINE;
	}
	if(axis==3)
	{
		format = format | DT_CENTER;
		if(!m_ax3LineBr)format = format | DT_BOTTOM;
		pointSize = m_cFontHeight;
		if(pDoc->m_userLineBrkPerCol)userForceLineBrk = TRUE;
		if(m_ax3LineBr)m_lineBr = TRUE;
		if(m_ax1LineBr)purpFormat = purpFormat ^ DT_SINGLELINE;
	}
	if(axis==2)
	{
		format = format ^ DT_SINGLELINE;
		format = format | DT_RIGHT;
		pointSize = m_bFontHeight;
		if(pDoc->m_userLineBrkPerBlk)userForceLineBrk = TRUE;
		if(m_ax2LineBr)m_lineBr = TRUE;
	}
	if(axis==4 && ::scratchPad.m_colorMode!=1)return;
	if(axis==4)
	{
		if(!m_ax4LineBr)format = format | DT_BOTTOM;
		format = format ^ DT_NOCLIP;
		pointSize = m_cbFontHeight;
		if(pDoc->m_userLineBrkPerCBlk)userForceLineBrk = TRUE;
	}
	PlugInHorizontalCoords(px,px2,axis,userForceLineBrk);
	PlugInVerticalCoords(py,py2,axis,userForceLineBrk);
	if(m_lineBr && axis!=2)
	{
		format = format ^ DT_SINGLELINE;
	}
	CRect rec = CRect(*px,*py,*px2,*py2);

	CString str = CString("");

	str += GetIndexString(axis);
	str = CString(AddIndexValString(str,axis));
	if(m_percent)
	{
		if(m_lineBr)str += "\n%";
		else str += "%";
	}

	LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfHeight = pointSize;
	logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_MODERN;
	logFont.lfQuality = DEFAULT_QUALITY;
	strcpy(logFont.lfFaceName,"Arial");

	CFont fontObj;
	CFont* font = &fontObj;
	CFont* pOldFont;
	CRect ax3Rect;
	CRect ax1Rect;
	if(m_initialOnDrawCell)//strictly calculate and return to original status
	{
		UINT ax1Format = format;
		UINT ax3Format = format;
		m_initialOnDrawCell = FALSE;
		int lbuf,tbuf,bbuf,rbuf,perpAxis;
		CRect feedRectAx1,feedRectAx3,rec2;
		double maxHeight,maxAx1Ht; 
		lbuf = left;
		tbuf = top;
		rbuf = right;
		bbuf = bot;
		m_ax3HtReduct = 0;
		if(axis==1)
		{
			perpAxis = 3;
			maxAx1Ht = *py2 - *py;
			feedRectAx1 = CRect(rec);
			ax3Format = purpFormat;
		}
		else
		{
			perpAxis = 1;
			maxHeight = *py2 - *py;
			feedRectAx3 = CRect(rec);
			ax1Format = purpFormat;
		}
		PlugInHorizontalCoords(px,px2,perpAxis,userForceLineBrk);
		PlugInVerticalCoords(py,py2,perpAxis,userForceLineBrk);
		rec2 = CRect(*px,*py,*px2,*py2);
		if(axis==1)
		{
			maxHeight = *py2 - *py;
			feedRectAx3 = CRect(rec2);
		}
		else 
		{
			maxAx1Ht = *py2 - *py;
			feedRectAx1 = CRect(rec2);
		}
		if(maxHeight>maxAx1Ht)maxHeight = maxAx1Ht;
		m_cFontHeight = 0;
		double maxPixSz = CalcMaxPointSize() * ::scratchPad.m_yppi;
		if(maxPixSz>maxHeight)maxPixSz = 
			maxHeight;
		ax3Rect = CalcPointSize(feedRectAx3,logFont,font,pDC,maxPixSz,
			ax3Format,forAx3,htReached);
		int curHt;
		if(axis==3)curHt = rec.Height();
		else curHt = rec2.Height();
		if(*htReached<curHt)m_ax3HtReduct = curHt - *htReached;
		int psBuf = m_cFontHeight;
		ax1Rect = CalcPointSize(feedRectAx1,logFont,font,pDC,maxPixSz,
			ax1Format,FALSE,htReached);
		font->DeleteObject();
		if(psBuf<m_cFontHeight)m_cFontHeight = psBuf;
		if(m_horizCrowd && !m_ax1LineBr)m_cFontHeight = 
			m_cFontHeight - m_safeReduct;
		if(m_cFontHeight<1)m_cFontHeight = 1;
		logFont.lfHeight = m_cFontHeight;
		CalcBlockPointSize(2);
		CalcBlockPointSize(4);
		left = lbuf;
		top = tbuf;
		right = rbuf;
		bot = bbuf;
	}
	m_lineBr = FALSE;
	font->CreateFontIndirect(&logFont);
	pOldFont = pDC->SelectObject(font); 
	COLORREF oTC = pDC->GetTextColor();
	pDC->SetTextColor(RGB(0,0,0));
	if(axis==3)top = top + m_ax3HtReduct;
	rec = CRect(left,top,right,bot);
	pDC->DrawText(str,&rec,format);
	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(oTC);
}

void CSerioView::DecideOnStyleAndFormatSizes()
{
	double smallestMarginVertically;
	double smallestMarginHorizontally;

	//determine least of: top margin,CBlock row space, block row space
	smallestMarginVertically = ::scratchPad.m_topM;
	if(m_colorModel==1 && ::scratchPad.m_cBRowsPer>1)
	{
		if(smallestMarginVertically>::scratchPad.m_cBRowSpace)
			smallestMarginVertically = ::scratchPad.m_cBRowSpace;
	}
	if(smallestMarginVertically>::scratchPad.m_bRowSpace && ::scratchPad.m_bRowsPer>1)
		smallestMarginVertically = ::scratchPad.m_bRowSpace;

	//determine least of: right margin, CBlock col space, block col space
	smallestMarginHorizontally = ::scratchPad.m_rightM;
	if(m_colorModel==1 && ::scratchPad.m_cBColsPer>1)
	{
		if(smallestMarginHorizontally>::scratchPad.m_cBColSpace)
			smallestMarginHorizontally = ::scratchPad.m_cBColSpace;
	}
	if(smallestMarginHorizontally>m_bColSpAvail && ::scratchPad.m_bColsPer>1)
		smallestMarginHorizontally = ::scratchPad.m_bColSpace;

	const double VSPACER = 0.025;
	const double HSPACER = 0.04;

	//xAxisDexSpace is that space which separates the block/cells from
	//their relevant indices which increment along the x axis
	if(VSPACER<=(.25 * smallestMarginVertically))
		m_xAxisDexSpace = ::scratchPad.m_yppi * VSPACER;
	else m_xAxisDexSpace = 0;
	if(m_xAxisDexSpace>m_rowSpace)m_xAxisDexSpace = m_rowSpace;


	//m_yAxisDexSpace is that space which separates te block/cells from
	//their relevant indices which increment along the y axis
	if(HSPACER<=(.25 * smallestMarginHorizontally))
		m_yAxisDexSpace = ::scratchPad.m_xppi * HSPACER;
	else m_yAxisDexSpace = 0;
	if(m_yAxisDexSpace>m_colSpace)m_yAxisDexSpace = m_colSpace;

	m_smallestMarginHorizontally = smallestMarginHorizontally * ::scratchPad.m_xppi;
	m_smallestMarginVertically = smallestMarginVertically * ::scratchPad.m_yppi;


	BOOL tightRect=FALSE,tallRect=FALSE,bRowSpaceAvail=FALSE;
	BOOL bColSpaceAvail=TRUE;
	double bColSpAvail = ::scratchPad.m_bColSpace;
	double bRowSpAvail = ::scratchPad.m_bRowSpace;
	double outScopHSpAvail = ::scratchPad.m_topM;
	double outScopVSpAvail = ::scratchPad.m_rightM;
	if(m_colorModel==1)
	{
		if(::scratchPad.m_cBColsPer!=1 && outScopHSpAvail>
			::scratchPad.m_cBColSpace)
			outScopHSpAvail = ::scratchPad.m_cBColSpace;
		if(::scratchPad.m_cBRowsPer!=1 && outScopVSpAvail>
			::scratchPad.m_cBRowSpace)
			outScopVSpAvail = ::scratchPad.m_cBRowSpace;
	}
	if(outScopVSpAvail<bRowSpAvail || ::scratchPad.m_bRowsPer==1)
		bRowSpAvail = outScopVSpAvail;
	if(outScopHSpAvail<bColSpAvail || ::scratchPad.m_bColsPer==1)
		bColSpAvail = outScopHSpAvail;

	//deduct for cblock index space
	if(m_colorModel==1)bRowSpAvail = bRowSpAvail * .4;//60% for cB index

	//set defaults
	m_ax1LineBr = FALSE;
	m_ax2LineBr = TRUE;
	m_ax3LineBr = FALSE;
	m_ax4LineBr = FALSE;

	//examine spatial factors
	if(::scratchPad.m_rectW<.15)tightRect = TRUE;
	if((::scratchPad.m_rectW * 1.4)<=bRowSpAvail)
		bRowSpaceAvail = TRUE;
	if(bColSpAvail<.2)bColSpaceAvail = FALSE;
	if((::scratchPad.m_rectH * 1.4)>bColSpAvail)tallRect = TRUE;

	//evaluate results
	if(tightRect && bRowSpaceAvail)m_ax3LineBr = TRUE;
	if(!bColSpaceAvail && tallRect)m_ax1LineBr = TRUE;
	//determine DrawText rectangle: (ie, the sides that do not 
	//directly correspond to the cell dimensions) from within the
	// DrawText/DT_CALCRECT loop

	m_bRowSpAvail = bRowSpAvail;
	m_bColSpAvail = bColSpAvail;
}

void CSerioView::PlugInVerticalCoords(int* top,int* bot,
									  int IncrDimension,
									  BOOL forceLineBrk)
{
	const double SPACER = 0.025;

	if(IncrDimension==1)//row indices showing vertical change in color
	{
		*top = m_top;
		*bot = m_bottom;
	}
	if(IncrDimension==2) //block indices
	{
		*top = m_blockY;
		*bot = 	m_blockY + (::scratchPad.m_blockH *
			 ::scratchPad.m_yppi);
	}
	if(IncrDimension==3)
	{
		*bot = m_top - m_xAxisDexSpace;
		*top = m_top - m_smallestMarginVertically;

		if(m_ax3LineBr)
		{
		}
	}
	if(IncrDimension==4)
	{
		double bottomSide,upperBound;
		*bot = m_cBDex_sideNearBlock;
		*top = m_cBDex_farSide;
	}
}

void CSerioView::PlugInHorizontalCoords(int* left,int* right,
										int IncrDimension,
										BOOL forceLineBrk)
{
	if(IncrDimension==1)
	{
		*left = m_right + m_yAxisDexSpace;
		*right = *left + ((m_bColSpAvail * 0.6) * ::scratchPad.m_xppi);
			//m_cellIndexHorExtent
	}
	if(IncrDimension==2) //block or C-Block depending
	{
		*left = m_bDex_farSide;
		*right = m_bDex_sideNearBlock - m_yAxisDexSpace;
	}
	if(IncrDimension==3)
	{
		*left = m_left;
		*right = m_right;
		m_cellIndexSpaceHoriz = *right - *left;
	}
	if(IncrDimension==4)
	{
		*left = m_cBFrameX;
		*right = m_right;
	}
}

double CSerioView::CalcMaxPointSize()
{
	const double sqrtStdPageArea = 9.669539;
	double maxFontHt = MAX_FONT_HT_INCHES;//in inches
	double pageArea = ::scratchPad.m_pageH * ::scratchPad.m_pageW;
	if(pageArea!=93.5)maxFontHt = (pageArea * maxFontHt)
		/ sqrtStdPageArea;
	return maxFontHt;
}

CRect CSerioView::CalcPointSize(CRect rect,LOGFONT logFont,CFont* font,
							   CDC * pDC,double maxPixSize,UINT format,
							   BOOL forAx3,int* largestHt)
{
	BOOL lineBr = FALSE;
	const int minPixSz = 5;
	m_cFontHeight = minPixSz;
	int maxPixSz = maxPixSize;
	int validHtBuf;
	*largestHt = 0;
	BOOL noCreate = FALSE;
	CFont* pOldFont;
	CRect calcRect = CRect(rect);
	CRect copyRect;
	CRect copyMaxR;
	CString tstStr;//to size bounding rect to largest needed size

	if((forAx3 && m_ax3LineBr)||(!forAx3 && m_ax1LineBr))
	{
		if(!m_percent)tstStr += "M\n2\n5\n5";
		else tstStr += "M100%";
		lineBr = TRUE;
	}
	else 
	{
		if(!m_percent)tstStr += "M255";
		else tstStr += "M100%";
	}
	format = format | DT_CALCRECT;
	BOOL maxReached = FALSE;
	BOOL maxPixSzRunWorked = FALSE;
	do
	{
		if(maxReached)maxPixSzRunWorked = TRUE;
		copyRect = CRect(calcRect);
		validHtBuf = *largestHt;
		m_cFontHeight += 1;
		if(m_cFontHeight>=maxPixSz && !maxReached)
		{
			m_cFontHeight = maxPixSz;
			copyMaxR = CRect(calcRect);
			maxReached = TRUE;
			break;
		}

		logFont.lfHeight = m_cFontHeight;  
		if (font->CreateFontIndirect(&logFont))
			pOldFont = pDC->SelectObject(font);
		else {AfxMessageBox("Error creating CFont via logFont object");
			noCreate = TRUE;}
		int hResult = pDC->DrawText(tstStr,&calcRect,format);
		if(hResult>*largestHt)*largestHt = hResult;
		if(!noCreate)
		{
			pDC->SelectObject(pOldFont);
			font->DeleteObject();
		}
	}
	while(rect==(calcRect | rect));	
	if(m_cFontHeight>2 && m_cFontHeight!=maxPixSz)
		m_cFontHeight = m_cFontHeight - 1;

	*largestHt = validHtBuf;

	if(maxReached && maxPixSzRunWorked)
	{
		copyRect = CRect(copyMaxR);
		m_cFontHeight = maxPixSz;
	}
	m_cellIndexHorExtent = copyRect.right - copyRect.left;
	return copyRect;
}
	
void CSerioView::CalcBlockPointSize(int asp)
{
	//max point size based on MAX_FONT_HT_INCHES inches high per 93.5 square inches
	//sq rt of 8.5 * 11 corresponds to MAX_FONT_HT_INCHES 
	
	const double sqrtStdPageArea = 9.669539;//square root of std page area
	double maxFontHt = MAX_FONT_HT_INCHES;
	double pageArea = ::scratchPad.m_pageH * ::scratchPad.m_pageW;
	double pageWeight = sqrt(pageArea);
	if(pageArea!=93.5)maxFontHt = (pageWeight * maxFontHt)
		/ sqrtStdPageArea;
	double cellWeight = 
		sqrt(::scratchPad.m_rectW * ::scratchPad.m_rectH);
	double blockWeight;
	if(asp==2)blockWeight = sqrt(::scratchPad.m_blockW * 
		::scratchPad.m_blockH);
	if(asp==4)blockWeight = sqrt(::scratchPad.m_cBlockW *
		::scratchPad.m_cBlockW);

	//assumes MM_TEXT default mode 
	//and that .lfHeight of LOGFONT is 1 to 1 with device unites (ie, pixels)
	//based on online MSDN calculation:
	//"lfHeight = -MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);"
	if(::scratchPad.m_yppi==0)return;
	double dcFontHt = m_cFontHeight;
	double yppi = ::scratchPad.m_yppi;
	double cellFontInchesHt = dcFontHt / yppi;
	if(cellFontInchesHt>=maxFontHt)
	{
		m_bFontHeight = (maxFontHt * ::scratchPad.m_yppi);
		m_cbFontHeight = m_bFontHeight;
		return;
	}
	//figure new block indice point size
	ASSERT(pageWeight>=blockWeight);
	double diff = 0;
	if(blockWeight>cellWeight)diff = blockWeight - cellWeight;
	double wtRange = 0;
	if(pageWeight>cellWeight)wtRange = pageWeight - cellWeight;
	double blockRate = 0;
	if(wtRange>0)blockRate = diff / wtRange;
	int htRange;
	if(m_cFontHeight<=(maxFontHt * ::scratchPad.m_yppi))
		htRange = (maxFontHt * ::scratchPad.m_yppi) - m_cFontHeight;
	else htRange = 0;
	int h = m_cFontHeight + (htRange * blockRate);
	if(asp==2)m_bFontHeight = h;
	if(asp==4)m_cbFontHeight = h;
}


CString CSerioView::GetIndexString(int axis)
{
	CString str;
	if(!m_lineBr && !m_abb)
	{
		if(m_BlueAxis==axis)str += "BLUE";
		if(m_GreenAxis==axis)str += "GREEN";
		if(m_RedAxis==axis)str += "RED";
	}
	if(m_lineBr && !m_abb)
	{
		if(m_BlueAxis==axis)str += "B\nL\nU\nE";
		if(m_GreenAxis==axis)str += "G\nR\nE\nE\nN";
		if(m_RedAxis==axis)str += "R\nE\nD";
	}
	if(m_lineBr && m_abb)
	{
		if(m_colorModel==0)
		{
			if(m_BlueAxis==axis)str += "B\n";
			if(m_GreenAxis==axis)str += "G\n";
			if(m_RedAxis==axis)str += "R\n";
		}
		else
		{
			if(m_CyanAxis==axis)str += "C\n";
			if(m_MagentaAxis==axis)str += "M\n";
			if(m_YellowAxis==axis)str += "Y\n";
			if(m_BlackAxis==axis)str += "K\n";
		}
	}
	if(!m_lineBr && m_abb)
	{
		if(m_colorModel==0)
		{
			if(m_BlueAxis==axis)str += "B ";
			if(m_GreenAxis==axis)str += "G ";
			if(m_RedAxis==axis)str += "R ";
		}
		else
		{
			if(m_CyanAxis==axis)str += "C ";
			if(m_MagentaAxis==axis)str += "M ";
			if(m_YellowAxis==axis)str += "Y ";
			if(m_BlackAxis==axis)str += "K ";
		}
	}
	
	return str;
}

CString CSerioView::AddIndexValString(CString str,int codAx)
{
	int val=0,v1s=0,v10s=0,v100s=0;
	int base,baseSq;
	if(m_hex){base = 16;baseSq = 256;}
	else {base = 10;baseSq = 100;}
	if(codAx==1)val = m_vertColr;
	if(codAx==2)val = m_blockColr;
	if(codAx==3)val = m_horzColr;
	if(codAx==4)val = m_cBlockColr;
	if(m_percent)val = GetRounded ((float)val * 0.392156);
	if(m_lineBr)
	{
		v1s = val % base;
		v10s = (val % baseSq) / base;
		v100s = val / baseSq;
	}
	char s[15] = {0};
	char s10[15] = {0};
	char s100[15] = {0};
	std::stringstream ostr(s,15);
	std::stringstream ostr10(s10,15);
	std::stringstream ostr100(s100,15);
	CString txt,txt2,txt3;
	if(!m_lineBr && !m_hex)txt.Format("%d",val);// = (CString)s;
	if(!m_lineBr && m_hex)txt = (CString)s;
	if(m_lineBr && !m_hex) 
	{
		ostr << v1s;// << ends;
		txt.Format("%d",v1s);// = (CString)s;
		ostr10 << v10s;// << ends;
		txt2.Format("%d",v10s); // = (CString)s10;
		ostr100 << v100s;// << ends; 
		txt3.Format("%d",v100s); // = (CString)s100;
	}
	if(m_lineBr && m_hex)
	{
		ostr << m_hex << v1s;// << ends;
		txt.Format("%d",v1s); // = (CString)s;
		ostr10 << m_hex << v10s;// << ends;
		txt2.Format("%d",v10s); // = (CString)s10;
		ostr100 << m_hex << v100s;// << ends;
		txt3.Format("%d",v100s); // = (CString)s100;
	}

	if(!m_lineBr)str += txt;
	else
	{
		if(v100s!=0)
		{
			str += txt3;
			str += CString("\n");
		}
		if(v10s!=0 || v100s!=0)
		{
			str += txt2;
			str += CString("\n");
		}
		str += txt;
	}
	return str;
}

int CSerioView::GetRounded(float fig)
{
	float f = fig;
	int val;
	for( ;f>=1; )
	{
		f = f - 1;
	}
	val = (int)fig;
	if(f>=0.5)val++;

	return val;
}


void CSerioView::SetIndexFormatCodes(CSerioDoc* pDoc)
{
	m_abb = TRUE;
	m_lineBr = FALSE;
	if(pDoc->m_dColorMode!=1)
	{
		//m_perc = FALSE;
	}
	else
	{
		//m_perc = TRUE;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CColorTag

IMPLEMENT_DYNCREATE(CColorTag, CCmdTarget)

CColorTag::CColorTag()
{
}

CColorTag::~CColorTag()
{
}


BEGIN_MESSAGE_MAP(CColorTag, CCmdTarget)
	//{{AFX_MSG_MAP(CColorTag)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSerioView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CSerioDoc* pDoc = GetDocument();
	//m_size = CSize(825,1070);
	m_size = CSize(((pDoc->m_dPageWidth +1) * 96),
		((pDoc->m_dPageHeight+1) * 96));
	SetScrollSizes(MM_TEXT, m_size);
	CView::OnUpdate(pSender,lHint,pHint);
}


void CSerioView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRect blankRegion;
	CPoint sPos;
	CSize sSize;

	if((nSBCode!=SB_THUMBTRACK)&&(nSBCode!=SB_THUMBPOSITION))
	{
		if(m_userIsDragging)
		{
			m_userIsDragging = FALSE;
		}
	}
	else 
	{
		m_userIsDragging = TRUE;
	}

	m_scrollBarInitDraw = TRUE;
	m_userInteruptsDraw = TRUE;

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);

	int minSR,maxSR;
	GetClientRect(&blankRegion);
	sPos = GetScrollPosition();
	GetScrollRange(SB_VERT,&minSR,&maxSR);

	if(nSBCode==SB_LINEDOWN)blankRegion.top = blankRegion.bottom - 
		(maxSR / 100);
	if(nSBCode==SB_PAGEDOWN)blankRegion.top = blankRegion.bottom - 
		(maxSR / 10);
	if(nSBCode==SB_LINEUP)blankRegion.bottom = maxSR / 100;
	if(nSBCode==SB_PAGEUP)blankRegion.bottom = maxSR / 10;
	if(!m_userIsDragging)InvalidateRect(blankRegion,FALSE);

}

void CSerioView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRect blankRegion;
	CPoint sPos;
	CSize sSize;

	if((nSBCode!=SB_THUMBTRACK)&&(nSBCode!=SB_THUMBPOSITION))
	{
		if(m_userIsDragging)
		{
			m_userIsDragging = FALSE;
			
		}
	}
	else 
	{
		m_userIsDragging = TRUE;
	}
	
	m_scrollBarInitDraw = TRUE;
	m_userInteruptsDraw = TRUE;

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);

	int minSR,maxSR;
	GetClientRect(&blankRegion);
	GetScrollRange(SB_HORZ,&minSR,&maxSR);
	if(nSBCode==SB_LINERIGHT)blankRegion.left = blankRegion.right - 
		(maxSR / 100);
	if(nSBCode==SB_PAGERIGHT)blankRegion.left = blankRegion.right - 
		(maxSR / 10);
	if(nSBCode==SB_LINELEFT)blankRegion.right = maxSR / 100;
	if(nSBCode==SB_PAGELEFT)blankRegion.right = maxSR / 10;
	if(!m_userIsDragging)InvalidateRect(blankRegion,FALSE);

}
