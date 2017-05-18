// Calc.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "RetractDlg.h"
#include "Registrar.h"
#include "Maestro.h"
#include "Bellows.h"
#include "ProgressBar.h"
#include "ToggleManager.h"
#include <sstream>
#include "SerioDoc.h"
#include "MessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MINCELL 0.03
#define MINBLK 0.07
#define MINCBLK 0.1
#define RGSZ 35
#define SHELFSZ 46
#define FLGSTORESZ 34
#define JACK_FAILURE 1
#define QUEEN_FAILURE 2
#define JACK_COUNT_IN_HOUSE_FAILURE 8
#define POST_COUNT_DENIAL 1
#define ADJUST_CYCLE 2


/////////////////////////////////////////////////////////////////////////////
// CCalc

IMPLEMENT_DYNCREATE(CCalc, CCmdTarget)


CCalc::CCalc()
{
	m_registered = FALSE;
	m_freePrintouts = 0;
	m_freeFiles = 0;
	changingOfTheGuard = FALSE;
	m_backSideMargChangeAtForRect = FALSE;
	m_arker = 1; //control variable in sync with coord - FeedCoords()
	cs1 = CString("\n\t- DERIVE COUNTS IS ENABLED ");
	cs2 = CString("\n\t- SIMULTANEOUS CHANGE REQUESTS IN\n\t    CONFLICT ");
	cs3 = CString("\n\t- CERTAIN SIZE ASPECTS ARE\n\t    LOCKED ");
	cs4 = CString("\n\t- CONSTRAINED RATIO ");
	cs5 = CString("\n\t- PAGE SIZE TOO SMALL ");
	cs6 = CString("\nA requested change was blocked because of the following conditions:\n");
	cs7 = CString("\n\nWould you like to make the maximum possible change?\n");
	cs8 = CString("\n\t- OUTER MARGINS ARE LOCKED ");
	cs9 = CString("\n\t- PAGE SIZE IS LOCKED ");
	cs10 = CString("\n\t- NORMAL CHART CONSTRAINTS\n\t    CONTRIBUTED TO AN UNSUCCESSFUL OUTCOME   \n");
	cs11 = CString("\n\t- ROW OR COLUMN COUNT OF \"1\" WAS\n\t    INVOLVED ");
	cs12 = CString("\n\t- A CERTAIN QUANTITY SETTING\n\t    IS LOCKED ");
	cs13 = CString("\n\t- A FREQUENCY OF DRAWN CELLS\n\t    IS BEING IMPOSED ");
	cs14 = CString("\n\t- COLOR RANGE EXTREMES ARE IMMOVABLE ");
	cs15 = CString("\n\t- A RESULTING VALUE DOES NOT FALL\n\t    WITHIN AN ACCEPTABLE COLOR RANGE ");
	cs16 = CString("\n\t- A MINIMUM SIZE FOR CELLS OR BLOCKS\n\t    WAS AN ISSUE ");
	cs17 = CString("\n\t- A CURRENT SETTING PROHIBITS THE\n\t    USE OF FRACTIONS FOR COLOR STEPS ");
	cs18 = CString("\n\t- COLOR RANGES ARE LOCKED ");
	cs19 = CString("\n\t- A CURRENT SETTING PROHIBITS ALTERATION\n\t    OF COLOR RANGE VALUES INDIRECTLY ");
	cs20 = CString("\n\t- A RESULTING COLOR RANGE VALUE WAS NOT\n\t    AN INTEGER\n\t ");
	cs21 = CString("\n\t- THE CURRENT CONFIGURATION REQUIRES A\n\t    MINIMUM NUMBER OF PAGES\n\t ");
	cs22 = CString("\n\t- COLOR RANGE EXTREMES COULD NOT\n\t    ACCOMODATE THIS PARTICULAR LARGE\n\t    NON-INTEGER FREQUENCY REQUEST ");
}

CCalc::~CCalc()
{
}


BEGIN_MESSAGE_MAP(CCalc, CCmdTarget)
	//{{AFX_MSG_MAP(CCalc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalc message handlers

CRegAspect* CCalc::SetContext(int nCode, float fCode,
		BOOL lockState, int member, CRegAspect* entry)
{	
	if(member==1) entry->m_nCode = nCode;
	if(member==2) entry->m_nType = nCode;
	//if(member==3) entry->m_fixed = lockState; //IDC_LOCKED21
	if(member==4) entry->m_locked = lockState;
	//if(member==5) entry->m_space = lockState;
	if(member==6) entry->m_horiz = lockState;
	if(member==7) entry->m_fixedRatio = lockState;
	if(member==8) entry->m_instigating = lockState;
	//if(member==9) entry->m_colorRanLock = lockState;
	if(member==10)entry->m_alt = lockState;
	//if(member==11)entry->m_surveyed = lockState;
	if(member==12)entry->m_nCount = nCode;
	if(member==13)entry->m_nSize = fCode;
	return entry;
}

BOOL CCalc::LoadCalcMembers()
{
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	return LoadCalcMembers(pDoc);
}


BOOL CCalc::LoadCalcMembers(CDocument* pDocument)	// assigns important values
{
	CSerioDoc* pDoc = (CSerioDoc*)pDocument;
	m_colorMode = pDoc->m_dColorMode;
	m_calcIntent = pDoc->m_dCalcIntent;
	m_cmyk = FALSE;
	if(m_colorMode==1)m_cmyk = TRUE;
	m_derivePages = pDoc->m_flags[23];
	CRegAspect* line;
	line = m_reg[18];
	m_virtPageH = line->m_nSize;
	line = m_reg[17];
	m_virtPageW = line->m_nSize;
	line = m_reg[16];
	m_pageH = line->m_nSize;
	line = m_reg[6];
	m_pageW = line->m_nSize;
	line = m_reg[9];
	m_cBlockH = line->m_nSize;
	line = m_reg[2];
	m_cBlockW = line->m_nSize;
	line = m_reg[8];
	m_blockH = line->m_nSize;
	line = m_reg[1];
	m_blockW = line->m_nSize;
	line = m_reg[7];
	m_rectH = line->m_nSize;
	line = m_reg[0];
	m_rectW = line->m_nSize;
	line = m_reg[10];
	m_topM = line->m_nSize;
	line = m_reg[11];
	m_botM = line->m_nSize;
	line = m_reg[3];
	m_leftM = line->m_nSize;
	line = m_reg[4];
	m_rightM = line->m_nSize;
	line = m_reg[12];
	m_rowsPer = line->m_nCount;
	line = m_reg[5];
	m_colsPer = line->m_nCount;
	line = m_reg[13];
	m_blockCount = line->m_nCount;	//blocks per document == steps
	line = m_reg[14];
	m_cBlockCount = line->m_nCount;	//cBlocks per document == steps
	//if(m_instigatorCount==99)m_totalCells = pDoc->m_dCellCount;
	if(m_colorMode==1)m_totalCells = m_rowsPer * m_colsPer * m_blockCount *
		m_cBlockCount;
	else m_totalCells = m_rowsPer * m_colsPer * m_blockCount;

	m_totalPages = pDoc->m_dPageCount;

	m_xppi = 96; //default
	m_yppi = 96; //default
	m_instigatorCount = 0;
	m_carryOutFrAdjOnly = FALSE;

	//Conglomerate block rows & spacing
	//m_cBRowsPer refers to the cBlock columns per page regardless
	//of how many pages multiply the columns
	line = m_reg[22];
	m_cBRowsPer = line->m_nCount;//per page
	if(m_cBRowsPer>1) 
	{
		double areaV = m_pageH - (m_topM + m_botM);
		double space = areaV -
			((double)m_cBRowsPer * m_cBlockH);
		m_cBRowSpace = space /(m_cBRowsPer - 1); 
	}
	if(m_cBRowsPer==1) m_cBRowSpace = m_virtPageH - m_cBlockH;
	
	if(m_cBRowsPer<1) AfxMessageBox(
	"corrupted data, start a new document or open another file");


	//block rows & spacing per conglomerate block
	line = m_reg[20];
	m_bRowsPer = line->m_nCount;
	if(m_bRowsPer>1)
	{
		double space;
		if(m_cmyk)space = m_cBlockH - (m_bRowsPer * m_blockH);
		if(!m_cmyk)	space = m_virtPageH - (m_bRowsPer * m_blockH);
		m_bRowSpace = space / (m_bRowsPer - 1);
	}
	if(m_bRowsPer==1)
	{
		if(m_cmyk)m_bRowSpace = m_virtPageH - m_blockH;
		if(!m_cmyk) m_bRowSpace = m_cBlockH - m_blockH;
	}
	if(m_bRowsPer<1) AfxMessageBox(
		"corrupted file, start a new document or open another file");

	// row spacing
	double space;
	space = m_blockH - (m_rectH * m_rowsPer); 
	if(m_rowsPer>1) m_rowSpace = space / (m_rowsPer - 1);
	if(m_rowsPer==1) m_rowSpace = space;
	if(m_rowsPer<1)  AfxMessageBox(
		"corrupted file, start a new document or open another file");

	//conglomerate block columns and spacing
	//m_cBColsPer refers to the cBlock columns per page regardless
	//of how many pages multiply the columns
	line = m_reg[21];
	m_cBColsPer = line->m_nCount;	
	if(m_cBColsPer>1) 
	{
		double areaH = m_pageW - (m_leftM + m_rightM);
		double space = areaH -
			((double)m_cBColsPer * m_cBlockW);
		m_cBColSpace = space /(m_cBColsPer - 1); 
	}
	if(m_cBColsPer==1) m_cBColSpace = 0;
	
	if(m_cBColsPer<1) AfxMessageBox(
	"corrupted data, start a new document or open another file");


	//block columns & spacing per conglomerate block
	line = m_reg[19];
	m_bColsPer = line->m_nCount;
	if(m_bColsPer>1)
	{
		double space;
		if(m_cmyk)space = m_cBlockW - (m_bColsPer * m_blockW);
		if(!m_cmyk)	space = m_virtPageW - (m_bColsPer * m_blockW);
		m_bColSpace = space / (m_bColsPer - 1);
	}
	if(m_bColsPer==1)
	{
		if(m_cmyk)m_bColSpace = m_cBlockW - m_blockW;
		if(!m_cmyk) m_bColSpace = m_virtPageW - m_blockW;
	}
	if(m_bColsPer<1) AfxMessageBox(
		"corrupted file, start a new document or open another file");

	// column spacing
	space = m_blockW - (m_rectW * m_colsPer); 
	if(m_colsPer>1) m_colSpace = space / (m_colsPer - 1);
	if(m_colsPer==1) m_colSpace = space;
	if(m_colsPer<1)  AfxMessageBox(
		"corrupted file, start a new document or open another file");

	return TRUE;
}


int CCalc::GetSize(void)
{
	int s = 0;

	return s;
}

BOOL CCalc::IsPageWSmaller(int nAspCode)
{
	BOOL f = TRUE;
	double areaH = ((m_pageW - m_leftM) - m_rightM);
	if(nAspCode==0)		//check block
		if(areaH>=m_blockW) f = FALSE;
	if(nAspCode==1)		//check c-block
		if(areaH>=m_cBlockW) f = FALSE;
	if(nAspCode==2)		//check virtual page
		if(areaH>=0) AfxMessageBox(
		"Data is corrupted: Virtual Frame not installed");
	return f;
}

BOOL CCalc::IsPageHSmaller(int nAspCode)
{
	BOOL f = TRUE;
	double areaV = ((m_pageH - m_topM) - m_botM);
	if(nAspCode==0)		//check block
		if(areaV>=m_blockH) f = FALSE;
	if(nAspCode==1)		//check c-block
		if(areaV>=m_cBlockH) f = FALSE;
	if(nAspCode==2)		//check virtual page
		if(areaV>=0) AfxMessageBox(
		"Data is corrupted: Virtual Frame not installed");

	return f;
}

UINT CCalc::GetPageCount()
{	
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	UINT count = pDoc->m_dPageCount;
	return count;
}


UINT CCalc::GetPageCellCount(UINT nPage)
{
	UINT cellCount,bCells,blocksPer,cBlocksPer,cellTot,pageTot;
	UINT pageCount;
	//figure actual cells per block
	bCells = m_colsPer * m_rowsPer;	//actual

	//figure actual number of c-blocks per page
	UINT potential = m_cBColsPer * m_cBRowsPer;	//potentially per page
	if(m_cBlockCount>=potential) cBlocksPer = potential;
	if(m_cBlockCount<potential) cBlocksPer = m_cBlockCount; 

	//figure actual blocks per c-block
	potential = m_bColsPer * m_bRowsPer;	//potentially per page
	if(m_blockCount>=potential) blocksPer = potential;
	if(m_blockCount<potential) blocksPer = m_blockCount;

	//CSerioDoc* pDoc = CSerioDoc::GetDoc();
	cellTot = m_totalCells;//pDoc->m_dCellCount;
	pageTot = m_totalPages;//pDoc->m_dPageCount;

	UINT normCellCount = cBlocksPer * blocksPer * bCells;
	UINT normPages = m_totalCells / normCellCount;
	UINT remCellCount = m_totalCells - (normCellCount * normPages);
	UINT neededPages;
	if(remCellCount==0)neededPages = normPages;
	else neededPages = normPages + 1;

	if(nPage<=normPages) cellCount = normCellCount;
	if(nPage==(normPages + 1)) cellCount = remCellCount;
	if(nPage>neededPages)cellCount = 0;
	
	return cellCount;
}


double CCalc::GetNextSpacingVal(BOOL bDim, int cycle)
{
	double space;/*
	if(cycle==1 && bDim) space = m_colSpace;
	if(cycle==2 && bDim) space = m_bColSpace;
	if(cycle==3 && bDim) space = m_cBColSpace;
	if(cycle==1 && !bDim) space = m_rowSpace;
	if(cycle==2 && !bDim) space = m_bRowSpace;
	if(cycle==3 && !bDim) space = m_cBRowSpace;*/
	return space;
}



///////////////////////////////////////////////////////////////////
//  Support for the View's obtaining coordinates

void CCalc::SetScale(int xppi, int yppi)
{
	m_xppi = xppi;
	m_yppi = yppi;
}

void CCalc::PassInScrollPosition(CPoint pt)
{
	m_drawRect.left = pt.x;
	m_drawRect.top = pt.y;
}

void CCalc::PassInViewSize(CRect vSRect)
{
	m_drawRect.right = m_drawRect.left + vSRect.right;
	m_drawRect.bottom = m_drawRect.top + vSRect.bottom;
}

void CCalc::FastForward(UINT * count,UINT page)
{
	double leftOfViewArea = (double)m_drawRect.left / m_xppi;
	if(leftOfViewArea>=m_leftM)leftOfViewArea -= m_leftM;
	else leftOfViewArea = 0.0;

	double topOfViewArea = (double)m_drawRect.top / m_yppi;
	if(topOfViewArea>=m_topM)topOfViewArea -= m_topM;
	else topOfViewArea = 0.0;

	InitializeCoords(page);

	UINT priorCount[6] = {0,0,0,0,0,0};
	BOOL clientRecStartsOnVertSpace = FALSE;
	BOOL clientRecStartsOnHorzSpace = FALSE;
	BOOL vtSpaceOutHasOccurred = FALSE;
	BOOL hzSpaceOutHasOccurred = FALSE;
	BOOL spaceOut = FALSE;
	double priorSpan,rem,span,space,horizontalRem=0.0,verticalRem=0.0;
	int i;
	for(i=0;i<6;i++)
	{
		if(i==0){priorSpan=leftOfViewArea;span=m_cBlockW;
			space=m_cBColSpace;}
		if(i==1){priorSpan=topOfViewArea;span=m_cBlockH;
			space=m_cBRowSpace;}
		if(i==2){priorSpan=horizontalRem;span=m_blockW;
			space=m_bColSpace;}
		if(i==3){priorSpan=verticalRem;span=m_blockH;
			space=m_bRowSpace;}
		if(i==4){priorSpan=horizontalRem;span=m_rectW;
			space=m_colSpace;}
		if(i==5){priorSpan=verticalRem;span=m_rectH;
			space=m_rowSpace;}
		rem = priorSpan;
	
		for(;rem>0;)
		{
			if(i%2==0)
			{
				if(clientRecStartsOnHorzSpace)break;
			}
			else if(clientRecStartsOnVertSpace)break;

			if(rem>=span)
			{
				rem -= span;
				priorCount[i]++;
			}
			else break;
			if(rem>space)rem -= space;
			else 
			{
				spaceOut = TRUE;
				break;
			}
		}
		if(i%2==0)
		{
			horizontalRem = rem;
			if(!hzSpaceOutHasOccurred)
				clientRecStartsOnHorzSpace = spaceOut;
			if(spaceOut)hzSpaceOutHasOccurred = TRUE;
		}
		else 
		{
			verticalRem = rem;
			if(!vtSpaceOutHasOccurred)
				clientRecStartsOnVertSpace = spaceOut;
			if(spaceOut)vtSpaceOutHasOccurred = TRUE;
		}
		spaceOut = FALSE;
	}

	m_vCountC = 1 + priorCount[5];
	m_hCountC = 1 + priorCount[4];
	m_vCountB = 1 + priorCount[3];
	m_hCountB = 1 + priorCount[2];
	m_vCountCB = 1 + priorCount[1];
	m_hCountCB = 1 + priorCount[0];

	m_cBlockFrame.x = m_leftM + ((m_hCountCB - 1) * 
		(m_cBlockW + m_cBColSpace)); 
	m_cBlockFrame.y = m_topM + ((m_vCountCB -1) *
		(m_cBlockH + m_cBRowSpace));
	m_blockFrame.x = m_cBlockFrame.x + ((m_hCountB - 1) *
		(m_blockW + m_bColSpace));
	m_blockFrame.y = m_cBlockFrame.y + ((m_vCountB -1) *
		(m_blockH + m_bRowSpace));

	m_left = m_blockFrame.x;
	m_right = m_left + m_rectW;
	m_top = m_blockFrame.y;
	m_bottom = m_top + m_rectH;

	for(i=1;i<m_hCountC;i++)
	{
		m_left = m_right + m_colSpace;
		m_right = m_left + m_rectW;
	}

	for(i=1;i<m_vCountC;i++)
	{
		m_top = m_bottom + m_rowSpace;
		m_bottom = m_top + m_rectH;
	}

	//m_hSpace = m_colSpace;
	//m_vSpace = m_rowSpace;

	UINT cellsPerBlock = m_rowsPer * m_colsPer;
	UINT cellsPerCBlock = m_bRowsPer * m_bColsPer * cellsPerBlock;
	UINT cellsPerPage = m_cBRowsPer * m_cBColsPer * cellsPerCBlock;

	m_CountB = m_hCountB + ((m_vCountB - 1) * m_bColsPer);
	m_CountCB = m_hCountCB + ((m_vCountCB - 1) * m_cBColsPer);//+
		//((page - 1) * cellsPerPage);

	*count = m_hCountC - 1 + ((m_vCountC - 1) * m_colsPer) +
		((m_hCountB - 1) * cellsPerBlock) +
		((m_vCountB - 1) * m_bColsPer * cellsPerBlock) +
		((m_hCountCB - 1) * cellsPerCBlock) +
		((m_vCountCB - 1) * m_cBColsPer * cellsPerCBlock) +
		((page - 1) * cellsPerPage);
}

int CCalc::FeedCoords(UINT count, UINT page)
{
	int val;
	//if(count==0 && m_arker==1) InitializeCoords(page);
	val = TransformRect(m_arker);
	if(m_arker==4) IncrementCounters(count,page);
	m_arker++;
	if(m_arker==5) m_arker = 1;
	return val;
}

void CCalc::InitializeCoords(UINT nPage)
{	
	m_blockFrame.x = m_leftM;
	m_blockFrame.y = m_topM;
	m_cBlockFrame.x = m_leftM;
	m_cBlockFrame.y = m_topM;
	
	//figure initial x1 coord
	m_left = m_blockFrame.x;
	m_right = m_leftM + m_rectW; 
	
	//figure initial y1 coord
	m_top = m_blockFrame.y;
	m_bottom = m_topM + m_rectH; 

	m_vCountC = 1;
	m_vCountB = 1;
	m_vCountCB = 1;
	m_hCountC = 1;
	m_hCountB = 1;
	m_hCountCB = 1;
	m_CountB = 1;
	m_CountCB = 1;

	//m_hSpace = m_colSpace;
	//m_vSpace = m_rowSpace;

}

BOOL CCalc::IncrementCounters(UINT count,UINT pageNum)
{	
	BOOL resetHC = FALSE, resetB = FALSE, resetCB = FALSE;
	BOOL incrementV = FALSE;
	UINT oldHCB = m_hCountCB, oldVCB = m_vCountCB;

	m_hCountC++;
	if(m_hCountC>m_colsPer)		
	{	
		m_vCountC++;			//longitudinal position in grid
		resetHC = TRUE;
		if(m_vCountC<=m_rowsPer)incrementV = TRUE;
		if(m_vCountC>m_rowsPer)
		{	
			m_hCountB++;
			m_CountB++;
			resetB = TRUE;
			//m_hSpace = m_bColSpace;
			//m_vSpace = m_bRowSpace;
		}
		if(m_hCountB>m_bColsPer) m_vCountB++;
		if(m_vCountB>m_bRowsPer || m_CountB>m_blockCount)
		{
			m_hCountCB++;
			m_CountCB++;
			resetCB = TRUE;
			//m_hSpace = m_cBColSpace;
			//m_vSpace = m_cBRowSpace;
		}
		if(m_hCountCB>m_cBColsPer && m_cmyk)
		{
			resetCB = TRUE;
			m_vCountCB++;
		}
	}
	//always increment horizontal coordinates
	m_left = m_right + m_colSpace;
	m_right = m_left + m_rectW;

	if(resetCB)
	{
		m_CountB = 1;
	}
	if(resetB)
	{
		GetNextFrame(oldHCB, oldVCB);
		m_top = m_blockFrame.y;
		m_bottom = m_top + m_rectH;
		m_vCountC = 1;
	}
	if(resetHC)	//modular: according to block n C-block counts
	{
		//m_rectCur;
		//if(scope==1) //  
		m_left = m_blockFrame.x;
		m_right = m_left + m_rectW;
		m_hCountC = 1;
	}
	if(incrementV)
	{
		m_top = m_bottom + m_rowSpace;
		m_bottom = m_top + m_rectH;
	}
	return TRUE;
}

UINT CCalc::GetCurrentCount(int dimens, UINT page)
{
	//dimensions: 1-column 2-row 3-block 4-cBlock
	UINT curRectNum;
	if(dimens==1) curRectNum = m_hCountC;
	if(dimens==2) curRectNum = m_vCountC;
	if(dimens==3 && m_colorMode==1)
		curRectNum = (m_bColsPer * (m_vCountB - 1)) + m_hCountB;
	if(dimens==3 && m_colorMode!=1)
	{
		UINT bsPerPage = m_bRowsPer * m_bColsPer;
		curRectNum = ((page - 1) * bsPerPage) + ((m_vCountB - 1) *
			m_bColsPer) + m_hCountB;
	}
	if(dimens==4)
	{
		//m_cBlockCount
		UINT cBsPerPage = m_cBRowsPer * m_cBColsPer;
		curRectNum = ((page - 1) * cBsPerPage) + ((m_vCountCB - 1) *
			m_cBColsPer) + m_hCountCB;
	}

	return curRectNum;
}

void CCalc::GetNextFrame(UINT oldHCountCB, UINT oldVCountCB)
{	
	UINT cBlocksPer, blocksPer;
	UINT potential = m_cBColsPer * m_cBRowsPer;	//potentially per page
	if(m_cBlockCount>=potential) cBlocksPer = potential;
	if(m_cBlockCount<potential) cBlocksPer = m_cBlockCount; 

	//figure actual blocks per c-block
	potential = m_bColsPer * m_bRowsPer;	//potentially per page
	if(m_blockCount>=potential) blocksPer = potential;
	if(m_blockCount<potential) blocksPer = m_blockCount;

	UINT frameNum;
	if(m_hCountB>m_bColsPer) m_hCountB = 1;
	if(m_vCountB>m_bRowsPer)
	{
		m_vCountB = 1;
		m_hCountB = 1;
	}
	if(m_hCountCB>m_cBColsPer)
	{
		m_hCountCB = 1;
		m_hCountB = 1;
		m_vCountB = 1;
	}
	frameNum = ((m_vCountB - 1) * m_bColsPer) + m_hCountB;
	//if(frameNum<=blocksPer)
	//{
		double curCBx; 
		curCBx = ((m_hCountCB - 1) * (m_cBlockW + m_cBColSpace))
			+ m_leftM;
		double curCBy;
		curCBy = ((m_vCountCB - 1) * (m_cBlockH + m_cBRowSpace))
			+ m_topM;
		double nextBx = (m_hCountB - 1) * (m_blockW + m_bColSpace);
		double nextBy = (m_vCountB - 1) * (m_blockH + m_bRowSpace);
		m_blockFrame.x = curCBx + nextBx;
		m_blockFrame.y = curCBy + nextBy;

		m_cBlockFrame.x = curCBx;
		m_cBlockFrame.y = curCBy;
	//}
}

int CCalc::TransformRect(int marker)
{	
	int val;
	if(marker==1) val = (int) (m_left * m_xppi);
	if(marker==2) val = (int) (m_top * m_yppi);
	if(marker==3) val = (int) (m_right * m_xppi);
	if(marker==4) val = (int) (m_bottom * m_yppi);
	return val;
}



///////////////////////////////////////////////////////////////////
// Performing manipulations to the data


BOOL CCalc::InstigateChange(float val, int nIDCode)
{
	BOOL valid = TRUE;
	m_processAgain = FALSE;
	m_instigatorCount++;
	CRegAspect* line;
	if(nIDCode<23)line = m_reg[nIDCode];
	else
	{
		valid = InstigateFrequency(val,nIDCode);
		return valid;
	}
	line->m_nNuSize = line->m_nSize;
	line->m_instigating = TRUE;
	line->m_origReqSize = val;
	line->m_alt = FALSE;
	line->m_processed = FALSE;
	return valid;
}

BOOL CCalc::InstigateChange(UINT val, int nIDCode)
{
	BOOL valid = TRUE;
	m_processAgain = FALSE;
	m_instigatorCount++;
	CRegAspect* line;
	if(nIDCode<23)line = m_reg[nIDCode];
	if(nIDCode>=23 && nIDCode<27)
	{
		valid = InstigateFrequency((float)val,nIDCode);
		return valid;
	}
	if(nIDCode>=27 && nIDCode<=34)
	{
		line = m_reg[nIDCode];
	}
	line->m_nNuCount = line->m_nCount;
	line->m_instigating = TRUE;
	line->m_origReqCount = val;
	line->m_alt = FALSE;
	line->m_processed = FALSE;
	 
	return TRUE;
}

BOOL CCalc::InstigateFrequency(float val, int nIDCode)
{
	CRegAspect* line;
	line = m_reg[nIDCode];
	line->m_origReqSize = val;
	line->m_instigating = TRUE;
	return TRUE;
}

void CCalc::ChangeLocksAndFlags(int nID,BOOL flag)
{
	if(nID<50)
	{
		CRegAspect* line = m_reg[nID];
		line->m_locked = flag;
	}
	if(nID==51) m_derivePages = flag;
	if(nID==52) m_cellR = flag;
	if(nID==53) m_cellSqR = flag;
	if(nID==54) m_uniCount = flag;
	if(nID==55) m_deriveCells = flag;
	if(nID==56) m_rangeInvolve = flag;
	if(nID==57) m_intSync = flag;
	if(nID==58) m_syncAll = flag;
}

void CCalc::RetractInstigatingLine(int i)
{
	CRegAspect* line = m_reg[i];
	line->m_instigating = FALSE;
	line->m_processed = FALSE;

	m_instigatorCount--;
}

void CCalc::ResetForReProcessing()
{
	CRegAspect* line;
	int type = 99;
	BOOL req = FALSE;
	int i;
	for(i=0;i<RGSZ;i++)
	{
		line = m_reg[i];
		type = line->m_nType;
		req = line->m_instigating;
		if(req && type==1)line->m_nNuSize = line->m_nSize;
		if(req && type==0)line->m_nNuCount = line->m_nCount;
		if(i==5 || i==12)
		{
			if(line->m_alt)line->m_nNuCount = line->m_nCount;
		}
		if(!req)line->m_alt = FALSE;
	}
	m_countDenial = FALSE;
	m_pageDenial = FALSE;
	m_processAgain = TRUE;	
}

BOOL CCalc::ProcessChangeRequests()
{
	BOOL grant,countGrant = FALSE,pageGrant = FALSE;
	SaveAtStartComputeSettings();
	SetProcessingOrder();
	m_processAgain = TRUE;
	m_pageDenial = FALSE;
	m_countDenial = FALSE;
	for( ;m_processAgain; )
	{
		BOOL result;
		ClearCaseFlags();
		m_flagReporting = FALSE;
		m_fixRCellChange = FALSE;
		m_mgnChange = FALSE;
		m_processAgain = FALSE;
		m_noAccept = FALSE;
		int dex;
		for(dex=0;dex<RGSZ;dex++)
		{
			CRegAspect* line = m_reg[dex];
			line->m_minSetCur = FALSE;
			line->m_maxSetCur = FALSE;
			line->m_minSet = FALSE;
			line->m_maxSet = FALSE;
			line->m_applied = FALSE;
			line->m_processed = FALSE;
			line->m_accepted = FALSE;
			line->m_histAlt = FALSE;
			line->m_nLastSize = line->m_nSize;
			line->m_nLastCount = line->m_nCount;
			line->m_nNuCount = line->m_nCount;
			line->m_nNuSize = line->m_nSize;
			line->m_alt = FALSE;//in neo- alt version
		}
		dex = 0;
		//apply page size
		//int pageReqs = RequestPageSizeChanges();
		int pageReqs = 0;
	//	if(!m_pageDenial)pageGrant = TRUE;
		//apply and validate new counts
		int countReqs = 0;
	//	if(!m_noAccept)countReqs = ProcessNewCountRequests();
	//	if(!m_countDenial)countGrant = TRUE;
	//	if(countGrant && pageGrant)grant = TRUE;
	//	else grant = FALSE;
		grant = TRUE;
		
		//apply other aspects
		m_flagReporting = TRUE;
	//	request = pageReqs + countReqs;
		int count = 0;
		int i = 0;
		BOOL req = FALSE;
		BOOL applied = FALSE;
		if(!m_noAccept)
		{
			for(count=0;count<SHELFSZ;count++)
			{
				m_change = FALSE;
				for(i=0;i<RGSZ;i++)
				{
					CRegAspect* line = m_reg[i];
					if(line->m_order==count)
					{
						req = line->m_instigating;
						applied = line->m_applied;
						if(req && !applied)
						{
							result = DirectChangeRequests(i);
							//line->m_processed = TRUE;
							if(result && !m_noAccept)
							{
								line->m_applied = TRUE;
								line->m_minSetCur = TRUE;
								line->m_maxSetCur = TRUE;
								LegitimizeCurrentFlags();
							}
							if(!result){grant = result;break;}
							if(!m_noAccept)AcceptChanges();
						}
						if(m_noAccept)break;
					}//if(m_order==count)
				}//for(i<RGSZ)
				
			}//for(count<36)
			
		}
		if(m_noAccept)ResetChangeRequestProcessingLoop();
		if(m_instigatorCount!=0 && grant)AcceptAllChanges();
		if(grant)LoadCalcMembers();
		if(!m_processAgain)
		{
			m_instigatorCount = 0;
			for(dex=0;dex<RGSZ;dex++) 
			{
				CRegAspect* line = m_reg[dex];
				line->m_instigating = FALSE;
			}
		}
	}//process loop
	return grant;
}
void CCalc::SetProcessingOrder()
{
	int i;
	int shelf[SHELFSZ];
	for(i=0;i<SHELFSZ;i++)
	{
		shelf[i] = 99;
	}
	BOOL rect = TRUE;
	BOOL colorRange;
	CRegAspect* line;

	for(i=0;i<RGSZ;i++)
	{
		line = m_reg[i];
		line->m_order = 99;
	}

	for(i=0;i<RGSZ;i++)
	{
		rect = TRUE;
		line = m_reg[i];
		if(line->m_instigating)
		{
			if(i==6 || i==16)//page resize
			{
				rect = FALSE;
				if(line->m_origReqSize>line->m_nNuSize)
				{
					if(i==6)shelf[i] = 5;
					if(i==16)shelf[i] = 6;
				}
				if(line->m_origReqSize<line->m_nNuSize)
				{
					if(i==6)shelf[i] = 35;
					if(i==16)shelf[i] = 36;
				}
			}
			if(i==15)//page count
			{
				shelf[i] = 45;
			}
			if(line->m_nType==0)//count change
			{
				rect = FALSE;
				if(line->m_origReqCount>line->m_nNuCount)
				{
					if(i==5)shelf[i] = 29;
					if(i==12)shelf[i] = 30;
					if(i==19)shelf[i] = 31;
					if(i==20)shelf[i] = 32;
					if(i==21)shelf[i] = 33;
					if(i==22)shelf[i] = 34;
					if(i==13)shelf[i] = 31;//spot availible from dialog
					if(i==14)shelf[i] = 33;//spot availible from dialog
				}
				if(line->m_origReqCount<line->m_nNuCount)
				{
					if(i==5)shelf[i] = 7;
					if(i==12)shelf[i] = 8;
					if(i==19)shelf[i] = 9;
					if(i==20)shelf[i] = 10;
					if(i==21)shelf[i] = 11;
					if(i==22)shelf[i] = 12;
					if(i==13)shelf[i] = 9;//spot availible from dialog
					if(i==14)shelf[i] = 11;//spot availible from dialog
				}
			}
			if(line->m_nNuSize<line->m_origReqSize)
			{
				if(i==23)shelf[i] = 1;
				if(i==24)shelf[i] = 2;
				if(i==25)shelf[i] = 3;
				if(i==26)shelf[i] = 4;
			}
			if(line->m_nNuSize>line->m_origReqSize)
			{
				if(i==23)shelf[i] = 41;
				if(i==24)shelf[i] = 42;
				if(i==25)shelf[i] = 43;
				if(i==26)shelf[i] = 44;
			}
			if(i==3 || i==4 || i==10 || i==11)//margin resize
			{
				rect = FALSE;
				if(line->m_origReqSize>line->m_nNuSize)
				{
					if(i==10)shelf[i] = 37;
					if(i==11)shelf[i] = 38;
					if(i==3)shelf[i] = 39;
					if(i==4)shelf[i] = 40;
				}
				if(line->m_origReqSize<line->m_nNuSize)
				{
					if(i==10)shelf[i] = 13;
					if(i==11)shelf[i] = 14;
					if(i==3)shelf[i] = 15;
					if(i==4)shelf[i] = 16;
				}
			}
			if(i>=27 && i<=34)//colorRange
			{
				rect = FALSE;
				int offset = 20;
				int dex1 = i,dex2 = i + 1;
				if(i%2==0)dex2 = i - 1;
				UINT start,end,nuStart,nuEnd,r,nuR;
				CRegAspect* mateLine;
				line = m_reg[dex1];
				mateLine = m_reg[dex2];
				if(shelf[i]==99)
				{
					start = line->m_nNuCount;
					if(line->m_instigating)nuStart = line->m_origReqCount;
					else nuStart = start;
					end = mateLine->m_nNuCount;
					if(mateLine->m_instigating)nuEnd =
						mateLine->m_origReqCount;
					else nuEnd = end;
					if(start>=end)r = start - end;
					else r = end - start;
					if(nuStart>nuEnd)nuR = nuStart - nuEnd;
					else nuR = nuEnd - nuStart;
					if(nuR>=r)
					{
						shelf[dex1] = dex1;
						shelf[dex2] = dex2;
					}
					else 
					{
						shelf[dex1] = dex1 - offset;
						shelf[dex2] = dex2 - offset;
					}
				}//if(shelf[i]==99)
			}//if(rangeExtreme)
			if(rect)//cell,block,cblock aspects
			{
				if(line->m_origReqSize>line->m_nNuSize)
				{
					if(i==0)shelf[i] = 28;
					if(i==1)shelf[i] = 25;
					if(i==2)shelf[i] = 23;
					if(i==7)shelf[i] = 27;
					if(i==8)shelf[i] = 26;
					if(i==9)shelf[i] = 24;
					if(i==17)shelf[i] = 17;//slots availible when frame req
					if(i==18)shelf[i] = 18;//slots available when frame req
				}
				if(line->m_origReqSize<line->m_nNuSize)
				{
					if(i==0)shelf[i] = 17;
					if(i==1)shelf[i] = 19;
					if(i==2)shelf[i] = 21;
					if(i==7)shelf[i] = 18;
					if(i==8)shelf[i] = 20;
					if(i==9)shelf[i] = 22;
					if(i==17)shelf[i] = 27;//slots available /frame requested
					if(i==18)shelf[i] = 28;//slots available /fr requested
				}
			}//if(rect)
		}//if(line->instigating)
	}//for()
	for(i=0;i<RGSZ;i++)
	{
		if(shelf[i]!=99)
		{
			line = m_reg[i];
			line->m_order = shelf[i];
		}
	}
	//manipulate order for block-format pre-emptive handling
	for(i=19;i<23;i++)
	{
		CRegAspect* inLine,*outLine;
		int inID,outID;
		if(i==19)inID = 1;
		if(i==20)inID = 8;
		if(i==21)inID = 2;
		if(i==22)inID = 9;
		outID = GetEnclosingAspectID(inID);
		if(m_colorMode!=1 && i<21)outID = GetEnclosingAspectID(outID);
		inLine = m_reg[inID];
		outLine = m_reg[outID];
		line = m_reg[i];
		if(line->m_instigating)
		{
			if(inLine->m_order > outLine->m_order)
			{
				if(line->m_order > outLine->m_order)
				{
					int buf = line->m_order;
					line->m_order = outLine->m_order;
					outLine->m_order = buf;
				}
			}
			else
			{
				if(line->m_order > inLine->m_order)
				{
					int buf = line->m_order;
					line->m_order = inLine->m_order;
					inLine->m_order = buf;
				}
			}
		}
	}
}

BOOL CCalc::DirectChangeRequests(int i)
{
	//these primary fuctions should have calls to CMessDlg object
	BOOL grant;
	if(i==0 || i==7) grant = RequestRect(i,FALSE);
	if(i==1 || i==8 || i==2 || i==9) grant = RequestRect(i,FALSE);
	if(i==17 || i==18) grant = RequestRect(i,FALSE);
	if(i==6 || i==16) grant = RequestRect(i,FALSE);
	if(i==3 || i==4 || i==10 || i==11) grant = RequestMargin(i);
	if(i==5 || i==12) grant = //RequestCountChange(i,TRUE);
		HandleHighLevelRequest(i);
	if(i==13 || i==14) grant = //RequestCountChange(i,TRUE);
		HandleHighLevelRequest(i);
	if(i==15) grant = RequestPageCount(); 
	if(i==19 || i==20) grant = RequestBlockFormatChange(i);
	if(i==21 || i==22) grant = RequestBlockFormatChange(i);
	if(i>=23 && i<=26) grant = HandleHighLevelRequest(i);
	if(i>=27 && i<=34) grant = HandleHighLevelRequest(i);
	return grant;
}


BOOL CCalc::RequestRect(int index,BOOL imperative)
{
	//contingencies involving imperative are geared to help count alterations
	BOOL canDo = FALSE,getInc = FALSE, getDec = FALSE,
		frameShrink = TRUE,	pageResize = FALSE, cellShrink = FALSE;
	BOOL margHitch = FALSE,horiz = TRUE,min=FALSE,max=FALSE;
	BOOL fromZero=FALSE;
	double old, nu, factor,initHitchFact,maxf,dif;
	double  maxCFact = 100.0, maxFrAdj = 100.0, maxMgnAdj = 100.0;
	double maxFrAdjFront = 100.0;
	double frFactor;
	int level,backSideID,cellID,bkFrID,mg3ID,mg4ID;

	CRegAspect* line = m_reg[index];
	horiz = line->m_horiz;
	old = line->m_nNuSize;
	nu = line->m_origReqSize;
	if(old==nu)return TRUE;
	if(old==0)fromZero = TRUE;
	if(!fromZero)factor = nu / old;
	else factor = 999999999999;
	if(line->m_locked){/*factor = 1.0;*/m_case3 = TRUE;/*return FALSE;*/}
	level = GetLevel(index);
	if(index==6 || index==16)pageResize = TRUE;
	if(factor>=1)
	{
		cellShrink = FALSE;
		frameShrink = FALSE;
		initHitchFact = 999999999999;
	}
	if(factor<1)
	{
		cellShrink = TRUE;
		frameShrink = TRUE;
		initHitchFact = 0.0;
		maxCFact = 0.0;
	}
	if(horiz){backSideID = 7;cellID = 0;mg3ID = 10;mg4ID = 11;}
	if(!horiz){backSideID = 0;cellID = 7;mg3ID = 3;mg4ID = 4;}
	line = m_reg[mg3ID];
	m_m3 = line->m_nNuSize;
	line = m_reg[mg4ID];
	m_m4 = line->m_nNuSize;

	
	margHitch = TRUE; //saves having to find out now
	if(margHitch)maxFrAdjFront = 
		InteriorAbilityForFrameChange(frameShrink,horiz);
	if(pageResize)frameShrink = !frameShrink;
	m_backFrCase = 0;
	if(margHitch)maxFrAdj = 
		InteriorAbilityForFrameChange(frameShrink,!horiz); 
	if(m_cellR)maxCFact = 
		AvailableCellChange(initHitchFact,backSideID,1,maxFrAdjFront);
	m_mgnChange = FALSE;
	m_cellFactor = 1.0;
	maxf = ChangeAspectSize(factor,index,level,maxFrAdj,
		maxCFact,imperative,FALSE);
	if(imperative && maxf==factor)
		maxf = ChangeAspectSize(factor,index,level,maxFrAdj,
		maxCFact,FALSE,FALSE);
	dif = 0.0;//a small difference is only to avoid divide by 0
	if(maxf>factor)dif = maxf - factor;
	if(maxf<=factor)dif = factor - maxf;
	if(fromZero)
	{
		if(line->m_origReqSize != line->m_nNuSize)	dif = 999999999999;	
	}
	if(!m_cellR)
	{
		if(factor>1 && maxf<factor)factor = maxf;
		if(factor<1 && maxf>factor)factor = maxf;
	}
	if(dif<=0.0000001 && m_cellR)ClearCaseFlags();
	if(m_cellR)
	{
		int sib;
		if(cellID==0)sib = 7;
		if(cellID==7)sib = 0;

		CRegAspect* lineC = m_reg[sib];
		lineC->m_origReqSize = lineC->m_nNuSize * m_cellFactor;
		ChangeAssociatedRectSize(m_cellFactor,sib,maxFrAdj);
	}
	int sz = FLGSTORESZ;
	BOOL flags [FLGSTORESZ];
	StoreRestoreCurrentFlags(TRUE,flags,sz);
	if(m_mgnChange && factor!=1)
	{
		ChangeAssociatedMarginSizes(!horiz);
		if(horiz)bkFrID = 18;
		else bkFrID = 17;
		line = m_reg[bkFrID];
		old = line->m_nNuSize;
		if(line->m_nNuSize!=0)frFactor = m_backFrameDerivative /
			line->m_nNuSize;
		else frFactor = 999999999999;
		line->m_origReqSize = m_backFrameDerivative;
		if(frFactor<=1)frameShrink = TRUE;
		else frameShrink = FALSE;
		maxFrAdjFront = maxFrAdj;
		initHitchFact = m_cellFactor;
		maxFrAdj = InteriorAbilityForFrameChange(frameShrink,horiz); 
		m_carryOutFrAdjOnly = TRUE;
		maxCFact = AvailableCellChange(initHitchFact,backSideID,1,
			maxFrAdjFront);
		BOOL minBuf = line->m_minSetCur;
		BOOL maxBuf = line->m_maxSetCur;
		maxf = ChangeAspectSize(frFactor,bkFrID,4,maxFrAdj,maxCFact,
			FALSE,FALSE);
		line->m_minSetCur = minBuf;
		line->m_maxSetCur = maxBuf;
		m_carryOutFrAdjOnly = FALSE;
		m_mgnChange = FALSE;
	}
	StoreRestoreCurrentFlags(FALSE,flags,sz);//FALSE indicates 'restore'
	if(dif>0.0000001)
	{	
		if(imperative){m_maxFactor=factor;return FALSE;}
		int ans = 0;
		if(m_flagReporting)
		{
			
			CMessDlg dlg;
			dlg.str = GetAdvisoryStrings();
			if(dlg.DoModal()==IDOK)
			{
				if(dlg.m_yes)ans = 1;
				if(dlg.m_no)ans = 2;
				canDo = TRUE;
			}
		}
		if(!m_flagReporting)
		{
			ans = 1;
		}
		if(ans==0)//clean up reg stop processing -- "CANCEL"
		{
			m_instigatorCount = 0;
			//RejectChanges();
			RestoreAtStartComputeSettings();
		}
		//accept max change & continue processing -- "YES"
		if(ans==1)
		{
			//if(maxf!=1)AcceptChanges();
			//if(maxf==1)RejectChanges();
		}
		//forgo this change continue processing -- "NO"
		if(ans==2)
		{
			m_noAccept = TRUE;
			return FALSE;
		}
	}
	//a small difference is only to avoid divide by 0
	if(dif<=0.0000001)
	{
		canDo = TRUE;
		//AcceptChanges();
		if(m_flagReporting)ClearCaseFlags();
	}
	m_maxFactor=factor;
	return canDo;
}
///////////////////////////////////////////////////////////////////////

BOOL CCalc::RequestMargin(int index)
{
	BOOL canDo=TRUE, horiz, bigger,frShrink,bkFrShrink;
	BOOL fromZero=FALSE, alt=FALSE;
	BOOL fixMarg=FALSE,fixMarg2=FALSE,fixSibMarg=FALSE;
	BOOL lock=FALSE,validBoost=TRUE;
	BOOL perpenHitch=FALSE,reqAdjust = FALSE,frontNonReqAlter = FALSE;
	BOOL backFrBigger=FALSE,fullCircle=FALSE;
	BOOL twoChannelCase = FALSE;
	BOOL bkFrInverse = FALSE,frFrInverse=FALSE;
	BOOL * bkFrInvert = &bkFrInverse;
	BOOL * frFrInvert = &frFrInverse;
	BOOL applyBackFrFlags = FALSE;
	double factor, nu, old, change = 0,curSize,origFact,frFactor;
	double maxf,maxAdj,maxFrAdj,maxFrAdjFront,maxCFact,initCFact=999999999999;
	double frontFrChange,backFrChange=0,bkTransmittedChange,dif;
	double frameChange=0.0,backFrameChange=0.0;
	double frontInverseFrChange;
	double bkComplyMargChg=1.0,origBoost;
	double maxSibAccomodation=0.0;
	double nuM3,nuM4,m3,m4;
	double * nuMarg3 = &nuM3;
	double * nuMarg4 = &nuM4;
	double * frChange = &frameChange;
	double * bkFrChange = &backFrameChange;
	double sibChange = 0.0,boomerSibChange = 0.0;
	m_boostMarg = FALSE;
	m_boostMargAmt = 1.0;
	int cellID,frID,bFrID,backSideID,sibID,mg3ID,mg4ID;
	int backFrFlags=0,frontFrFlags=0,invFrFrFlags=0;
	if(index==3){sibID = 4; mg3ID = 10; mg4ID = 11;}
	if(index==4){sibID = 3; mg3ID = 10; mg4ID = 11;}
	if(index==10){sibID = 11; mg3ID = 3; mg4ID = 4;}
	if(index==11){sibID = 10; mg3ID = 3; mg4ID = 4;}

	//goal: origReqSize
	//change: discrepancy between goal and current position
	//first: try to implement change via frame (re-size frame contents)
	//secondly: balance of unachieved change via other margin (re-position)

	//case 1:instigating marg hitched to back margins and
	//	sib margin is hitched to the other back margins and there are two
	//channels so to speak
	//case 2: only the instigating marg is hitched to the back
	//case 3: only the sib is hitched to the back
	//case 4: no hitches
	//case 5: all are hitched and have one factor or boostMargAmt

	CRegAspect* line;
	CRegAspect* sibLine;
	sibLine = m_reg[sibID];
	line = m_reg[index];
	line->m_asking = TRUE;
	alt = line->m_alt;
	curSize = line->m_nNuSize;
	nu = line->m_origReqSize;
	old = line->m_nNuSize; 
	if(old!=0)factor = nu / old;
	else 
	{
		factor = 999999999999;
		m_boostMarg = TRUE;
		m_boostMargAmt = nu;
		m_boostMargID = index;
		validBoost = AscertainBoostValidity(index,sibID,mg3ID,mg4ID);
		if(!validBoost)m_case5 = TRUE;			
	}
	origFact = factor;
	origBoost = m_boostMargAmt;
	if(!validBoost)m_boostMargAmt = 0.0;
	if(line->m_origReqSize>curSize)
	{
		change = line->m_origReqSize - curSize;
		if(m_boostMarg)change = m_boostMargAmt;
		bigger = TRUE;
		frShrink = TRUE;
		bkFrShrink = TRUE;
	}
	if(line->m_origReqSize<=curSize)
	{
		change = curSize - line->m_origReqSize;
		bigger = FALSE;
		frShrink = FALSE;
		bkFrShrink = FALSE;
	}

	if(index==3 || index==4)
		{horiz = TRUE;frID = 17;bFrID = 18;backSideID = 7;}
	if(index==10 || index==11)
		{horiz = FALSE;frID = 18;bFrID = 17;backSideID = 0;}

	line = m_reg[mg3ID];
	m3 = line->m_nNuSize;
	line = m_reg[mg4ID];
	m4 = line->m_nNuSize;
	nuM3 = m3;
	nuM4 = m4;

	BOOL m3is = DetermineInterlock(index,mg3ID);
	BOOL m4is = DetermineInterlock(index,mg4ID);
	BOOL sibIs = DetermineInterlock(index,sibID);
	fixMarg = CheckMarginMobility(index,4,!bigger);
	if(!fixMarg)
	{
		//firstly diagnos ability to move
		if(m3is || m4is)perpenHitch = TRUE;
		if(perpenHitch)
		{
			int flagBuf = m_backFrCase;
			backFrChange = InteriorAbilityForFrameChange(bkFrShrink,!horiz);
			backFrFlags = m_backFrCase;
			m_backFrCase = flagBuf;
			double m3change = 0.0, m4change = 0.0;
			if(m3is)
			{
				line = m_reg[mg3ID];
				if(bigger && !m_boostMarg)m3change =
					 (line->m_nNuSize * factor) - line->m_nNuSize;	
				if(!bigger && !m_boostMarg)m3change = 
					line->m_nNuSize - (line->m_nNuSize * factor);
				nuM3 = line->m_nNuSize * factor;
				if(m_boostMarg)
				{
					if(validBoost)
					{
						m3change = m_boostMargAmt;
						nuM3 = m_boostMargAmt;
					}
				}
			}
			if(m4is)
			{
				line = m_reg[mg4ID];
				if(bigger && !m_boostMarg)m4change = 
					(line->m_nNuSize * factor) - line->m_nNuSize;
				if(!bigger && !m_boostMarg) m4change = 
					line->m_nNuSize - (line->m_nNuSize * factor);
				nuM4 = line->m_nNuSize * factor;
				if(m_boostMarg)
				{
					if(validBoost)
					{
						m4change = m_boostMargAmt;
						nuM4 = m_boostMargAmt;
					}
				}
			}
			bkTransmittedChange = m3change + m4change;
			if(backFrChange<bkTransmittedChange)
			{
				dif = bkTransmittedChange - backFrChange;
				bkComplyMargChg = 0.0;
				int bkSibID;
				if(!m3is)
				{
					bkSibID = mg3ID;
					line = m_reg[mg3ID];
					line->m_nConting = line->m_nNuSize;
				}
				else 
				{
					bkSibID = mg4ID;
					line = m_reg[mg4ID];
					line->m_nConting = line->m_nNuSize;
				}
				if(!m3is || !m4is)
				{
					line = m_reg[bkSibID];
					lock = line->m_locked;
					if(bigger && line->m_minSet)lock = TRUE;
					if(!bigger && line->m_maxSet)lock =TRUE;
					if(!lock && bigger)
					{
						if(dif<=line->m_nNuSize)
						{
							bkComplyMargChg = dif;
							line->m_nConting = line->m_nNuSize - dif;
							dif = 0.0;
						}
						else
						{
							dif = dif - line->m_nNuSize;
							bkComplyMargChg = line->m_nNuSize;
							line->m_nConting = 0.0;
						}
					}//if(!lock && bigger)
					if(!lock && !bigger)
					{
						bkComplyMargChg = dif;
						dif = 0.0;
						line->m_nConting = line->m_nNuSize + dif;
					}
					if(lock)backFrFlags = backFrFlags | 8;
				}//if(!m3is || !m4is)
				backFrameChange = backFrChange;
				bkTransmittedChange = bkTransmittedChange - dif;
				line = m_reg[bkSibID];
				if(!m3is)nuM3 = line->m_nConting;
				if(!m4is)nuM4 = line->m_nConting;
			}//if(backFrChange<bkTransmittedChange)
			else 
			{
				//backFrChange = bkTransmittedChange;
				backFrameChange = bkTransmittedChange;
			}

			//if request did not get met, modify request
			if(bkTransmittedChange!=(m3change + m4change))
			{
				applyBackFrFlags = TRUE;
				//m_case4 = TRUE;
				//m_case3 = TRUE;
				if(!m3is || !m4is)
				{
					double bkTransmitMarg,nuBkTransmitMarg;
					if(m3is)bkTransmitMarg = m3;
					if(m4is)bkTransmitMarg = m4;
					if(bigger)
					{
						nuBkTransmitMarg = bkTransmitMarg + backFrChange
							+ bkComplyMargChg;
						if(m_boostMarg)nuBkTransmitMarg = backFrChange + 
							bkComplyMargChg;
					}
					else nuBkTransmitMarg = bkTransmitMarg - 
						backFrChange - bkComplyMargChg;		
					if(bkTransmitMarg!=0 && !m_boostMarg)factor = 
						nuBkTransmitMarg / bkTransmitMarg;
					else
					{
						m_boostMargAmt = nuBkTransmitMarg;
						if(m3is)nuM3 = nuBkTransmitMarg;
						if(m4is)nuM4 = nuBkTransmitMarg;
					}
				}
				else//if(m3is && m4is)
				{
					if(m3!=0 || m4!=0)
					{
						if(bigger)factor = (backFrChange + (m3 + m4)) / 
							(m3 + m4);
						else factor = ((m3 + m4) - backFrChange) /
							(m3 + m4);
					}
					else 
					{
						factor = 999999999999;
						if(m_boostMarg && validBoost)
						{
							double maxBackBoost;
							maxBackBoost = backFrChange / 2;
							if(maxBackBoost<m_boostMargAmt)m_boostMargAmt
								= maxBackBoost;
							nuM3 = maxBackBoost;
							nuM4 = maxBackBoost;
						}
					}
				}
				if(m3is && !m_boostMarg)
				{
					line = m_reg[mg3ID];
					nuM3 = line->m_nNuSize * factor;
				}
				if(m4is && !m_boostMarg)
				{
					line = m_reg[mg4ID];
					nuM4 = line->m_nNuSize * factor;
				}
			}//if(bkTransmittedChange [has changed]
		}//if(perpenHitch)

		//diagnos front side with possibly modified factor
		BOOL adjReq = FALSE;
		if(factor!=origFact)adjReq = TRUE;
		if(origBoost!=m_boostMargAmt)adjReq = TRUE;
		if(adjReq)
		{
			line = m_reg[index];
			if(bigger)change = 
				(line->m_nNuSize * factor) - line->m_nNuSize;
			if(!bigger)change = 
				line->m_nNuSize - (line->m_nNuSize * factor);
			if(m_boostMarg)change = m_boostMargAmt;
		}
		int flagBuf = m_backFrCase;
		m_backFrCase = 0;
		frontFrChange = InteriorAbilityForFrameChange(frShrink,horiz);
		frontFrFlags = m_backFrCase;
		m_backFrCase = 0;
		frontInverseFrChange = 
			InteriorAbilityForFrameChange(!frShrink,horiz);
		invFrFrFlags = m_backFrCase;
		m_backFrCase = flagBuf;
		double frontReq = change;
		BOOL m3SibHitch = DetermineInterlock(sibID,mg3ID);
		BOOL m4SibHitch = DetermineInterlock(sibID,mg4ID);
		BOOL sibHitch = (m3SibHitch || m4SibHitch);
		//'two-channel' means: two resize-rate groups that cross from back
		//to front sides and that move independantly of eachother
		if((m3is || m4is) && (!m3is || !m4is) && sibHitch && !sibIs)
			twoChannelCase = TRUE;		
		if(sibIs)//bkComplyMargChg is then irrelevant
		{
			line = m_reg[sibID];
			if(bigger)
			{
				sibChange = (line->m_nNuSize * factor)
					- line->m_nNuSize;
				if(m_boostMarg)sibChange = m_boostMargAmt;
			}
			else sibChange = line->m_nNuSize
				- (line->m_nNuSize * factor);
			frontReq = frontReq + sibChange;
		}
		if(frontReq>frontFrChange && !twoChannelCase)
		{
			frameChange = frontFrChange;
			double maxBkInverseFrChange = 
				InteriorAbilityForFrameChange(bigger,!horiz);
			dif = frontReq - frontFrChange;
			if(!sibIs)//figure ramifications independantly (not case 5)
			{	
				if(m3SibHitch || m4SibHitch)//case: 3 (not 1)		
				{
					bkFrInverse = TRUE;
					if(sibLine->m_nNuSize==0 && !bigger)
					{
						BOOL valid = AscertainBoostValidity(sibID,index,
							mg3ID,mg4ID);
						if(valid)
						{
							int looseMgID;
							double maxBackBoost = 0.0;
							if(m3SibHitch && !m4SibHitch)looseMgID = mg4ID;
							if(!m3SibHitch && m4SibHitch)looseMgID = mg3ID;
							if(!m3SibHitch || !m4SibHitch)
							{
								line = m_reg[looseMgID];
								//knowing this is not two-channel gives us
								//the right to allocate from the back
								if(!line->m_locked)maxBackBoost = 
									maxBkInverseFrChange + line->m_nNuSize;
								else maxBackBoost = maxBkInverseFrChange;
							}
							if(m3SibHitch && m4SibHitch)
							{
								maxBackBoost = maxBkInverseFrChange / 2;
							}
							m_boostMarg2ndary = TRUE;
							m_boostMarg2ndaryID = sibID;
							m_boostMarg2ndaryAmt = maxBackBoost;
							m_direct2ndaryBoost = FALSE;
							maxSibAccomodation = maxBackBoost;
						}
						else maxSibAccomodation = 0.0;
					}
					if(sibLine->m_nNuSize==0 && bigger)
						maxSibAccomodation = 0.0;
					if(sibLine->m_nNuSize!=0 && bigger)
					{
						double maxM3change=0.0,maxM4change=0.0,shrinkRate;
						double neededShrinkRate;
						if(sibLine->m_nNuSize>dif && sibLine->m_nNuSize!=0)
							neededShrinkRate = (sibLine->m_nNuSize - dif)
							 / sibLine->m_nNuSize;
						else neededShrinkRate = 0.0;
						if(sibLine->m_locked)neededShrinkRate = 1.0;
						if(sibLine->m_minSet)neededShrinkRate = 1.0;
						shrinkRate = neededShrinkRate;
						//figure max backside factor for sib
						if(m3SibHitch)
						{
							line = m_reg[mg3ID];
							if(!line->m_locked && !line->m_minSet)
								maxM3change = line->m_nNuSize - 
								(line->m_nNuSize * neededShrinkRate);
							else 
							{
								neededShrinkRate = 1.0;
								maxM3change = 0.0;
							}
						}
						if(m4SibHitch)
						{
							line = m_reg[mg4ID];
							if(!line->m_locked && !line->m_minSet)
								maxM4change = line->m_nNuSize -
								(line->m_nNuSize * neededShrinkRate);
							else 
							{
								maxM4change = 0.0;
								neededShrinkRate = 1.0;
							}
						}
						shrinkRate = neededShrinkRate;
						if((maxM3change + maxM4change)>maxBkInverseFrChange)
						{
							if(m3SibHitch && m4SibHitch)
							{
								shrinkRate = ((m3 + m4) - maxBkInverseFrChange)
									 / (m3 + m4);
								nuM3 = m3 * shrinkRate;
								nuM4 = m4 * shrinkRate;
							}
							if(m3SibHitch && !m4SibHitch)
							{
								line = m_reg[mg4ID];
								if(!line->m_locked)shrinkRate = (m3 -
									maxBkInverseFrChange) / m3;
								else 
								{
									double m4adj = (m3 - (m3 * shrinkRate)) -
										maxBkInverseFrChange;
									nuM4 = m4 + m4adj;
								}
								nuM3 = shrinkRate * m3;
							}
							if(!m3SibHitch && m4SibHitch)
							{
								line = m_reg[mg3ID];
								if(!line->m_locked)shrinkRate = (m4 -
									maxBkInverseFrChange) / m4;
								else 
								{
									double m3adj = (m4 - (m4 * shrinkRate)) -
										maxBkInverseFrChange;
									nuM3 = m3 + m3adj;
								}
								nuM4 = shrinkRate * m4;
							}
							
							maxSibAccomodation = sibLine->m_nNuSize - 
								(sibLine->m_nNuSize * shrinkRate);
							backFrameChange = maxBkInverseFrChange;
						}//if(maxM3change + maxM4change)>maxBkInverseFrChange
						else
						{
							backFrameChange = maxM3change + maxM4change;
							if(m3SibHitch)nuM3 = m3 * shrinkRate;
							if(m4SibHitch)nuM4 = m4 * shrinkRate;
							maxSibAccomodation = sibLine->m_nNuSize - 
								(sibLine->m_nNuSize * shrinkRate);
						}
					}//if(sibLine->m_nNuSize!=0 && bigger)
					if(sibLine->m_nNuSize!=0 && !bigger)
					{
						BOOL sibLoose = FALSE;
						double growRate,neededGrowRate;
						neededGrowRate = (sibLine->m_nNuSize + dif) / 
							sibLine->m_nNuSize;
						if(sibLine->m_locked)neededGrowRate = 1.0;
						if(sibLine->m_maxSet)neededGrowRate = 1.0;
						if(m3SibHitch && m4SibHitch)
						{
							if((m3 + m4)!=0)growRate = 
								(maxBkInverseFrChange + m3 + m4) /
								(m3 + m4);
							else 
							{
								growRate = neededGrowRate;
								sibLoose = TRUE;
							}
							if(neededGrowRate<growRate)growRate = 
								neededGrowRate;
							nuM3 = m3 * growRate;
							nuM4 = m4 * growRate;
							backFrameChange = (nuM3 - m3) + (nuM4 - m4);
						}
						double bkTransmitChange,backDif;
						if(!m3SibHitch && m4SibHitch)
						{
							line = m_reg[mg4ID];
							bkTransmitChange = (line->m_nNuSize * neededGrowRate) - 
								line->m_nNuSize;
							if(line->m_nNuSize!=0 && 
								bkTransmitChange>maxBkInverseFrChange)
							{
								line = m_reg[mg3ID];
								if(!line->m_locked)
								{
									backDif = bkTransmitChange - maxBkInverseFrChange;
									if(nuM3>=backDif)nuM3 = nuM3 - backDif;
									else 
									{
										nuM3 = 0.0;
										growRate = (m4 + (m3 + maxBkInverseFrChange))
											 / m4;
									}
								}
								else growRate = (m4 + maxBkInverseFrChange)
									/ m4;
							}
							else
							{
								growRate = neededGrowRate;
								backFrameChange = backDif;
								sibLoose = TRUE;
							}
							nuM4 = m4 * growRate;
						}
						if(m3SibHitch && !m4SibHitch)
						{
							line = m_reg[mg3ID];
							bkTransmitChange = (line->m_nNuSize * neededGrowRate) - 
								line->m_nNuSize;
							if(line->m_nNuSize!=0 && 
								bkTransmitChange>maxBkInverseFrChange)
							{
								line = m_reg[mg4ID];
								if(!line->m_locked)
								{
									backDif = bkTransmitChange - maxBkInverseFrChange;
									if(nuM4>=backDif)nuM4 = nuM4 - backDif;
									else 
									{
										nuM4 = 0.0;
										growRate = (m3 + (m4 + maxBkInverseFrChange))
											 / m3;
									}
								}
								else growRate = (m3 + maxBkInverseFrChange)
									/ m3;
							}
							else
							{
								growRate = neededGrowRate;
								backFrameChange = backDif;
								sibLoose = TRUE;
							}
							nuM3 = m3 * growRate;
						}
						if(!m3SibHitch && !m4SibHitch)sibLoose = TRUE;

						if(sibLoose)maxSibAccomodation = dif;
						else maxSibAccomodation = (sibLine->m_nNuSize * 
							growRate) - sibLine->m_nNuSize;
					}//if(sibLine->m_nNuSize!=0 && !bigger)
				}//if(m3SibHitch || m4SibHitch)
				else
				{
					if(bigger)
					{
						if(!sibLine->m_locked && !sibLine->m_minSet)
						{
							if(sibLine->m_nNuSize>=dif)
								maxSibAccomodation = dif;
							else maxSibAccomodation = sibLine->m_nNuSize;
						}
						else maxSibAccomodation = 0.0;
					}
					else
					{
						if(!sibLine->m_locked && !sibLine->m_maxSet)
							maxSibAccomodation = dif;
					}
				}
				if(dif>maxSibAccomodation)dif = dif - maxSibAccomodation;
				else dif = 0.0;
			}//if(!sibIs)
			if(sibIs)
			{
				maxSibAccomodation = 0.0;
				//the instigating factor was modified already by m3 & m4
				//constraints
			}
			frontReq = frontReq - dif;
			if(frontReq>=(maxSibAccomodation + frontFrChange))
				sibChange = maxSibAccomodation;
			else sibChange = frontReq - frontFrChange;
		}//if(frontReq>frontFrChange && !twoChannelCase)
		if(frontReq<=frontFrChange && !twoChannelCase)
		{
			frameChange = frontReq;
		}			
		if(twoChannelCase)
		{
			factor = FindFullCircleMarginChange(index,sibID,
				mg3ID,mg4ID,m3is,change,backFrChange,frontFrChange,
				frChange,bkFrChange,bigger,bkFrInvert,frFrInvert,
				nuMarg3,nuMarg4);
			if(bigger)sibChange = sibLine->m_nNuSize - 
				sibLine->m_nConting;
			else sibChange = sibLine->m_nConting - 
				sibLine->m_nNuSize;
			maxSibAccomodation = sibChange;
		}
		//limiting factors exist for single-channel problems
		BOOL limitFront = FALSE;
		if(!twoChannelCase)
		{
			if(sibIs && frontReq!=(change + sibChange))limitFront = TRUE;
			if(!sibIs)
			{
				if((change>=sibChange) && (frontReq!=(change - sibChange)))
					limitFront = TRUE;
				if((change<sibChange) && (frontReq!=(sibChange - change)))
					limitFront = TRUE;
			}
			if(!validBoost)limitFront = TRUE;
		}
		if(limitFront)
		{
			//m_case3 = TRUE;
			if(sibIs)
			{
				line = m_reg[index];
				CRegAspect* line2;
				line2 = m_reg[sibID];
				double nuSpan,oldSpan;
				oldSpan = line->m_nNuSize + line2->m_nNuSize;
				if(bigger)nuSpan =
					line->m_nNuSize + line2->m_nNuSize + frontReq;
				if(!bigger)nuSpan = 
					line->m_nNuSize + line2->m_nNuSize - frontReq;
				if(oldSpan!=0)factor = nuSpan / oldSpan;
				else 
				{
					factor = 999999999999;
					if(m_boostMarg && m_boostMargAmt>(frontFrChange / 2))
						m_boostMargAmt = frontFrChange / 2;
				}
			}
			if(!sibIs)
			{
				line = m_reg[index];
				if(bigger && !fullCircle)
				{
					double nuMarg = line->m_nNuSize + frontFrChange +
						maxSibAccomodation ;
					if(line->m_nNuSize!=0)factor = nuMarg / line->m_nNuSize;
				}
				if(!bigger && !fullCircle)
				{
					if(line->m_nNuSize!=0)factor = (line->m_nNuSize - 
						maxSibAccomodation - frontFrChange) / line->m_nNuSize;
				}
			}
		}//if(limitFront)
		adjReq = FALSE;
		if(factor!=origFact)adjReq = TRUE;
		if(!validBoost)m_boostMargAmt = 0.0;
		if(m_boostMargAmt!=origBoost)adjReq = TRUE;
		if(adjReq)
		{
			line = m_reg[index];
			if(bigger)change = 
				(line->m_nNuSize * factor) - line->m_nNuSize;
			if(!bigger)change = 
				line->m_nNuSize - (line->m_nNuSize * factor);
			if(m_boostMarg)change = m_boostMargAmt;
		}
		int frameFlags = 0;
		if(!frFrInverse)frameFlags = frontFrFlags;
		else frameFlags = invFrFrFlags;
		if(applyBackFrFlags)frameFlags = frameFlags | backFrFlags;
		if(frameFlags==(frameFlags | 1))m_case3 = TRUE;
		if(frameFlags==(frameFlags | 2))m_case11 = TRUE;
		if(frameFlags==(frameFlags | 4))m_case16 = TRUE;
		if(frameFlags==(frameFlags | 8))m_case8 = TRUE;

		//secondly implement move/////////////////////////////////////

		//implement front side changes

		//implement original margin change
		line = m_reg[index];
		line->m_asking = FALSE;
		if(factor!=1.0)
		{
			line->m_nNuSize = line->m_nNuSize * factor;
			if(bigger)
			{
				//line->m_minSetCur = TRUE;
				if(m_boostMarg)line->m_nNuSize = m_boostMargAmt;
			}
			//else line->m_maxSetCur = TRUE;
			line->m_alt = TRUE;
		}

		line = m_reg[sibID];
		line->m_asking = FALSE;
		if(sibIs && factor!=1.0)
		{
			line->m_nNuSize = line->m_nNuSize * factor;
			if(bigger)
			{
				line->m_minSetCur = TRUE;
				if(m_boostMarg)line->m_nNuSize = m_boostMargAmt;
			}
			else line->m_maxSetCur = TRUE;
			line->m_alt = TRUE;
		}
		if(!sibIs && factor!=1.0)
		{
			if(maxSibAccomodation!=0)
			{
				if(bigger)
				{
					if(line->m_nNuSize>=maxSibAccomodation)
						line->m_nNuSize = line->m_nNuSize - 
						maxSibAccomodation;
					else line->m_nNuSize = 0.0;//total quality
					line->m_minSetCur = TRUE;
				}
				else 
				{
					line->m_nNuSize = line->m_nNuSize + 
						maxSibAccomodation;
					line->m_maxSetCur = TRUE;
				}
				line->m_alt = TRUE;			
			}
		}

		if(frameChange!=0)
		{
			line = m_reg[frID];
			if(bigger)//decrease frame to accomodate
			{
				initCFact = 0.0;
				if(!frFrInverse && !line->m_minSet)
				{
					if(frameChange<=line->m_nNuSize)
						line->m_origReqSize = line->m_nNuSize - 
							frameChange;
					else line->m_origReqSize = 0.0;
					frShrink = TRUE;
				}
				if(frFrInverse && !line->m_maxSet)line->m_origReqSize = 
					line->m_nNuSize + frameChange;
			}

			if(!bigger)
			{
				if(!frFrInverse && !line->m_maxSet)
					line->m_origReqSize = line->m_nNuSize + frameChange;
				if(frFrInverse && !line->m_minSet)
				{
					if(frameChange>=line->m_nNuSize)
						line->m_origReqSize = line->m_nNuSize - 
							frameChange;
					else line->m_origReqSize = 0.0;
				}
			}
			old = line->m_nNuSize;
			nu = line->m_origReqSize;
			if(old!=0)frFactor = nu / old;
			else frFactor = 999999999999;
			maxFrAdj = InteriorAbilityForFrameChange(bkFrShrink,!horiz); 
			m_carryOutFrAdjOnly = TRUE;
			maxFrAdjFront = InteriorAbilityForFrameChange(frShrink,horiz);
			maxCFact = 
				AvailableCellChange(initCFact,backSideID,1,maxFrAdjFront);
			//m_mgnChange = FALSE;
			BOOL minBuf = line->m_minSetCur;
			BOOL maxBuf = line->m_maxSetCur;
			m_cellFactor = 1.0;
			maxf = ChangeAspectSize(frFactor,frID,4,maxFrAdj,maxCFact,
				FALSE,FALSE);
			line->m_minSetCur = minBuf;
			line->m_maxSetCur = maxBuf;
			m_carryOutFrAdjOnly = FALSE;
			double actualFrameChange;
			if(bigger)actualFrameChange = old - line->m_nNuSize;
			else actualFrameChange = line->m_nNuSize - old;
			double dif;
			if(actualFrameChange>=frameChange)dif = actualFrameChange - 
				frameChange;
			else dif = frameChange - actualFrameChange;
			if(dif>.00001)AfxMessageBox("A processing error has occurred.  If Problem persists, please notify vendor.  Function: MarginRequest()");
		
		}
		if(backFrameChange>0)
		{
			line = m_reg[bFrID];
			if(bigger)//decrease frame to accomodate
			{
				initCFact = 0.0;
				if(!bkFrInverse && !line->m_minSet)
				{
					bkFrShrink = TRUE;
					if(backFrameChange<=line->m_nNuSize)
						line->m_origReqSize = line->m_nNuSize - 
							backFrameChange;
					else line->m_origReqSize = 0.0;
				}
				if(bkFrInverse && !line->m_maxSet)
				{
					line->m_origReqSize = line->m_nNuSize + 
						backFrameChange;
					bkFrShrink = FALSE;
				}
			}
			if(!bigger)
			{
				if(!bkFrInverse && !line->m_maxSet)
				{
					line->m_origReqSize = line->m_nNuSize + 
						backFrameChange;
					bkFrShrink = FALSE;
				}
				if(bkFrInverse && !line->m_minSet)
				{
					if(line->m_nNuSize>=backFrameChange)
					{
						line->m_origReqSize = line->m_nNuSize - 
							backFrameChange;
					}
					else line->m_origReqSize = 0.0;
					bkFrShrink = TRUE;
				}
			}
			old = line->m_nNuSize;
			nu = line->m_origReqSize;
			if(old!=0)frFactor = nu / old;
			else frFactor = 999999999999;
			maxFrAdj = InteriorAbilityForFrameChange(frShrink,horiz); 
			maxFrAdjFront = InteriorAbilityForFrameChange(bkFrShrink,!horiz);
			maxCFact = 
				AvailableCellChange(initCFact,backSideID,1,maxFrAdjFront);
			//m_mgnChange = FALSE;
			m_cellFactor = 1.0;
			BOOL minBuf = line->m_minSetCur;
			BOOL maxBuf = line->m_maxSetCur;
			m_carryOutFrAdjOnly = TRUE;
			maxf = ChangeAspectSize(frFactor,bFrID,4,maxFrAdj,maxCFact,
				FALSE,FALSE);
			line->m_minSetCur = minBuf;
			line->m_maxSetCur = maxBuf;
			m_carryOutFrAdjOnly = FALSE;
			double actualFrameChange;
			if((bigger && !bkFrInverse)||(!bigger && bkFrInverse))
				actualFrameChange = old - line->m_nNuSize;
			if((!bigger && !bkFrInverse)||(bigger && bkFrInverse)) 
				actualFrameChange = line->m_nNuSize - old;
			double dif;
			if(actualFrameChange>=backFrameChange)dif = actualFrameChange - 
				backFrameChange;
			else dif = backFrameChange - actualFrameChange;
			if(dif>.00001)AfxMessageBox("A processing error has occurred.  If Problem persists, please notify vendor.  Function: MarginRequest()");
		}
		//change backside margins
		line = m_reg[mg3ID];
		line->m_nNuSize = nuM3;
		line->m_alt = TRUE;
		line = m_reg[mg4ID];
		line->m_nNuSize = nuM4;
		line->m_alt = TRUE;
	}//if(!fixMarg)
	
	//if(maxf==factor)AcceptChanges();
	if(factor>=origFact)dif = factor - origFact;
	else dif = origFact - factor;
	if(m_boostMarg && !validBoost)dif = origBoost;
	if(dif>0.00001 || fixMarg)
	{
		if(m3is || m4is || sibIs)m_case4 = TRUE;
		else
		{

		}
		int ans = 0;
		if(m_flagReporting)
		{
			CMessDlg dlg;
			dlg.str = GetAdvisoryStrings();
			if(dlg.DoModal()==IDOK)
			{
				if(dlg.m_yes)ans = 1;
				if(dlg.m_no)ans = 2;
				canDo = TRUE;
			}
		}
		if(!m_flagReporting)
		{
			ans = 1;
		}
		if(ans==0)//clean up reg stop processing 
		{
			m_instigatorCount = 0;
			//RejectChanges();
			RestoreAtStartComputeSettings();
		}
		//accept max change & continue
		if(ans==1)
		{
			//if(maxf!=1)AcceptChanges();
			//if(maxf==1)RejectChanges();
		}
		//forgo this change continue processing
		if(ans==2)
		{
			m_noAccept = TRUE;
			return FALSE;
		}
	}
	m_fixRCellChange = FALSE;

	return canDo;
}

double CCalc::FindFullCircleMarginChange(int index,int sibID,int m3ID,
										 int m4ID,BOOL m3is,
										 double curChange,
										 double backFrChange,
										 double frontFrChange,
										 double * frameChange,
										 double * backFrameChange,
										 BOOL bigger,BOOL * bkFrInverse,
										 BOOL * frFrInverse,
										 double * nuM3,
										 double * nuM4)
{
	//rework sibChange bkComplyMargChg and change to make the 
	//most of the frame adjustment parameters of both back
	//and front  this function handles the 'two-channel' situations,
	//whereas the main margin change function handles the single-
	//channel situations
	double factor=1.0,trackFactor=1.0,posFactor=1.0,curFactor;
	double curM1,curM2,curM3,curSib;
	double minBackDepleteFact,minFrontDepleteFact;
	double backDexLinkSpan,backSibLinkSpan;
	double boostAmt,trackBoostAmt;
	double bkFrChgConsummed=0.0,frFrChgConsummed=0.0;
	double lagSideDepleteFact;
	BOOL backFrChangeUsed=FALSE,frontFrChangeUsed=FALSE;
	BOOL totalDepletion = FALSE,conclude = FALSE;
	BOOL isBoost = FALSE,inversEffect=FALSE;
	BOOL bkFrInvert=FALSE,frFrInvert=FALSE;
	BOOL horiz = FALSE;
	BOOL allFree = TRUE,dexLinkFree=TRUE,sibLinkFree=TRUE;
	if(index==3 || index==4)horiz = TRUE;
	CRegAspect* line,*m3Line,*m4Line,*sibLine;
	line = m_reg[index];
	m3Line = m_reg[m3ID];
	m4Line = m_reg[m4ID];
	sibLine = m_reg[sibID];
	if(line->m_locked)allFree = FALSE;
	if(bigger && line->m_maxSet)allFree = FALSE;
	if(!bigger && line->m_minSet)allFree = FALSE;
	if(m3Line->m_locked)allFree = FALSE;
	if(m4Line->m_locked)allFree = FALSE;
	if(sibLine->m_locked)allFree = FALSE;
	if(bigger && sibLine->m_minSet)allFree = FALSE;
	if(!bigger && sibLine->m_maxSet)allFree = FALSE;
	if(line->m_nNuSize!=0 && bigger)curFactor = (line->m_nNuSize + 
		curChange) / line->m_nNuSize;
	if(line->m_nNuSize!=0 && !bigger)curFactor = (line->m_nNuSize - 
		curChange) / line->m_nNuSize;
	if(line->m_nNuSize==0)
	{
		isBoost = TRUE;
		curFactor = 999999999999;
	}
	if(m3is)
	{
		backDexLinkSpan = m3Line->m_nNuSize;
		backSibLinkSpan = m4Line->m_nNuSize;
		if(bigger && m3Line->m_maxSet){allFree = FALSE;
			dexLinkFree = FALSE;}
		if(!bigger && m3Line->m_minSet){allFree = FALSE;
			dexLinkFree = FALSE;}
		if(bigger && m4Line->m_minSet){allFree = FALSE;
			sibLinkFree = FALSE;}
		if(!bigger && m4Line->m_maxSet){allFree = FALSE;
			sibLinkFree = FALSE;}
	}
	else 
	{
		backDexLinkSpan = m4Line->m_nNuSize;
		backSibLinkSpan = m3Line->m_nNuSize;
		if(bigger && m4Line->m_maxSet){allFree = FALSE;
			dexLinkFree = FALSE;}
		if(!bigger && m4Line->m_minSet){allFree = FALSE;
			dexLinkFree = FALSE;}
		if(bigger && m3Line->m_minSet){allFree = FALSE;
			sibLinkFree = FALSE;}
		if(!bigger && m3Line->m_maxSet){allFree = FALSE;
			sibLinkFree = FALSE;}
	}
	curM1 = line->m_nNuSize;
	curM2 = backDexLinkSpan;
	curM3 = backSibLinkSpan;
	curSib = sibLine->m_nNuSize;
	double nuFactor,nuBoost=0.0,oldBackSpan,nuFrontSpan;
	BOOL frontDepleteIsValid = TRUE;
	BOOL backDepleteIsValid = TRUE;
	//	which frame is depleted first by the change?
	//	what factor of change depletes this frame change?
	if(backFrChange!=0 && frontFrChange!=0 && dexLinkFree)
	{
		if(backDexLinkSpan!=0)
		{
			if(bigger)minBackDepleteFact = 
				(backDexLinkSpan + backFrChange) / backDexLinkSpan;
			else
			{
				if(backDexLinkSpan>=backFrChange)minBackDepleteFact = 
					(backDexLinkSpan - backFrChange) / backDexLinkSpan;
				else 
				{
					minBackDepleteFact = 0.0;
					backDepleteIsValid = FALSE;
				}
			}
		}
		else isBoost = TRUE;
		if(line->m_nNuSize!=0)
		{
			if(bigger)minFrontDepleteFact = 
				(line->m_nNuSize + frontFrChange) / line->m_nNuSize;
			else
			{
				if(line->m_nNuSize>frontFrChange)minFrontDepleteFact = 
					(line->m_nNuSize - frontFrChange) / line->m_nNuSize;
				else 
				{
					minFrontDepleteFact = 0.0;
					frontDepleteIsValid = FALSE;
				}
			}
		}
		else isBoost = TRUE;
		if(!isBoost)
		{
			if(bigger)
			{
				if(minBackDepleteFact<=minFrontDepleteFact
					&& sibLinkFree)
				{
					if(curFactor<=minBackDepleteFact)
					{
						bkFrChgConsummed = (backDexLinkSpan * curFactor) - 
							backDexLinkSpan;
						frFrChgConsummed = (line->m_nNuSize * curFactor) -
							line->m_nNuSize;
						trackFactor = curFactor;
						conclude = TRUE;
					}
					if(curFactor>minBackDepleteFact)
					{
						backFrChangeUsed = TRUE;
						bkFrChgConsummed = backFrChange;
						if(minBackDepleteFact!=minFrontDepleteFact)
							frFrChgConsummed = (line->m_nNuSize * 
								minBackDepleteFact) - line->m_nNuSize;
						else 
						{
							if(frontDepleteIsValid)frFrChgConsummed = 
								frontFrChange;
						}
						trackFactor = minBackDepleteFact;
					}
				}
				if(minFrontDepleteFact<minBackDepleteFact)
				{
					if(curFactor<=minFrontDepleteFact)
					{
						bkFrChgConsummed = (backDexLinkSpan * curFactor) - 
							backDexLinkSpan;
						frFrChgConsummed = (line->m_nNuSize * curFactor) -
							line->m_nNuSize;
						trackFactor = curFactor;
						conclude = TRUE;
					}
					if(curFactor>=minFrontDepleteFact)
					{
						frontFrChangeUsed = TRUE;
						frFrChgConsummed = frontFrChange;
						if(minBackDepleteFact!=minFrontDepleteFact)
							bkFrChgConsummed = (backDexLinkSpan * 
								minFrontDepleteFact) - backDexLinkSpan;
						else 
						{
							if(backDepleteIsValid)bkFrChgConsummed = 
								backFrChange;
						}
						trackFactor = minFrontDepleteFact;
					}
				}
				curM1 = curM1 + frFrChgConsummed;
				curM2 = curM2 + bkFrChgConsummed;
			}
			else //if(!bigger)
			{
				if(minBackDepleteFact>=minFrontDepleteFact
					&& sibLinkFree)
				{
					if(curFactor>=minBackDepleteFact)
					{
						bkFrChgConsummed = backDexLinkSpan - 
							(backDexLinkSpan * curFactor);
						frFrChgConsummed = line->m_nNuSize -
							(line->m_nNuSize * curFactor);
						trackFactor = curFactor;
						conclude = TRUE;
					}
					if(curFactor<minBackDepleteFact)
					{
						backFrChangeUsed = TRUE;
						bkFrChgConsummed = backFrChange;
						if(minBackDepleteFact!=minFrontDepleteFact)
							frFrChgConsummed = line->m_nNuSize - 
								(line->m_nNuSize * minBackDepleteFact);
						else 
						{
							if(frontDepleteIsValid)frFrChgConsummed = 
								frontFrChange;
						}
						trackFactor = minBackDepleteFact;
					}
				}
				if(minBackDepleteFact<minFrontDepleteFact)
				{
					if(curFactor>=minFrontDepleteFact)
					{
						bkFrChgConsummed = backDexLinkSpan - 
							(backDexLinkSpan * curFactor);
						frFrChgConsummed = line->m_nNuSize -
							(line->m_nNuSize * curFactor);
						trackFactor = curFactor;
						conclude = TRUE;
					}
					if(curFactor<=minFrontDepleteFact)
					{
						frontFrChangeUsed = TRUE;
						frFrChgConsummed = frontFrChange;
						if(minBackDepleteFact!=minFrontDepleteFact)
							bkFrChgConsummed = backDexLinkSpan - 
								(backDexLinkSpan * minFrontDepleteFact);	
						else 
						{
							if(backDepleteIsValid)bkFrChgConsummed = 
								backFrChange;
						}
						trackFactor = minFrontDepleteFact;
					}
				}
				curM1 = curM1 - frFrChgConsummed;
				curM2 = curM2 - bkFrChgConsummed;
			}//if(!bigger)				
		}//if(!isBoost)
		else //(isBoost)
		{
			if(frontFrChange>=backFrChange)
			{
				if(m_boostMargAmt>=backFrChange)
				{
					backFrChangeUsed = TRUE;
					bkFrChgConsummed = backFrChange;
					frFrChgConsummed = backFrChange;
					trackBoostAmt = backFrChange;
				}
				else 
				{
					bkFrChgConsummed = m_boostMargAmt;
					frFrChgConsummed = m_boostMargAmt;
					trackBoostAmt = m_boostMargAmt;
					conclude = TRUE;
				}
			}
			if(frontFrChange<=backFrChange)
			{
				if(m_boostMargAmt>=frontFrChange)
				{
					frontFrChangeUsed = TRUE;
					frFrChgConsummed = frontFrChange;
					bkFrChgConsummed = frontFrChange;
					trackBoostAmt = frontFrChange;
				}
				else 
				{
					frFrChgConsummed = m_boostMargAmt;
					bkFrChgConsummed = m_boostMargAmt;
					trackBoostAmt = m_boostMargAmt;
					conclude = TRUE;
				}
			}
			curM1 = curM1 + frFrChgConsummed;
			curM2 = curM2 + bkFrChgConsummed;
		}//if(boost)
	}//if(backFrChange!=0 && frontFrChange!=0)
	if(backFrChange==0 && frontFrChange==0)
	{
		backFrChangeUsed = TRUE;
		frontFrChangeUsed = TRUE;
		bkFrChgConsummed = 0;
		frFrChgConsummed = 0;
	}
	if(backFrChange==0)backFrChangeUsed = TRUE;
	if(frontFrChange==0)frontFrChangeUsed = TRUE;
	if(backFrChangeUsed && frontFrChangeUsed)totalDepletion = TRUE;
	if(conclude)
	{
		if(m3is){*nuM3 = curM2;*nuM4 = curM3;}
		else {*nuM3 = curM3; *nuM4 = curM2;}
		line->m_nConting = curM1;
		sibLine->m_nConting = curSib;
		*backFrameChange = bkFrChgConsummed;
		*frameChange = frFrChgConsummed;
		*bkFrInverse = bkFrInvert;
		*frFrInverse = frFrInvert;
		factor = trackFactor;
		return factor;
	}

	//what is the affect of the transmitted change on the frame that is 
	//not yet depleted after the first frame allowance is used up: Is it
	//an inversion?
	double transmitRatio //...the two margins linked that start the change
		, compliantRatio;//...one back and one front margin absorbing the 
							//changes form a ratio that determines how
						//the last (undepleted)frame is changed
	if(line->m_nNuSize!=0)transmitRatio = backDexLinkSpan / 
		line->m_nNuSize;
	else transmitRatio = 1;
	if(sibLine->m_nNuSize!=0)compliantRatio = backSibLinkSpan / 
		sibLine->m_nNuSize;
	else compliantRatio = 1;
	if(compliantRatio<transmitRatio && backFrChangeUsed)
		inversEffect = TRUE;
	if(compliantRatio>transmitRatio && frontFrChangeUsed)
		inversEffect = TRUE;
	BOOL h = FALSE;
	BOOL inversFrShrink = !bigger;
	if(backFrChange==0){backFrChangeUsed = TRUE;h = horiz;}
	if(frontFrChange==0){frontFrChangeUsed = TRUE;h = !horiz;}
	double inverseFrChange,relFrameChg,reverseStgFact,r;
	if(inversEffect)inverseFrChange = 
			InteriorAbilityForFrameChange(inversFrShrink,h);
	if(((backFrChange==0 && frontFrChange!=0) || (backFrChange!=0 &&
		 frontFrChange==0)) && allFree)
	{
		BOOL lagSideFrUsed = FALSE;
		BOOL curFactReached = FALSE,reverseStage = TRUE;
		BOOL endButRefine = FALSE;
		int prec = 4;
		double frameChg,frameChangeRem,frChgConsummed,r;
		double nLT,sLT,nDST,sDST,nDSC,sDSC,nLC,sLC;
		if(frontFrChangeUsed)
		{
			sLT = curM2;
			sDST = curM1;
			sLC = curM3;
			sDSC = curSib;
			frameChangeRem = backFrChange - bkFrChgConsummed;
			frChgConsummed = bkFrChgConsummed;
			if(inversEffect)bkFrInvert = TRUE;
		}
		if(backFrChangeUsed)
		{
			sLT = curM1;
			sDST = curM2;
			sLC = curSib;
			sDSC = curM3;
			frameChangeRem = frontFrChange - frFrChgConsummed;
			frChgConsummed = frFrChgConsummed;
			if(inversEffect)frFrInvert = TRUE;
		}

		if(bigger)
		{
			//find closest percent to .00000000 accuracy
			//'n' means new
			//'s' means starting or original
			//'L' means side that did not use available frame change
			//'DS' means side that did deplete available frame change
			//'T' means side that transmits the original rate of change
			//'C' means compliant side margins
			for(r=trackFactor;r<curFactor;)
			{
				nLT = r * sLT; 
				nDST = r * sDST;
				nDSC = sDSC - (nDST - sDST);
				nLC = sLC * (nDSC / sDSC);
				if(!inversEffect)frameChg = frChgConsummed +
					((nLT - sLT) - (sLC - nLC));
				else
				{
					relFrameChg = ((sLC - nLC) - (nLT - sLT));
					if(reverseStage)
					{
						frameChg = frChgConsummed + relFrameChg;
						if(frChgConsummed<relFrameChg)
						{
							reverseStage = FALSE;
							reverseStgFact = r;
							frChgConsummed = relFrameChg - 
								frChgConsummed;
							if(inverseFrChange>frChgConsummed)
								frameChangeRem = inverseFrChange -
									frChgConsummed;
							else 
							{
								frameChangeRem = 0;
								endButRefine = TRUE;
							}
						}
					}
					else frameChg = frChgConsummed + relFrameChg;
				}
				if(r>=curFactor || frameChg>=frameChangeRem ||
					(sDSC<=(nDST - sDST)))
				{
					if(sDSC==(nDST - sDST))break;
					if(r==trackFactor)break;
					if(prec==12)break;
					if(prec==8){prec = 12; r = r - 0.00000001;}
					if(prec==4){prec = 8; r = r - 0.0001;}
					frameChg = frChgConsummed;
				}
				if(prec==4)r = r + 0.0001;
				if(prec==8)r = r + 0.00000001;
				if(prec==12)r = r + 0.000000000001;
			}
		}
		else //if(!bigger)
		{
			//find closest percent to .00000000 accuracy
			//first find 10,000th of a ratio change
			for(r=trackFactor;r>curFactor;)
			{
				nLT = r * sLT; 
				nDST = r * sDST;
				nDSC = sDSC + (sDST - nDST);
				nLC = sLC * (nDSC / sDSC);
				if(!inversEffect)frameChg = frChgConsummed +
					((sLT - nLT) - (nLC - sLC));
				else 
				{
					relFrameChg = ((nLC - sLC) - (sLT - nLT));
					if(reverseStage)
					{
						frameChg = frChgConsummed + relFrameChg;
						if(frChgConsummed<relFrameChg)
						{
							reverseStage = FALSE;
							reverseStgFact = r;
							frChgConsummed = relFrameChg - 
								frChgConsummed;
							if(inverseFrChange>frChgConsummed)
								frameChangeRem = inverseFrChange -
									frChgConsummed;
							else 
							{
								frameChangeRem = 0;
								endButRefine = TRUE;
							}
						}
					}
					else frameChg = frChgConsummed + relFrameChg;
				}
				if(r<=curFactor || frameChg>=frameChangeRem || 
					endButRefine)
				{
					if(sDSC==(sDST - nDST))break;
					if(r==trackFactor)break;
					if(prec==12)break;
					if(prec==8){prec = 12; r = r + 0.00000001;}
					if(prec==4){prec = 8; r = r + 0.0001;}
					frameChg = frChgConsummed;
					if(endButRefine && reverseStgFact<r)
						reverseStage = FALSE;
				}
				if(prec==4)r = r - 0.0001;
				if(prec==8)r = r - 0.00000001;
				if(prec==12)r = r - 0.000000000001;
			}
		}
		trackFactor = r;
		BOOL frFrChangeUsed = FALSE;
		BOOL bkFrChangeUsed = FALSE;
		if(backFrChangeUsed)
		{
			frFrChgConsummed = frFrChgConsummed + frameChg;
			if(frFrChgConsummed==frontFrChange)frFrChangeUsed = TRUE;
			curM1 = nLT;
			curM2 = nDST;
			curSib = nLC;
			curM3 = nDSC;
		}
		if(frontFrChangeUsed)
		{
			bkFrChgConsummed = bkFrChgConsummed + frameChg;
			if(bkFrChgConsummed==backFrChange)bkFrChangeUsed = TRUE;
			curM2 = nLT;
			curM1 = nDST;
			curM3 = nLC;
			curSib = nDSC;
		}
		if(frFrChangeUsed)frontFrChangeUsed = TRUE;
		if(bkFrChangeUsed)backFrChangeUsed = TRUE;
	}//if((backFrChange==0 && frontFrChange!=0) || (backFrChange!=0 &&
		// frontFrChange==0))
	if(curM1<0.0000000001)curM1 = 0.0;
	if(curM2<0.0000000001)curM2 = 0.0;
	if(curM3<0.0000000001)curM3 = 0.0;
	if(curSib<0.0000000001)curSib = 0.0;
	line->m_nConting = curM1;
	if(m3is)
	{
		*nuM3 = curM2;
		*nuM4 = curM3;
		//m3Line->m_nConting = curM2;
		//m4Line->m_nConting = curM3;
	}
	if(!m3is)
	{
		*nuM3 = curM3;
		*nuM4 = curM2;
		//m3Line->m_nConting = curM3;
		//m4Line->m_nConting = curM2;
	}
	sibLine->m_nConting = curSib;
	*backFrameChange = bkFrChgConsummed;
	*frameChange = frFrChgConsummed;
	*bkFrInverse = bkFrInvert;
	*frFrInverse = frFrInvert;
	factor = trackFactor;
	return factor;
}



///////////////////////////////////////////////////////////////////////
//merely for the sole pupose of diagnosing situations where constrained
// margins want to act upon this frame
double CCalc::InteriorAbilityForFrameChange(BOOL shrink, BOOL horiz)
{
	double change = 0.0,inAsp,asp,pageAsp,frameAsp,minAsp,nuInAsp;
	double nuOutAsp;
	BOOL lock = FALSE, innerLock = FALSE;
	BOOL interLock = FALSE, alt = FALSE;
	BOOL clear = TRUE, chainExtends = TRUE, loose = TRUE;
	BOOL nufRm = TRUE,case16=FALSE,case3=FALSE;
	CRegAspect* line,* countLine;
	int id,countID,inID,level,holdLevel = 4,count,pageID,frameID;
	int holdLevID;
	double minSizes[5];//convenient even though 0 & 1 are unused

	if(horiz) {id=17;pageID=6;frameID=17;}
	if(!horiz) {id=18;pageID=16;frameID=18;}
	line = m_reg[pageID];
	alt = line->m_alt;
	pageAsp = line->m_nNuSize;
	line = m_reg[frameID];
	alt = line->m_alt;
	frameAsp = line->m_nNuSize;
	holdLevID = id;

	for(level=4;level>1;level--)
	{
		line = m_reg[id];
		lock = line->m_locked;
		if(shrink && line->m_minSet)lock = TRUE;
		if(lock && level==4)return 0.0;

		inID = GetEnclosedAspectID(id);
		line = m_reg[inID];
		inAsp = line->m_nNuSize;

		countID = GetAssociatedCountID(inID);
		countLine = m_reg[countID];
		count = countLine->m_nNuCount;

		if(level==4)nuOutAsp = MINCBLK * count;
		nuInAsp = nuOutAsp / count;

		if(shrink)
		{
			double min;
			if(level==4)min = MINCBLK;
			if(level==3)min = MINBLK;//should work for any m_colorMode
			if(level==2)min = MINCELL;
			if(nuInAsp<min)
			{
				innerLock = TRUE;
				nuInAsp = min;
				holdLevel = level;
				holdLevID = id;
				m_backFrCase = m_backFrCase | 4;//case16 = TRUE;
				m_backFrCase = m_backFrCase ^ 1;//case3 = FALSE;
			}
			if(nuInAsp<inAsp && line->m_locked)
			{
				innerLock = TRUE;
				nuInAsp = inAsp;
				holdLevel = level;
				holdLevID = id;
				m_backFrCase = m_backFrCase | 1;//case3 = TRUE;
				m_backFrCase = m_backFrCase ^ 4;//case16 = FALSE;
			}
		}
		else if(line->m_maxSet)innerLock = TRUE;
	
		if(count!=1)chainExtends = FALSE;
		if(chainExtends && innerLock && count==1)
		{
			if(!shrink)
			{
				m_backFrCase = m_backFrCase | 1;//m_case3 = TRUE;
				m_backFrCase = m_backFrCase | 2;//m_case11 = TRUE;
			}
			loose = FALSE;
		}

		minSizes[level] = nuInAsp * count;

		nuOutAsp = nuInAsp;

		id = GetEnclosedAspectID(id);
	}

	if(shrink)//determine max decrease
	{	
		inAsp = minSizes[holdLevel];
		nuOutAsp = minSizes[holdLevel];
		id = GetEnclosingAspectID(holdLevID);
		level = holdLevel + 1;
		for( ;level<5;level++)
		{
			inID = GetEnclosedAspectID(id);
			countID = GetAssociatedCountID(inID);

			countLine = m_reg[countID];
			count = countLine->m_nNuCount;

			nuOutAsp = inAsp * count;

			inAsp = nuOutAsp;
			id = GetEnclosingAspectID(id);
		}
	}
	if(!shrink && loose)change = 999999999999;
	if(!shrink && !loose){m_case3M = TRUE;m_case11M = TRUE;change = 0.0;}
	if(shrink)change = frameAsp - nuOutAsp;
	if(change<0.000001)change = 0.0;
	if(case3)m_backFrCase = m_backFrCase | 2;//m_case3 = TRUE;
	if(case16)m_backFrCase = m_backFrCase | 6;//m_case16 = TRUE;
	return change;
}

double CCalc::AvailableCellChange(double fact, int id, int level,
								  double deltaFr)
{
	BOOL grow;
	int sib;
	double deltaC = 99,change,factC = 1.0;
	if(fact==999999999999)grow = TRUE;
	else grow = FALSE;
	if(grow)factC = GetMaxIncrease(fact,id,level,deltaFr,deltaC,
		TRUE,TRUE);
	if(!grow)factC = GetMaxDecrease(fact,id,level,deltaFr,deltaC,
		TRUE,TRUE);
	change = factC;
	return change;
}



BOOL CCalc::AutoAdjustCount(unsigned long * change,BOOL incrs,
							  BOOL curAspectIsHoriz,unsigned long * cols,
							  unsigned long * rows)
{
	unsigned long reduct,addAmt;
	BOOL nuFormat = TRUE;
	if(incrs)
	{
		addAmt = *change;
		if(addAmt==0)nuFormat = FALSE;
		if(addAmt>0)
		{
			if(curAspectIsHoriz)
			{
				*cols = *cols + 1;
				if(addAmt>=*rows)addAmt = addAmt - *rows;
				else addAmt = 0;
			}
			if(!curAspectIsHoriz)
			{
				*rows = *rows + 1;
				if(addAmt>=*cols)addAmt = addAmt - *cols;
				else addAmt = 0;
			}
		}
		*change = addAmt;
	}
	else
	{
		reduct = *change;
		if(reduct==0)nuFormat = FALSE;
		if(reduct>0)
		{
			if(curAspectIsHoriz)
			{
				if(reduct>=*rows && *cols>1)
				{
					reduct = reduct - *rows;
					*cols = *cols - 1;
				}
				else nuFormat = FALSE;
			}
			if(!curAspectIsHoriz)
			{
				if(reduct>=*cols && *rows>1)
				{
					reduct = reduct - *cols;
					*rows = *rows - 1;
				}
				else nuFormat = FALSE;
			}
		}
		*change = reduct;
	}
	return nuFormat;
}

BOOL CCalc::AutoAdjustCellCount(unsigned long * changeAmt,BOOL incrs,
							  BOOL curAspectIsHoriz,unsigned long * cols,
							  unsigned long * rows)
{
	BOOL nuAmt = FALSE;
	if(incrs)
	{
		if(curAspectIsHoriz)
		{
			if(*changeAmt>0){*cols = *cols + 1;nuAmt =TRUE;}
		}
		else if(*changeAmt>0){*rows = *rows + 1;nuAmt = TRUE;}			
	}
	else
	{
		if(curAspectIsHoriz)
		{
			if(*cols>1 && *changeAmt>0){*cols = *cols - 1;nuAmt = TRUE;}
		}
		else if(*rows>1 && *changeAmt>0){*rows = *rows - 1;nuAmt = TRUE;}
	}
	if(nuAmt)*changeAmt = *changeAmt - 1;
	return nuAmt;
}


void CCalc::StoreOrRestoreOriginalReqValues(CRegAspect * pLines[],BOOL store)
{
	if(store)
	{
		int i;
		for(i=0;i<27;i++)
		{
			CRegAspect * line = m_reg[i];
			CRegAspect * origLine = pLines[i];
			line->m_minSetCur = origLine->m_minSetCur;
			line->m_maxSetCur = origLine->m_maxSetCur;
			line->m_maxSet = origLine->m_maxSet;
			line->m_minSet = origLine->m_minSet;
			line->m_origReqSize = origLine->m_origReqSize;
			line->m_origReqCount = origLine->m_origReqCount;
		}
	}
	else
	{
		int i;
		for(i=0;i<27;i++)
		{
			CRegAspect * line = m_reg[i];
			CRegAspect * origLine = pLines[i];
			origLine->m_minSet = line->m_minSet;
			origLine->m_maxSet = line->m_maxSet;
			origLine->m_maxSetCur = line->m_maxSetCur;
			origLine->m_minSetCur = line->m_minSetCur;
			origLine->m_origReqSize = line->m_origReqSize;
			origLine->m_origReqCount = line->m_origReqCount;
		}
	}
}

void CCalc::StoreOrRemoveNewRegValues(CRegAspect * pLines[],BOOL store)
{
	if(store)
	{
		int i;
		for(i=0;i<27;i++)
		{
			CRegAspect * line = m_reg[i];
			CRegAspect * origLine = pLines[i];
			origLine->m_minSetCur = line->m_minSetCur;
			origLine->m_maxSetCur = line->m_maxSetCur;
			origLine->m_minSet = line->m_minSet;
			origLine->m_maxSet = line->m_maxSet;
			origLine->m_nNuSize = line->m_nNuSize;
			origLine->m_nNuCount = line->m_nNuCount;
			origLine->m_alt = line->m_alt;
		}
	}
	else
	{
		int i;
		for(i=0;i<27;i++)
		{
			CRegAspect * line = m_reg[i];
			CRegAspect * origLine = pLines[i];
			line->m_minSetCur = origLine->m_minSetCur;
			line->m_maxSetCur = origLine->m_maxSetCur;
			line->m_maxSet = origLine->m_maxSet;
			line->m_minSet = origLine->m_minSet;
			line->m_nNuSize = origLine->m_nNuSize;
			line->m_nNuCount = origLine->m_nNuCount;
			line->m_alt = origLine->m_alt;
		}
	}
}


BOOL CCalc::TestRangeAdjustments(UINT nuCount,UINT *range,BOOL incrs,
								 double freq,BOOL botLock,BOOL topLock,
								 UINT *toZ,UINT *toT)
{
	if(!m_rangeInvolve){m_case19 = TRUE;return FALSE;}
	BOOL permit = FALSE,widen=FALSE,narrow=FALSE;
	BOOL wideNuR=FALSE,naroNuR=FALSE;
	BOOL rangeAcceptible=FALSE;
	UINT measR,rangeAdjW=0,rangeAdjNa=0,maxRangeIncr=0,maxRangeDecr=0;
	UINT rangeAdj;
	if(!topLock)maxRangeIncr = *toT;
	if(!botLock)maxRangeIncr = maxRangeIncr + *toZ;
	if(!botLock)maxRangeDecr = *range;
	if(!topLock)maxRangeDecr = *range;
	int i;

	if(*range>(freq * (nuCount - 1)))naroNuR = TRUE;
	if(*range<(freq * (nuCount - 1)))wideNuR = TRUE;
	

	UINT nuSteps = freq * (nuCount - 1);
	if(nuSteps > 255){m_case15=TRUE;return FALSE;}

	if(wideNuR)rangeAdjW = nuSteps - *range;
	if(naroNuR)rangeAdjNa = *range - nuSteps;
	

	if(maxRangeIncr>=rangeAdjW && wideNuR)widen = TRUE;
	if(maxRangeDecr>=rangeAdjNa && naroNuR)narrow = TRUE;
		
	if(!widen && !narrow)
	{
		if(naroNuR || wideNuR)
		{
			if(wideNuR && (botLock || topLock))m_case18 = TRUE;
			if(wideNuR && (!botLock || !topLock))m_case14 = TRUE;
			if(naroNuR)
			{
				if(!botLock || !topLock)m_case15 = TRUE;
				else m_case18 = TRUE;
			}
			return FALSE;
		}
		else rangeAcceptible = TRUE;
	}
	if(widen)
	{	measR = rangeAdjW;
		if(!botLock)
		{
			if(*toZ>=measR){*toZ = *toZ - measR;measR = 0;}
			else {measR = measR - *toZ;*toZ = 0;}	
		}
		if(!topLock)
		{
			if(*toT>=measR){*toT = *toT - measR;measR = 0;}
			else {measR = measR - *toT;*toT = 0;}
		}
		if(measR!=0)
		{
			if(!topLock && !botLock)m_case14 = TRUE;
			if(topLock && botLock)m_case18 = TRUE;
			else if(topLock || botLock){m_case18 = TRUE;m_case14 = TRUE;}
		}
	}
	if(narrow && !widen)
	{
		measR = rangeAdjNa;
		if(!topLock)
		{
			if(*range>=measR){*toT = *toT + measR;measR = 0;}
			else 
			{
				m_case15 = TRUE;
				return FALSE;
			}
		}
		if(!botLock && topLock)
		{
			if(*range>=measR){*toZ = *toZ + measR;measR = 0;}
			else
			{
				m_case15 = TRUE;
				return FALSE;	
			}
		}
	}

	if(rangeAcceptible)permit = TRUE;
	if(measR==0){permit = TRUE;*range = 255 - (*toZ + *toT);}
	return permit;

}


BOOL CCalc::RequestBlockFormatChange(int index)
{
	BOOL lock = FALSE;
	BOOL cando=FALSE,grows=FALSE,shrinks=FALSE,countIncrs=TRUE;
	BOOL bulkProblem=FALSE;
	BOOL alt=FALSE;
	unsigned long count;
	int inID,outID;
	CRegAspect* line,*inLine,*outLine;

	if(index==19){inID = 1;outID = 2;}
	if(index==20){inID = 8;outID = 9;}
	if(m_colorMode!=1)outID = GetEnclosingAspectID(outID);
	if(index==21){inID = 2;outID = 17;}
	if(index==22){inID = 9;outID = 18;}

	inLine = m_reg[inID];
	outLine = m_reg[outID];
	line = m_reg[index];

	if(line->m_nNuCount>=line->m_origReqCount)countIncrs = FALSE;
	else countIncrs = TRUE;

	count = line->m_origReqCount;

	//determine if it is advantageous to change the count first
	BOOL nuCountForInBlockRequest = TRUE,nuCountForRect1;
	BOOL nuCountForOutBlockRequest = TRUE,nuCountForRect2;
	BOOL processInChangeFirst = TRUE;
	BOOL inShrink = TRUE;
	BOOL outShrink = TRUE;
	BOOL changeRect1 = TRUE;
	BOOL changeRect2 = TRUE;
	int firstRectID = inID;
	int secondRectID = outID;
	unsigned long countBuf = line->m_nNuCount;

	if(!inLine->m_instigating)inLine->m_origReqSize =inLine->m_nNuSize;
	if(!outLine->m_instigating)outLine->m_origReqSize = outLine->m_nNuSize;
	if(inLine->m_origReqSize>inLine->m_nNuSize)inShrink = FALSE;
	if(outLine->m_origReqSize>outLine->m_nNuSize)outShrink = FALSE;

	if(inShrink && count==1)//then count of two+ is needed
		nuCountForInBlockRequest = FALSE;
	if(!outShrink && count==1)//then count of two+ is needed
		nuCountForOutBlockRequest = FALSE;

	//determine if it is advantageous to process the inner block first
	if(count>line->m_nNuCount)
	{
		if(!inShrink)processInChangeFirst = FALSE;
	}

	//set up for initial series of requests
	if(processInChangeFirst)
	{
		changeRect1 = inLine->m_instigating;
		changeRect2 = outLine->m_instigating;
		nuCountForRect1 = nuCountForInBlockRequest;
		nuCountForRect2 = nuCountForOutBlockRequest;
	}
	else
	{
		firstRectID = outID;
		secondRectID = inID;
		changeRect1 = outLine->m_instigating;
		changeRect2 = inLine->m_instigating;
		nuCountForRect1 = nuCountForOutBlockRequest;
		nuCountForRect2 = nuCountForInBlockRequest;
	}

	//change first aspect
	if(nuCountForRect1)line->m_nNuCount = count;
	m_flagReporting = FALSE;
	if(changeRect1)RequestRect(firstRectID,FALSE);
	line->m_nNuCount = countBuf;
	
	//change second aspect
	if(nuCountForRect2)line->m_nNuCount = count;
	if(changeRect2)RequestRect(secondRectID,FALSE);
	line->m_nNuCount = countBuf;

	//diagnos results
	double bulkSpan = count * inLine->m_nNuSize;
	double roomSpan = outLine->m_nNuSize;

	if(bulkSpan>roomSpan)bulkProblem = TRUE;

	//new counts of 1 preceded and handled elsewhere, but here's the superflous attempt
	if(count==1 && bulkSpan!=roomSpan)bulkProblem = TRUE;

	//if too much bulk is created or too little for a count of '1',
	//then attempt to implement a non-requested block-col or -row change
	if(bulkProblem)
	{
		if(!inLine->m_minSet)
		{
			if(!inLine->m_locked)
			{
				if(nuCountForInBlockRequest)line->m_nNuCount = count;
				else line->m_nNuCount = countBuf;
				double reqBuf = inLine->m_origReqSize;
				inLine->m_origReqSize = roomSpan;
				if(count!=1)inLine->m_origReqSize = roomSpan / count;
				RequestRect(inID,FALSE);
				inLine->m_origReqSize = reqBuf;
				roomSpan = outLine->m_nNuSize;
				bulkSpan = inLine->m_nNuSize * count;
				if(count!=1 && bulkSpan<=roomSpan)cando = TRUE;
				if(roomSpan==bulkSpan)cando = TRUE;
			}
		}
		if(!cando && !outLine->m_maxSet)
		{
			if(!outLine->m_locked)
			{
				if(nuCountForOutBlockRequest)line->m_nNuCount = count;
				else line->m_nNuCount = countBuf;
				double reqBuf = outLine->m_origReqSize;
				outLine->m_origReqSize = bulkSpan;
				if(count!=1)outLine->m_origReqSize = bulkSpan * count;
				RequestRect(outID,FALSE);
				outLine->m_origReqSize = reqBuf;
				roomSpan = outLine->m_nNuSize;
				bulkSpan = inLine->m_nNuSize * count;
				if(count!=1 && bulkSpan<=roomSpan)cando = TRUE;
				if(roomSpan==bulkSpan)cando = TRUE;
			}
		}
		if(!cando)line->m_nNuCount = countBuf;
		else line->m_nNuCount = count;
	}
	else cando = TRUE;

	m_flagReporting = TRUE;

	if(cando)
	{
		line = m_reg[index];
		line->m_nNuCount = count;
		line->m_alt = TRUE;
		if(index==19)m_bColsPer = count;
		if(index==20)m_bRowsPer = count;
		if(index==21)m_cBColsPer = count;
		if(index==22)m_cBRowsPer = count;
		m_totalCells = m_cBlockCount * m_blockCount * m_colsPer *
			m_rowsPer;
	}
	if(!cando)
	{
		unsigned long affordableBlocks = 1;
		if(countIncrs)
		{
			if(inLine->m_nNuSize!=0)
				affordableBlocks = outLine->m_nNuSize / inLine->m_nNuSize;
			else affordableBlocks = line->m_nNuCount;
		}
		else affordableBlocks = 2;
		line->m_nNuCount = affordableBlocks;

		int ans = 0;
		CMessDlg dlg;
		dlg.str = GetAdvisoryStrings();
		if(dlg.DoModal()==IDOK)
		{
			if(dlg.m_yes)ans = 1;
			if(dlg.m_no)ans = 2;
		}
		if(ans==0)//clean up reg stop processing 
		{
			m_instigatorCount = 0;
			RejectChanges();
			RestoreAtStartComputeSettings();
		}
		//accept max change & continue
		if(ans==1)
		{
		//	AcceptChanges();
		}
		//forgo this change continue processing
		if(ans==2){	m_noAccept = TRUE;RejectChanges();}
	}

	return cando;
}

BOOL CCalc::RequestCBlockFormatChange(int index)
{
	BOOL cando;
	return cando;
}


double CCalc::ChangeAssociatedRectSize(double fact, int id, 
									   double maxFrAdj)
{
	double factor,max,asp;
	BOOL lock,req,alt;
	int level = 1;
	CRegAspect* line = m_reg[id];
	lock = line->m_locked;
	if(lock)
	{
		if(fact!=1.0)m_case3 = TRUE;
		return 1.0;
	}
	req = line->m_instigating;
	if(req)
	{
		double nuSize = line->m_origReqSize;
		double oldSize = line->m_nNuSize;
		if(oldSize==0){AfxMessageBox("Invalid data");return 1.0;}
		double assocFact = nuSize / oldSize;
		if((assocFact-fact)<0.00001)return fact;
		if(assocFact<1 && fact>1) m_case2 = TRUE; //reqs in conflict
		if(assocFact>1 && fact<1) m_case2 = TRUE; //reqs in conflict
		//DO I WANT TO SUPPORT A MAX CHANGE FOR TWO+ REQUESTS HERE????
		m_case4 = TRUE;
		return 1.0;
	}

	if(fact<1)max = GetMaxDecrease(fact,id,level,maxFrAdj,0,FALSE,TRUE);
	if(fact>1)max = GetMaxIncrease(fact,id,level,maxFrAdj,0,FALSE,TRUE);

	if(max>fact) AfxMessageBox("Erroneous return from CCalc::ChangeAspectSize();");
//	if(max<fact) max = ChangeAspectSize(max,id,level);

//	if(max==1){factor = 1;}		

	return max;
}

double CCalc::ChangeAssociatedMarginSizes(BOOL vertIsBackside)//called with !horiz
{
	int mgnID,mgnID2,mgnID3,mgnID4,frID;
	if(!vertIsBackside){mgnID=3; mgnID2=4;mgnID3=10; mgnID4=11;}
	if(vertIsBackside){mgnID=10; mgnID2=11; mgnID3=3; mgnID4=4;}
	BOOL boostRate1Marg = FALSE,boostRate2Marg = FALSE;
	BOOL m3arb=TRUE,m4arb=TRUE,validM1Boost=FALSE,validM2Boost=FALSE;
	double old,nu,rate1,rate2,boostMarg1Amt,boostMarg2Amt;

	//ascertain ratio from dictating set of margins on front side
	CRegAspect* line1 = m_reg[mgnID];
	old = line1->m_nSize;
	nu = line1->m_nNuSize;
	BOOL alt = line1->m_alt;
	if(alt)
	{
		if(old!=0)rate1 = nu / old;
		else 
		{
			validM1Boost = TRUE;//honor any change from zero as valid
				//AscertainBoostValidity(mgnID,mgnID2,mgnID3,mgnID4);
			if(validM1Boost)
			{
				rate1 = 999999999999;
				boostRate1Marg = TRUE;
				boostMarg1Amt = nu;
			}
			else rate1 = 1.0;
		}
	}
	if(!alt) rate1 = 1.0;
	CRegAspect* line2 = m_reg[mgnID2];
	old = line2->m_nSize;
	nu = line2->m_nNuSize;
	alt = line2->m_alt;
	if(alt)
	{
		if(old!=0)rate2 = nu / old;
		else
		{
			validM2Boost = TRUE;//honor any new non-zero value
				//AscertainBoostValidity(mgnID2,mgnID,mgnID3,mgnID4);
			if(validM2Boost)
			{
				rate2 = 999999999999;
				boostRate2Marg = TRUE;
				boostMarg2Amt = nu;
			}
			else rate2 = 1.0;
		}
	}
	if(!alt) rate2 = 1.0;

	//apply rates where appropriate to responding margins on back-side
	CRegAspect* line3 = m_reg[mgnID3];
	CRegAspect* line4 = m_reg[mgnID4];
	CRegAspect* line;

	BOOL link13 = DetermineInterlock(mgnID,mgnID3);
	BOOL link14 = DetermineInterlock(mgnID,mgnID4);
	BOOL link23 = DetermineInterlock(mgnID2,mgnID3);
	BOOL link24 = DetermineInterlock(mgnID2,mgnID4);

	if(link13)
	{
		line3->m_nNuSize = line3->m_nSize * rate1;
		if(boostRate1Marg)line3->m_nNuSize = boostMarg1Amt;
		if(rate1!=1.0)line3->m_alt = TRUE;
		m3arb = FALSE;
	}
	if(link14)
	{
		line4->m_nNuSize = line4->m_nSize * rate1;
		if(boostRate1Marg)line4->m_nNuSize = boostMarg1Amt;
		if(rate1!=1.0)line4->m_alt = TRUE;
		m4arb = FALSE;
	}
	if(link23)
	{
		line3->m_nNuSize = line3->m_nSize * rate2;
		if(boostRate2Marg)line3->m_nNuSize = boostMarg2Amt;
		if(rate2!=1.0)line3->m_alt = TRUE;
		m3arb = FALSE;
	}
	if(link24)
	{
		line4->m_nNuSize = line4->m_nSize * rate2;
		if(boostRate2Marg)line4->m_nNuSize = boostMarg2Amt;
		if(rate2!=1.0)line4->m_alt = TRUE;
		m4arb = FALSE;
	}
	//change backside margins
	if(m3arb)
	{
		line = m_reg[mgnID3];
		if(!m_backSideMargChangeAtForRect)
		{
			if(line->m_nNuSize!=m_m3)line->m_alt = TRUE;
			line->m_nNuSize = m_m3;
		}
	}
	if(m4arb)
	{
		line = m_reg[mgnID4];
		if(!m_backSideMargChangeAtForRect)
		{
			if(line->m_nNuSize!=m_m4)line->m_alt = TRUE;
			line->m_nNuSize = m_m4;
		}
	}

	double ratio = 1;
	return ratio;
}

double CCalc::ChangeAspectSize(double fact,int id,int level)
{
	BOOL pre = TRUE;
	double dummy = 1,dummy1 = 1;
	double max = 1;
	if(fact>1)max = GetMaxIncrease(fact,id,level,dummy,dummy1,pre,FALSE);
	if(fact<1)max = GetMaxDecrease(fact,id,level,dummy,dummy1,pre,FALSE);
	return max;
}

double CCalc::ChangeAspectSize(double fact,int id,int level,
		double deltaFr,double deltaC,BOOL prelim,BOOL forC)
{	
	double max = 1;
	if(fact>1)max = GetMaxIncrease(fact,id,level,deltaFr,deltaC,
									prelim,forC);
	if(fact<1)max = GetMaxDecrease(fact,id,level,deltaFr,deltaC,
									prelim,forC);
	return max;
}

double CCalc::GetMaxIncrease(double fact, int id, int level,double maxFrAdj,
							 double maxCFact,BOOL prelim,BOOL forRect)
{
	double inAsp,outAsp,oldAsp,nuAsp;
	double oldPageSpan,oldPageFrame,pageSpan;
	double factor;
	double marg,marg2,oldMargSpan,backMgnSpanParam;
	double nuMargLimit,nuMargLimit2,nuMargSpan;
	double oldBackMargSpan,curBackMargSpan;
	double minFrontMargSpan,maxFrontMargSpan;
	double oldM3,oldM4,m3,m4,maxRate3,maxRate4;
	double maxRateM3,maxRateM4,optRateM1,optRateM2,cellFactor;
	double absoMax,maxRate34,M1param,M2param;
	double nuFrame,nuSpan,backCell,maxCellAsp;
	double nuM1,nuM2;

	int inID = id, outID, mgnID, mgnID2,mgnID3,mgnID4;
	int pframeID,countID,pageID, enclosedID,sibling;
	int lastAltLevel = 0, startLevel = level;
	signed short welds = 0;
	UINT count;

	BOOL horiz,alt=FALSE,constrainR = FALSE,app = FALSE;
	BOOL limit,lock=FALSE,nufRm = FALSE,findMax = FALSE;
	BOOL m3lck=FALSE,m4lck=FALSE,m1lck=FALSE,m2lck=FALSE;
	BOOL fixMarg = FALSE, fixMarg2 = FALSE;
	BOOL min = FALSE, max = FALSE;
	BOOL fixM = FALSE, interlock = FALSE,outAspReq = FALSE;
	BOOL fix = FALSE,req=FALSE,vacLock=FALSE,squeeze=FALSE;
	BOOL cellImpede=FALSE,cellWeld=FALSE,suckOut=TRUE;

	m_boostMarg2ndary = FALSE;
	m_boostMarg = FALSE;

	//limit cell change by maxCFact
	if(level==1 && !prelim && m_cellR && !forRect)
	{
		if(fact>maxCFact)
		{
			cellImpede = TRUE;
			m_case4 = TRUE;
			fact = maxCFact;
			ApplyCellCaseFlags();
		}
		m_cellFactor = fact;
	}

	CRegAspect* line = m_reg[id];
	alt = line->m_alt;
	lock = line->m_locked;
	horiz = line->m_horiz;
	max = line->m_maxSet;
	min = line->m_minSet;
	constrainR = line->m_fixedRatio;
	oldAsp = line->m_nSize;
	if(prelim && forRect)nuAsp = 999999999999;
	if(!prelim && !forRect)nuAsp = line->m_origReqSize;
	if(!prelim && forRect)nuAsp = line->m_nNuSize * fact;
	if(prelim && !forRect)nuAsp = line->m_nNuSize * fact;
	if(cellImpede)nuAsp = fact * line->m_nNuSize;
	if(m_cellR && level==1)maxCellAsp = maxCFact * line->m_nSize;
	if(prelim && !forRect)
	{
		m_frontM1Rate = 1.0;
		m_frontM2Rate = 1.0;
	}


	inAsp = nuAsp;
	line->m_nConting = inAsp;

	if(min && nuAsp<line->m_nNuSize)
	{
		return 1.0;
	}
	if(max)
	{
		m_case2 = TRUE;
		return 1.0;
	}
	if(!prelim)line->m_alt = TRUE;//request IS being made from somewhere!
	if(!prelim && !forRect)line->m_applied = TRUE;
	if(constrainR)m_fixRCellChange = TRUE;
	

	if(lock)
	{
		if(prelim)m_case3C = TRUE;
		if(level==5)m_case9 = TRUE;
		return 1.0;
	}
	
	if(horiz)
		{pframeID=17; pageID=6; mgnID=3; mgnID2=4;mgnID3=10;mgnID4=11;}
	if(!horiz)
		{pframeID=18; pageID=16; mgnID=10; mgnID2=11;mgnID3=3;mgnID4=4;}

	if(id!=6 && id!=16)squeeze = TRUE;
	if(id==6 || id==16)squeeze = FALSE;

	int margCode = 1;
	if(level==4)margCode = 4;
	fixMarg = CheckMarginMobility(mgnID,margCode,squeeze);
	fixMarg2 = CheckMarginMobility(mgnID2,margCode,squeeze);
	if(fixMarg && fixMarg2)fix = TRUE;

	line = m_reg[mgnID];
	m1lck = line->m_locked;
	marg = line->m_nNuSize;
	nuM1 = marg;

	line = m_reg[mgnID2];
	m2lck = line->m_locked;
	marg2 = line->m_nNuSize;
	nuM2 = marg2;

	//initialize 'backside' factors
	line = m_reg[mgnID3];
	m3 = line->m_nNuSize;
	req = line->m_instigating;
	lock = line->m_locked;
	if(lock)m3lck = TRUE;
	oldM3 = line->m_nSize;
	
	line = m_reg[mgnID4];
	m4 = line->m_nNuSize;
	req = line->m_instigating;
	lock =  line->m_locked;
	if(lock)m4lck = TRUE;
	oldM4 = line->m_nSize;
	
	oldBackMargSpan = oldM4 + oldM3;
	curBackMargSpan = m4 + m3;

	if(squeeze)
	{
		absoMax = 0.0;
		backMgnSpanParam = curBackMargSpan - maxFrAdj; //gives a minimum
		if(m1lck)M1param = marg;
		else M1param = 0.0;
		if(m2lck)M2param = marg2;
		else M2param = 0.0;
		minFrontMargSpan = M1param + M2param;
	}
	if(!squeeze)
	{
		absoMax = 999999999999;
		double M3param;
		double M4param;
		if(m3lck)M3param = 0.0;
		else M3param = m3;
		if(m4lck)M4param = 0.0;
		else M4param = m4;
		backMgnSpanParam = M4param + M3param + maxFrAdj; //gives a maximum
		maxFrontMargSpan = 999999999999;
	}

	line = m_reg[pageID];
	oldPageSpan = line->m_nSize;
	pageSpan = line->m_nNuSize;

	line = m_reg[pframeID];
	//oldPageFrame = line->m_nSize;
	
	//ascertain if there are welded aspects below
	//current level to determine suction
	enclosedID = GetEnclosedAspectID(id);
	if(level==4 && m_colorMode!=1)enclosedID = 
		GetEnclosedAspectID(enclosedID);
	countID = GetAssociatedCountID(enclosedID);



	double * nuAspect = &nuAsp;
	double * f = &fact;
	double * pMaxCFact = &maxCFact;
	BOOL * outSideWeld = &cellWeld;
	BOOL margInsuff = FALSE;
	int startID = id;
	welds = FigureWeldsAndRamifications(level,countID,suckOut,startID,
									margInsuff,id,fixMarg,fixMarg2,fix,
									nuAspect,f,pMaxCFact,outSideWeld,
									min);
	if(welds<0 || welds==-1)vacLock = TRUE;
	line = m_reg[id];
	line->m_nConting = nuAsp;

	if(vacLock/* && startLevel!=4*/)
	{
		m_case11 = TRUE;
		m_case3 = TRUE;
		return 1.0;
	}
	level = startLevel;
	outID = inID;
	if(level==2 && m_colorMode!=1)outID = GetEnclosingAspectID(inID);
	lock = FALSE;


	//special level==5 stuff
	if(level==5)
	{
		inID = GetEnclosedAspectID(inID);
		line = m_reg[pframeID];
		inAsp = line->m_nNuSize;
		line->m_nConting = inAsp;
		nuFrame = inAsp;
		pageSpan = nuAsp;
	}

	//Increment both up and down through the heirarchy of blocks,
	//c-blocks, etc... and determine how much 'max' change can be
	//placed in the m_nConting member variable
	for( ;level<6;level++)
	{
		outID = GetEnclosingAspectID(outID);//if level==5 unnecessary but accurate
		line = m_reg[outID];//line is now in step with 'level'['s]under 5
		outAspReq = line->m_instigating;
		max = line->m_maxSet;
		outAsp = line->m_nNuSize;
		if(level==5)outAsp = nuAsp;
		lock = line->m_locked;

		int countID = GetAssociatedCountID(inID);
		if(countID!=99)
		{
			line = m_reg[countID];
			count = line->m_nNuCount;
		}
		else count = 1;

		nuSpan = inAsp * count;
		
		if(level==4 || level==5)
		{
			line = m_reg[inID];
			oldPageFrame = line->m_nNuSize;
			double * optRM1 = &optRateM1;
			double * optRM2 = &optRateM2;
			nuMargSpan = outAsp - nuSpan;
			if(level==4)
			{
				if(nuMargSpan<minFrontMargSpan)nuMargSpan = 
					minFrontMargSpan;
				if(nuSpan>outAsp)nuMargSpan = minFrontMargSpan;
				nuFrame = outAsp - nuMargSpan;
			}
			if(level==4)CalcMarginSqueezeRates(optRM1,optRM2,mgnID,
								mgnID2,mgnID3, mgnID4, absoMax,
								maxFrAdj, nuMargSpan, backMgnSpanParam,
								squeeze,nuFrame,pageSpan);
			if(level==5)CalcMarginExpandRates(optRM1,optRM2,mgnID,
								mgnID2,mgnID3, mgnID4, absoMax,
								maxFrAdj, nuMargSpan, backMgnSpanParam,
								squeeze,nuFrame,outAsp);
			nuM1 = (optRateM1 * marg);
			nuM2 = (optRateM2 * marg2);
			if(m_boostMarg)
			{
				if(m_boostMargID==mgnID)nuM1 = m_boostMargAmt;
				if(m_boostMargID==mgnID2)nuM2 = m_boostMargAmt;
			}
			if(m_boostMarg2ndary)
			{
				if(m_boostMarg2ndaryID==mgnID)nuM1 = m_boostMarg2ndaryAmt;
				if(m_boostMarg2ndaryID==mgnID2)nuM2 = m_boostMarg2ndaryAmt;
			}
			nuMargSpan = nuM1 + nuM2;
			nuFrame = nuAsp - nuMargSpan;
			//backside cell change may run into margin conflicts
			if(!prelim && forRect)
			{
				BOOL conflict = FALSE;
				if(DetermineInterlock(mgnID,mgnID3) && 
					(m_frontM1Rate != optRateM1)) conflict = TRUE;
				if(DetermineInterlock(mgnID,mgnID4) && 
					(m_frontM1Rate != optRateM2)) conflict = TRUE;
				if(DetermineInterlock(mgnID2,mgnID3) && 
					(m_frontM2Rate != optRateM1)) conflict = TRUE;
				if(DetermineInterlock(mgnID2,mgnID4) && 
					(m_frontM2Rate != optRateM2)) conflict = TRUE;
				if(conflict)
				{
					m_case4 = TRUE;
					return 1.0;
				}
				else m_backSideMargChangeAtForRect = TRUE;
			}
			lock = TRUE;
			if(level==4)
			{
				outAsp = pageSpan - nuMargSpan;
				if(m_carryOutFrAdjOnly)outAsp = nuAsp;
			}
			if(level==5)
			{
				//check if the margins are adaquate
				if(nuMargSpan<(outAsp - inAsp))
				{
					double availAsp;
					BOOL frameGrowLimit=FALSE;
					//refigure fact & inAsp if margins couldn't expand
					//and the expandability of frame is limited
					margInsuff = TRUE;
					welds = FigureWeldsAndRamifications
						(level,countID,suckOut,startID,
						 margInsuff,id,fixMarg,fixMarg2,fix,
						 nuAspect,f,pMaxCFact,outSideWeld,
						 min);
					if((welds==3 && m_colorMode!=1)|| welds>3)
					{
						availAsp = nuMargSpan + maxCellAsp;
						if(availAsp!=nuAsp)
						{
							nuAsp = availAsp;
							inAsp = availAsp;
							frameGrowLimit = TRUE;
							outAsp = availAsp + nuMargSpan;
							line = m_reg[id];
							fact = outAsp / line->m_nNuSize;
						}
					}
					if(inAsp<(outAsp - nuMargSpan))
					{
						if(!frameGrowLimit && welds!=-1)
						{
							inAsp = outAsp - nuMargSpan;
							nuAsp = outAsp;
						}
					}
					if(welds==-1)
					{
						outAsp = inAsp + nuMargSpan;
						nuAsp = outAsp;
						line = m_reg[id];
						fact = outAsp / line->m_nNuSize;
					}

					line = m_reg[pframeID];
					line->m_nConting = outAsp - nuMargSpan;
				}
			}
		}

		//handle situations
		if(nuSpan<=outAsp)
		{
			ClearMargCaseFlags();
			ClearCellCaseFlags();
			if(prelim)return fact;
			nufRm = TRUE;
			inAsp = outAsp;
			break;
		}
		if(lock || max)// || (level!=5 && outAspReq)
		{
			if(level==4)ApplyMargCaseFlags();
			if(lock && level!=4) m_case3 = TRUE;
			if(max)m_case2 = TRUE;
			findMax = TRUE; break;
		}
		if(nuSpan>outAsp)
		{
			line = m_reg[outID];
			line->m_nConting = nuSpan;	
			lastAltLevel = level;
		}

		inID = outID;
		if(level==2 && m_colorMode!=1)level++;
		if(level==1 && m_colorMode!=1)outID = GetEnclosingAspectID(outID);
		inAsp = nuSpan;  
	}//for( ;level<


	if(level>4)
	{
		nufRm = TRUE;
		level = 5;
	}
	startLevel = GetLevel(id);
	for( ;level>=startLevel;level--)
	{
		if(nufRm && level <= lastAltLevel)
		{
			line = m_reg[outID];
			if(!prelim)
			{
				line->m_nNuSize = line->m_nConting;
				line->m_alt = TRUE;
			}
		}
		if(nufRm && level==5)//is never pushed out by inner aspects
		{
			if(!fixMarg && !fixMarg2)
			{
				line = m_reg[pframeID];
				line->m_nNuSize = line->m_nConting;
				double nuMarg;
				double nuMarg2;
				line = m_reg[mgnID];
				nuMarg = nuM1;
				if(line->m_nSize!=0)
					m_frontM1Rate = nuM1;
				else m_frontM1Rate = 999999999999;
				line->m_nNuSize = nuMarg;
				line->m_alt = TRUE;
				line = m_reg[mgnID2];
				nuMarg2 = nuM2;
				line->m_nNuSize = nuMarg2;
				if(line->m_nSize!=0)
					m_frontM2Rate = nuMarg2 / line->m_nSize;
				else m_frontM2Rate = 999999999999;
				line->m_alt = TRUE;
				m_mgnChange = TRUE;
			}
			if(!fixMarg && fixMarg2)
			{
				double nuMarg;
				line = m_reg[mgnID];
				nuMarg = nuM1;
				line->m_nNuSize = nuMarg;
				if(line->m_nSize!=0)
					m_frontM1Rate = nuMarg / line->m_nSize;
				else m_frontM1Rate = 999999999999;
				line->m_alt = TRUE;
				m_mgnChange = TRUE;
			}
			if(fixMarg && !fixMarg2)
			{
				double nuMarg2;
				line =m_reg[mgnID2];
				nuMarg2 = nuM2;
				line->m_nNuSize = nuMarg2;
				if(line->m_nSize!=0)
					m_frontM2Rate = nuMarg2 / line->m_nSize;
				else m_frontM2Rate = 999999999999;
				line->m_alt = TRUE;
				m_mgnChange = TRUE;
			}
			if(fixMarg && fixMarg2)
			{
				//line = m_reg[pframeID];
				//line->m_nNuSize = line->m_nConting;
				//line->m_alt = TRUE;
			}
		}
		if((nufRm && level>startLevel) ||(nufRm && startLevel==4 &&
			!m_carryOutFrAdjOnly))
		{
			if(level==4)
			{
				line = m_reg[mgnID];
				if(!prelim)
				{
					line->m_nNuSize = nuM1;
					m_frontM1Rate = optRateM1;
					line->m_alt = TRUE;
					m_mgnChange = TRUE;
				}
				line = m_reg[mgnID2];
				if(!prelim)
				{
					line->m_nNuSize = nuM2;
					m_frontM2Rate = optRateM2;
					line->m_alt = TRUE;
					m_mgnChange = TRUE;
				}
				line = m_reg[pframeID];
				if(!prelim)
				{
					line->m_nNuSize = nuSpan;
					line->m_alt = TRUE;
				}
			}
			outID = inID;
			inID = GetEnclosedAspectID(inID);
			if(level==4 && m_colorMode!=1)
			{
				inID = GetEnclosedAspectID(inID);
			}
		}
		BOOL finalit = FALSE;
		if(startLevel==2 && level==4 && m_colorMode!=1)
			finalit = TRUE;
		if(level==startLevel)finalit = TRUE;
		if(nufRm && finalit)
		{
			line = m_reg[id];
			line->m_nNuSize = line->m_nConting;
			if(level==5)line->m_nNuSize = nuAsp;
			line->m_alt = TRUE;
			line->m_minSetCur = TRUE;
			line->m_maxSetCur = TRUE;
			factor = fact;
			break;
		}
		if(findMax)
		{
			if(level<4)
			{
				int countID = GetAssociatedCountID(inID);
				line = m_reg[countID];
				UINT count;
				count = line->m_nNuCount;
				if(count!=0)inAsp = outAsp / count;
				else inAsp = 999999999999;
				line = m_reg[inID];
				if(prelim && level==startLevel)
				{
					double oldInAsp = line->m_nNuSize;
					if(oldInAsp!=0)factor = inAsp / oldInAsp;
					else factor = 999999999999;
					return factor;
				}
				if(!prelim)
				{
					line->m_alt = TRUE;
					line->m_nNuSize = inAsp;
				}
				if(m_colorMode!=1 && startLevel==2 && level==4)
					finalit = TRUE;	
				if(finalit)
				{
					factor = (outAsp / count) / oldAsp;
					if(level==1)m_cellFactor = factor;
				}
				outID = inID;
				inID = GetEnclosedAspectID(inID);
				outAsp = inAsp;
			}
			//level==4 signifies: 1)margin aspects were involved and
			//2)that the request was not from page aspect and there fore
			//3)margins were not enlarged within this function call, but
			//may have been squeezed
			if(level==4)//signifies that margin specifics were involved
			{
				line = m_reg[inID];
				if(!prelim)
				{
					//outAsp retained relevant val
					line->m_nNuSize = outAsp; 
					line->m_alt = TRUE;
				}
				if(startLevel==4)fact = line->m_nNuSize / line->m_nSize;

				//notify if margin constraints that are a problem in terms
				//of complexity
				if(fixM)m_case4 = TRUE;

				if(!fixMarg && !fixMarg2)
				{
					line = m_reg[mgnID];
					if(!prelim)line->m_nNuSize = nuM1;
					if(optRateM1!=1.0)m_mgnChange = TRUE;
					m_frontM1Rate = optRateM1;
					if(!prelim)
					{
						line->m_alt = TRUE;
					}
					line = m_reg[mgnID2];
					if(!prelim)line->m_nNuSize = nuM2;
					if(optRateM2!=1.0)m_mgnChange = TRUE;
					m_frontM2Rate = optRateM2;
					if(!prelim)
					{
						line->m_alt = TRUE;
					}
					
					m_case5 = TRUE;//page too small notification
				}
				if(fixMarg && !fixMarg2)
				{
					line = m_reg[mgnID2];
					if(!prelim)line->m_nNuSize = nuM2;
					if(optRateM2!=1.0)m_mgnChange = TRUE;
					m_frontM2Rate = optRateM2;
					if(!prelim)
					{
						line->m_alt = TRUE;
						m_case3 = TRUE;
					}
				}
				if(!fixMarg && fixMarg2)
				{
					line = m_reg[mgnID];
					if(!prelim)line->m_nNuSize = nuM1;
					if(optRateM1!=1.0)m_mgnChange = TRUE;
					m_frontM1Rate = optRateM1;
					if(!prelim)
					{
						line->m_alt = TRUE;
						m_case3 = TRUE;
					}
				}
				outID = inID;
				inID = GetEnclosedAspectID(inID);
				if(m_colorMode!=1)inID = GetEnclosedAspectID(inID);
				
			}//if(level==4)
			
		}//if(findMax
		if(level==4 && m_colorMode!=1)level--;
	}//for
		
	//if(drawn by block)m_fixRCellChange = TRUE;
	//provide for aspects drawn in by a count equal to 1
	level = startLevel;
	line = m_reg[id];
	outAsp = line->m_nNuSize;
	enclosedID = GetEnclosedAspectID(id);
	if(level==4 && m_colorMode!=1)
		enclosedID = GetEnclosedAspectID(enclosedID);
	if(level==5 && m_colorMode!=1 && welds>0)welds++;
	for( ;welds>0;welds--)
	{
		line = m_reg[enclosedID];
		if(!prelim)
		{
			if(enclosedID==0 || enclosedID==7)
			{
				if(!forRect)
				{
					if(line->m_nNuSize!=0)
						m_cellFactor = nuAsp / line->m_nNuSize;
					else m_cellFactor = 999999999999;
				}
			}
			if(enclosedID==17 || enclosedID==18)outAsp = line->m_nConting;
			line->m_nNuSize = outAsp;
			line->m_alt = TRUE;
		}
		enclosedID = GetEnclosedAspectID(enclosedID);
	}
	
	return factor;
}


/////////////////////////////////////////////////////////////////////

double CCalc::GetMaxDecrease(double fact, int id, int level,double maxFrAdj,
							 double maxCFact,BOOL prelim,BOOL forRect)
{
	double inAsp,outAsp,oldInAsp,oldAvail,nuAsp;
	double pageSpan, oldPageSpan,oldPageFrame;
	double oldAsp,factMod = fact, factor;
	double marg,marg2,startMarg,startMarg2;
	double m3,m4,oldM3,oldM4;
	double optRateM1,optRateM2;
	double oldBackMargSpan,backMgnSpanParam,nuMargSpan;
	double maxFrontMargSpan,minFrontMargSpan,nuFrame;
	double M1param,M2param,absoMax;
	double minCellAsp = 0.0;
	double nuM1,nuM2;
	double minSz;
	m_boostMarg2ndary = FALSE;
	m_boostMarg = FALSE;

	if(prelim)m_frontM1Rate = 1.0;
	if(prelim)m_frontM2Rate = 1.0;

	int inID, outID = id, mgnID, mgnID2,mgnID3,mgnID4;
	int	pframeID,pageID,countID,enclosingID;
	int lastAltLevel = 10,startLevel = level;
	int welds = 0,modeAdj = 0;
	UINT count;

	BOOL horiz, alt=FALSE,max=FALSE,req=FALSE,app=FALSE,min=FALSE;
	BOOL limit,lock,nufRm = FALSE,findMax = FALSE,inAspReq = FALSE;
	BOOL constrainR = FALSE,interpolateCellFlags=FALSE;
	BOOL mConstr=FALSE,mConstr2=FALSE;
	BOOL fixMarg = FALSE, fixMarg2 = FALSE, suckMrgFr = FALSE;
	BOOL m1lck=FALSE,m2lck=FALSE,m3lck=FALSE,m4lck=FALSE;
	BOOL fixM = FALSE, interlock = FALSE, vacLock = FALSE;
	BOOL fix = FALSE,squeeze = FALSE,suckOut = FALSE;
	BOOL cellImpede=FALSE,frameWeld=FALSE,modifiedOutAsp=FALSE;
	BOOL minCase16=FALSE;
	BOOL minCase4=FALSE;
	BOOL lockCase3=FALSE;

	CRegAspect* line,*cLine;
		
	line = m_reg[id];
	alt = line->m_alt;
	horiz = line->m_horiz;
	min = line->m_minSet;
	max = line->m_maxSet;
	constrainR = line->m_fixedRatio;
	oldAsp = line->m_nSize;
	nuAsp = line->m_origReqSize;

	//limit cell change by maxCFact and by MINCELL
	if(level==1)
	{
		minSz = MINCELL;
		if(nuAsp<minSz)
		{ 
			fact = minSz / line->m_nNuSize;
			if(forRect)m_case16C = TRUE;
			else m_case16 = TRUE;
			cellImpede = TRUE;
		}

		if(!prelim && m_cellR && !forRect)
		{
			if(fact<maxCFact)
			{
				cellImpede = TRUE;
				m_case4 = TRUE;
				fact = maxCFact;
				ApplyCellCaseFlags();
			}
			m_cellFactor = fact;
		}
	}

	if(cellImpede)nuAsp = fact * line->m_nSize;

	line->m_nConting = nuAsp;
	//if(!prelim && forRect)line->m_nConting

	if(max && nuAsp>line->m_nNuSize)
	{
		if(line->m_nSize!=0)return line->m_nNuSize / line->m_nSize;
		else
		{
			AfxMessageBox("Bad data.  Start over by opening a new chart.");
			return 999999999999;			
		}
	}
	//changes already made are incidental to prior requests
	if(min)
	{
		if(line->m_nSize!=0) factor = line->m_nNuSize / line->m_nSize;
		else factor = 9999999999999;
		m_case2 = TRUE;
		return factor;
	}

	if(!prelim)
	{
		if(!forRect)line->m_applied = TRUE;
	}
	if(constrainR)m_fixRCellChange = TRUE;

	if(level==1)
	{
		BOOL locked = line->m_locked;
		if(locked && !prelim)
		{
			m_case3 = TRUE;
			m_cellFactor = 1.0;
			return 1.0;
		}
		if(locked && prelim){m_case3C = TRUE; return 1.0;}
	}

	if(horiz)
		{pframeID=17; pageID=6; mgnID=3; mgnID2=4; mgnID3=10; mgnID4=11;}
	if(!horiz)
		{pframeID=18; pageID=16; mgnID=10; mgnID2=11; mgnID3=3; mgnID4=4;}

	if(id!=6 && id!=16)squeeze = FALSE;
	if(id==6 || id==16)squeeze = TRUE;

	int margCode = 1;
	if(level==4)margCode = 4;
	fixMarg = CheckMarginMobility(mgnID,margCode,squeeze);
	fixMarg2 = CheckMarginMobility(mgnID2,margCode,squeeze);
	if(fixMarg && fixMarg2)fix = TRUE;
		
	line = m_reg[mgnID];
	m1lck = line->m_locked;
	marg = line->m_nNuSize;

	line = m_reg[mgnID2];
	m2lck = line->m_locked;
	marg2 = line->m_nNuSize;

	//initialize 'backside' factors
	line = m_reg[mgnID3];
	m3 = line->m_nSize;
	req = line->m_instigating;
	lock = line->m_locked;
	if(lock)m3lck = TRUE;
	oldM3 = line->m_nNuSize;
	
	line = m_reg[mgnID4];
	m4 = line->m_nSize;
	req = line->m_instigating;
	lock =  line->m_locked;
	if(lock)m4lck = TRUE;
	oldM4 = line->m_nNuSize;
	
	oldBackMargSpan = oldM4 + oldM3;

	if(squeeze)
	{
		absoMax = 0.0;
		backMgnSpanParam = oldBackMargSpan - maxFrAdj;
		if(m1lck)M1param = marg;
		else M1param = 0.0;
		if(m2lck)M2param = marg2;
		else M2param = 0.0;
		minFrontMargSpan = M1param + M2param;
	}
	if(!squeeze)
	{
		absoMax = 999999999999;
		backMgnSpanParam = oldBackMargSpan + maxFrAdj;
		if(m1lck)M1param = marg;
		else M1param = 999999999999;
		if(m2lck)M2param = marg2;
		else M2param = 999999999999;
		maxFrontMargSpan = M1param + M2param;
	}

	line = m_reg[pageID];
	oldPageSpan = line->m_nSize;
	pageSpan = line->m_nNuSize;

	line = m_reg[pframeID];
	oldPageFrame = line->m_nNuSize;
	nuFrame = line->m_nNuSize;

	//ascertain if there are welded aspects above
	//current level to determine suction
	countID = GetAssociatedCountID(id);
	enclosingID = GetEnclosingAspectID(id);
	if(level==2 && m_colorMode!=1)enclosingID = 
		GetEnclosingAspectID(enclosingID);
	if(m_colorMode!=1)modeAdj = 1;

	double * nuAspect = &nuAsp;
	double * f = &fact;
	double * pMaxCFact = &maxCFact;
	BOOL * outSideWeld = &frameWeld;
	BOOL margInsuff = FALSE;
	int startID = id;
	welds = FigureWeldsAndRamifications(level,countID,suckOut,startID,
									margInsuff,id,fixMarg,fixMarg2,fix,
									nuAspect,f,pMaxCFact,outSideWeld,
									max);
	if(welds<0 || welds==-1)vacLock = TRUE;
	line = m_reg[id];
	line->m_nConting = nuAsp;
	if(m_carryOutFrAdjOnly){welds = 0;vacLock = FALSE;}
	if(vacLock && startLevel!=4)
	{
		m_case11 = TRUE;
		if(level!=3 && (m_colorMode==1 || level!=2))m_case3 = TRUE;
		return 1.0;
	}
	level = startLevel;
	outAsp = nuAsp;

	//start IDs and level adjustment
	lock = FALSE;

	if(level==4) inID = GetEnclosedAspectID(outID);

	BOOL earlyExit = TRUE;
	for( ;level>1;level--)
	{
		if(level==3 && m_colorMode!=1)level--;
		if(level==startLevel && startLevel!=4)
			inID = GetEnclosedAspectID(outID);
		if(level!=startLevel || (startLevel==4 && m_colorMode!=1))
			inID = GetEnclosedAspectID(inID);
		if(level>=3)minSz = MINCBLK;
		if(level==2)minSz = MINBLK;
		line = m_reg[inID];
		alt = line->m_alt;
		inAspReq = line->m_instigating;
		app = line->m_applied;//TRUE implies aspect is 'instigating'
		min = line->m_minSet;
		lock = line->m_locked;
		inAsp = line->m_nNuSize;
		if(m_cellR && level==2)minCellAsp = maxCFact * line->m_nSize;

		if(level==5)
		{
			double * optRM1 = &optRateM1;
			double * optRM2 = &optRateM2;
			if(outAsp>=oldPageFrame)nuMargSpan = outAsp - oldPageFrame;
			else nuMargSpan = 0.0;
			nuFrame = outAsp - nuMargSpan;
			
			CalcMarginSqueezeRates(optRM1,optRM2,mgnID,
								mgnID2,mgnID3, mgnID4, absoMax,
								maxFrAdj, nuMargSpan, backMgnSpanParam,
								squeeze,nuFrame,outAsp);
	
			nuM1 = optRateM1 * marg;
			nuM2 = optRateM2 * marg2;
			if(m_boostMarg)
			{
				if(m_boostMargID==mgnID)nuM1 = m_boostMargAmt;
				if(m_boostMargID==mgnID2)nuM2 = m_boostMargAmt;
			}
			if(m_boostMarg2ndary)
			{
				if(m_boostMarg2ndaryID==mgnID)nuM1 = m_boostMarg2ndaryAmt;
				if(m_boostMarg2ndaryID==mgnID2)nuM2 = m_boostMarg2ndaryAmt;
			}
			nuMargSpan = nuM1 + nuM2;
			if(outAsp>=nuMargSpan)outAsp = outAsp - nuMargSpan;
			else {outAsp = 0;nuAsp = nuMargSpan;}
			nuFrame = outAsp;
		}
		if(/*level==4 || */((startLevel + welds + modeAdj)>=4)
			&& startLevel!=5)//x number of welds involves x no. of levels
		{
			if(startLevel!=4 || !m_carryOutFrAdjOnly)
			{
				//figure the frame as what is necessary from lower level
				//request
				nuFrame = outAsp;
				nuMargSpan = pageSpan - nuFrame;
			}
			line = m_reg[outID];
			oldInAsp = line->m_nSize;
			double * optRM1 = &optRateM1;
			double * optRM2 = &optRateM2;

			CalcMarginExpandRates(optRM1,optRM2,mgnID,
								mgnID2,mgnID3, mgnID4, absoMax,
								maxFrAdj, nuMargSpan, backMgnSpanParam,
								squeeze,nuFrame,pageSpan);
			nuM1 = optRateM1 * marg;
			nuM2 = optRateM2 * marg2;
			if(m_boostMarg)
			{
				if(m_boostMargID==mgnID)nuM1 = m_boostMargAmt;
				if(m_boostMargID==mgnID2)nuM2 = m_boostMargAmt;
			}
			if(m_boostMarg2ndary)
			{
				if(m_boostMarg2ndaryID==mgnID)nuM1 = m_boostMarg2ndaryAmt;
				if(m_boostMarg2ndaryID==mgnID2)nuM2 = m_boostMarg2ndaryAmt;
			}
			nuMargSpan = nuM1 + nuM2;
			if(m_carryOutFrAdjOnly)nuMargSpan = pageSpan - nuAsp;
			if(nuMargSpan<(pageSpan - nuAsp))
			{
				nuAsp = pageSpan - nuMargSpan;
				line = m_reg[id];
				line->m_nConting = nuAsp;
				outAsp = nuAsp;
				if(nuAsp!=0)fact = oldPageFrame / nuAsp;
				else AfxMessageBox("Corrupted data! Please delete file and start a new chart.");
			}
		}
		countID = GetAssociatedCountID(inID);
		if(countID!=99)
		{
			cLine = m_reg[countID];
			count = cLine->m_nNuCount;
		}
		else count = 1;
		if(level==5 && !fixMarg) m_mgnChange = TRUE;
		if(level==5 && !fixMarg2)m_mgnChange = TRUE;
		if(level==5)count = 1;//there will always be 1 page-frame
		
		double innerBulk = inAsp * count;
		double minAsp;

		//handle various situations with required minimum sizes
		if(level==2)minSz = MINCELL;
		if(level==3)minSz = MINBLK;
		if(level==4)minSz = MINCBLK;
		minSz = minSz * count;
		if(level==5)minSz = MINCBLK; 
		minAsp = minSz;
		if(m_cellR && level==2)minAsp = minCellAsp * count;
		if(minAsp>minSz){interpolateCellFlags = TRUE;minCase4=TRUE;}
		if(minAsp>outAsp)
		{
			outAsp = minAsp;
			modifiedOutAsp = TRUE;
			if(!minCase4)minCase16 = TRUE;
		}
		else minCase4 = FALSE;

		if(innerBulk<=outAsp && !modifiedOutAsp)
		{
			if(prelim)return fact;
			nufRm = TRUE;
			earlyExit = TRUE;
			break;
		}
		if(innerBulk>outAsp || modifiedOutAsp)
		{
			earlyExit = FALSE;

			//set relavant flags
			if(lock)m_case3 = TRUE;

			//assess inner aspect mobility
			BOOL pin = FALSE;
			if(inAspReq && app)pin = TRUE;
			if(min)pin = TRUE;
			BOOL cstrain = line->m_fixedRatio;
			if(level==2 && cstrain)m_fixRCellChange = TRUE;
			
			//exit or not while leaving understandable trail
			line = m_reg[inID];
			if(!pin)line->m_nConting = outAsp / count;
			if(pin || lock)
			{
				minCase16 = FALSE;
				minCase4 = FALSE;
				lockCase3 = TRUE;
				findMax = TRUE; 
				break;
			}	
			lastAltLevel = level;
			if(level!=2)outAsp = outAsp / count;
			else
			{
				inAsp = outAsp / count;
				break;//not only prevents loop iteration but
								//also keeps 'level' from decrementing
			}
		}
		//increment idMod,cheat level & idMod
		outID = inID;
		if(level==5 && m_colorMode!=1)inID = GetEnclosedAspectID(inID);
	}

	if(lockCase3)m_case3 = TRUE;
	if(minCase4)m_case4 = TRUE;
	if(minCase16)m_case16 = TRUE;
	if(!lock && findMax) m_case2 = TRUE;
	if(!nufRm && !findMax)nufRm = TRUE;
	if(vacLock && prelim) {m_case11C = TRUE;return 1.0;}
	if(!vacLock && nufRm && prelim) return fact;
	if(modifiedOutAsp){findMax = TRUE;nufRm = FALSE;}

	for( ;level<6;level++)
	{
		if(nufRm && !earlyExit)
		{
			BOOL pin = FALSE;
			line = m_reg[inID];
			if(line->m_instigating && line->m_applied)pin = TRUE;
			if(line->m_minSet)pin = TRUE;
			if(!pin)line->m_nNuSize = line->m_nConting;
			if(!prelim && !pin)
			{
				line->m_alt = TRUE;
			}
			if(level==2 && m_cellR)
			{
				if(minCellAsp>line->m_nConting)
					line->m_nNuSize = minCellAsp;
				if(!prelim)
				{
					if(line->m_nSize!=0)
					m_cellFactor = line->m_nNuSize / line->m_nSize;
					else m_cellFactor = 999999999999;
				}
			}
		}
		if((nufRm && level==5)||(!m_carryOutFrAdjOnly && startLevel==4
			&& level==4))
		{
			double nuMarg,nuMarg2;
			if(!fixMarg || !fixMarg2)m_mgnChange = TRUE;
			m_frontM1Rate = optRateM1;
			m_frontM2Rate = optRateM2;
			if(!fixMarg && !fixMarg2)
			{
				double mSpaceAvail,oldSpan;
				line = m_reg[inID];
				inAsp = line->m_nSize;
				oldSpan = oldPageSpan - inAsp;
				if(oldSpan!=0)
				{
					mSpaceAvail = nuAsp -  nuFrame;
					nuMarg = (marg * mSpaceAvail)/oldSpan;
					nuMarg2 = (marg2 * mSpaceAvail)/oldSpan;
				}
				if(oldSpan==0)
				{
					nuMarg = 0.0;
					nuMarg2 = 0.0;
				}
				if(!prelim)
				{
					line = m_reg[mgnID];
					line->m_nNuSize = nuM1;// = nuMarg;
					line->m_alt = TRUE;
					line = m_reg[mgnID2];
					line->m_nNuSize = nuM2;// = nuMarg2
					line->m_alt = TRUE;
				}
			}
			if(!fixMarg && fixMarg2)
			{
				nuMarg = nuM1;
				if(!prelim)
				{
					line = m_reg[mgnID];
					line->m_nNuSize = nuMarg;
					line->m_alt = TRUE;
					//line->m_maxSetCur = TRUE;
				}
			}
			if(fixMarg && !fixMarg2)
			{
				if(!prelim)
				{
					nuMarg2 = nuM2;
					line =m_reg[mgnID2];
					line->m_nNuSize = nuMarg2;
					line->m_alt = TRUE;
				}
			}

		}//if(level==5)
		if(nufRm && earlyExit)
		{
			//double aspect = inAsp;
			///if(level==lastAltLevel)aspect = outAsp;
			//line = m_reg[inID];
			//line->m_nNuSize = aspect;
			//line->m_alt = TRUE;
			earlyExit = FALSE;
		}

		if(nufRm)
		{
			inID = outID;
			outID = GetEnclosingAspectID(outID);
			if(level==2 && m_colorMode!=1)outID = 
				GetEnclosingAspectID(outID);
		}
		if(nufRm && level==startLevel)
		{
			line = m_reg[id];
			line->m_nNuSize = line->m_nConting;
			line->m_maxSetCur = TRUE;
			line->m_minSetCur = TRUE;
			line->m_alt = TRUE;
			factor = fact;
			break;
		}
		if(findMax)
		{
			line = m_reg[inID];
			if(!prelim && line->m_nNuSize!=inAsp)
			{
				line->m_nNuSize = inAsp;
				line->m_alt = TRUE;
				//line->m_maxSetCur = TRUE;
				//m_case3 = TRUE;
			}
			if(level==5)
			{
				double margTotal = 0.0;

				//notify if margin constraints that are a problem in terms
				//of complexity
				if(fixM)m_case4 = TRUE;

				//check for locked margins
				if(!fixMarg && !fixMarg2)
				{
					line = m_reg[mgnID];
					line->m_nNuSize = 0.0;
					if(!prelim)
					{
						line->m_alt = TRUE;
					}
					line = m_reg[mgnID2];
					if(!prelim)
					{
						//line->m_minSetCur = TRUE;
						//line->m_maxSetCur = TRUE;
						line->m_alt = TRUE;
					}
					line->m_nNuSize = 0.0;
					m_frontM1Rate = 0.0;
					m_frontM2Rate = 0.0;
					m_mgnChange = TRUE;
				}
				if(fixMarg && !fixMarg2)
				{
					margTotal = marg;
					line = m_reg[mgnID2];
					line->m_nNuSize = 0.0;
					if(!prelim)
					{
						line->m_alt = TRUE;
					}
					m_frontM2Rate = 0.0;
					m_mgnChange = TRUE;
				}
				if(!fixMarg && fixMarg2)
				{
					margTotal = marg2;
					line = m_reg[mgnID];
					line->m_nNuSize = 0.0;
					if(!prelim)
					{
						line->m_alt = TRUE;
					}
					m_frontM1Rate = 0.0;
					m_mgnChange = TRUE;
				}
				if(fixMarg && fixMarg2)margTotal = marg + marg2;
				
				line = m_reg[outID];
				if(line->m_origReqSize + margTotal>=line->m_nConting)
					ApplyMargCaseFlags();				
				inAsp = inAsp + margTotal;
			}//if(level==5

			int countID = GetAssociatedCountID(inID);
			if(countID!=99)
			{
				cLine = m_reg[countID];
				count = cLine->m_nNuCount;
			}
			else count = 1;

			if(level==startLevel)
			{
				outAsp = inAsp * count;
				line = m_reg[outID];
				factor = outAsp / line->m_nNuSize;
				if(!prelim)
				{
					line->m_nNuSize = outAsp;
					line->m_alt = TRUE;
				}
				break;
			}	
			inID = outID;
			outID = GetEnclosingAspectID(outID);
			if(level==2 && m_colorMode!=1)
				outID = GetEnclosingAspectID(outID);
			inAsp = inAsp * count;

		}//if(findMax
		if(level==2 && m_colorMode!=1)level++;
	}//for


	//provide for aspects drawn in by a count equal to 1
	if(level!=startLevel || findMax)
	{
		line = m_reg[outID];
		outAsp = line->m_nNuSize;
	}
	level = startLevel + 1;
	if(prelim)welds = 0;
	if(level==3 && m_colorMode!=1)level++;
	enclosingID = id;//cheat initial GetEnclosingAspectID()
	for( ;welds>0;welds--)
	{
		if(level!=4)
		{
			enclosingID = GetEnclosingAspectID(enclosingID);
			line = m_reg[enclosingID];
			line->m_nNuSize = outAsp;
			if(!prelim)line->m_alt = TRUE;
		}
		if(level==4 && (!fixMarg || !fixMarg2))
		{
			line = m_reg[pframeID];
			line->m_nNuSize = outAsp;
			line->m_alt = TRUE;
			//line->m_maxSetCur = TRUE;
		}
		//if margins are drawn by shrinking outer block size
		//unless request is a margin/frame request
		if(level==4 && startLevel!=4)
		{
			if(!prelim)
			{
				line->m_alt = TRUE;
			}
			if(!fixMarg && fixMarg2)
			{
				m_case8 = TRUE;
				line = m_reg[mgnID];
				line->m_nNuSize = nuM1;
				if(!prelim)
				{
					line->m_alt = TRUE;
				}
				if(startMarg!=0)
					m_frontM1Rate = line->m_nNuSize / startMarg;
				else m_frontM1Rate = 999999999999;
				m_mgnChange = TRUE;
			}
			if(fixMarg && !fixMarg2)
			{
				m_case8 = TRUE;
				line = m_reg[mgnID2];
				line->m_nNuSize = nuM2;
				if(!prelim)
				{
					line->m_alt = TRUE;
				}
				if(startMarg2!=0)
					m_frontM2Rate = line->m_nNuSize / startMarg2;
				else m_frontM2Rate = 999999999999;
				m_mgnChange = TRUE;
			}
			if(!fixMarg && !fixMarg2)
			{
				line = m_reg[mgnID];
				line->m_nNuSize = nuM1;
				if(startMarg!=0)
					m_frontM1Rate = line->m_nNuSize / startMarg;
				else m_frontM1Rate = 999999999999;
				if(!prelim)
				{
					line->m_alt = TRUE;
					//line->m_maxSetCur = TRUE;
				}
				line = m_reg[mgnID2];
				line->m_nNuSize = nuM2;
				if(startMarg2!=0)
					m_frontM2Rate = line->m_nNuSize / startMarg2;
				else m_frontM2Rate = 999999999999;
				if(!prelim)
				{
					line->m_alt = TRUE;
				}
				m_mgnChange = TRUE;
			}
			level++;
			if(level==3 && m_colorMode!=1)
			{
				level++;
				enclosingID = GetEnclosingAspectID(enclosingID);
			}
		}
	}
	return factor;
}

BOOL CCalc::RequestPageCount()
{
	UINT nuPCount;
	BOOL approval = FALSE;
	CRegAspect* cLine = m_reg[15];
	nuPCount = cLine->m_origReqCount;
	if(nuPCount>=cLine->m_nNuCount)
	{
		cLine->m_nNuCount = nuPCount;
		cLine->m_alt = TRUE;
		approval = TRUE;
	}
	else
	{
		UINT standPgCellCt = GetPageCellCount(1);
		UINT lastNeededPg = m_totalCells / standPgCellCt;
		if(((double)m_totalCells /(double)standPgCellCt)>
			(double)lastNeededPg)
			lastNeededPg++;
		//UINT finalPgCellCt = GetPageCellCount(lastNeededPg);
		if(nuPCount>=lastNeededPg)
		{
			cLine->m_nNuCount = nuPCount;
			cLine->m_alt = TRUE;
			approval = TRUE;
		}
		else 
		{
			BOOL ans = 0;
			m_case21 = TRUE;
			if(m_flagReporting)
			{
				CMessDlg dlg;
				dlg.str = GetAdvisoryStrings();
				if(dlg.DoModal()==IDOK)
				{
					if(dlg.m_yes)ans = 1;
					if(dlg.m_no)ans = 2;
				}
			}
			if(ans==1)
			{
				approval = TRUE;
				nuPCount = lastNeededPg;
				cLine->m_alt = TRUE;
				cLine->m_nNuCount = nuPCount;
			}
			if(ans==2)m_noAccept = TRUE;
		}
	}
	return approval;
}


/////////////////////////////////////////////////////////////////////
void CCalc::AcceptChanges()
{
	int c;
	BOOL alt = FALSE, proc = FALSE, accept = FALSE, req = FALSE;
	BOOL firstCaught = FALSE;
	CRegAspect* line;
	int count;
	for(count=0;count<SHELFSZ;count++)
	{
		for(c=0;c<RGSZ;c++)
		{
			line = m_reg[c];
			if(count==line->m_order)
			{
				proc = line->m_processed;
				req = line->m_instigating;
				if(!proc && req && !firstCaught)
				{
					line->m_processed = TRUE;
					firstCaught = TRUE;
		//			req = FALSE;
				}
			}
		}
	}
	for(c=0;c<RGSZ;c++)
	{
		line = m_reg[c];
		alt = line->m_alt;
		if(alt)
		{
			line->m_histAlt = TRUE;
			line->m_nLastCount = line->m_nNuCount;
			line->m_nLastSize = line->m_nNuSize;
			line->m_accepted = TRUE;
			line->m_alt = FALSE;
			line->m_minSetCur = FALSE;
			line->m_maxSetCur = FALSE;
		}
		//ascending order reqs not processed; 1 per call to Accept Changes
	}
	m_change = TRUE;
}

void CCalc::RejectChanges()
{
}

BOOL CCalc::AcceptAllChanges()
{
	int c;
	BOOL alt = FALSE, accept = FALSE;
	for(c=0;c<RGSZ;c++)
	{
		CRegAspect* line = m_reg[c];
		alt = line->m_histAlt;
		accept = line->m_accepted;
		if(alt)
		{
			if(accept)
			{
				if(line->m_nType==0)line->m_nCount = line->m_nNuCount;
				if(line->m_nType==1)line->m_nSize = line->m_nNuSize;
			}
			line->m_alt = FALSE;
			line->m_histAlt = FALSE;
			line->m_instigating = FALSE;
//			line->m_fixed = FALSE;
			line->m_minSetCur = FALSE;
			line->m_maxSetCur = FALSE;
			line->m_processed = FALSE;
			line->m_accepted = FALSE;
		}
	}
	m_change = TRUE;

	return TRUE;
}

void CCalc::ResetChangeRequestProcessingLoop()
{
	int reqCount = 0,item1,item2,item3,item4,item5,item6;
	CRetractDlg dlg;
	CRegAspect* line;
	line = m_reg[19];
	if(line->m_instigating)dlg.m_strikeAll = TRUE;
	line = m_reg[20];
	if(line->m_instigating)dlg.m_strikeAll = TRUE;
	BOOL countsIn = FALSE,take = FALSE;
	signed i = 0;
	for(i=0;i<RGSZ;i++)
	{
		line = m_reg[i];
		BOOL req = line->m_instigating;
		take = FALSE;
		//give priority to counts
		if(countsIn && line->m_nType!=0)take = TRUE;
		if(!countsIn && line->m_nType==0)take = TRUE;
		if(req && take)
		{
			reqCount++;
			CString s = GetAspectString(i);
			dlg.SetItems(s);
			s = GetInitialRequestString(i);
			dlg.SetInitialRequest(s);
			s = GetResultingValueString(i);
			dlg.SetResultingValue(s);
			if(reqCount==1)item1 = i;
			if(reqCount==2)item2 = i;
			if(reqCount==3)item3 = i;
			if(reqCount==4)item4 = i;
			if(reqCount==5)item5 = i;
			if(reqCount==6)item6 = i;
		}
		if(i==(RGSZ - 1) && !countsIn){countsIn = TRUE; i = -1;}
	}
	dlg.m_asp = GetAspectString(i);
	if(dlg.DoModal()==IDOK)
	{
		BOOL checked = FALSE;
		if(reqCount>0 && dlg.m_chk1)
		{checked = TRUE;RetractInstigatingLine(item1);}
		if(reqCount>1 && dlg.m_chk2)
		{checked = TRUE;RetractInstigatingLine(item2);}
		if(reqCount>2 && dlg.m_chk3)
		{checked = TRUE;RetractInstigatingLine(item3);}
		if(reqCount>3 && dlg.m_chk4)
		{checked = TRUE;RetractInstigatingLine(item4);}
		if(reqCount>4 && dlg.m_chk5)
		{checked = TRUE;RetractInstigatingLine(item5);}
		if(reqCount>5 && dlg.m_chk6)
		{checked = TRUE;RetractInstigatingLine(item6);}
		ResetForReProcessing();
	}
}

CString CCalc::GetAspectString(int i)
{
	CString str;
	if(i==0)str = "cell width";
	if(i==1)str = "block width";
	if(i==2)str = "c-block width";
	if(i==3)str = "left margin";
	if(i==4)str = "right margin";
	if(i==5)str = "column count";
	if(i==6)str = "page width";
	if(i==7)str = "cell height";
	if(i==8)str = "block height";
	if(i==9)str = "c-block height";
	if(i==10)str = "upper margin";
	if(i==11)str = "lower margin";
	if(i==12)str = "row count";
	if(i==13)str = "block count";
	if(i==14)str = "c-block count";
	if(i==15)str = "page count";
	if(i==16)str = "page height";
	if(i==17)str = "frame width";
	if(i==18)str = "frame height";
	if(i==19)str = "block columns";
	if(i==20)str = "block rows";
	if(i==21)str = "c'block columns";
	if(i==22)str = "c'block rows";
	if(i==23)str = "steps per column";
	if(i==24)str = "steps per row";
	if(i==25)str = "steps per block";
	if(i==26)str = "steps per c'block";
	if(i==27)str = "x axis start color";
	if(i==28)str = "x axis end color";
	if(i==29)str = "y axis start color";
	if(i==30)str = "y axis end color";
	if(i==31)str = "block start color";
	if(i==32)str = "block end color";
	if(i==33)str = "c-block start color";
	if(i==34)str = "c-block end color";

	return str;
}

CString CCalc::GetInitialRequestString(int i)
{
	CRegAspect* line = m_reg[i];
	BOOL factSet = FALSE;
	int type = line->m_nType;
	double val1;
	int val2;
	if(type!=1 && type!=0)AfxMessageBox("Faulty data in registry:m_nType");
	if(type==1)//float
	{
		val1 = line->m_origReqSize;
	}
	if(type==0)//count
	{
		val2 = line->m_origReqCount;
	}
	char s[25];
	std::ostringstream ostr(s,25);
	if(type==1)	ostr << val1;// << ends;
	if(type==0) ostr << val2; // << ends;
	CString str = (CString)s;
	return str;
}

CString CCalc::GetResultingValueString(int i)
{
	CRegAspect* line = m_reg[i];
	BOOL factSet = FALSE;
	int type = line->m_nType;
	double val1;
	UINT val2;
	if(type!=1 && type!=0)AfxMessageBox("Faulty data in registry:m_nType");
	if(type==1)//float
	{
		val1 = line->m_nNuSize;
	}
	if(type==0)//count
	{
		val2 = line->m_nNuCount;
	}
	char s[25];
	std::ostringstream ostr(s,25);
	if(type==1)	ostr << val1;// << ends;
	if(type==0) ostr << (int)val2;// << ends;
	CString str = (CString)s;
	return str;
}

void CCalc::SaveAtStartComputeSettings()
{
	int i = 0;
	CRegAspect* line;
	line = m_reg[i];
	m_rectW = line->m_nSize;
	line = m_reg[++i];
	m_blockW = line->m_nSize;
	line = m_reg[++i];
	m_cBlockW = line->m_nSize;
	line = m_reg[++i];
	m_leftM = line->m_nSize;
	line = m_reg[++i];
	m_rightM = line->m_nSize;
	line = m_reg[++i];
	m_colsPer = line->m_nCount;
	line = m_reg[++i];
	m_pageW = line->m_nSize;
	line = m_reg[++i];
	m_rectH = line->m_nSize;
	line = m_reg[++i];
	m_blockH = line->m_nSize;
	line = m_reg[++i];
	m_cBlockH = line->m_nSize;
	line = m_reg[++i];
	m_topM = line->m_nSize;
	line = m_reg[++i];
	m_botM = line->m_nSize;
	line = m_reg[++i];
	m_rowsPer = line->m_nCount;
	line = m_reg[++i];
	m_blockCount = line->m_nCount;
	line = m_reg[++i];
	m_cBlockCount = line->m_nCount;
	line = m_reg[++i];
	m_pageC = line->m_nCount;
	line = m_reg[++i];
	m_pageH = line->m_nSize;
	line = m_reg[++i];
	m_virtPageW = line->m_nSize;
	line = m_reg[++i];
	m_virtPageH = line->m_nSize;
	line = m_reg[++i];
	m_blockCols = line->m_nCount;
	line = m_reg[++i];
	m_blockRows = line->m_nCount;
	line = m_reg[++i];
	m_cBlockCols = line->m_nCount;
	line = m_reg[++i];
	m_cBlockRows = line->m_nCount;
	line = m_reg[++i];
	m_colFreq = line->m_nSize;
	line = m_reg[++i];
	m_rowFreq = line->m_nSize;
	line = m_reg[++i];
	m_blkFreq = line->m_nSize;
	line = m_reg[++i];
	m_cBlkFreq = line->m_nSize;
	m_colF = m_colFrom;
	m_colT = m_colTo;
	m_rowF = m_rowFrom;
	m_rowT = m_rowTo;
	m_blockF = m_blockFrom;
	m_blockT = m_blockTo;
	m_cBlockF = m_cBlockFrom;
	m_cBlockT = m_cBlockTo;


}
void CCalc::RestoreAtStartComputeSettings()
{
	int i = 0;
	CRegAspect* line;
	line = m_reg[i];
	line->m_nSize = m_rectW;
	line = m_reg[++i];
	line->m_nSize = m_blockW;
	line = m_reg[++i];
	line->m_nSize = m_cBlockW;
	line = m_reg[++i];
	line->m_nSize = m_leftM;
	line = m_reg[++i];
	line->m_nSize = m_rightM;
	line = m_reg[++i];
	//line->m_colsPer = line->m_nCount;
	m_colsPer = line->m_nCount;
	line = m_reg[++i];
	line->m_nSize = m_pageW;
	line = m_reg[++i];
	line->m_nSize = m_rectH;
	line = m_reg[++i];
	line->m_nSize = m_blockH;
	line = m_reg[++i];
	line->m_nSize = m_cBlockH;
	line = m_reg[++i];
	line->m_nSize = m_topM;
	line = m_reg[++i];
	line->m_nSize = m_botM;
	line = m_reg[++i];
	//line->m_nCount = m_rowsPer;
	m_rowsPer = line->m_nCount; 
	line = m_reg[++i];
	line->m_nCount = m_blockCount;
	line = m_reg[++i];
	line->m_nCount = m_cBlockCount;
	line = m_reg[++i];
	line->m_nCount = m_pageC;
	line = m_reg[++i];
	line->m_nSize = m_pageH;
	line = m_reg[++i];
	line->m_nSize = m_virtPageW;
	line = m_reg[++i];
	line->m_nSize = m_virtPageH;
	line = m_reg[++i];
	line->m_nCount = m_blockCols;
	line = m_reg[++i];
	line->m_nCount = m_blockRows;
	line = m_reg[++i];
	line->m_nCount = m_cBlockCols;
	line = m_reg[++i];
	line->m_nCount = m_cBlockRows;
	line = m_reg[++i];
	line->m_nSize = m_colFreq;
	line = m_reg[++i];
	line->m_nSize = m_rowFreq;
	line = m_reg[++i];
	line->m_nSize = m_blkFreq;
	line = m_reg[++i];
	line->m_nSize = m_cBlkFreq;
	m_colFrom = m_colF;
	m_colTo = m_colT;
	m_rowFrom = m_rowF;
	m_rowTo = m_rowT;
	m_blockFrom = m_blockF;
	m_blockTo = m_blockT;
	m_cBlockFrom = m_cBlockF;
	m_cBlockTo = m_cBlockT;
}

/////////////////////////////////////////////////////////////////////
//Helper functions for calculator

int CCalc::FigureWeldsAndRamifications(int level,int countID,BOOL
								suckOut,int levID, BOOL margInsuff,
								int id,BOOL fixMarg,BOOL fixMarg2,
								BOOL fix,double * nuAsp,double * fact,
								double * maxCFact,BOOL * outSideWeld,
								BOOL minMax)
{
	CRegAspect* line;
	int welds = 0,nextLevID=levID,pframeID;
	double maxCellAsp,maxFrameAsp;
	signed int bump;
	BOOL vacLock = FALSE;
	int extreme;
	if(!suckOut)
	{
		extreme = 5;
		bump = 1;
	}
	else
	{
		extreme = 1;
		bump = -1;
	}
	if(suckOut)
	{
		nextLevID = GetEnclosedAspectID(levID);
		if(m_colorMode!=1 && level==4)nextLevID = GetEnclosedAspectID(nextLevID);
	}
	if(!suckOut)
	{
		nextLevID = GetEnclosingAspectID(levID);
		if(m_colorMode!=1 && level==2)nextLevID = GetEnclosingAspectID(nextLevID);
	}
	if(suckOut && level==1)level--;
	if(!suckOut && level==5)level++;
	for( ;level!=(extreme + bump);)
	{
		if(level==3 && m_colorMode!=1)
		{
			if(suckOut)
			{
				level--;
				levID = nextLevID;
				nextLevID = GetEnclosedAspectID(levID);
			}
			else 
			{
				level++;
				levID = GetEnclosingAspectID(levID);
				nextLevID = GetEnclosingAspectID(levID);
			}
			if(suckOut)countID = GetAssociatedCountID(nextLevID);
			else countID = GetAssociatedCountID(levID);
		}
		int count;
		if(countID!=99)
		{
			line = m_reg[countID];
			count = line->m_nNuCount;
		}
		else count = 1;
		BOOL immoble = FALSE,limitSet=FALSE,locked=FALSE;
		line = m_reg[nextLevID];
		locked = line->m_locked;
		if(suckOut)limitSet = line->m_maxSet;
		else limitSet = line->m_minSet;
		if(locked || limitSet)immoble = TRUE;
		if((level!=5 && suckOut) || (level!=4 && !suckOut))
		{
			if(count!=1)break;
			if(count==1 && immoble){ vacLock = TRUE; break; }
			welds++;
			if(nextLevID==0 || nextLevID==7)
			{
				*outSideWeld = TRUE;
				maxCellAsp = *maxCFact * line->m_nNuSize;
				double commonAsp = *nuAsp;
				BOOL margSep = FALSE;
				if(suckOut && (id==6 || id==16))
				{
					margSep = TRUE;
					pframeID = GetEnclosedAspectID(id);
				}
				if(margSep)
				{	
					line = m_reg[levID];
					commonAsp = line->m_nNuSize;
				}
				if(suckOut && maxCellAsp<commonAsp)
				{
					if(!margSep)
					{
						*nuAsp = maxCellAsp;
						if(minMax && (*nuAsp < (double)(line->m_nNuSize)))vacLock = TRUE;
						else 
						{
							line =  m_reg[id];
							if(line->m_nNuSize!=0)
								*fact = *nuAsp / line->m_nNuSize;
							else AfxMessageBox("Bad data. Start a new color chart.");
						}
					}
					if(margSep)
					{
						line = m_reg[pframeID];
						line->m_nConting = maxCellAsp;
					}
				}
			}
		}
		if((level==4 && !suckOut)||(level==5 && suckOut))
		{
			BOOL draw = FALSE;
			if(fix || margInsuff)draw = TRUE;
			if(fixMarg && fixMarg2)draw = TRUE;
			if(draw)
			{
				m_case8 = TRUE;
				welds++;
				if(level==4 && (fixMarg && fixMarg2))
					{vacLock = TRUE; break;}
			}
			else break;
		}
		if(suckOut)
		{
			levID = nextLevID;
			nextLevID = GetEnclosedAspectID(levID);
			level--;
			if(level==4 && m_colorMode!=1)nextLevID = 
				GetEnclosedAspectID(nextLevID);
		}
		else 
		{
			level++;
			levID = nextLevID;
			nextLevID = GetEnclosingAspectID(levID);
			if(level==2 && m_colorMode!=1)nextLevID = 
				GetEnclosingAspectID(nextLevID);
		}
		if(suckOut)countID = GetAssociatedCountID(nextLevID);
		else countID = GetAssociatedCountID(levID);
		if(suckOut && level==1)level--;
		if(!suckOut && level==5)level++;
	}
	if(vacLock)return -1;
	return welds;
}

void CCalc::CalcMarginSqueezeRates(double * optRateM1,double * optRateM2,
								   int mgnID,int mgnID2,int mgnID3,
								   int mgnID4,	double absoMax,
								   double maxFrAdj, double nuMargSpan,
								   double backMgnSpanParam,
								   BOOL squeeze, double nuFrame,
								   double nuPage)
{
	m_reOpt = FALSE;
	BOOL lck13 = DetermineInterlock(mgnID,mgnID3);
	BOOL lck14 = DetermineInterlock(mgnID,mgnID4);
	BOOL lck12 = DetermineInterlock(mgnID,mgnID2);
	BOOL lck23 = DetermineInterlock(mgnID2,mgnID3);
	BOOL lck24 = DetermineInterlock(mgnID2,mgnID4);
	BOOL lck34 = DetermineInterlock(mgnID3,mgnID4);
	//find optimum frontside margin rates
	*optRateM1 = GetOptimumMarginRate(mgnID,nuMargSpan,lck13,lck14,
		lck12,lck23,lck24,lck34);
	*optRateM2 = GetOptimumMarginRate(mgnID2,nuMargSpan,lck13,lck14,
		lck12,lck23,lck24,lck34);
	//find maximum backside margin rates
	double maxRateM4;
	double * mR4 = &maxRateM4;
	double maxRateM3 = GetBacksideMarginRate(mgnID3,absoMax,maxFrAdj,
		optRateM1,optRateM2,mR4,lck13,lck14,lck12,lck23,lck24,lck34);
	//if rates not compatible get closest compatible frontside
	double optRM1 = *optRateM1;
	double optRM2 = *optRateM2;
	*optRateM1 = GetCompatibleMargRate(optRM1,mgnID,optRateM2,
		maxRateM3,maxRateM4,squeeze,lck13,lck14,lck12,
		lck23,lck24,nuFrame,nuMargSpan,maxFrAdj);
}

void CCalc::CalcMarginExpandRates(double * optRateM1,double * optRateM2,
								  int mgnID,int mgnID2,int mgnID3,
								  int mgnID4,double absoMax,
								  double maxFrAdj, double nuMargSpan,
								  double backMgnSpanParam,BOOL squeeze, 
								  double nuFrame,double nuPage)
{
	m_reOpt = FALSE;
	double m1,m2;
	CRegAspect* line;
	line = m_reg[mgnID];
	m1 = line->m_nNuSize;
	line = m_reg[mgnID2];
	m2 = line->m_nNuSize;
	BOOL lck13 = DetermineInterlock(mgnID,mgnID3);
	BOOL lck14 = DetermineInterlock(mgnID,mgnID4);
	BOOL lck12 = DetermineInterlock(mgnID,mgnID2);
	BOOL lck23 = DetermineInterlock(mgnID2,mgnID3);
	BOOL lck24 = DetermineInterlock(mgnID2,mgnID4);
	BOOL lck34 = DetermineInterlock(mgnID3,mgnID4);
	//find optimum frontside margin rates
	*optRateM1 = GetOptimumMarginRate(mgnID,nuMargSpan,lck13,lck14,
		lck12,lck23,lck24,lck34);
	*optRateM2 = GetOptimumMarginRate(mgnID2,nuMargSpan,lck13,lck14,
		lck12,lck23,lck24,lck34);
	//find maximum backside margin rates
	double maxRateM4;
	double * mR4 = &maxRateM4;
	double maxRateM3 = GetBacksideMarginRate(mgnID3,absoMax,maxFrAdj,
		optRateM1,optRateM2,mR4,lck13,lck14,lck12,lck23,lck24,lck34);
	//if rates not compatible get closest compatible frontside
	double optRM1 = *optRateM1;
	double optRM2 = *optRateM2;
	*optRateM1 = GetCompatibleMargRate(optRM1,mgnID,optRateM2,
		maxRateM3,maxRateM4,squeeze,lck13,lck14,lck12,
		lck23,lck24,nuFrame,nuMargSpan,maxFrAdj);
	//
	if((m1 * (*optRateM1)) + (m2 * (*optRateM2))!=nuMargSpan)m_reOpt = TRUE;
}

BOOL CCalc::DetermineInterlock(int m1,int m2)
{
	BOOL bond = FALSE;
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	int mgnCode = pDoc->m_dMargRat;
	if(mgnCode%17==0 && (m1 * m2)==30) bond = TRUE;
	if(mgnCode%13==0 && (m1 * m2)==40) bond = TRUE;
	if(mgnCode%11==0 && (m1 * m2)==110) bond = TRUE;
	if(mgnCode%7==0 && (m1 * m2)==12) bond = TRUE;
	if(mgnCode%5==0 && (m1 * m2)==33) bond = TRUE;
	if(mgnCode%3==0 && (m1 * m2)==44) bond = TRUE;
	return bond;
}

double CCalc::GetOptimumMarginRate(int mID,double nuMargTotal,BOOL hitch13,
								   BOOL hitch14,BOOL hitch12,BOOL hitch23,
								   BOOL hitch24,BOOL hitch34)
{
	double rate,m1,m2,m3,m4,generic,oldMargSpace,rate1,rate2;
	double unResolvedMSpan=nuMargTotal,m1Yield=0.0,m2Yield=0.0;
	double genericBoost;
	int mgn1,mgn2,mgn3,mgn4;
	BOOL crossLock=FALSE,lock12=FALSE;
	BOOL alt=FALSE,lock=FALSE,req=FALSE,mlck=FALSE,m2lck=FALSE;
	BOOL margSqueeze = FALSE;
	if(mID==3 || mID==4){mgn1 = 3;mgn2 = 4;mgn3 = 10;mgn4 = 11;}
	if(mID==10 || mID==11){mgn1 = 10;mgn2 = 11;mgn3 = 3;mgn4 = 4;}
	CRegAspect* line;

	line = m_reg[mgn1];
	m1 = line->m_nNuSize;
	mlck = line->m_locked;

	line = m_reg[mgn2];
	m2 = line->m_nNuSize;
	m2lck = line->m_locked;

	line = m_reg[mgn3];
	m3 = line->m_nNuSize;

	line = m_reg[mgn4];
	m4 = line->m_nNuSize;

	if(nuMargTotal<(m1 + m2))margSqueeze = TRUE;
	m_untiedMgnIsAsset = FALSE;
	m_frontMgnOptionsExist = FALSE;

	if(hitch12 && mlck)crossLock = TRUE;
	if(hitch12 && m2lck)crossLock = TRUE;
	oldMargSpace = m1 + m2;

	BOOL m1BoostValid = FALSE,m2BoostValid = FALSE;
	if(m1==0)m1BoostValid = AscertainBoostValidity(mgn1,mgn2,mgn3,mgn4);
	if(m2==0)m2BoostValid = AscertainBoostValidity(mgn2,mgn1,mgn3,mgn4); 

	if(oldMargSpace!=0)
	{
		generic = unResolvedMSpan / oldMargSpace;
		if(margSqueeze)	genericBoost = 0.0;
		if(m1==0 && !margSqueeze)
		{
			double margSpanDif = unResolvedMSpan - oldMargSpace;
			if(m1BoostValid)
			{
				generic = ((margSpanDif * .5) + oldMargSpace) / m2;
				genericBoost = margSpanDif * .5;
			}				
			else genericBoost = 0.0;
		}
		if(m2==0 && !margSqueeze)
		{
			double margSpanDif = unResolvedMSpan - oldMargSpace;
			if(m2BoostValid)
			{
				generic = ((margSpanDif * .5) + oldMargSpace) / m1;
				genericBoost = margSpanDif * .5;
			}
			else genericBoost = 0.0;
		}
	}
	if(oldMargSpace==0)
	{
		generic = 999999999999;
		if(m1BoostValid && m2BoostValid)genericBoost = unResolvedMSpan / 2;
		if(m1BoostValid && !m2BoostValid)genericBoost = unResolvedMSpan;
		if(!m1BoostValid && m2BoostValid)genericBoost = unResolvedMSpan;
		if(!m1BoostValid && !m2BoostValid)genericBoost = 0.0;
	}

	if(hitch13 && hitch24)
	{
		if(m1!=0)m1Yield = m3 / m1;
		else m1Yield = 999999999999;
		if(m2!=0)m2Yield = m4 / m2;
		else m1Yield = 999999999999;
	}
	if(hitch14 && hitch23)
	{
		if(m2!=0)m2Yield = m3 / m2;
		else m1Yield = 999999999999;
		if(m1!=0)m1Yield = m4 / m1;
		else m1Yield = 999999999999;
	}
	m_m1isHighYield = TRUE;
	if(m1Yield>m2Yield)m_m1isHighYield = FALSE;
	if(!mlck && !m2lck)
	{
		rate1 = generic;
		rate2 = generic;
		if(m1==0)
		{
			if(m1BoostValid)
			{
				rate1 = 999999999999;
				m_boostMargAmt = genericBoost;
				m_boostMarg = TRUE;
				m_boostMargID = mgn1;
			}
			else rate1 = 1.0;
		}
		if(m2==0)
		{
			if(m2BoostValid)
			{
				rate2 = 999999999999;
				m_boostMarg2ndaryAmt = genericBoost;
				m_boostMarg2ndary = TRUE;
				m_boostMarg2ndaryID = mgn2;
			}
			else rate2 = 1.0;
		}
		BOOL noPlay=FALSE;
		if((m2==0 || m1==0) && margSqueeze)noPlay = TRUE;
		if(!hitch12 && !noPlay)m_frontMgnOptionsExist = TRUE;
		if(!hitch13 && !hitch14 && m_frontMgnOptionsExist)
		{
			m_untiedMgnID = mgn1;
			if(margSqueeze && rate1!=0.0)m_untiedMgnIsAsset = TRUE;
			if(!margSqueeze)m_untiedMgnIsAsset = TRUE;
		}
		if(!hitch23 && !hitch24 && m_frontMgnOptionsExist)
		{
			m_untiedMgnID = mgn2;
			if(margSqueeze && rate2!=0.0)m_untiedMgnIsAsset = TRUE;
			if(!margSqueeze)m_untiedMgnIsAsset = TRUE;
		}
	}
	if(mlck && m2lck){rate1 = 1.0;rate2 = 1.0;}
	if(mlck && !m2lck)
	{
		if(nuMargTotal<m1)unResolvedMSpan = 0.0;
		else unResolvedMSpan = nuMargTotal - m1;
		if(m2!=0)rate2 = unResolvedMSpan / m2;
		else 
		{
			BOOL validBoost = FALSE;
			validBoost = AscertainBoostValidity(mgn2,mgn1,mgn3,mgn4);
			if(validBoost)
			{
				rate2 = 999999999999;
				m_boostMarg2ndaryAmt = unResolvedMSpan;
				m_boostMarg2ndary = TRUE;
				m_boostMarg2ndaryID = mgn2;
			}
			else rate2 = 1.0;
		}
		rate1 = 1.0;
		if(crossLock)rate2 = 1.0;
		if(!hitch23 && !hitch24)
		{
			if(margSqueeze && m2!=0)
			{m_untiedMgnID = mgn2;m_untiedMgnIsAsset = TRUE;}
		}
	}
	if(!mlck && m2lck)
	{
		if(nuMargTotal<m2)unResolvedMSpan = 0.0;
		else unResolvedMSpan = nuMargTotal - m2;
		if(m1!=0)rate1 = unResolvedMSpan / m1;
		else 
		{
			BOOL validBoost = FALSE;
			validBoost = AscertainBoostValidity(mgn1,mgn2,mgn3,mgn4);
			if(validBoost)
			{
				rate1 = 999999999999;
				m_boostMargAmt = unResolvedMSpan;
				m_boostMarg = TRUE;
				m_boostMargID = mgn1;
			}
			else rate1 = 1.0;
		}
		rate2 = 1.0;
		if(crossLock)rate1 = 1.0;
		if(!hitch13 && !hitch14)
		{
			if(margSqueeze && m1!=0.0)
			{m_untiedMgnID = mgn1;m_untiedMgnIsAsset = TRUE;}
		}
	}
	
	if(mID==3 || mID==10)rate = rate1;
	if(mID==4 || mID==11)rate = rate2;
	return rate;
}

double CCalc::GetBacksideMarginRate(int mID,double absoMax,double maxFrAdj,
									double * m1R,double * m2R,
									double * m4Rate,BOOL hitch13,
									BOOL hitch14,BOOL hitch12,
									BOOL hitch23,BOOL hitch24,BOOL hitch34)
{
	double rate,m3R=1.0,m4R=1.0;
	double m3,m4,backUpMargSpan,nuBkMargSpan,oldBkMargSpan,backFrChange;
	double intendedMgnSum;
	double m1,m2,nuM3,nuM4,nuM1,nuM2;
	double m3BoostAmt,m4BoostAmt;
	int mgnID3,mgnID4,mgnID1,mgnID2,looseMargCode;
	int frID;
	BOOL bigger,horiz,frameBigger,margSqueeze;
	BOOL m3isHighYield,m3arb=TRUE,m4arb=TRUE;
	BOOL m3lck=FALSE,m4lck=FALSE,alt=FALSE,m1lck=FALSE,m2lck=FALSE;
	BOOL m3Boost=FALSE,m4Boost = FALSE,m3Boost2=FALSE,m4Boost2=FALSE;
	BOOL bkFrChangeInverse=FALSE,twoChannelCase=FALSE;
	BOOL frameLimit = FALSE;
	CRegAspect* line;
	CRegAspect* frLine;

	if(mID==3 || mID==4)
		{mgnID3 = 3;mgnID4 = 4;mgnID1 = 10;mgnID2=11,frID=17;horiz=FALSE;}
	if(mID==10 || mID==11)
		{mgnID3 = 10;mgnID4 = 11;mgnID1 = 3;mgnID2=4,frID=18;horiz=TRUE;}
	//the possibility exists upon a re-calculation with m_reOpt=TRUE, that 
	//the set of margin rates: m1R and m2R may be a combination of an 
	//increase and a decrease

	frLine = m_reg[frID];

	line = m_reg[mgnID3];
	m3lck = line->m_locked;
	m3 = line->m_nNuSize;
	line->m_nConting = line->m_nNuSize;
	nuM3 = line->m_nNuSize;

	line = m_reg[mgnID4];
	m4lck = line->m_locked;
	m4 = line->m_nNuSize;
	line->m_nConting = line->m_nNuSize;
	nuM4 = line->m_nNuSize;

	line = m_reg[mgnID1];
	m1 = line->m_nNuSize;
	m1lck = line->m_locked;
	nuM1 = m1 * (*m1R);

	line = m_reg[mgnID2];
	m2 = line->m_nNuSize;
	m2lck = line->m_locked;
	nuM2 = m2 * (*m2R);

	if(m3lck || m4lck || m1lck || m2lck)m_case8M=TRUE;

	if(absoMax==0.0){margSqueeze = TRUE;frameBigger = FALSE;}
	else {margSqueeze = FALSE;frameBigger = TRUE;}

	if(hitch13 && hitch24 && !hitch14 && !hitch23)m_reOpt = TRUE;
	if(hitch14 && hitch23 && !hitch13 && !hitch24)m_reOpt = TRUE;

	if(m_boostMarg || m_boostMarg2ndary)
	{
		if(m_boostMarg)m3Boost = DetermineInterlock(mgnID3,m_boostMargID);
		if(m_boostMarg)m4Boost = DetermineInterlock(mgnID4,m_boostMargID);
		if(m_boostMarg2ndary)m3Boost2 = DetermineInterlock(mgnID3,
			m_boostMarg2ndaryID);
		if(m_boostMarg2ndary)m4Boost2 = DetermineInterlock(mgnID4,
			m_boostMarg2ndaryID);
		if(m3Boost){m3BoostAmt = m_boostMargAmt;m3arb = FALSE;}
		if(m4Boost){m4BoostAmt = m_boostMargAmt;m4arb = FALSE;}
		if(m3Boost2){m3BoostAmt = m_boostMarg2ndaryAmt;m3arb = FALSE;}
		if(m4Boost2){m4BoostAmt = m_boostMarg2ndaryAmt;m4arb = FALSE;}
	}

	if(hitch13 && m3arb){m3R = *m1R;m3arb=FALSE;nuM3 = m3 * (*m1R);}
	if(hitch23 && m3arb){m3R = *m2R;m3arb=FALSE;nuM3 = m3 * (*m2R);}
	if(hitch14 && m4arb){m4R = *m1R;m4arb=FALSE;nuM4 = m4 * (*m1R);}
	if(hitch24 && m4arb){m4R = *m2R;m4arb=FALSE;nuM4 = m4 * (*m2R);}
	nuM3 = (m3 * m3R);
	if(m3Boost || m3Boost2)nuM3 = m3BoostAmt;
	nuM4 = (m4 * m4R);
	if(m4Boost || m4Boost2)nuM4 = m4BoostAmt;
	intendedMgnSum = nuM3 + nuM4;
	if(m3lck)
	{
		m3R = 1.0;
		nuM3 = m3;
		m3arb=FALSE;
		if(hitch34){m4R = 1.0;nuM4 = m4;m4arb=FALSE;}
	}
	if(m4lck)
	{
		m4R = 1.0;
		nuM4 = m4;
		m4arb=FALSE;
		if(hitch34){m3R = 1.0;nuM3 = m3;m3arb=FALSE;}
	}

	//valid boosts are determined at marg request time
	//if(m3Boost)nuBkMargSpan = nuBkMargSpan - m_boostMargAmt;
	//if(m4Boost)nuBkMargSpan = nuBkMargSpan - m_boostMargAmt;
	//establish basis for undetermined margin rates

	//At this point some of the rates controlling the back are arbitrary
	//and some are imposed.  The problem is that we are dealing with many
	//variables at once: maxFrAdj can be and expansion or a shrinking of
	//the backside frame.  m4 can be free to accomodate or forced to
	//impose change, that change can be either compatible or more 
	//incompatible with what is going on with the other margin
	double nuSpan;
	if(m3arb)
	{
		if(!margSqueeze && !m4arb)
		{
			if(m3>=(nuM4 - m4))
			{
				//only real scenario in this context
				if(m3!=0)m3R = (m3 - (nuM4 - m4)) / m3;
				//else m3R = 1.0; 
			}
			else 
			{
				m3R = 0.0;
				nuM3 = 0.0;
				if(maxFrAdj<((nuM4 - m4) - m3))
				{
					frameLimit = TRUE;
					double dif = ((nuM4 - m4) - m3) - maxFrAdj;
					if(m_frontMgnOptionsExist && m_untiedMgnIsAsset && 
						!m_reOpt)
					{
						double m4Adj;// = ;
						nuM4 -= dif;
						if(m4!=0)m4R = nuM4 / m4;
						else m4R = 0.0;
						if(m_untiedMgnID==mgnID1)
						{
							m4Adj = (*m2R * m2) - (m4R * m2);
							*m2R = m4R;
							if(m1!=0)*m1R = (nuM1 - m4Adj) / m1;
							else	m_boostMargAmt = nuM1 - m4Adj;
						}
						else 
						{
							m4Adj = (*m1R * m1) - (m4R * m1);
							*m1R = m4R;
							if(m2!=0)*m2R = (nuM2 - m4Adj) / m2;
							else m_boostMarg2ndaryAmt = nuM2 - m4Adj;
						}
					}
				}
			}
		}//if(!margSqueeze && !m4arb)
		if(margSqueeze && !m4arb) 
		{
			if(m3!=0)m3R = (m3 + (m4 - nuM4)) / m3;
			else
			{
				m3R = 999999999999;
				m3Boost = TRUE;
				m3BoostAmt = m3 + (m4 - nuM4);
			}
		}
	}//if(m3arb)
	else
	{
		if(m4arb)
		{
			if(margSqueeze)
			{
				if(m4!=0)m4R = (m4 + (m3 - nuM3)) / m4;
				else
				{
					m4R = 999999999999;
					m4Boost = TRUE;
					m4BoostAmt = m4 + (m3 - nuM3);
				}
			}
			else 
			{
				if(m4>(nuM3 - m3))
				{
					if(m4!=0)m4R = (m4 - (nuM3 - m3)) / m4;
					else
					{
						m4R = 999999999999;
						m4Boost = TRUE;
						m4BoostAmt = m4 - (nuM3 - m3);
					}
				}

				else
				{
					nuM4 = 0.0;
					m4R = 0.0;
					if(maxFrAdj<((nuM3 - m3) - m4))
					{
						frameLimit = TRUE;
						if(m3!=0)m3R = (m3 + maxFrAdj + m4) / m3;
						else
						{
							m3R = 999999999999;
							m3Boost = TRUE;
							m3BoostAmt = m3 + maxFrAdj + m4;
						}
					}
				}
			}
		}//if(m4arb)	
		else
		{
			BOOL tameFrAdj = FALSE;
			if(margSqueeze && (((m4 - nuM4) + (m3 - nuM3))>maxFrAdj))
				tameFrAdj = TRUE;
			if(!margSqueeze && (((nuM4 - m4) + (nuM3 - m3))>maxFrAdj))
				tameFrAdj = TRUE;
			if(tameFrAdj)frameLimit = TRUE;
			if(!m_reOpt && tameFrAdj)
			{
				if(m3R!=1.0 && m4R!=1.0)
				{
					double nuR;
					double mgSpn = m3 + m4;
					double adjMgSpan;
					if(margSqueeze)adjMgSpan = (mgSpn - maxFrAdj);
					if(!margSqueeze)adjMgSpan = (mgSpn + maxFrAdj);
					if(mgSpn!=0)nuR = adjMgSpan / mgSpn;
					else
					{
						nuR = 999999999999;
						m3Boost = TRUE;
						m4Boost = TRUE;
						m3BoostAmt = adjMgSpan;
						m4BoostAmt = adjMgSpan;
					}
					m3R = nuR;
					m4R = nuR;
				}
				double nuSubordMgSpan;
				if(m3R==1.0 && m4R!=1.0)
				{
					if(margSqueeze)
					{
						if(m4>maxFrAdj)nuSubordMgSpan = m4 - maxFrAdj;
						else nuSubordMgSpan = 0.0;
					}
					else nuSubordMgSpan = m4 + maxFrAdj;
					if(m4!=0)m4R = nuSubordMgSpan	/ m4;
					else
					{
						m4R = 999999999999;
						m4Boost = TRUE;
						m4BoostAmt = nuSubordMgSpan;
					}
				}
				if(m3R!=1.0 && m4R==1.0)
				{
					if(margSqueeze)
					{
						if(m3>maxFrAdj)nuSubordMgSpan = m3 - maxFrAdj;
						else nuSubordMgSpan = 0.0;
					}
					else nuSubordMgSpan = m3 + maxFrAdj;
					if(m3!=0)m3R = nuSubordMgSpan / m3;
					else
					{
						m3R = 999999999999;
						m3Boost = TRUE;
						m3BoostAmt = nuSubordMgSpan;
					}
				}
			}//if(!m_reOpt && tameFrAdj)

			//twoChannelAdj only TRUE if either a lock has inhibited
			//the results or if the maxFrAdj has limited them
			BOOL twoChannelAdj = FALSE;
			double margSum = (m3R * m3) + (m4R * m4);
			if(intendedMgnSum!=margSum)twoChannelAdj = TRUE;//locks impede
			if(m_reOpt && tameFrAdj)twoChannelAdj = TRUE;//frame impedes
			//locks and possibly the maxFrAdj problem
			if(m_reOpt && m_case8M && twoChannelAdj)
			{
				double nuR,lckM,freeM,nuLckM,nuFreeM,sumDif,freeMgAdj;
				double frontDif,m3HitchedRate,m4HitchedRate;
				double frontMovR,frontLckMOrigR,nuMoveBoostAmt;
				double backMovR;
				double movBoostAmt,m3HitchedBoostAmt,m4HitchedBoostAmt;
				double frontMovBoostAmt,frontLckBoostAmt;
				int lckMgID,freeMgID,m3HitchedID,m4HitchedID;
				int frontMovingID,frontLockedID;
				BOOL movBoost=FALSE,lckBoost=FALSE;
				BOOL m3HitchedBoost=FALSE,m4HitchedBoost=FALSE;
				BOOL frontMovBoost=FALSE,frontLckBoost=FALSE;
				if(hitch13 && hitch24)
				{
					m3HitchedID=mgnID1;
					m4HitchedID=mgnID2;
					m3HitchedRate = *m1R;
					m4HitchedRate = *m2R;
					if(m_boostMarg)
					{
						m3HitchedBoost = TRUE;
						m3HitchedBoostAmt = m_boostMargAmt;
					}
					if(m_boostMarg2ndary)
					{
						m4HitchedBoost = TRUE;
						m4HitchedBoostAmt = m_boostMarg2ndaryAmt;
					}
				}
				if(hitch14 && hitch23)
				{
					m3HitchedID = mgnID2;
					m4HitchedID = mgnID1;
					m3HitchedRate = *m2R;
					m4HitchedRate = *m1R;
					if(m_boostMarg)
					{
						m4HitchedBoost = TRUE;
						m4HitchedBoostAmt = m_boostMargAmt;
					}
					if(m_boostMarg2ndary)
					{
						m3HitchedBoost = TRUE;
						m3HitchedBoostAmt = m_boostMarg2ndaryAmt;
					}
				}
				if(m3R!=1.0)
				{
					freeMgID = mgnID3;
					lckMgID = mgnID4;
					freeM = m3;
					lckM = m4;
					frontMovingID = m3HitchedID;
					frontLockedID = m4HitchedID;
					frontMovR = m3HitchedRate;
					frontLckMOrigR = m4HitchedRate;
					backMovR = m3R;
					if(m4HitchedBoost)
					{
						lckBoost = TRUE;
						frontLckBoostAmt = m4HitchedBoostAmt;
					}
					if(m3HitchedBoost)
					{
						movBoost = TRUE;
						frontMovBoostAmt = m3HitchedBoostAmt;
					}
				}
				else
				{
					freeMgID = mgnID4;
					lckMgID = mgnID3;
					freeM = m4;
					lckM = m3;
					frontMovingID = m4HitchedID;
					frontLockedID = m3HitchedID;
					frontMovR = m4HitchedRate;
					frontLckMOrigR = m3HitchedRate;
					backMovR = m4R;
					if(m3HitchedBoost)
					{
						lckBoost = TRUE;
						frontLckBoostAmt = m3HitchedBoostAmt;
					}
					if(m4HitchedBoost)
					{
						movBoost = TRUE;
						frontMovBoostAmt = m4HitchedBoostAmt;
					}
				}
				CRegAspect* frontMovLine,* frontLckLine;
				frontMovLine = m_reg[frontMovingID];
				frontLckLine = m_reg[frontLockedID];
				if(!margSqueeze)
				{
					double frontDif = (frontLckLine->m_nNuSize * 
						frontLckMOrigR) - frontLckLine->m_nNuSize;
					if(lckBoost)frontDif = frontLckBoostAmt;
					double nuMoveRate;
					if(frontMovLine->m_nNuSize!=0)nuMoveRate = (frontDif + 
						(frontMovLine->m_nNuSize * frontMovR)) /
						frontMovLine->m_nNuSize;
					else 
					{
						nuMoveRate = 999999999999;
						nuMoveBoostAmt = frontDif + frontMovBoostAmt;
						movBoost = TRUE;
					}
					if(backMovR==1.0)
					{
						nuMoveRate = 1.0;
						nuMoveBoostAmt = 0;
					}
					nuFreeM = nuMoveRate * freeM;
					if(movBoost)nuFreeM = nuMoveBoostAmt;
					if((nuFreeM - freeM)>=maxFrAdj)nuFreeM = freeM + 
						maxFrAdj;
					if(!movBoost)nuR = nuFreeM / freeM;
				}
				if(margSqueeze)
				{
					double frontDif = frontLckLine->m_nNuSize - 
						(frontLckLine->m_nNuSize * frontLckMOrigR);
					if(lckBoost)frontDif = frontLckBoostAmt;
					double nuMoveRate,nuFrontMoveM;
					if((frontMovLine->m_nNuSize * frontMovR)>=frontDif)
						nuFrontMoveM = (frontMovLine->m_nNuSize * 
						frontMovR) - frontDif;
					else nuFrontMoveM = 0.0;

					if(backMovR==1.0)nuFrontMoveM = 
						frontMovLine->m_nNuSize;

					if(frontMovLine->m_nNuSize!=0)nuMoveRate = 
						nuFrontMoveM / frontMovLine->m_nNuSize;
					else
					{
						nuMoveRate = 999999999999;
						nuMoveBoostAmt = nuFrontMoveM;
						movBoost = TRUE;
					}
					nuFreeM = nuMoveRate * freeM;
					if(movBoost)nuFreeM = nuMoveBoostAmt;
					if((freeM - nuFreeM)>=maxFrAdj)nuFreeM = freeM - 
						maxFrAdj;
					if(!movBoost)nuR = nuFreeM / freeM;
				}
				if(m3R!=1.0)
				{
					m3BoostAmt = nuMoveBoostAmt;
					m3R = nuR;
					nuM3 = nuFreeM;
					if(hitch13)
					{
						*m1R = m3R;
						if(m3Boost || m3Boost2)m_boostMargAmt = m3BoostAmt;
					}
					if(hitch23)
					{
						*m2R = m3R;
						if(m3Boost || m3Boost2)m_boostMarg2ndaryAmt = 
							m3BoostAmt;
					}
				}
				else
				{
					m4BoostAmt = nuMoveBoostAmt;
					m4R = nuR;
					nuM4 = nuFreeM;
					if(hitch14)
					{
						*m1R = m4R;
						if(m3Boost || m4Boost2)m_boostMarg2ndaryAmt = 
							m4BoostAmt;
					}
					if(hitch24)
					{
						*m2R = m4R;
						if(m4Boost || m4Boost2)m_boostMarg2ndaryAmt = 
							m4BoostAmt;
					}
				}
			}//(m_reOpt && m_case8M && twoChannelAdj)
			if(m_reOpt && !m_case8M && twoChannelAdj)//maxFrAdj limitation
			{
				//only unhandled senario is !m3arb && !m4arb
				if(margSqueeze)//anticipating only 'no' from maxFrAdj
				{
					m3R = 1.0;
					if(m3Boost || m3Boost2)m3BoostAmt = 0.0;
					m4R = 1.0;
					if(m4Boost || m4Boost2)m4BoostAmt = 0.0;
				}
				if(!margSqueeze)
				{
					double share = maxFrAdj * .5;
					if(m3!=0)m3R = (m3 + share) / m3;
					else m3BoostAmt = share;
					if(m4!=0)m4R = (m4 + share) / m4;
					else m4BoostAmt = share;
				}
			}//(m_reOpt && !m_case8M && twoChannelAdj)
		}//if(!m4arb)
	}
	if(!m3Boost && !m3Boost2)nuM3 = m3 * m3R;
	else nuM3 = m3BoostAmt;
	if(!m4Boost && !m4Boost2)nuM4 = m4 * m4R;
	else nuM4 = m4BoostAmt;
	if((nuM3>=m3)&&(nuM4>=m4))backFrChange = (nuM3 - m3) + (nuM4 - m4);
	if((nuM3>=m3)&&(nuM4<m4))
	{
		if((nuM3 - m3)>=(m4 - nuM4))backFrChange = 
			(nuM3 - m3) - (m4 - nuM4);
		else backFrChange = (m4 - nuM4) - (nuM3 - m3);
	}
	if((nuM3<m3)&&(nuM4<m4))backFrChange = (m3 - nuM3) + (m4 - nuM4);
	if((nuM3<m3)&&(nuM4>=m4))
	{
		if((m3 - nuM3)>=(nuM4 - m4))backFrChange = 
			(m3 - nuM3) - (nuM4 - m4);
		else backFrChange = (nuM4 - m4) - (m3 - nuM3);
	}
	if(margSqueeze)m_backFrameDerivative = frLine->m_nNuSize + 
		backFrChange;
	else m_backFrameDerivative = frLine->m_nNuSize - backFrChange;
	m_m3 = nuM3;
	m_m4 = nuM4;
	//if(m3!=0)m3R = nuM3 / m3;
	//else m3R = 999999999999;
	//if(m4!=0)m4R = nuM4 / m4;
	//else m4R = 999999999999;
	rate = m3R;
	*m4Rate = m4R;
	if(frameLimit && !m_carryOutFrAdjOnly)
	{
		if(m_backFrCase==(m_backFrCase|1))m_case3 = TRUE;
		if(m_backFrCase==(m_backFrCase|2))m_case11 = TRUE;
		if(m_backFrCase==(m_backFrCase|4))m_case16 = TRUE;
	}
	if(hitch13 || hitch14 || hitch23 || hitch24 || hitch34)m_case4M = TRUE;
	return rate;
}

double CCalc::GetCompatibleMargRate(double optR1,int mgnID,double * optR2,
									double maxR3,double maxR4,BOOL squeeze,
									BOOL hitch13,BOOL hitch14,BOOL hitch12,
									BOOL hitch23,BOOL hitch24,
									double nuFrame,double nuMargSpan,
									double maxFrAdj)
{
	BOOL m1arb=FALSE,adj2=FALSE,adj3=FALSE,adj4=FALSE,horiz;
	BOOL crossHitch = FALSE,alt=FALSE;
	BOOL lock1=FALSE,lock2=FALSE,lock3=FALSE,lock4=FALSE;
	BOOL m1Boost=FALSE,m2Boost=FALSE;
	int mID1,mID2,pgID,mID3,mID4,bkFrID;

	double rate,rate1,rate2,maxR1,maxR2,nuMarg1,nuMarg2,margRem;
	double maxReOptRate1=0.0,maxReOptRate2=0.0;
	double margSumChange,oldSumSpan, nuSumSpan,margResult;
	double nuM1,nuM2;
	CRegAspect* line;
	if(mgnID==3 || mgnID==4){mID1=3;mID2=4;mID3=10;mID4=11;pgID=6;
		horiz=TRUE;bkFrID=18;}
	if(mgnID==10 || mgnID==11){mID1=10;mID2=11;mID3=3;mID4=4;pgID=16;
		horiz=FALSE;bkFrID=17;}
	crossHitch = DetermineInterlock(mID1,mID2);
	rate1 = optR1;
	rate2 = *optR2;
	margRem = nuMargSpan;

	double pageAsp;
	line = m_reg[pgID];
	pageAsp = line->m_nNuSize;

	line = m_reg[mID1];
	double origM1 = line->m_nNuSize;
	lock1 = line->m_locked;

	line = m_reg[mID2];
	double origM2 = line->m_nNuSize;
	lock2 = line->m_locked;

	line = m_reg[mID3];
	lock3 = line->m_locked;

	line = m_reg[mID4];
	lock4 = line->m_locked;

	if(lock1 || lock2 || lock3 || lock4)m_case8M = TRUE;

	if(m_boostMarg || m_boostMarg2ndary)
	{
		if(m_boostMargID==mID1 || hitch12)m1Boost = TRUE;
		if(m_boostMarg2ndaryID==mID2 || hitch12)m2Boost = TRUE;
	}
	if(m1Boost)
	{
		if(hitch13)maxR3 = m_boostMargAmt;
		if(hitch14)maxR4 = m_boostMargAmt;
		optR1 = m_boostMargAmt;
		nuM1 = m_boostMargAmt;
	}
	if(m2Boost)
	{
		if(hitch23)maxR3 = m_boostMarg2ndaryAmt;
		if(hitch24)maxR4 = m_boostMarg2ndaryAmt;
		*optR2 = m_boostMarg2ndaryAmt;
		nuM2 = m_boostMarg2ndaryAmt;
	}
	maxR1 = 0.0;
	maxR2 = 0.0;
	if(!squeeze){maxR1 = 999999999999;maxR2 = 999999999999;}
	if(hitch13 && !hitch14)maxR1 = maxR3;
	if(hitch14 && !hitch13)maxR1 = maxR4;
	if(hitch14 && hitch13)
	{
		if(squeeze && maxR4>=maxR3)maxR1 = maxR4;
		if(!squeeze && maxR4>=maxR3)maxR1 = maxR3;
		if(squeeze && maxR3>=maxR4)maxR1 = maxR3;
		if(!squeeze && maxR3>=maxR4)maxR1 = maxR4;
	}
	if(lock1)maxR1 = 1.0;

	if(hitch23 && !hitch24)maxR2 = maxR3;
	if(hitch24 && !hitch23)maxR2 = maxR4;
	if(hitch24 && hitch23)
	{
		if(squeeze && maxR4>=maxR3)maxR2 = maxR4;
		if(!squeeze && maxR4>=maxR3)maxR2 = maxR3;
		if(squeeze && maxR3>=maxR4)maxR2 = maxR3;
		if(!squeeze && maxR3>=maxR4)maxR2 = maxR4;
	}
	if(lock2)maxR2 = 1.0;
	if(crossHitch)
	{
		if(lock1 || lock2){maxR2 = 1.0;maxR1 = 1.0;}
	}
	if(maxR1>optR1 && squeeze){m1arb = TRUE; optR1 = maxR1;}
	if(maxR2>*optR2 && squeeze){adj2 = TRUE; *optR2 = maxR2;}
	if(maxR1<optR1 && !squeeze){m1arb = TRUE; optR1 = maxR1;}
	if(maxR2<*optR2 && !squeeze){adj2 = TRUE; *optR2 = maxR2;}

	if(!m1Boost)nuM1 = origM1 * optR1;
	else nuM1 = optR1;
	if(!m2Boost)nuM2 = origM2 * (*optR2);
	else nuM2 = *optR2;
	margResult = nuM1 + nuM2;
	
	if(nuMargSpan!=margResult && m_frontMgnOptionsExist &&
		m_untiedMgnIsAsset)
	{
		int cID,trID;
		double complyM,transM,complyR,transR,nuComplyM,nuTransM;
		if(m_untiedMgnID==mID1){cID=mID1;trID=mID2;transR = *optR2;}
		if(m_untiedMgnID==mID2){cID=mID2;trID=mID1;transR = optR1;}
		line = m_reg[trID];
		transM = line->m_nNuSize;
		line = m_reg[cID];
		complyM = line->m_nNuSize;
		nuTransM = (transM * transR);				
		if(m_boostMarg && (m_boostMargID==trID))nuTransM = 
			m_boostMargAmt;
		if(m_boostMarg2ndary && (m_boostMarg2ndaryID==trID))nuTransM = 
			m_boostMarg2ndaryAmt;
		if(nuMargSpan>nuTransM)nuComplyM = 
			nuMargSpan - nuTransM;
		else nuComplyM = 0.0;
		if(complyM!=0)complyR = nuComplyM / complyM;
		else 
		{
			if(cID==mID1)
			{
				complyR = 99;
				m_boostMarg = TRUE;
				m_boostMargAmt = nuComplyM;
				m_boostMargID = mID1;
			}
			if(cID==mID2)
			{
				complyR = 999999999999;
				m_boostMarg2ndary = TRUE;
				m_boostMarg2ndaryAmt = nuComplyM;
				m_boostMarg2ndaryID = mID2;
			}
		}

		if(m_untiedMgnID==mID1)optR1 = complyR;
		if(m_untiedMgnID==mID2)*optR2 = complyR;
	}

	//if(m_reOpt):
	//determine best investment of frontside change.  Transmitting 
	//margins that are more of a tail (than a dog) make  greater
	//changes in the backside and are therefore 'low' yield: ie, they
	//give less front-side bang for the back-side buck.
	//calculate normal and "inverse" back-frame-change 
	//possibilities and compare resulting front frame changes pertaining
	//to both options
	if(m_reOpt)
	{
		//setup
		double m1=origM1,m2=origM2,m3,m4;
		double nuHY,nuLY,hiRate,loRate,loBkAdj;
		double frameChange,bkFrChange,initBkFrChange;
		double hiBoostAmt,loBoostAmt;
		int hyID=mID1,lyID=mID2,hyBkID,lyBkID;
		BOOL theEnd=TRUE,m3isHighYield,hiBoost=FALSE,loBoost=FALSE;
		CRegAspect* hiLine,*loLine,*hiBLine,*loBLine;
		line = m_reg[mID3];
		m3 = line->m_nNuSize;
		line = m_reg[mID4];
		m4 = line->m_nNuSize;
		hiRate = optR1;
		loRate = *optR2;
		if(m_boostMarg)
		{
			hiBoost = TRUE;
			hiBoostAmt = m_boostMargAmt;
		}
		if(m_boostMarg2ndary)
		{
			loBoost = TRUE;
			loBoostAmt = m_boostMarg2ndaryAmt;
		}
		if(!m_m1isHighYield)
		{
			hyID = mID2;
			lyID = mID1;
			hiRate = *optR2;
			loRate = optR1;
			if(m_boostMarg2ndary)
			{
				hiBoostAmt = m_boostMarg2ndaryAmt;
				hiBoost = TRUE;
			}
			if(m_boostMarg)
			{
				loBoostAmt = m_boostMargAmt;
				loBoost = TRUE;
			}
		}
		hiLine = m_reg[hyID];
		loLine = m_reg[lyID];
		m3isHighYield  = TRUE;
		if(DetermineInterlock(hyID,mID3)){hyBkID = mID3;lyBkID = mID4;}
		else {hyBkID = mID4;lyBkID = mID3;m3isHighYield = FALSE;}
		hiBLine = m_reg[hyBkID];
		loBLine = m_reg[lyBkID];
		double prec = 0.0001;
		double hiF,loF,hiBk,loBk,nHiF,nLoF,nHiBk,nLoBk;
		double change=0.0,loops=0.0;
		double netBkChange;
		double lowest = 999999999999;
		BOOL adjHiF,adjLoF;
		hiF = hiLine->m_nNuSize * hiRate;
		if(hiBoost)hiF = hiBoostAmt;
		nHiF = hiF;
		loF = loLine->m_nNuSize * loRate;
		if(loBoost)loF = loBoostAmt;
		nLoF = loF;
		hiBk = hiBLine->m_nNuSize * hiRate;
		nHiBk = hiBk;
		loBk = loBLine->m_nNuSize * loRate;
		nLoBk = loBk;
		if(squeeze)initBkFrChange = (hiBLine->m_nNuSize - hiBk) + 
			(loBLine->m_nNuSize - loBk);
		else initBkFrChange = (hiBk - hiBLine->m_nNuSize) +
			(loBk - loBLine->m_nNuSize);
		netBkChange = initBkFrChange;
		if(hiF==0 && !squeeze)loops = 100000000000;
		if(loF==0 && squeeze)loops = 100000000000;
		if(maxFrAdj>=initBkFrChange)loops = 100000000000;
		if(m_case3M)loops = 100000000000;

		for( ;loops<100000000000; )//increase span loop
		{
			//the starting margin values are supposed to be valid in their
			//compliance with the necessary front frame request and 
			//invalid in their effect on the back-side frame
			if(hiF>change && squeeze)
			{
				theEnd = FALSE;
				nHiF = hiF - change;
				nLoF = loF + change;
				hiRate = (nHiF / hiF);
				loRate = (nLoF / loF);
			}
			if(loF>change && !squeeze)
			{
				theEnd = FALSE;
				nHiF = hiF + change;
				nLoF = loF - change;
				hiRate = (nHiF / hiF);
				loRate = (nLoF / loF);
			}
			nHiBk = hiRate * hiBk;
			nLoBk = loRate * loBk;
			if(loRate>=1.0)loBkAdj = nLoBk - loBk;
			else loBkAdj = loBk - nLoBk;
			bkFrChange = loBkAdj - (nHiBk - hiBk);
			if(bkFrChange<=initBkFrChange)netBkChange = initBkFrChange -
				bkFrChange;
			else netBkChange = 0.0;
			if(lowest<netBkChange)theEnd = TRUE;
			if(!theEnd)lowest = netBkChange;
			if(netBkChange<=maxFrAdj || theEnd)
			{
				theEnd = FALSE;
				loops = 0.0;
				lowest = 999999999999;
				if(change==0.0)break;
				if(prec==0.000000000001)break;
				if(prec==0.00000001){change -= prec;prec = 0.000000000001;}
				if(prec==0.0001){change -= prec;prec = 0.00000001;}
			}
			else {change += prec;loops++;theEnd = TRUE;}	
		}//for(;;)
		if(netBkChange<=maxFrAdj)//accept new values 
		{
			hiBLine->m_nConting = nHiBk;
			loBLine->m_nConting = nLoBk;
			if(m_m1isHighYield){optR1 = hiRate;*optR2 = loRate;}
			else {optR1 = loRate;*optR2 = hiRate;}
			line = m_reg[bkFrID];
			if(squeeze)m_backFrameDerivative = line->m_nNuSize + 
				netBkChange;
			else m_backFrameDerivative = line->m_nNuSize - netBkChange;
		}
		else //figure closest values
		{
			loBLine->m_nConting = 0.0;
			hiBLine->m_nConting = hiBLine->m_nNuSize + maxFrAdj + 
				loBLine->m_nNuSize;
			if(m_m1isHighYield)
			{
				*optR2 = 0.0;
				optR1 = (loBLine->m_nNuSize + maxFrAdj + 
					hiBLine->m_nNuSize) / (loBLine->m_nNuSize + 
					0.0000000000001);
			}
			if(!m_m1isHighYield)
			{
				optR1 = 0.0;
				*optR2 = (loBLine->m_nNuSize + maxFrAdj +
					hiBLine->m_nNuSize)	/ (loBLine->m_nNuSize + 
					0.0000000000001);
			}
			line = m_reg[bkFrID];
			m_backFrameDerivative = line->m_nNuSize - maxFrAdj;
		}
		if(m3isHighYield)
		{
			m_m3 = hiBLine->m_nConting;
			m_m4 = loBLine->m_nConting;
		}
		else 
		{
			m_m3 = loBLine->m_nConting;
			m_m4 = hiBLine->m_nConting;
		}

	}//if(m_reOpt)
	

	m_reOpt = FALSE;
	return optR1;
}

BOOL CCalc::ReportMarginInvolvement(int mgnID)
{
	BOOL involved = FALSE;
	CSerioDoc* pDoc = CSerioDoc::GetDoc();
	int mgnCode = pDoc->m_dMargRat;
	if(mgnCode%17==0 || mgnCode%5==0 || mgnCode%7==0)
	{ 
		if(mgnID==3)involved = TRUE;
	}
	if(mgnCode%13==0 || mgnCode%3==0 || mgnCode%7==0)
	{ 
		if(mgnID==4)involved = TRUE;
	}
	if(mgnCode%17==0 || mgnCode%13==0 || mgnCode%11==0)
	{ 
		if(mgnID==10)involved = TRUE;
	}
	if(mgnCode%11==0 || mgnCode%5==0 || mgnCode%3==0)
	{ 
		if(mgnID==11)involved = TRUE;
	}
	return involved;
}

BOOL CCalc::AscertainBoostValidity(int index,int sibID,int m3ID,int m4ID)
{
	BOOL valid = TRUE,hitched = FALSE,involved = FALSE;
	int id;
	CRegAspect* line;
	involved = ReportMarginInvolvement(index);
	if(involved)
	{
		int i;
		for(i=0;i<3;i++)
		{
			if(i==0)id = sibID;
			if(i==1)id = m3ID;
			if(i==2)id = m4ID;
			hitched = DetermineInterlock(index,id);
			if(hitched)
			{
				line = m_reg[id];
				if(line->m_nNuSize!=0)valid = FALSE;
				if(line->m_locked){valid = FALSE;m_case8 = TRUE;}
			}
			hitched = FALSE;
		}
	}
	if(!valid)m_case4 = TRUE;
	return valid;
}


BOOL CCalc::CheckMarginMobility(int mID, int qCode, BOOL squeeze)
{
//	double marg,marg2,startMarg,startMarg2;
	BOOL imobile = FALSE;
	CRegAspect* line = m_reg[mID];
	BOOL h = line->m_horiz;
	BOOL bothMs = FALSE,crossLock = FALSE,fixM = FALSE;
	BOOL mgnReq3 = FALSE,mgnReq4 = FALSE;
	BOOL mgnSet3=FALSE,mgnSet4=FALSE;
	BOOL m1Min = FALSE, m2Min = FALSE, m1Max = FALSE, m2Max = FALSE;
	BOOL fixMarg=FALSE,fixMarg2=FALSE;
	BOOL mgnLock = FALSE,mgnReq = FALSE,mgnReqAp = FALSE,mgnReqAp2=FALSE;
	BOOL mgnLock2 = FALSE,mgnReq2 = FALSE;
	BOOL mConstr = FALSE,alt = FALSE,applied=FALSE,applied2=FALSE;
	int m3,m4,mgnID,mgnID2;
	if(h){ mgnID=3; mgnID2=4; m3=10; m4=11;}
	if(!h){ mgnID=10; mgnID2=11; m3=3; m4=4;}

	int sz = FLGSTORESZ;
	BOOL flags[FLGSTORESZ];
	StoreRestoreCurrentFlags(TRUE,flags,sz);
	
	line = m_reg[mgnID];
	mgnLock = line->m_locked;
	if(mgnLock)	m_case8M = TRUE;
	mgnReq = line->m_instigating;
	if(mgnReq && line->m_applied)mgnLock = TRUE;
	mgnReqAp = line->m_asking;
	mConstr = line->m_fixedRatio;
	m1Max = line->m_maxSet;
	m1Min = line->m_minSet;
	if(mgnReqAp && m1Max && !squeeze) m_case2M = TRUE;
	if(mgnReqAp && m1Min && squeeze) m_case2M = TRUE;

	line = m_reg[mgnID2];
	mgnLock2 = line->m_locked;
	if(mgnLock2)m_case8M = TRUE;
	mgnReq2 = line->m_instigating;
	if(mgnReq2 && line->m_applied)mgnLock2 = TRUE;
	mgnReqAp2 = line->m_asking;
	mConstr = line->m_fixedRatio;
	m2Max = line->m_maxSet;
	m2Min = line->m_minSet;
	if(mgnReqAp2 && m2Max && !squeeze) m_case2M = TRUE;
	if(mgnReqAp2 && m2Min && squeeze) m_case2M = TRUE;

	
	if(mgnReq2 && mgnReq)bothMs = TRUE;
	BOOL look = FALSE;
	BOOL m3Lock,m4Lock;
	BOOL m1is = ReportMarginInvolvement(mgnID);
	BOOL m2is = ReportMarginInvolvement(mgnID2);
	BOOL m3is = ReportMarginInvolvement(m3);
	BOOL m4is = ReportMarginInvolvement(m4);
	BOOL m1Freeze = FALSE;
	BOOL m2Freeze = FALSE;
	crossLock = DetermineInterlock(mgnID,mgnID2);
	if(m1is || m2is) look = TRUE;
	if(look)
	{
		line = m_reg[m3];
		m3Lock = line->m_locked;
		if(line->m_instigating && line->m_applied)mgnReq3 = TRUE;
		if(!squeeze && line->m_maxSet)mgnSet3 = TRUE;
		if(squeeze && line->m_minSet)mgnSet3 = TRUE;
		line = m_reg[m4];
		m4Lock = line->m_locked;
		if(line->m_instigating && line->m_applied)mgnReq4 = TRUE;
		if(!squeeze && line->m_maxSet)mgnSet4 = TRUE;
		if(squeeze && line->m_minSet)mgnSet4 = TRUE;

		if(m3is && mgnSet3)
		{	
			if(m1Freeze || DetermineInterlock(m3,mgnID))m1Freeze = TRUE;
			if(m2Freeze || DetermineInterlock(m3,mgnID2))m2Freeze = TRUE;
			m_case2M = TRUE;
		}
		if(m4is && mgnSet4)
		{
			if(m1Freeze || DetermineInterlock(m4,mgnID))m1Freeze = TRUE;
			if(m2Freeze || DetermineInterlock(m4,mgnID2))m2Freeze = TRUE;
			m_case2M = TRUE;
		}
		if(m3is && m3Lock)
		{	
			if(m1Freeze || DetermineInterlock(m3,mgnID))m1Freeze = TRUE;
			if(m2Freeze || DetermineInterlock(m3,mgnID2))m2Freeze = TRUE;
			m_case8M = TRUE;
		}
		if(m4is && m4Lock)
		{
			if(m1Freeze || DetermineInterlock(m4,mgnID))m1Freeze = TRUE;
			if(m2Freeze || DetermineInterlock(m4,mgnID2))m2Freeze = TRUE;
			m_case8M = TRUE;
		}
		if(m3is && mgnReq3)
		{	
			if(m1Freeze || DetermineInterlock(m3,mgnID))m1Freeze = TRUE;
			if(m2Freeze || DetermineInterlock(m3,mgnID2))m2Freeze = TRUE;
			m_case2M = TRUE;
		}
		if(m4is && mgnReq4)
		{
			if(m1Freeze || DetermineInterlock(m4,mgnID))m1Freeze = TRUE;
			if(m2Freeze || DetermineInterlock(m4,mgnID2))m2Freeze = TRUE;
			m_case2M = TRUE;
		}
		if(!m2Freeze && !m1Freeze) 
		{
			m_case2M = FALSE;
			m_case4M = FALSE;
		}
	}
	if(m1Freeze || m2Freeze)fixM = TRUE;
	if(m1Freeze	|| mgnLock)fixMarg = TRUE;
	if(m2Freeze	|| mgnLock2)fixMarg2 = TRUE;
	/*if(qCode==4)	
	{
		if(mgnReq && mgnReqAp)fixMarg = TRUE;
		if(mgnReq2 && mgnReqAp2)fixMarg2 = TRUE;	
	}
	*/
	//if(mgnReq && applied)fixMarg = TRUE;
	//if(mgnReq2 && applied2)fixMarg2 = TRUE;
	if(squeeze && m2Min){fixMarg2 = TRUE;m_case2M = TRUE;}
	if(squeeze && m1Min){fixMarg = TRUE;m_case2M = TRUE;}
	if(!squeeze)
	{
		if(m2Max){fixMarg2 = TRUE;m_case2M = TRUE;}
		if(m1Max){fixMarg = TRUE;m_case2M = TRUE;}
	}

	BOOL fix = FALSE;
	if(crossLock && fixMarg)fix = TRUE;
	if(crossLock && fixMarg2)fix = TRUE;
	if(fix)
	{
		fixMarg = TRUE;
		fixMarg2 = TRUE;
//		if(startLevel!=4 && !bothMs)
		m_case4M = TRUE;
		m_case8M = TRUE;
	}
	if(mID==mgnID)imobile = fixMarg;
	if(mID==mgnID2)imobile = fixMarg2;
	if(!imobile)StoreRestoreCurrentFlags(FALSE,flags,sz);
	if(mID!=mgnID && mID!=mgnID2)AfxMessageBox("Invalid margin information via CheckMarginMobility()");

	return imobile;
}


BOOL CCalc::TestExpandibility(int level,BOOL horiz)//for count reduction only
{
	BOOL margShrink = FALSE,alt = FALSE;
	int mgnID,mgnID2,nID,startLevelID;
	int countID = 99;
	if(horiz)
	{
		if(level==1){countID = 5;nID = 0;}
		if(level==2){countID = 19;nID = 1;}
		if(level==3){countID = 21;nID = 2;}
		//if(level==4){countID = 21;nID = 17;}
		mgnID = 3;mgnID2 = 4;
	}
	if(!horiz)
	{
		if(level==1){countID = 12;nID = 7;}
		if(level==2){countID = 20;nID = 8;}
		if(level==3){countID = 22;nID = 9;}
		//if(level==4){countID = 99;nID = 18;}
		mgnID = 10; mgnID2 = 11;
	}
	startLevelID = nID;
	BOOL cando = FALSE;
	for( ;level>0;level--)
	{
		CRegAspect* line;
		int count;
		if(countID!=99)
		{
			line = m_reg[countID];
			alt = line->m_alt;
			if(alt)count = line->m_nNuCount;
			if(!alt)count = line->m_nCount;
		}
		else count = 1;
		line = m_reg[nID];
		int locked = line->m_locked;
		if(nID==startLevelID && locked)
		{
			m_case3 = TRUE;
			return FALSE;
		}
		if(level!=4)
		{
			if(count!=1){cando = TRUE;break;}
			if(count==1 && locked){cando = FALSE;break;}
		}
		if(level==4)//not likely needed to check expandibility
		{
			BOOL m1fix = CheckMarginMobility(mgnID,1,margShrink);
			BOOL m2fix = CheckMarginMobility(mgnID2,1,margShrink);
			if(m1fix && m2fix)cando = FALSE;
			if(!m1fix || !m2fix)cando = TRUE;
		}
		nID = GetEnclosedAspectID(nID);
		countID = GetAssociatedCountID(nID);
		if(level==4)nID = GetEnclosedAspectID(nID);
		if(level==4 && m_colorMode!=1)level--;
	}

	return cando;
}

BOOL CCalc::TestContractibility(int level,BOOL horiz)//for count reduction only
{
	BOOL margShrink = TRUE,alt = FALSE;
	int mgnID,mgnID2,nID,startLevelID;
	CRegAspect* line;
	int countID = 99;
	if(horiz)
	{
		if(level==1){countID = 5;nID = 0;}//not valid level
		if(level==2){countID = 19;nID = 1;}
		if(level==3){countID = 21;nID = 2;}
		if(level==4){countID = 99;nID = 17;}
		mgnID = 3;mgnID2 = 4;
	}
	if(!horiz)
	{
		if(level==1){countID = 12;nID = 7;}//not valid level
		if(level==2){countID = 20;nID = 8;}
		if(level==3){countID = 20;nID = 9;}
		if(level==4){countID = 22;nID = 18;}
		mgnID = 10; mgnID2 = 11;
	}
	startLevelID = nID;
	BOOL cando = FALSE;
	for( ;level<5;level++)
	{
		int count;
		if(countID!=99)
		{
			line = m_reg[countID];
			alt = line->m_alt;
			if(alt)count = line->m_nNuCount;
			if(!alt)count = line->m_nCount;
		}          
		else count = 1;
		line = m_reg[nID];
		int locked = line->m_locked;
		if(nID==startLevelID && locked)
		{
			m_case3 = TRUE;
			return FALSE;
		}
		if(level!=4)
		{
			if(count!=1){cando = TRUE;break;}
			if(count==1 && locked){cando = FALSE;break;}
		}
		if(level==4)
		{
			BOOL m1fix = CheckMarginMobility(mgnID,1,margShrink);
			BOOL m2fix = CheckMarginMobility(mgnID2,1,margShrink);
			if(m1fix && m2fix)cando = FALSE;
			if(!m1fix || !m2fix)cando = TRUE;
		}
		countID = GetAssociatedCountID(nID);
		nID = GetEnclosingAspectID(nID);
		if(level==1)nID = GetEnclosingAspectID(nID);
		if(level==2 && m_colorMode!=1)level++;
	}

	return cando;
}

int CCalc::GetEnclosingAspectID(int id)
{
	int outID;
	if(id==0) outID = 1;
	if(id==1) outID = 2;
	if(id==2) outID = 17;
	if(id==3) outID = 6;
	if(id==4) outID = 6;
	if(id==5) outID = 1;
	if(id==6) outID = 6;
	if(id==7) outID = 8;
	if(id==8) outID = 9;
	if(id==9) outID = 18;
	if(id==10) outID = 16;
	if(id==11) outID = 16;
	if(id==12) outID = 8;
	if(id==16) outID = 16;
	if(id==17) outID = 6;
	if(id==18) outID = 16;
	if(id==19) outID = 2;
	if(id==20) outID = 8;
	if(id==21) outID = 21;
	if(id==22) outID = 22;
	return outID;
}

int CCalc::GetEnclosedAspectID(int id)
{
	int inID;
	if(id==0) inID = 0;
	if(id==1) inID = 0;
	if(id==2) inID = 1;
	if(id==3) inID = 17;
	if(id==4) inID = 17;
	if(id==5) inID = 0;
	if(id==6) inID = 17;
	if(id==7) inID = 7;
	if(id==8) inID = 7;
	if(id==9) inID = 8;
	if(id==10) inID = 18;
	if(id==11) inID = 18;
	if(id==12) inID = 7;
	if(id==16) inID = 18;
	if(id==17) inID = 2;
	if(id==18) inID = 9;
	if(id==19) inID = 0;
	if(id==20) inID = 7;
	if(id==21) inID = 1;
	if(id==22) inID = 8;
	return inID;
}

int CCalc::GetAssociatedCountID(int id)
{
	int cID = 99;
	if(id==0)cID = 5; 
	if(id==1)cID = 19;
	if(id==2)cID = 21;
	if(id==7)cID = 12;
	if(id==8)cID = 20;
	if(id==9)cID = 22;

	return cID;
}

int CCalc::GetAssociatedSizeID(int id)
{
	int cID = 99;
	if(id==5)cID = 0; 
	if(id==19)cID = 1;
	if(id==21)cID = 2;
	if(id==12)cID = 7;
	if(id==20)cID = 8;
	if(id==22)cID = 9;

	return cID;

}

int CCalc::GetSiblingMarginID(int id)
{
	int sib = 99;
	if(id==3)sib = 4;
	if(id==4)sib = 3;
	if(id==10)sib = 11;
	if(id==11)sib = 10;
	return sib;
}

int CCalc::GetLevel(int id)
{
	int level = 99;
	if(id==0)level = 1; 
	if(id==1)level = 2;
	if(id==2)level = 3;
	if(id==7)level = 1;
	if(id==8)level = 2;
	if(id==9)level = 3;
	if(id==6 || id==16)level = 5;
	if(id==17 || id==18)level = 4;
	if(level==99)AfxMessageBox(
		"Invalid index fed to CCalc::GetLevel");
	return level;
}

/////////////////////////////////////////////////////////////////
// Strings and notices
CString CCalc::GetAdvisoryStrings()
{
	CString s = cs6; 
	if(m_case1) {s += cs1; m_case1 = FALSE;}
	if(m_case2) {s += cs2; m_case2 = FALSE;}
	if(m_case3) {s += cs3; m_case3 = FALSE;}
	if(m_case4) {s += cs4; m_case4 = FALSE;}
	if(m_case5) {s += cs5; m_case5 = FALSE;}
	if(m_case8) {s += cs8; m_case8 = FALSE;}
	if(m_case9) {s += cs9; m_case9 = FALSE;}
	if(m_case10) {s += cs10; m_case10 = FALSE;}
	if(m_case11) {s += cs11; m_case11 = FALSE;}
	if(m_case12) {s += cs12; m_case12 = FALSE;}
	if(m_case13) {s += cs13; m_case13 = FALSE;}
	if(m_case14) {s += cs14; m_case14 = FALSE;}
	if(m_case15) {s += cs15; m_case15 = FALSE;}
	if(m_case16) {s += cs16; m_case16 = FALSE;}
	if(m_case17) {s += cs17; m_case17 = FALSE;}
	if(m_case18) {s += cs18; m_case18 = FALSE;}
	if(m_case19) {s += cs19; m_case19 = FALSE;}
	if(m_case20) {s += cs20; m_case20 = FALSE;}
	if(m_case21) {s += cs21; m_case21 = FALSE;}
	if(m_case22) {s += cs22; m_case22 = FALSE;}

	s += cs7;
	return s;
}

void CCalc::StoreRestoreCurrentFlags(BOOL store,BOOL flags [],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		if(store)
		{
			if(i==0)flags[i] = m_case1;
			if(i==1)flags[i] = m_case2;
			if(i==2)flags[i] = m_case3;
			if(i==3)flags[i] = m_case4;
			if(i==4)flags[i] = m_case5;
			//if(i==5)flags[i] = m_case6;
			//if(i==6)flags[i] = m_case7;
			if(i==7)flags[i] = m_case8;
			if(i==8)flags[i] = m_case9;
			if(i==9)flags[i] = m_case10;
			if(i==10)flags[i] = m_case11;
			if(i==11)flags[i] = m_case12;
			if(i==12)flags[i] = m_case13;
			if(i==13)flags[i] = m_case14;
			if(i==14)flags[i] = m_case15;
			if(i==15)flags[i] = m_case16;
			if(i==17)flags[i] = m_case17;
			if(i==18)flags[i] = m_case18;
			if(i==19)flags[i] = m_case19;

			if(i==20)flags[i] = m_case3M;
			if(i==21)flags[i] = m_case4M;
			if(i==22)flags[i] = m_case8M;
			if(i==23)flags[i] = m_case11M;

			if(i==24)flags[i] = m_case3C;
			if(i==25)flags[i] = m_case8C;
			if(i==26)flags[i] = m_case9C;
			if(i==27)flags[i] = m_case11C;
			if(i==28)flags[i] = m_case16C;

			if(i==29)flags[i] = m_case13FCR;
			if(i==30)flags[i] = m_case14FCR;

			if(i==31)flags[i] = m_case20;
			if(i==32)flags[i] = m_case21;
			if(i==33)flags[i] = m_case22;
		}
		else
		{
			if(i==0)m_case1 = flags[i];
			if(i==1)m_case2 = flags[i];
			if(i==2)m_case3 = flags[i];
			if(i==3)m_case4 = flags[i];
			if(i==4)m_case5 = flags[i];
			//if(i==5)m_case6 = flags[i];
			//if(i==6)m_case7 = flags[i];
			if(i==7)m_case8 = flags[i];
			if(i==8)m_case9 = flags[i];
			if(i==9)m_case10 = flags[i];
			if(i==10)m_case11 = flags[i];
			if(i==11)m_case12 = flags[i];
			if(i==12)m_case13 = flags[i];
			if(i==13)m_case14 = flags[i];
			if(i==14)m_case15 = flags[i];
			if(i==15)m_case16 = flags[i];
			if(i==17)m_case17 = flags[i];
			if(i==18)m_case18 = flags[i];
			if(i==19)m_case19 = flags[i];

			if(i==20)m_case3M = flags[i];
			if(i==21)m_case4M = flags[i];
			if(i==22)m_case8M = flags[i];
			if(i==23)m_case11M = flags[i];

			if(i==24)m_case3C = flags[i];
			if(i==25)m_case8C = flags[i];
			if(i==26)m_case9C = flags[i];
			if(i==27)m_case11C = flags[i];
			if(i==28)m_case16C = flags[i];

			if(i==29)m_case13FCR = flags[i];
			if(i==30)m_case14FCR = flags[i];

			if(i==31)m_case20 = flags[i];
			if(i==32)m_case21 = flags[i];
			if(i==33)m_case22 = flags[i];
		}
	}
}

void CCalc::AddOriginalFlags(BOOL flags [],int sz)
{
	int i;
	BOOL on = FALSE;
	for(i=0;i<sz;i++)
	{
		if(i==0 && flags[i])m_case1 = TRUE;
		if(i==1 && flags[i])m_case2 = TRUE;
		if(i==2 && flags[i])m_case3 = TRUE;
		if(i==3 && flags[i])m_case4 = TRUE;
		if(i==4 && flags[i])m_case5 = TRUE;
		//if(i==6  if(i==7
		if(i==7 && flags[i])m_case8 = TRUE;
		if(i==8 && flags[i])m_case9 = TRUE;
		if(i==9 && flags[i])m_case10 = TRUE;
		if(i==10 && flags[i])m_case11 = TRUE;
		if(i==11 && flags[i])m_case12 = TRUE;
		if(i==12 && flags[i])m_case13 = TRUE;
		if(i==13 && flags[i])m_case14 = TRUE;
		if(i==14 && flags[i])m_case15 = TRUE;
		if(i==15 && flags[i])m_case16 = TRUE;
		if(i==17 && flags[i])m_case17 = TRUE;
		if(i==18 && flags[i])m_case18 = TRUE;
		if(i==19 && flags[i])m_case19 = TRUE;

		if(i==20 && flags[i])m_case3M = TRUE;
		if(i==21 && flags[i])m_case4M = TRUE;
		if(i==22 && flags[i])m_case8M = TRUE;
		if(i==23 && flags[i])m_case11M = TRUE;

		if(i==24 && flags[i])m_case3C = TRUE;
		if(i==25 && flags[i])m_case8C = TRUE;
		if(i==26 && flags[i])m_case9C = TRUE;
		if(i==27 && flags[i])m_case11C = TRUE;
		if(i==28 && flags[i])m_case16C = TRUE;

		if(i==29 && flags[i])m_case13FCR = TRUE;
		if(i==30 && flags[i])m_case14FCR = TRUE;

	}
}

void CCalc::ClearCaseFlags()
{
	m_case1=FALSE;m_case2=FALSE;m_case3=FALSE;m_case4=FALSE;
	m_case5=FALSE;m_case8=FALSE;m_case9=FALSE;m_case10=FALSE;
	m_case11=FALSE;m_case12=FALSE;m_case13=FALSE;m_case14=FALSE;
	m_case15=FALSE;m_case16=FALSE;m_case17=FALSE;m_case18=FALSE;
	m_case19=FALSE;m_case20=FALSE;m_case21=FALSE;m_case22=FALSE;
	ClearMargCaseFlags();
	ClearCellCaseFlags();
	ClearFreqCaseFlags();
}

void CCalc::ClearMargCaseFlags()
{
	m_case3M = FALSE;
	m_case4M = FALSE;
	m_case8M = FALSE;
	m_case11M = FALSE;
}

void CCalc::ClearCellCaseFlags()
{
	m_case3C = FALSE;
	m_case8C = FALSE;
	m_case9C = FALSE;
	m_case11C = FALSE;
	m_case16C = FALSE;
}

void CCalc::ApplyMargCaseFlags()
{
	if(m_case2M)m_case2 = TRUE;
	if(m_case3M)m_case3 = TRUE;
	if(m_case4M)m_case4 = TRUE;
	if(m_case8M)m_case8 = TRUE;
	if(m_case11M)m_case11 = TRUE;
}

void CCalc::ApplyCellCaseFlags()
{
	if(m_case3C)m_case3 = TRUE;
	if(m_case8C)m_case8 = TRUE;
	if(m_case9C)m_case9 = TRUE;
	if(m_case11C)m_case11 = TRUE;
	if(m_case16C)m_case16 = TRUE;
}

void CCalc::ApplyFreqCaseFlags()
{
	if(m_case13FCR)m_case13 = TRUE;
	if(m_case14FCR)m_case14 = TRUE;
}

void CCalc::ClearFreqCaseFlags()
{
	m_case13FCR = FALSE;
	m_case14FCR = FALSE;
}

void CCalc::LegitimizeCurrentFlags()
{
	CRegAspect* line;

	int i;
	for(i=0;i<RGSZ;i++)
	{
		line = m_reg[i];
		if(line->m_minSetCur)
		{
			line->m_minSet = TRUE;
			line->m_minSetCur = FALSE;
		}
		if(line->m_maxSetCur)
		{
			line->m_maxSet = TRUE;
			line->m_maxSetCur = FALSE;
		}
	}
}
/////////////////////////////////////////////////////////////////

double CCalc::DivideF(double dividend, double divisor)
{
	ASSERT(divisor!=0);
	UINT quotient = 0;
	if(dividend > divisor)
	{
		for( ;dividend>=divisor; )
		{
			dividend = dividend - divisor;
			quotient++;
		}
		m_rem = dividend;
	}
	if( dividend < divisor)
	{
		//divide by 1 to  x power to reduce size of divisor
	}
		return quotient;
}

/////////////////////////////////////////////////////////////////////
//Higher-Level Functions

//Port of entry for count,range,frequency
BOOL CCalc::HandleHighLevelRequest(int index)
{
	BOOL outCome = FALSE;
	BOOL startClrLock,endClrLock,kingIncrs=TRUE;
	BOOL fLock,cLock;
	BOOL reqModified = FALSE;
	BOOL requestCompromised = FALSE;
	int countID,startID,endID,freqID,rangeID;
	int whoIsKing = 0;
	UINT iRequestVal,range,count,botColor,topColor;
	UINT iRequestValTop,iRequestValBot;
	double dRequestVal,freq;
	CRegAspect* line;

	line = m_reg[index];
	iRequestVal = line->m_origReqCount;
	dRequestVal = line->m_origReqSize;

	if(index==5 || index==27 || index==28 || index==23)
		{countID=5;startID=27;endID=28;freqID=23;}
	if(index==12 || index==29 || index==30 || index==24)
		{countID=12;startID=29;endID=30;freqID=24;}
	if(index==13 || index==31 || index==32 || index==25)
		{countID=13;startID=31;endID=32;freqID=25;}
	if(index==14 || index==33 || index==34 || index==26)
		{countID=14;startID=33;endID=34;freqID=26;}
	rangeID = startID;

	whoIsKing = 1;
	if(countID==index)whoIsKing = 2;
	if(freqID==index)whoIsKing = 3;

	line = m_reg[countID];
	count = line->m_nNuCount;
	cLock = line->m_locked;
	if(line->m_instigating && line->m_applied)cLock = TRUE;

	line = m_reg[startID];
	startClrLock = line->m_locked;
	if(line->m_instigating && line->m_applied)startClrLock = TRUE;
	botColor = line->m_nNuCount;

	line = m_reg[endID];
	endClrLock = line->m_locked;
	if(line->m_instigating && line->m_applied)endClrLock = TRUE;
	topColor = line->m_nNuCount;

	if(topColor>=botColor)range = topColor - botColor;
	else range = botColor - topColor;

	line = m_reg[freqID];
	freq = line->m_nNuSize;
	fLock = line->m_locked;
	if(line->m_instigating && line->m_applied)fLock = TRUE;

	if(index==startID || index==endID)
	{
		UINT nuRange,origRange;
		CRegAspect * sLine,*eLine;
		sLine = m_reg[startID];
		eLine = m_reg[endID];
		UINT startVal=botColor,endVal=topColor;
		UINT origStartVal=botColor,origEndVal=topColor;
		if(sLine->m_instigating)startVal = sLine->m_origReqCount;
		if(eLine->m_instigating)endVal = eLine->m_origReqCount;
		if(startVal>=endVal)nuRange = startVal - endVal;
		else nuRange = endVal - startVal;
		if(origStartVal>=origEndVal)origRange = origStartVal - 
			origEndVal;
		else origRange = origEndVal - origStartVal;
		if(origRange>=nuRange)kingIncrs = TRUE;
		else kingIncrs = FALSE;
		iRequestVal = nuRange;
		iRequestValTop = endVal;
		iRequestValBot = startVal;
		range = origRange;
	}

	CProgressMgr * mgr = new CProgressMgr();
	mgr->InitializeProgressMgr(index,dRequestVal,iRequestVal,range,
					count,freq,botColor,topColor,startClrLock,endClrLock);
	mgr->LoadCountID(countID);
	mgr->LoadRangeID(startID,endID);
	mgr->LoadFreqID(freqID);

	CProgressBar* progBar;
	progBar = new CProgressBar();
	progBar->Create(IDD_MY_STATUS_BAR,NULL);
	progBar->ShowWindow(SW_SHOW);
	//progBar->UpdateProgressBar();
	
	mgr->RegisterFrequencyLock(fLock);

	kingIncrs = mgr->DoesTheKingRequestAnIncrease();

	CCellCount * c = new CCellCount();
	c->InitializeCellCount(count,iRequestVal,whoIsKing,kingIncrs,cLock);

	CColorRange * r = new CColorRange();
	r->InitializeColorRange(range,iRequestValBot,iRequestValTop,whoIsKing,
		kingIncrs,botColor,topColor,startClrLock,endClrLock,mgr);
	
	CFrequency * f = new CFrequency();
	f->InitializeFrequency(freq,dRequestVal,whoIsKing,kingIncrs,fLock);

	UINT nuCount,nuRange;
	double nuFreq;
	if(mgr->IsKingCount())nuCount = c->GetPheasibleCount(index,mgr);
	if(mgr->IsKingRange())nuRange = r->GetPheasibleRange(index,mgr);
	if(mgr->IsKingFrequency())nuFreq = 
		f->GetPheasibleFrequency(index,mgr);

	if(mgr->GetFlags()!=0)reqModified = TRUE;

	InitializeProgressBar(mgr,progBar);

	BOOL qSubmit=FALSE;//not merely the mobility of Queen but the alignment of 
					   //the three royals
	BOOL contin=TRUE,consensus=FALSE;
	BOOL royalValuesAreStale = FALSE;
	for( ;consensus==FALSE; )
	{
		BOOL kingIsCount = mgr->IsKingCount();
		if(kingIsCount)
		{
			qSubmit = GetComplianceFromQueen(mgr,r,c,f,progBar);
			if(!qSubmit)
			{
				r->ResetRange(mgr);
				f->ResetFrequency(mgr);
				contin = c->RelaxKingCountRequest(mgr);	
				requestCompromised = TRUE;
				mgr->IsQueenExhausted();//only to reset
			}				
			else
			{
				consensus = AchieveCountChange(index,
								(unsigned long)mgr->GetCount());
				if(!consensus)
				{
					if(mgr->IsQueenExhausted())
					{
						r->ResetRange(mgr);
						f->ResetFrequency(mgr);
						contin = c->RelaxKingCountRequest(mgr);
						//if(contin)mgr->ResetQueenJackValues();
					}
					else mgr->m_queensMailBox->DepositMessage(POST_COUNT_DENIAL);
				}
			}
		}
		else 
		{
			qSubmit = GetComplianceFromQueen(mgr,r,c,f,progBar);
			if(qSubmit)
			{
				if(mgr->IsQueenExhausted())//ie,range==0 || count==0
				{	
					mgr->RestoreOriginalValues();	
					requestCompromised = TRUE;
					break;	
				}
				else consensus = TRUE;
			}
			else
			{
				mgr->NotifyOfConcern(QUEEN_FAILURE);
				mgr->DetermineNatureOfProblem();
				if(mgr->IsKingRange())
				{
					c->ResetCount(mgr);
					f->ResetFrequency(mgr);
					contin = r->RelaxKingRangeRequest(mgr);
				}
				if(mgr->IsKingFrequency())
				{
					c->ResetCount(mgr);
					r->ResetRange(mgr);
					contin = f->RelaxKingFrequencyRequest(mgr);
				}
				if(contin)requestCompromised = TRUE;
			}
		}
		if(!contin)break;
	}

	delete progBar;

	int ans = 0;
	if(requestCompromised || reqModified || !consensus)
	{
		unsigned long flags = mgr->GetFlags();
		if(flags==(flags | 1))m_case2 = TRUE;
		if(flags==(flags | 2))m_case12 = TRUE;
		if(flags==(flags | 4))m_case13 = TRUE;
		if(flags==(flags | 8))m_case14 = TRUE;
		if(flags==(flags | 16))m_case15 = TRUE;
		if(flags==(flags | 32))m_case17 = TRUE;
		if(flags==(flags | 64))m_case18 = TRUE;
		if(flags==(flags | 128))m_case19 = TRUE;
		if(flags==(flags | 256))m_case20 = TRUE;
		if(flags==(flags | 512))m_case22 = TRUE;

		if(m_flagReporting)
		{
			
			CMessDlg dlg;
			dlg.str = GetAdvisoryStrings();
			if(dlg.DoModal()==IDOK)
			{
				if(dlg.m_yes)ans = 1;
				if(dlg.m_no)ans = 2;
			}
		}
		if(!m_flagReporting)
		{
			ans = 1;
			outCome = TRUE;
		}
		if(ans==0)//clean up reg stop processing -- "CANCEL"
		{
			outCome = FALSE;
			m_instigatorCount = 0;
			RestoreAtStartComputeSettings();
		}
		//accept max change & continue processing -- "YES"
		if(ans==1)
		{
			outCome = TRUE;
		}
		//forgo this change continue processing -- "NO"
		if(ans==2)
		{
			m_noAccept = TRUE;
			outCome = FALSE;
		}

	}
	else outCome = TRUE;

	if(outCome)
	{
		line = m_reg[countID];
		line->m_nNuCount = (unsigned long)mgr->GetCount();
		line->m_alt = TRUE;
		if(countID==13)m_blockCount = line->m_nNuCount;
		if(countID==14)m_cBlockCount = line->m_nNuCount;
		if(countID==5)m_colsPer = line->m_nNuCount;
		if(countID==12)m_rowsPer = line->m_nNuCount;
		m_totalCells = m_cBlockCount * m_blockCount * m_colsPer *
			m_rowsPer;
		line = m_reg[freqID];
		line->m_nNuSize = (float)mgr->GetFrequency();
		line->m_alt = TRUE;
		line = m_reg[startID];
		line->m_nNuCount = (unsigned long)mgr->GetStartColor();
		line->m_alt = TRUE;
		if(startID==27)m_rowFrom = line->m_nNuCount;
		if(startID==29)m_colFrom = line->m_nNuCount;
		if(startID==31)m_blockFrom = line->m_nNuCount;
		if(startID==33)m_cBlockFrom = line->m_nNuCount;
		line = m_reg[endID];
		line->m_nNuCount = (unsigned long)mgr->GetEndColor();
		line->m_alt = TRUE;
		if(endID==28)m_rowTo = line->m_nNuCount;
		if(endID==30)m_colTo = line->m_nNuCount;
		if(endID==32)m_blockTo = line->m_nNuCount;
		if(endID==34)m_cBlockTo = line->m_nNuCount;
	}
	else
	{	
	}
	ClearCaseFlags();
	delete mgr;
	delete c;
	delete r;
	delete f;


	return outCome;
}

//preserves or modifies two other aspects
BOOL CCalc::GetComplianceFromQueen(CProgressMgr * mgr,CColorRange * r,
								   CCellCount * c,CFrequency * f,CDialog* progDlg)
{
	unsigned long outsideLoopVal = 0;
	unsigned long insideLoopVal = 0;
	CProgressBar* progBar  = (CProgressBar*)progDlg;
	BOOL outCome=FALSE;
	BOOL jSubmit=FALSE;
	BOOL contin=TRUE;
	BOOL queenIsCount = mgr->IsQueenCount();
	//to determine unwanted modifications	
	for( ;outCome==FALSE; )
	{
		jSubmit = GetComplianceFromJack(mgr,r,c,f);
		if(queenIsCount)
		{
			if(jSubmit)outCome = AchieveCountChange(mgr->GetQueenID(),
									(unsigned long)mgr->GetCount());
			if(!outCome)contin = c->ModifyQueenCount(mgr);
		}
		else
		{
			BOOL keepPosted = FALSE;
			if(!jSubmit)keepPosted = TRUE;
			if(!jSubmit || mgr->m_queensMailBox->CheckMessageBox(POST_COUNT_DENIAL,keepPosted))
			{
				if(mgr->IsQueenRange())contin = r->ModifyQueenRange(mgr);
				if(mgr->IsQueenFrequency())//not implemented
					contin = f->ModifyQueenFrequency(mgr);	
			}
			else outCome = TRUE;
		}
		outsideLoopVal = mgr->GetKingsProgress();
		insideLoopVal = mgr->GetQueensProgress();
		progBar->UpdateProgressBar(outsideLoopVal,insideLoopVal);	
		if(!contin)break;		
	}

	return outCome;
}

BOOL CCalc::GetComplianceFromJack(CProgressMgr * mgr,CColorRange* range,
								  CCellCount * count,CFrequency * freq)
{
	BOOL outCome = FALSE;
	BOOL consensus = FALSE;
	BOOL finalize = FALSE;
	BOOL consensusRealized = FALSE;
	outCome = mgr->AssessNewValues();
	if(!outCome)
	{
		if(mgr->IsJackRange())consensus = range->AdjustJackRange(mgr);
		if(mgr->IsJackCount())
		{
			consensus = count->AdjustJackCount(mgr);
			if(consensus)
			{
				finalize = AchieveCountChange(mgr->GetCountID(),
							(unsigned long)mgr->GetCount());
				consensusRealized = TRUE;
			}
			if(!finalize)consensus = FALSE;
		}
		if(mgr->IsJackFrequency())consensus = freq->AdjustJackFrequency(mgr);
	}
	if(mgr->IsJackCount())
	{
		if(!consensus && !consensusRealized)
			mgr->NotifyOfConcern(JACK_COUNT_IN_HOUSE_FAILURE);
	}
	if(consensus)outCome = TRUE;

	return outCome;
}

void CCalc::InitializeProgressBar(CProgressMgr* pMgr, CDialog* pDlg)
{
	unsigned long outsideLoopVal = 0;
	unsigned long insideLoopVal = 0;

	CProgressBar* progBar  = (CProgressBar*)pDlg;
	outsideLoopVal = pMgr->GetKingsJourneyLeft();
	insideLoopVal = pMgr->GetQueensJourneyLeft();
	progBar->InitializeProgressBar(outsideLoopVal,insideLoopVal);	
}


BOOL CCalc::AchieveCountChange(int index,unsigned long nuCount)
{
	BOOL doable = FALSE;

	CRegistrar* regis = new CRegistrar();
	CMaestro* maestro = new CMaestro();
	CBellows* bellows = new CBellows();
	CToggleManager axisToggler;
	CToggleManager requestToggler;
	CRegAspect* line;

	UINT cols,rows;
	UINT * pCols = &cols;
	UINT * pRows = &rows;

	//set up objects
	regis->InitializeRegistry(index,nuCount,m_colorMode,pCols,pRows,bellows);
	LoadCountChangeRegistryValues(regis);
	maestro->InitializeMaestro(regis);
	bellows->SetUpManipulations(maestro);
	int togInterval = 2,togOffset = 0,stagger = 16,staggerOffset = 0;
	axisToggler.SetUpForAutoTracking(togInterval,togOffset,stagger,staggerOffset);
	togInterval = 1;
	togOffset = 0;
	stagger = 8;
	staggerOffset = 6;
	requestToggler.SetUpForAutoTracking(togInterval,togOffset,stagger,staggerOffset);

	//store flags going in
	int sz = FLGSTORESZ;
	BOOL flags [FLGSTORESZ];
	StoreRestoreCurrentFlags(TRUE,flags,sz);

	//take snapshot of m_reg and other CCalc variables
	CRegAspect * lines[27];
	CRegAspect * origRegBuf[27];
	int n;
	for(n=0;n<27;n++)
	{
		CRegAspect * l = m_reg[n];
		CRegAspect * lcopy = new CRegAspect();
		CRegAspect * lcopyBuf = new CRegAspect();
		lines[n] = lcopy;
		lcopy->m_nNuSize = l->m_nNuSize;
		lcopy->m_nNuCount = l->m_nNuCount;
		lcopy->m_origReqSize = l->m_origReqSize;
		lcopy->m_origReqCount = l->m_origReqCount;
		lcopy->m_minSetCur = l->m_minSetCur;
		lcopy->m_maxSetCur = l->m_maxSetCur;
		lcopy->m_minSet = l->m_minSet;
		lcopy->m_maxSet = l->m_maxSet;
		lcopy->m_alt = l->m_alt;
		lcopy->m_instigating = l->m_instigating;
		lcopy->m_applied = l->m_applied;
		origRegBuf[n] = lcopyBuf;
		lcopyBuf->m_nNuSize = l->m_nNuSize;
		lcopyBuf->m_nNuCount = l->m_nNuCount;
		lcopyBuf->m_origReqSize = l->m_origReqSize;
		lcopyBuf->m_origReqCount = l->m_origReqCount;
		lcopyBuf->m_minSetCur = l->m_minSetCur;
		lcopyBuf->m_maxSetCur = l->m_maxSetCur;
		lcopyBuf->m_minSet = l->m_minSet;
		lcopyBuf->m_maxSet = l->m_maxSet;
		lcopyBuf->m_alt = l->m_alt;
		lcopyBuf->m_instigating = l->m_instigating;
		lcopyBuf->m_applied = l->m_applied;
	}

	m_flagReporting = FALSE;
	BOOL chartModified = FALSE;
	BOOL exit = FALSE;

	for(;exit==FALSE;)
	{
		chartModified = FALSE;
		if(requestToggler.Report(0))maestro->ToggleRequestSize();
		if(axisToggler.Report(0))
		{
			maestro->ToggleAxisConcerns();
			//ClearCaseFlags();
		}
		chartModified = bellows->ExploreChartAspectResize();
		StoreOrRemoveNewRegValues(lines,TRUE);
		doable = maestro->TestForAnsweredRequest();//affects return of 
												//maestro->StoreValues()
		//diagnostic code
		line = m_reg[7];
		double cellH = line->m_nNuSize;
		line = m_reg[0];
		double cellW = line->m_nNuSize;
		//if(cellW != cellH)
		if(regis->GetCurrentRowCount()==22)
		//if(doable)
		{
			BOOL stop = TRUE;
		}

		exit = doable;
		//clean up request specific flags and restore original flags
		StoreOrRemoveNewRegValues(lines,maestro->StoreValues());
		if(maestro->GetFailureCount()>=32)exit = TRUE;
	}
		//reset m_reg object && pertinant variables
	m_flagReporting = TRUE;
	//restore initial flags
	//StoreRestoreCurrentFlags(FALSE,flags,sz);
	AddOriginalFlags(flags,sz);

	if(doable)
	{
		BOOL colChange = FALSE;
		BOOL rowChange = FALSE;
		line = m_reg[regis->GetColumnID()];
		if(cols!=line->m_nNuCount)colChange = TRUE;
		if(colChange)
		{
			cols = regis->GetCurrentColumnCount();
			line->m_alt = TRUE;
			line->m_nNuCount = cols;
		}
		if(index==13)m_bColsPer = cols; 
		if(index==14)m_cBColsPer = cols;

		line = m_reg[regis->GetRowID()];
		if(rows!=line->m_nNuCount)rowChange = TRUE;
		if(rowChange)
		{
			rows = regis->GetCurrentRowCount();
			line->m_alt = TRUE;
			line->m_nNuCount = rows;
		}
	}
	else StoreOrRemoveNewRegValues(origRegBuf,FALSE);

	for(n=0;n<27;n++)
	{
		delete lines[n];
		delete origRegBuf[n];
	}

	regis->DestroyRegistry();
	maestro->DestroyMaestro();
	bellows->DestroyBellows();

	return doable;
}

void CCalc::LoadCountChangeRegistryValues(CRegistrar * regis)
{
	CRegAspect * colLine = m_reg[regis->GetColumnID()];
	regis->SetColumnInfo(colLine);
	CRegAspect * rowLine = m_reg[regis->GetRowID()];
	regis->SetRowInfo(rowLine);
	CRegAspect * reqLine = m_reg[regis->GetRequestIndex()];
	regis->SetRequestInfo(reqLine);

	regis->SetTotalPages(m_totalPages);
}