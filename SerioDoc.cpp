// SerioDoc.cpp : implementation of the CSerioDoc class
//

#include "stdafx.h"
#include "ProtoColor.h"

#include "SerioDoc.h"

#include "ViewControlDlg.h"
#include "BlockLayoutDlg.h"
#include "CBlockLayoutDlg.h"
#include "ColorFormDlg.h"
#include "QuickLayout.h"
#include "CellAspectsDlg.h"
#include "OrientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RGSZ 35
#define VIEW_DLG_REFUSE_FOCUS 2222

////////////////////////////////////////////////////////////////////
// CSerioDoc

IMPLEMENT_DYNCREATE(CSerioDoc, CDocument)

BEGIN_MESSAGE_MAP(CSerioDoc, CDocument)
	//{{AFX_MSG_MAP(CSerioDoc)
	ON_COMMAND(ID_COLOR_SPEC, OnSpecifyColor)
	ON_COMMAND(ID_CELL_SPECS, OnCellSpecs)
	ON_COMMAND(ID_SPECIFY_ORIENT, OnSpecifyOrient)
	ON_COMMAND(ID_LAYOUT, OnQuickLayout)
	ON_COMMAND(ID_C_BLOCK_LAYOUT, OnCBlockLayout)
	ON_COMMAND(ID_BLOCK_LAYOUT, OnBlockLayout)
	ON_COMMAND(ID_CMYK_BUTTON, OnCMYKButton)
	ON_COMMAND(ID_CMY_BUTTON, OnCMYButton)
	ON_COMMAND(ID_RGB_BUTTON, OnRGBButton)
	ON_COMMAND(ID_VIEW_PAGEFINDER, OnViewPagefinder)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PAGEFINDER, OnUpdateViewPagefinder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//removed from messagemap:
//	ON_COMMAND(ID_HELP, OnHelp)
//	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)


/////////////////////////////////////////////////////////////////////
// CSerioDoc construction/destruction

CSerioDoc::CSerioDoc()
{
	m_dMouldy = TRUE;	//controls whether the view re-loads coords
	m_auto = FALSE;		//toggles check - Highly Automated menu item
	m_user = TRUE;		//toggles check - Full User Control menu item
	m_viewDlgOn = FALSE; //enables ViewDialog menu item
	m_dCalledByDlg = FALSE;
	m_dDlgInProcess = FALSE;
	m_dCalcIntent = 0;
	m_dViewDlgCloseIsSimulated = FALSE;
	m_willBeActive = TRUE;
	m_preventViewDlgFocus = FALSE;
	m_dProcessingMouseActivate = FALSE;
	m_viewDlg = NULL;
	m_dFormatDlgChangedView = FALSE;
}

CSerioDoc::~CSerioDoc()
{
	//need to delete allocated  object in m_reg ::scratchPad.
}

extern CCalc scratchPad;

BOOL CSerioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_dViewDlgRect.left = 15;
	m_dViewDlgRect.top = 115;
	m_dViewDlgRect.right = 110;//width
	m_dViewDlgRect.bottom = 54;
	TidyUpPreviousDoc();
	CAspects* pAspects;
	m_dasp = initDims(); //Loads float defaults to new CAspect object
	pAspects = m_dasp;					//should be called only if it is a new document

	initStrings();		//Loads all dialog CString values if New document
	initInts();			//Loads all dialog Int values if New document
	initBOOLs();		//Loads all flags if New Document
	
	initDoc(pAspects);		//Loads dialogs from either serialized or 
							//new objects
	
	initCells();	//Loads defaults from m_cellList

	if(::scratchPad.m_firstInit)
	{
		try
		{
			RegisterAspects();
			::scratchPad.LoadCalcMembers();
		}
		catch(...)
		{
			//no active frame will be corrected in
			//CChildFrame::ActivateFrame()
		}
	}
	//else ::scratchPad.m_firstInit = TRUE;

	// (SDI documents will reuse this document)
	return TRUE;
}

void CSerioDoc::TidyUpPreviousDoc()
{
	CSerioApp* pApp = (CSerioApp*) AfxGetApp();
	POSITION pos = pApp->m_pDocTemplate->GetFirstDocPosition();
	CSerioDoc* pDoc;
	int i;
	for(i=0;i<1000;i++)
	{
		pDoc = 
			(CSerioDoc*)pApp->m_pDocTemplate->GetNextDoc(pos);
		if(pDoc->m_viewDlgOn)
		{
			if(!pDoc->m_dViewDlgCloseIsSimulated)
			{
				pDoc->SimulateCloseViewDlg();
			}
		}
		if(pos==NULL)break;
	}
}

////////////////////////////////////////////////////////////////////
// CSerioDoc serialization

void CSerioDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		if(!scratchPad.m_registered)
		{
			if(scratchPad.m_freeFiles>9)
			{
				AfxMessageBox("THE SAVE & SAVE AS FUNCTIONALITY HAS BEEN DISABLED.  To save more chart configurations, you can fully enable ProtoColor by purchasing an authorization code!  See User's.doc for more information.");
				return;
			}
			else
			{
				scratchPad.m_freeFiles++;
				CWinApp* app = AfxGetApp();
				app->WriteProfileInt("ProtoColor1.0", "testFiles",scratchPad.m_freeFiles);
			}
		}

		//if(!scratchPad.m_registered && scratchPad.m_freeFiles>10)
		//{
		//	AfxMessageBox("To save more chart configurations, you can fully enable ProtoColor by purchasing an authorization code!  See User's.doc for more information.");
		//	return;
		//}

		ar << m_dBitDepth;
		ar << m_dBlockCols;
		ar << m_dBlockCount;
		ar << m_dBlockHeight;
		ar << m_dBlockRows;
		ar << m_dBlockWidth;
		ar << m_dCBlockCols;
		ar << m_dCBlockRows;
		ar << m_dCBlockCount;
		ar << m_dCellCount;
		ar << m_dCellHeight;
		ar << m_dCellRatio;
		ar << m_dCellWidth;
		ar << m_dCglomBlockHeight;
		ar << m_dCglomBlockWidth;
		ar << m_dColCount;
		ar << m_dColorMode;
		ar << m_dColRowCount;
		ar << m_dConstrMode;
		ar << m_dDerivePCnt;
		ar << m_dDerivePCnt;
		ar << m_dEF2B;
		ar << m_dEF2L;
		ar << m_dEL2R;
		ar << m_dEndRange;
		ar << m_dET2B;
		ar << m_dFBlock;
		ar << m_dFCBlock;
		ar << m_dFCol;
		ar << m_dFRow;
		ar << m_dIsSquare;
		ar << m_dLeftMarg;
		ar << m_dLowerMarg;
		ar << m_dMargRat;
		ar << m_dModeContext;
		ar << m_dNext;
		ar << m_dOrientation_0;
		ar << m_dOrientation_1;
		ar << m_dOrientation_2;
		ar << m_dOutlineClr;
		ar << m_dPageCount;
		ar << m_dPageHeight;
		ar << m_dPageWidth;
		ar << m_dPalette;
		ar << m_dPosEd;
		ar << m_dRightMarg;
		ar << m_dRowCount;
		ar << m_dSF2B;
		ar << m_dSF2L;
		ar << m_dSL2R;
		ar << m_dST2B;
		ar << m_dStartRange;
		ar << m_dStepFreq;
		ar << m_dUnitMeas;
		ar << m_dUpperMarg;
		ar << m_dVirtualPageHeight;
		ar << m_dVirtualPageWidth;
		ar << m_nCurMode;

		ar << m_userLineBrkPerCol;
		ar << m_userLineBrkPerRow;
		ar << m_userLineBrkPerBlk;
		ar << m_userLineBrkPerCBlk;
		ar << m_dCurPage;
		ar << m_dShowPage;
		ar << m_dDerivePCnt;
		ar << m_dIsSquare;
		ar << m_dCellRatio;
		ar << m_sizeDoc;

		m_flags.Serialize(ar);
		m_strArray.Serialize(ar);
		m_cellList.Serialize(ar);
	}
	else
	{
		ar >> m_dBitDepth;
		ar >> m_dBlockCols;
		ar >> m_dBlockCount;
		ar >> m_dBlockHeight;
		ar >> m_dBlockRows;
		ar >> m_dBlockWidth;
		ar >> m_dCBlockCols;
		ar >> m_dCBlockRows;
		ar >> m_dCBlockCount;
		ar >> m_dCellCount;
		ar >> m_dCellHeight;
		ar >> m_dCellRatio;
		ar >> m_dCellWidth;
		ar >> m_dCglomBlockHeight;
		ar >> m_dCglomBlockWidth;
		ar >> m_dColCount;
		ar >> m_dColorMode;
		ar >> m_dColRowCount;
		ar >> m_dConstrMode;
		ar >> m_dDerivePCnt;
		ar >> m_dDerivePCnt;
		ar >> m_dEF2B;
		ar >> m_dEF2L;
		ar >> m_dEL2R;
		ar >> m_dEndRange;
		ar >> m_dET2B;
		ar >> m_dFBlock;
		ar >> m_dFCBlock;
		ar >> m_dFCol;
		ar >> m_dFRow;
		ar >> m_dIsSquare;
		ar >> m_dLeftMarg;
		ar >> m_dLowerMarg;
		ar >> m_dMargRat;
		ar >> m_dModeContext;
		ar >> m_dNext;
		ar >> m_dOrientation_0;
		ar >> m_dOrientation_1;
		ar >> m_dOrientation_2;
		ar >> m_dOutlineClr;
		ar >> m_dPageCount;
		ar >> m_dPageHeight;
		ar >> m_dPageWidth;
		ar >> m_dPalette;
		ar >> m_dPosEd;
		ar >> m_dRightMarg;
		ar >> m_dRowCount;
		ar >> m_dSF2B;
		ar >> m_dSF2L;
		ar >> m_dSL2R;
		ar >> m_dST2B;
		ar >> m_dStartRange;
		ar >> m_dStepFreq;
		ar >> m_dUnitMeas;
		ar >> m_dUpperMarg;
		ar >> m_dVirtualPageHeight;
		ar >> m_dVirtualPageWidth;
		ar >> m_nCurMode;

		ar >> m_userLineBrkPerCol;
		ar >> m_userLineBrkPerRow;
		ar >> m_userLineBrkPerBlk;
		ar >> m_userLineBrkPerCBlk;
		ar >> m_dCurPage;
		ar >> m_dShowPage;
		ar >> m_dDerivePCnt;
		ar >> m_dIsSquare;
		ar >> m_dCellRatio;
		ar >> m_sizeDoc;
	
		m_flags.SetSize(65,10);
		m_flags.Serialize(ar);

		m_strArray.Serialize(ar);

		m_cellList.Serialize(ar);

	}

}

///////////////////////////////////////////////////////////////////////
// CSerioDoc diagnostics

#ifdef _DEBUG
void CSerioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSerioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////////
// CSerioDoc commands

void CSerioDoc::initDoc(CAspects* pasp)
{

	int size;
	m_dBitDepth = m_strArray[2];
	m_dPalette = m_strArray[6];
	m_dUnitMeas = m_strArray[7];

	m_dConstrMode = m_strArray[13];
	m_dModeContext = m_strArray[15];
	

	size = pasp->m_asp.GetSize();
	
	m_dPageWidth = pasp->m_asp[size-16];
	m_dPageHeight = pasp->m_asp[size-15];
	m_dLeftMarg = pasp->m_asp[size-14];
	m_dLowerMarg = pasp->m_asp[size-13];
	m_dRightMarg = pasp->m_asp[size-12];
	m_dUpperMarg = pasp->m_asp[size-11];
	m_dCellWidth = pasp->m_asp[size-10];
	m_dCellHeight = pasp->m_asp[size-9];
	m_dBlockWidth = pasp->m_asp[size-8];
	m_dBlockHeight = pasp->m_asp[size-7];
	m_dCglomBlockWidth = pasp->m_asp[size-6];
	m_dCglomBlockHeight = pasp->m_asp[size-5];
	m_dFRow = pasp->m_asp[size-4];
	m_dFCol = pasp->m_asp[size-3];
	m_dFBlock = pasp->m_asp[size-2];
	m_dFCBlock = pasp->m_asp[size-1];




}

//////////////////////////////////////////////////////////////
// CCell

IMPLEMENT_SERIAL(CCell,CObject,1)
CCell::CCell()
{

}


BOOL CCell::DrawCell(CDC* pDC)
{/*
	int x1 , y1 , x2 , y2;

	CPen penGreen;
	if(penGreen.CreatePen(PS_SOLID, 1,RGB(0,0,0)))
	{
		CPen* pOldPen = 
			pDC->SelectObject(&penGreen);

		x1 = m_rect[0]; y1 = m_rect[1]; 
		x2 = m_rect[2]; y2 = m_rect[3];

		pDC->Rectangle(x1,y1,x2,y2);
		pDC->SelectObject(pOldPen);
	}*/
	return TRUE;
}
//////////////////////////////////////////////////////////
// CAspects

IMPLEMENT_SERIAL(CAspects,CObject,1)
CAspects::CAspects()
{

}

void CAspects::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
	}
	else
	{
	}
	m_asp.Serialize(ar);
}


////////////////////////////////////////////////////////
// Dialogs

void CSerioDoc::OnSpecifyColor() 
{
	BOOL update = FALSE;
	m_dDlgInProcess = TRUE;
	// Call the CColorFormDlg object
	CColorFormDlg dlg;
	//Initialize data
	m_dNext = FALSE;
//	dlg.m_nBitDepth = m_dBitDepth;
//	dlg.m_nPalette = m_dPalette;
	dlg.m_nColorMode = m_dColorMode;
	dlg.m_nMaxSteps = m_strArray[10];
	dlg.m_nOutLineClr = m_strArray[m_dOutlineClr];	//31 - 34
	dlg.m_calcIntent = m_dCalcIntent;
	//dlg.m_StepBas = m_flags[22];
	dlg.m_StartL2R = m_dSL2R;
	dlg.m_StartT2B = m_dST2B;
	dlg.m_StartF2L = m_dSF2L;
	dlg.m_StartF2B = m_dSF2B;
	dlg.m_EndL2R = m_dEL2R;
	dlg.m_EndT2B = m_dET2B;
	dlg.m_EndF2L = m_dEF2L;
	dlg.m_EndF2B = m_dEF2B;
	dlg.m_TogLock = m_flags[38];
	dlg.m_TogLock2 = m_flags[39];
	dlg.m_TogLock3 = m_flags[40];
	dlg.m_TogLock4 = m_flags[41];
	dlg.m_TogLock5 = m_flags[42];
	dlg.m_TogLock6 = m_flags[43];
	dlg.m_TogLock7 = m_flags[44];
	dlg.m_TogLock8 = m_flags[45];
	//Invoke the dlg box
	if (dlg.DoModal()== IDOK)
	{
		//catch color mode change
		BOOL colorChange = FALSE; 
		int cWas;
		if(m_dColorMode!=dlg.m_nColorMode)
		{
			colorChange = TRUE;
			cWas = m_dColorMode;
		}
		//retrieve the dialog data
//		m_dBitDepth = dlg.m_nBitDepth;
//		m_dPalette = dlg.m_nPalette;
		m_dCalcIntent = dlg.m_calcIntent;
		m_dColorMode = dlg.m_nColorMode;
		m_strArray[10] = dlg.m_nMaxSteps;
		if(dlg.m_nOutLineClr=="white")m_dOutlineClr = 31;
		if(dlg.m_nOutLineClr=="black")m_dOutlineClr = 32;
		if(dlg.m_nOutLineClr=="gray")m_dOutlineClr = 33;
		if(dlg.m_nOutLineClr=="same as cell")m_dOutlineClr = 34;
		//m_flags[22] = dlg.m_StepBas;
		m_dSL2R = dlg.m_StartL2R;
		m_dST2B = dlg.m_StartT2B;
		m_dSF2L = dlg.m_StartF2L;
		m_dSF2B = dlg.m_StartF2B;
		m_dEL2R = dlg.m_EndL2R;
		m_dET2B = dlg.m_EndT2B;
		m_dEF2L = dlg.m_EndF2L;
		m_dEF2B = dlg.m_EndF2B;
		if(dlg.m_autoLock)
		{
			dlg.m_TogLock = TRUE;
			dlg.m_TogLock2 = TRUE;
			dlg.m_TogLock3 = TRUE;
			dlg.m_TogLock4 = TRUE;
			dlg.m_TogLock5 = TRUE;
			dlg.m_TogLock6 = TRUE;
			dlg.m_TogLock7 = TRUE;
			dlg.m_TogLock8 = TRUE;

		}
		m_flags[38] = dlg.m_TogLock;
		m_flags[39] = dlg.m_TogLock2;
		m_flags[40] = dlg.m_TogLock3;
		m_flags[41] = dlg.m_TogLock4;
		m_flags[42] = dlg.m_TogLock5;
		m_flags[43] = dlg.m_TogLock6;
		m_flags[44] = dlg.m_TogLock7;
		m_flags[45] = dlg.m_TogLock8;

		InductNewValues();//from scratchPad to CSerioDoc

		m_dNext = dlg.m_next; //Call next dlg
		BOOL notConvert = TRUE;
		if(colorChange && m_dColorMode==1)
		{notConvert = FALSE;ConvertToCMYK(cWas);}
		if(colorChange && m_dColorMode==0)
		{notConvert = FALSE;ConvertToRGB(cWas);}
		if(colorChange && m_dColorMode==2) 
		{notConvert = FALSE;ConvertToCMY(cWas);}
		
		if(notConvert)update = TRUE;

		SetModifiedFlag();
	}
	RegisterAspects();
	::scratchPad.LoadCalcMembers();
	if(GetNextVal())CallDialog(2);
	if(update)UpdateAllViews(NULL);
	m_dDlgInProcess = FALSE;
}

	
void CSerioDoc::OnQuickLayout() 
{
	BOOL update = FALSE;
	m_dDlgInProcess = TRUE;
	// Call the Quick Layout Dlg box
	CQuickLayout dlg;
	//Initialize data

	m_dNext = FALSE;	//flag to jump to next dialog in PostNCDestroy()
	//::MgnResult = m_LDlgMultiple;	//Global for CClickStatc
	dlg.m_next = FALSE;
	dlg.m_MargRatResult = m_dMargRat;
	dlg.m_nPageWidth = m_dPageWidth;
	dlg.m_nPageHeight = m_dPageHeight;
	dlg.m_nUpperMarg = m_dUpperMarg;
	dlg.m_nLeftMarg = m_dLeftMarg;
	dlg.m_nLowerMarg = m_dLowerMarg;
	dlg.m_nRightMarg = m_dRightMarg;
	dlg.m_nUnits = m_dUnitMeas;
	dlg.m_nUnits1 = m_dUnitMeas;
	dlg.m_nUnits2 = m_dUnitMeas;
	dlg.m_nUnits3 = m_dUnitMeas;
	dlg.m_nUnits4 = m_dUnitMeas;
	dlg.m_nUnits5 = m_dUnitMeas;
	dlg.m_nPageCount = m_dPageCount;
	//dlg.m_nDerivePageCount = m_dDerivePCnt;
	dlg.m_nShowPage = m_dShowPage;
	dlg.m_TogLock = m_flags[46];
	dlg.m_TogLock2 = m_flags[47];
	dlg.m_TogLock3 = m_flags[48];
	dlg.m_TogLock4 = m_flags[49];
	dlg.m_TogLock5 = m_flags[50];
	dlg.m_TogLock6 = m_flags[51];
	dlg.m_TogLock7 = m_flags[52];


	//Invoke the dlg box
	if (dlg.DoModal()== IDOK)
	{
		//retrieve the dialog data
		m_dPageWidth = dlg.m_nPageWidth;
		m_dPageHeight = dlg.m_nPageHeight;
		m_dUpperMarg = dlg.m_nUpperMarg;
		m_dLeftMarg = dlg.m_nLeftMarg;
		m_dLowerMarg = dlg.m_nLowerMarg;
		m_dRightMarg = dlg.m_nRightMarg;
		m_dUnitMeas = dlg.m_nUnits;
		m_dUnitMeas = dlg.m_nUnits1;
		m_dUnitMeas = dlg.m_nUnits2;
		m_dUnitMeas = dlg.m_nUnits3;
		m_dUnitMeas = dlg.m_nUnits4;
		m_dUnitMeas = dlg.m_nUnits5;
		m_dPageCount = dlg.m_nPageCount;
		//m_dDerivePCnt = dlg.m_nDerivePageCount;
		m_dShowPage = dlg.m_nShowPage;
		m_dMargRat = dlg.m_MargRatResult;

		m_flags[46] = dlg.m_TogLock;
		m_flags[47] = dlg.m_TogLock2;
		m_flags[48] = dlg.m_TogLock3;
		m_flags[49] = dlg.m_TogLock4;
		m_flags[50] = dlg.m_TogLock5;
		m_flags[51] = dlg.m_TogLock6;
		m_flags[52] = dlg.m_TogLock7;
		m_dNext = dlg.m_next;
		
		InductNewValues();//from scratchPad to CSerioDoc
		if(m_dColorMode!=1)
		{
			m_dCglomBlockWidth = m_dVirtualPageWidth;
			m_dCglomBlockHeight = m_dVirtualPageHeight;
		}
		SetModifiedFlag();
		update = TRUE;
	}
	RegisterAspects();
	::scratchPad.LoadCalcMembers();
	
	if(GetNextVal())CallDialog(3);
	if(update)UpdateAllViews(NULL);
	m_dDlgInProcess = FALSE;
}

void CSerioDoc::OnCellSpecs() 
{	
	BOOL update = FALSE;
	BOOL cancel = TRUE;
	m_dDlgInProcess = TRUE;
	// Calls Cell Aspects DLG box
	CCellAspectsDlg* dlg = new CCellAspectsDlg();

	//test to see if we can pass in a pointer to the CAspects
	//CCellAspectsDlg* pdlg = &dlg;

	m_dNext = FALSE; //flag to direct to next dialog
	dlg->m_color = m_dColorMode;
//	dlg->m_pCCellAsp = pdlg;

	dlg->m_CellWidthVal = m_dCellWidth;
	dlg->m_CellHeightVal = m_dCellHeight;
	dlg->m_BlockWidthVal = m_dBlockWidth;
	dlg->m_BlockHeightVal = m_dBlockHeight;
	dlg->m_CBlockWidthVal = m_dCglomBlockWidth;
	dlg->m_CBlockHeightVal = m_dCglomBlockHeight;
	dlg->m_nUnits = m_dUnitMeas;//m_strArray[7];
	dlg->m_nUnits2 = m_dUnitMeas;//m_strArray[7];
	dlg->m_nUnits3 = m_dUnitMeas;//m_strArray[7];
	dlg->m_nUnits4 = m_dUnitMeas;//m_strArray[7];
	dlg->m_nUnits5 = m_dUnitMeas;//m_strArray[7];
	dlg->m_nUnits6 = m_dUnitMeas;//m_strArray[7];
	//dlg->m_nStartRange = m_dStartRange;
//	dlg->m_nEndRange = m_dEndRange;
//	dlg->m_nAbstractStepNum = m_strArray[11];
//	dlg->m_nPaintedStepFreq = m_dStepFreq;
//	dlg->m_nCellCount = m_dCellCount;
	dlg->m_nColCount = m_dColCount;
	dlg->m_nRowCount = m_dRowCount;
	dlg->m_nBlockCount = m_dBlockCount;
	dlg->m_nCBlockCount = m_dCBlockCount;
	//dlg->m_nDeriveCells = m_flags[23];
	dlg->m_Reflect = m_flags[24];
	//dlg->m_nIsSquare = m_dIsSquare;
	dlg->m_nCellRatio = m_dCellRatio;
	dlg->m_CnsRow = m_flags[25];
	dlg->m_CnsCol = m_flags[26];
	dlg->m_CnsBlock = m_flags[27];
	dlg->m_CnsCBlock = m_flags[28];
	dlg->m_IntSync = m_flags[29];
	//dlg->m_SyncAll = m_flags[37];
	//dlg->m_F_BLK = 
	dlg->m_F_ROW = m_dFRow;
	dlg->m_F_COL = m_dFCol;
	dlg->m_F_BLK = m_dFBlock;
	dlg->m_F_CBLK = m_dFCBlock;

//	dlg->m_TogLock = m_flags[53];
	dlg->m_TogLock2 = m_flags[54];//row lock
	dlg->m_TogLock3 = m_flags[55];//col lock
	dlg->m_TogLock4 = m_flags[56];//block lock
	dlg->m_TogLock5 = m_flags[57];//c-block lock
	dlg->m_TogLock6 = m_flags[58];
	dlg->m_TogLock7 = m_flags[59];
	dlg->m_TogLock8 = m_flags[60];
	dlg->m_TogLock9 = m_flags[61];
	dlg->m_TogLock10 = m_flags[62];
	dlg->m_TogLock11 = m_flags[63];

	if (dlg->DoModal()==IDOK)
	{
		cancel = FALSE;
		//retrieve the dialog data
		m_dCellWidth = dlg->m_CellWidthVal;
		m_dCellHeight = dlg->m_CellHeightVal;
		m_dBlockWidth = dlg->m_BlockWidthVal;
		m_dBlockHeight = dlg->m_BlockHeightVal;
		m_dCglomBlockWidth = dlg->m_CBlockWidthVal;
		m_dCglomBlockHeight = dlg->m_CBlockHeightVal;
		m_dUnitMeas = dlg->m_nUnits;
//		m_dCellCount = dlg->m_nCellCount;
		m_dColCount = dlg->m_nColCount;
		m_dRowCount = dlg->m_nRowCount;
		m_dBlockCount = dlg->m_nBlockCount;
		m_dCBlockCount = dlg->m_nCBlockCount;

//		m_dStartRange = dlg->m_nStartRange;
//		m_dEndRange = dlg->m_nEndRange;
//		m_strArray[11] = dlg->m_nAbstractStepNum;
//		m_dStepFreq = dlg->m_nPaintedStepFreq;
//		m_dIsSquare = dlg->m_nIsSquare;
		m_dCellRatio = dlg->m_nCellRatio;
		//flags[23] = dlg->m_nDeriveCells;
		m_flags[24] = dlg->m_Reflect;
		m_flags[25] = dlg->m_CnsRow;
		m_flags[26] = dlg->m_CnsCol;
		m_flags[27] = dlg->m_CnsBlock;
		m_flags[28] = dlg->m_CnsCBlock;
		m_flags[29] = dlg->m_IntSync;
		//m_flags[37] = dlg->m_SyncAll;	//Causes row,column,blocks etc to
										//be drawn equally as often in rel.
										//to the color steps

		m_dFRow = dlg->m_F_ROW;
		m_dFCol = dlg->m_F_COL;
		m_dFBlock = dlg->m_F_BLK;
		m_dFCBlock = dlg->m_F_CBLK;

//		m_flags[53] = dlg-m_TogLock;
		m_flags[54] = dlg->m_TogLock2;
		m_flags[55] = dlg->m_TogLock3;
		m_flags[56] = dlg->m_TogLock4;
		m_flags[57] = dlg->m_TogLock5;
		m_flags[58] = dlg->m_TogLock6;
		m_flags[59] = dlg->m_TogLock7;
		m_flags[60] = dlg->m_TogLock8;
		m_flags[61] = dlg->m_TogLock9;
		m_flags[62] = dlg->m_TogLock10;
		m_flags[63] = dlg->m_TogLock11;

		InductNewValues();//from scratchPad to CSerioDoc
		SetModifiedFlag();
		update = TRUE;
	}
	if(cancel && m_dFormatDlgChangedView)update = TRUE;
	m_dFormatDlgChangedView = FALSE;
	RegisterAspects();
	::scratchPad.LoadCalcMembers();
	delete dlg;
	if(GetNextVal())CallDialog(5);
	if(update)UpdateAllViews(NULL);
	m_dDlgInProcess = FALSE;
}

void CSerioDoc::OnSpecifyOrient() 
{
	//COrientDlg *orientDlg;
		
	//orientDlg = new COrientDlg;
	//orientDlg->Create(IDD_DIALOG6, NULL);
	COrientDlg dlg;

	dlg.m_colorMode = m_dColorMode;
	
	dlg.m_DirFB = m_strArray[19];
	dlg.m_DirFL = m_strArray[20];
	dlg.m_DirLR = m_strArray[29];
	dlg.m_DirTB = m_strArray[30];
	

	if(dlg.DoModal()==IDOK)
	{
		m_strArray[19] = dlg.m_DirFB;
		m_strArray[20] = dlg.m_DirFL;
		m_strArray[29] = dlg.m_DirLR;
		m_strArray[30] = dlg.m_DirTB;
		if(m_dColorMode==0)m_dOrientation_0 = dlg.m_tempOrient;
		if(m_dColorMode==1)m_dOrientation_1 = dlg.m_tempOrient;
		if(m_dColorMode==2)m_dOrientation_2 = dlg.m_tempOrient;

		SetModifiedFlag();
		UpdateAllViews(NULL);
	}

}

int CSerioDoc::OnCBlockLayoutPrompt(UINT count)
{
	int code = 0;//0 not called, 1 handled, 2 cancelled
	BOOL nuf = TRUE, tooMany = FALSE;
	m_cancel = FALSE;
	if(count>m_dBlockCols * m_dBlockRows * m_dPageCount)nuf = FALSE;
	if(!nuf)
	{
		m_dCBlocksNeeded = count;
		m_dCalledByDlg = TRUE;
		OnCBlockLayout();
		code = 1;
	}
	if(m_cancel)code = 2;
	return code;
}

int CSerioDoc::OnBlockLayoutPrompt(UINT count)
{
	int code = 0;
	BOOL nuf = TRUE,tooMany = FALSE;
	m_cancel = FALSE;
	CRegAspect* bCoLine = ::scratchPad.m_reg[19];
	CRegAspect* bRoLine = ::scratchPad.m_reg[20];
	unsigned long bCols = bCoLine->m_nNuCount;
	unsigned long bRows = bRoLine->m_nNuCount;
	if(m_dColorMode!=1)
	{
		if(count>(bCols * bRows * m_dPageCount))nuf = FALSE;
	}
	else if(count>(bCols * bRows))nuf = FALSE;
	if(!nuf)
	{
		m_dBlocksNeeded = count;
		m_dCalledByDlg = TRUE;
		m_dExtraColsRows = FALSE;
		OnBlockLayout();
		code = 1;
	}
	if(m_cancel)code = 2;//from BlockLayoutParametersDialog
	return code;
}

void CSerioDoc::OnCBlockLayout() 
{
	m_cancel = TRUE;
	m_dDlgInProcess = TRUE;
	m_dIfServCglom = TRUE;
	UINT cBlocksPPgNeeded;
	if(m_dColorMode==1)
	{
		CCBlockLayoutDlg dlg;
		dlg.byDlg = m_dCalledByDlg;
		dlg.extra = m_dExtraColsRows;
		if(!m_dCalledByDlg)
		{								//m_dCBlockCols * m_dCBlockRows;
			cBlocksPPgNeeded = m_dCBlockCount / m_dPageCount;
			dlg.m_blocksNeeded = cBlocksPPgNeeded;
			dlg.m_blockW = m_dCglomBlockWidth;
			dlg.m_blockH = m_dCglomBlockHeight;
			dlg.m_blockCols = m_dCBlockCols;
			dlg.m_blockRows = m_dCBlockRows;
			dlg.m_frameH = m_dVirtualPageHeight;
			dlg.m_frameW = m_dVirtualPageWidth;
		}
		else
		{
			//m_dCBlocksNeeded having been set at OnCBlockLayoutPrompt()
			cBlocksPPgNeeded = m_dCBlockCols * m_dCBlockRows;
			for(;(cBlocksPPgNeeded * m_dPageCount)<m_dCBlocksNeeded;)
			{
				cBlocksPPgNeeded += 1;
			}
			CRegAspect* line;
			dlg.m_blocksNeeded = cBlocksPPgNeeded;
			line = ::scratchPad.m_reg[2];
			dlg.m_blockW = line->m_nNuSize;
			line = ::scratchPad.m_reg[9];
			dlg.m_blockH = line->m_nNuSize;
			line = ::scratchPad.m_reg[21];
			dlg.m_blockCols = line->m_nNuCount;
			line = ::scratchPad.m_reg[22];
			dlg.m_blockRows = line->m_nNuCount;
			line = ::scratchPad.m_reg[18];
			dlg.m_frameH = line->m_nNuSize;
			line = ::scratchPad.m_reg[17];
			dlg.m_frameW = line->m_nNuSize;
		}
		if (dlg.DoModal()==IDOK)
		{	
			m_cancel = FALSE;
			m_dExtraColsRows = FALSE;

			CRegAspect* line;
			line = ::scratchPad.m_reg[21];
			if(line->m_nNuCount!=dlg.m_blockCols)
				::scratchPad.InstigateChange(dlg.m_blockCols,21);
			line = ::scratchPad.m_reg[22];
			if(line->m_nNuCount!=dlg.m_blockRows)
				::scratchPad.InstigateChange(dlg.m_blockRows,22);
			line = ::scratchPad.m_reg[18];
			if(line->m_nNuSize!=dlg.m_frameH)
				::scratchPad.InstigateChange(dlg.m_frameH,18);
			line = ::scratchPad.m_reg[17];
			if(line->m_nNuSize!=dlg.m_frameW)
				::scratchPad.InstigateChange(dlg.m_frameW,17);
			line = ::scratchPad.m_reg[2];
			if(line->m_nNuSize!=dlg.m_blockW)
				::scratchPad.InstigateChange(dlg.m_blockW,2);
			line = ::scratchPad.m_reg[9];
			if(line->m_nNuSize!=dlg.m_blockH)
				::scratchPad.InstigateChange(dlg.m_blockH,9);

			BOOL result = ::scratchPad.ProcessChangeRequests();		

			if(result)
			{
				if(!m_dCalledByDlg)
				{
					InductNewValues();//from scratchPad to CSerioDoc
					//m_dCBlockCount = m_dCBlocksNeeded;
				}
				else 
				{
					//CRegAspect* line = ::scratchPad.m_reg[14];	
					//line->m_nNuCount = m_dCBlocksNeeded;
					//line->m_nCount = m_dCBlocksNeeded;
					//::scratchPad.InstigateChange(m_dBlocksNeeded,14);
					//BOOL ok = ::scratchPad.ProcessChangeRequests();
				}
				::scratchPad.LoadCalcMembers();
				SetModifiedFlag();
				if(m_dCalledByDlg)m_dFormatDlgChangedView = TRUE;
				UpdateAllViews(NULL);
			}
		}
	}
	if(m_dColorMode!=1) AfxMessageBox(
		"Dialog box not available with current color mode");
	if(!m_dCalledByDlg)
	{
		RegisterAspects();
		::scratchPad.LoadCalcMembers();
		m_dDlgInProcess = FALSE;
	}
	m_dCalledByDlg = FALSE;
}

void CSerioDoc::OnBlockLayout() 
{
	CRegAspect* line;
	m_cancel = TRUE;
	m_dDlgInProcess = TRUE;
	m_dIfServCglom = FALSE;
	UINT blocksPPgNeeded = 0;
	CBlockLayoutDlg dlg;
	
	//dlg.m_blockDlg = &dlg;
	if(!m_dCalledByDlg)
	{
		dlg.m_blockH = m_dBlockHeight;
		dlg.m_blockW = m_dBlockWidth;
		dlg.m_blockCols = m_dBlockCols;
		dlg.m_blockRows = m_dBlockRows;
		if(m_dColorMode!=1)
		{
			m_dBlocksNeeded = m_dBlockCount / m_dPageCount;
			dlg.m_frameH = m_dVirtualPageHeight;
			dlg.m_frameW = m_dVirtualPageWidth;
		}
		if(m_dColorMode==1)
		{
			m_dBlocksNeeded = m_dBlockCount;
			dlg.m_frameH = m_dCglomBlockHeight;
			dlg.m_frameW = m_dCglomBlockWidth;
		}

	}
	if(m_dCalledByDlg)
	{
		line = ::scratchPad.m_reg[8];
		dlg.m_blockH = line->m_nNuSize;
		line = ::scratchPad.m_reg[1];
		dlg.m_blockW = line->m_nNuSize;
		line = ::scratchPad.m_reg[19];
		dlg.m_blockCols = line->m_nNuCount;
		line = ::scratchPad.m_reg[20];
		dlg.m_blockRows = line->m_nNuCount;

		if(m_dColorMode!=1)
		{
			//m_dBlocksNeeded having been set at OnBlockRowPrompt()
			blocksPPgNeeded = m_dBlockCols * m_dBlockRows;
			for(;(blocksPPgNeeded * m_dPageCount)<m_dBlocksNeeded;)
			{
				blocksPPgNeeded += 1;
			}

			m_dBlocksNeeded = blocksPPgNeeded;
			line = ::scratchPad.m_reg[18];
			dlg.m_frameH = line->m_nNuSize;
			line = ::scratchPad.m_reg[17];
			dlg.m_frameW = line->m_nNuSize;
		}
		if(m_dColorMode==1)
		{
			line = ::scratchPad.m_reg[9];
			dlg.m_frameH = line->m_nNuSize;
			line = ::scratchPad.m_reg[2];
			dlg.m_frameW = line->m_nNuSize;
		}
	}
	dlg.byDlg = m_dCalledByDlg;
	dlg.extra = m_dExtraColsRows;
	dlg.m_blocksNeeded = m_dBlocksNeeded;
	if (dlg.DoModal()==IDOK)
	{	
		m_cancel = FALSE;
		m_dExtraColsRows = FALSE;
		if(m_dColorMode!=1)
		{
			line = ::scratchPad.m_reg[18];
			if(line->m_nNuSize!=dlg.m_frameH)
				::scratchPad.InstigateChange(dlg.m_frameH,18);
			line = ::scratchPad.m_reg[17];
			if(line->m_nNuSize!=dlg.m_frameW)
				::scratchPad.InstigateChange(dlg.m_frameW,17);
		}
		if(m_dColorMode==1)
		{
			line = ::scratchPad.m_reg[9];
			if(line->m_nNuSize!=dlg.m_frameH)
				::scratchPad.InstigateChange(dlg.m_frameH,9);
			line = ::scratchPad.m_reg[2];
			if(line->m_nNuSize!=dlg.m_frameW)
				::scratchPad.InstigateChange(dlg.m_frameW,2);
		}
		line = ::scratchPad.m_reg[20];
		if(line->m_nNuCount!=dlg.m_blockRows)
			::scratchPad.InstigateChange(dlg.m_blockRows,20);
		line = ::scratchPad.m_reg[19];
		if(line->m_nNuCount!=dlg.m_blockCols)
			::scratchPad.InstigateChange(dlg.m_blockCols,19);
		line = ::scratchPad.m_reg[8];
		if(line->m_nNuSize!=dlg.m_blockH)
			::scratchPad.InstigateChange(dlg.m_blockH,8);
		line = ::scratchPad.m_reg[1];
		if(line->m_nNuSize!=dlg.m_blockW)
			::scratchPad.InstigateChange(dlg.m_blockW,1);

		BOOL result = ::scratchPad.ProcessChangeRequests();		

		if(result)
		{
			if(!m_dCalledByDlg)
			{
				InductNewValues();//from scratchPad to CSerioDoc
				
				if(m_dColorMode!=1)
				{
					m_dCglomBlockWidth = m_dVirtualPageWidth;
					m_dCglomBlockHeight = m_dVirtualPageHeight;
				}
			}
			else 
			{
				//CRegAspect* line = ::scratchPad.m_reg[13];	
				//line->m_nNuCount = m_dBlocksNeeded;
				//line->m_nCount = m_dBlocksNeeded;
				//::scratchPad.InstigateChange(m_dBlocksNeeded,13);
				//BOOL ok = ::scratchPad.ProcessChangeRequests();
			}
			::scratchPad.LoadCalcMembers();
			UpdateAllViews(NULL);
			if(m_dCalledByDlg)m_dFormatDlgChangedView = TRUE;
			SetModifiedFlag();
		}
	}
	if(!m_dCalledByDlg)
	{
		RegisterAspects();
		::scratchPad.LoadCalcMembers();
		m_dDlgInProcess = FALSE;
	}
	m_dCalledByDlg = FALSE;
}

void CSerioDoc::OnViewControlDlg() 
{
	m_viewDlg = new CViewControlDlg();
	m_viewDlg->m_curPage = m_dCurPage;
	m_viewDlg->m_curPageBuf = m_dCurPage;
	m_viewDlg->Create(IDD_VIEW_PAGE , NULL);
	m_viewDlg->MoveWindow(m_dViewDlgRect.left,m_dViewDlgRect.top,
		m_dViewDlgRect.right,m_dViewDlgRect.bottom,TRUE);
}

BOOL CSerioDoc::RestoreViewControlDlg()
{
	BOOL doesExist = FALSE;
	if(m_viewDlgOn && m_dViewDlgCloseIsSimulated)
	{
		OnViewControlDlg();
		m_dViewDlgCloseIsSimulated = FALSE;
		doesExist = TRUE;
	}
	return doesExist;
}

BOOL CSerioDoc::ValidateNewPageView(UINT nuPage)
{
	BOOL valid = FALSE;
	if((nuPage<=m_dPageCount)&&(nuPage>0))
	{
		valid = TRUE;
		UpdateAllViews(NULL);
		m_dCurPage = nuPage;
	}

	return valid;
}

///////////////////////////////////////////////////////////////////
// Miscellaneous

void CSerioDoc::ConvertToCMYK(int oldc)
{
	m_dBitDepth = "32-bit";
	m_dBlockCols = 3;	
	m_dBlockCount = 6;	//per c-block
	m_dBlockHeight = 1.95;
	m_dBlockRows = 2;
	m_dBlockWidth = 2.1;
	m_dCBlockCols = 1;	//per page
	m_dCBlockCount = 6;	//per document
	m_dCBlockRows = 2;	//per page
	m_dCellCount = 1296;
	m_dCellHeight = 0.3;
	m_dCellWidth = 0.3;
	m_dCglomBlockHeight = 4.25;
	m_dCglomBlockWidth = 7;
	m_dColCount = 6;
	m_dVirtualPageHeight = 9.5; //aka: pageFrame height
	m_dVirtualPageWidth = 7;	//aka: pageFrame width
	//m_dColRowCount = ??;
	m_dLeftMarg = .75;
	m_dLowerMarg = .75;
	m_dRightMarg = .75;
	m_dRowCount = 6;
	m_dUpperMarg = .75;
	m_dPageWidth = 8.5;
	m_dPageHeight = 11;
	m_dFCol = 51.0;
	m_dFRow = 51.0;
	m_dFBlock = 51.0;
	m_dFCBlock = 51.0;

	m_dPageCount = 3;
	m_dCurPage = 1;
	if(IsViewDlgOn())
	{
		if(!m_dViewDlgCloseIsSimulated)
		{
			m_viewDlg->m_curPage = 1;
			m_viewDlg->UpdateData(FALSE);
		}
	}
	
	SetModifiedFlag();
	RegisterAspects();
	::scratchPad.LoadCalcMembers();

	UpdateAllViews(NULL);
}

void CSerioDoc::ConvertToRGB(int oldc)
{
	CAspects* pAspects;
	m_dasp = initDims(); //Loads float defaults to new CAspect object
	pAspects = m_dasp;					//should be called only if it is a new document

	initStrings();		//Loads all dialog CString values if New document
	initInts();			//Loads all dialog Int values if New document
	initBOOLs();		//Loads all flags if New Document
	
	initDoc(pAspects);		//Loads dialogs from either serialized or 
							//new objects
	
	initCells();	//Loads defaults from m_cellList

	m_dPageCount = 1;
	m_dCurPage = 1;
	if(IsViewDlgOn())
	{
		if(!m_dViewDlgCloseIsSimulated)
		{
			m_viewDlg->m_curPage = 1;
			m_viewDlg->UpdateData(FALSE);
		}
	}

	//initRegObject();
	// (SDI documents will reuse this document)
	SetModifiedFlag();
	RegisterAspects();
	::scratchPad.LoadCalcMembers();
	UpdateAllViews(NULL);

	return;
}

void CSerioDoc::ConvertToCMY(int oldc)
{
	m_dBlockCols = 1;
	m_dBlockCount = 6;
	m_dBlockHeight = 1.0;
	m_dBlockRows = 6;
	m_dBlockWidth = 7.0;
	m_dCBlockCols = 1;
	m_dCBlockCount = 1;
	m_dCBlockRows = 1;
	m_dCellCount = 108;
	m_dCellHeight = .2;
	m_dCellWidth = .85;
	m_dCglomBlockHeight = 10.0;
	m_dCglomBlockWidth = 7.0;
	m_dColCount = 6;
	m_dVirtualPageHeight = 10.0;
	m_dVirtualPageWidth = 7.0;
	m_dLeftMarg = .5;
	m_dLowerMarg = .5;
	m_dRightMarg = 1.0;
	m_dRowCount = 4;
	m_dUpperMarg = .5;
	m_dFCol = 51.0;
	m_dFRow = 85.0;
	m_dFBlock = 51.0;
	m_dFCBlock = 255.0;

	m_dPageCount = 1;
	m_dCurPage = 1;
	if(IsViewDlgOn())
	{
		if(!m_dViewDlgCloseIsSimulated)
		{
			m_viewDlg->m_curPage = 1;
			m_viewDlg->UpdateData(FALSE);
		}
	}

	SetModifiedFlag();
	RegisterAspects();
	::scratchPad.LoadCalcMembers();
	UpdateAllViews(NULL);
}



///////////////////////////////////////////////////////////////////
// Initialization functions

void CSerioDoc::initCells()
{/*
	int a = 45, b = 45, c = 160, d = 160;
	
	CCell* pRect = new CCell();
	m_cellList.AddTail(pRect);
	//SetModifiedFlag();

	pRect->m_rect.Add( a);
	pRect->m_rect.Add( b);
	pRect->m_rect.Add( c);
	pRect->m_rect.Add( d);
*/

//	UpdateAllViews(NULL,NULL,NULL);

}

CAspects* CSerioDoc::initDims()
{
	CAspects* pdata = new CAspects();
	pdata->m_asp.Add(8.5);	//page width
	pdata->m_asp.Add(11.0);	//page height
	pdata->m_asp.Add(.5);	//left margin
	pdata->m_asp.Add(.5);	//lower	margin
	pdata->m_asp.Add(.5);	//right	margin
	pdata->m_asp.Add(.75);	//upper margin
	pdata->m_asp.Add(.15);	//cell width
	pdata->m_asp.Add(.15);	//cell height
	pdata->m_asp.Add(3.5);	//block width
	pdata->m_asp.Add(3.0);	//block height
	pdata->m_asp.Add(7.5);	//C-block width
	pdata->m_asp.Add(9.75);	//C-block height

#ifdef _DEBUG
	pdata->m_asp.Add(85.0);	//m_CnsRow
	pdata->m_asp.Add(51.0);
	pdata->m_asp.Add(51.0);
	pdata->m_asp.Add(255.0);
#endif

#ifndef _DEBUG
	pdata->m_asp.Add(15.0);	//m_CnsRow
	pdata->m_asp.Add(15.0);
	pdata->m_asp.Add(51.0);
	pdata->m_asp.Add(255.0);
#endif

	m_dVirtualPageHeight = 9.75;	//Virtual page height
	m_dVirtualPageWidth = 7.5;		//Virtual page width

	return pdata;
}

void CSerioDoc::initStrings()			
{
	//only when and if this is a new document


	m_strArray[0] = "8-bit";
	m_strArray[1] = "16-bit";
	m_strArray[2] = "24-bit";
	m_strArray[3] = "32-bit";
	m_strArray[4] = "system palette";
	m_strArray[5] = "default palette";
	m_strArray[6] = "none";
	m_strArray[7] = "inches";
	m_strArray[8] = "centimeters";
	m_strArray[9] = "pixels";
	m_strArray[10] = "steps (0 to 255)";
	m_strArray[11] = "percent (0 to 100)";

	m_strArray[12] = "Custom...";		//Constrain modes
	m_strArray[13] = "Freeze Blocks";
	m_strArray[14] = "Proportional";
	m_strArray[15] = "margin resize";	//contexts modes will plug into
	m_strArray[16] = "cell resize";
	m_strArray[17] = "page increase";
	m_strArray[18] = "default";
										
	m_strArray[19] = "the MINIMUM value";	//Color Orientation
	m_strArray[20] = "the MINIMUM value";	
	m_strArray[21] = "(RED)";				//strings not in use....
	m_strArray[22] = "(GREEN)";				//
	m_strArray[23] = "(BLUE)";				//
	m_strArray[24] = "(CYAN)";				//
	m_strArray[25] = "(MAGENTA)";			//
	m_strArray[26] = "(YELLOW)";			//...since CStatics were
	m_strArray[27] = "(BLACK)";				//sub-classed
	m_strArray[28] = "(N/A)";
	m_strArray[29] = "the MINIMUM value";
	m_strArray[30] = "the MINIMUM value";

	m_strArray[31] = "white";				//outline colors
	m_strArray[32] = "black";
	m_strArray[33] = "gray";
	m_strArray[34] = "same as cell";

	//m_strArray[] = "Both ends"	//Placement options in Insert dialog
}

void CSerioDoc::initInts()
{
	m_dOutlineClr = 34;	//index into m_strArray[]

	m_dCurPage = 1;
	m_dPageCount = 1;
	m_dStepFreq = 5;
	m_dStartRange = 0;
	m_dEndRange = 255;

#ifdef _DEBUG
	m_dCellCount = 144;
	m_dRowCount = 4;
	m_dColCount = 6;
#endif

#ifndef _DEBUG
	m_dCellCount = 1536;
	m_dRowCount = 16;
	m_dColCount = 16;
#endif

	m_dBlockCount = 6;
	m_dCBlockCount = 1;

	m_dMargRat = 1;

	m_dColorMode = 0;		//initiallized: 0-RGB  1-CMYK 2-CMY
						
	m_dOrientation_0 = 6;	//6-default rgb 
	m_dOrientation_1 = 14;	//14 default cmyk
	m_dOrientation_2 = 8;	//8-default cmy
	m_dSL2R = 0;
	m_dST2B = 0;
	m_dSF2L = 0;
	m_dSF2B = 0;
	m_dEL2R = 255;
	m_dET2B = 255;
	m_dEF2L = 255;
	m_dEF2B = 255;

	m_dPosEd = 0;

	m_dBlockCols = 2;//per c-block or per page
	m_dBlockRows = 3;//per c-block or per page
	m_dCBlockCols = 1;// per page
	m_dCBlockRows = 1;// per page
}

void CSerioDoc::initBOOLs()
{	
	m_dShowPage = TRUE;
	m_dDerivePCnt = FALSE;
	m_dIsSquare = FALSE;
	m_dCellRatio = FALSE;
	m_flags.SetSize(65,10);		//CArray for Constrain Mode Dialog flags...
	m_flags[0] = FALSE;
	m_flags[1] = TRUE;
	m_flags[2] = FALSE;
	m_flags[3] = TRUE;
	m_flags[4] = FALSE;
	m_flags[5] = TRUE;
	m_flags[6] = FALSE;
	m_flags[7] = TRUE;
	m_flags[8] = FALSE;
	m_flags[9] = TRUE;
	m_flags[10] = FALSE;
	m_flags[11] = FALSE;
	m_flags[12] = TRUE;
	m_flags[13] = TRUE;
	m_flags[14] = FALSE;
	m_flags[15] = TRUE;
	m_flags[16] = FALSE;
	m_flags[17] = TRUE;
	m_flags[18] = FALSE;
	m_flags[19] = TRUE;
	m_flags[20] = FALSE;

	m_flags[21] = FALSE;		//Insert use both index descriptions
	m_flags[22] = FALSE;		//ColorFormDlg  steps based on other
	
	m_flags[23] = FALSE;		//CCellAspectsDlg derive cells from other
	m_flags[24] = TRUE;			//m_Reflect-reflect color range in counts

	m_flags[25] = FALSE;			//Activate Basic Aspects CCellAspectsDlg
	m_flags[26] = FALSE;
	m_flags[27] = FALSE;
	m_flags[28] = FALSE;
	m_flags[29] = TRUE;
	m_flags[30] = FALSE;
	m_flags[31] = FALSE;
	m_flags[32] = TRUE;
	m_flags[33] = TRUE;
	m_flags[34] = TRUE;
	m_flags[35] = TRUE;
	m_flags[36] = TRUE;
	m_flags[37] = FALSE; //SyncAll

	m_flags[38] = FALSE; //Color dlg.-- locks
	m_flags[39] = FALSE;
	m_flags[40] = FALSE;
	m_flags[41] = FALSE;
	m_flags[42] = FALSE;
	m_flags[43] = FALSE;
	m_flags[44] = FALSE;
	m_flags[45] = FALSE;

	m_flags[46] = FALSE;	//Layout dlg.-- locks
	m_flags[47] = FALSE;
	m_flags[48] = FALSE;
	m_flags[49] = FALSE;
	m_flags[50] = FALSE;
	m_flags[51] = FALSE;
	m_flags[52] = FALSE;

	m_flags[53] = FALSE;	//CCellAspectsDlg -- locks
	m_flags[54] = FALSE;
	m_flags[55] = FALSE;
	m_flags[56] = FALSE;
	m_flags[57] = FALSE;
	m_flags[58] = FALSE;
	m_flags[59] = FALSE;
	m_flags[60] = FALSE;
	m_flags[61] = FALSE;
	m_flags[62] = FALSE;
	m_flags[63] = FALSE;

	m_dBlockColLck = FALSE;
	m_dBlockRowLck = FALSE;
	m_dCBlockColLck = FALSE;
	m_dCBlockRowLck = FALSE;

	m_dNext = FALSE;
	//sent to OnBlockRow
	m_dExtraColsRows = FALSE;
	m_dCalledByDlg = FALSE;
	m_userLineBrkPerCol = FALSE;
	m_userLineBrkPerRow = FALSE;
	m_userLineBrkPerBlk = FALSE;
	m_userLineBrkPerCBlk = FALSE;
}

CDlgStrArray::CDlgStrArray()
{
	SetSize(40,5);
}

CSerioDoc* CSerioDoc::GetDoc()
{
	CMDIChildWnd* pChild = 
		((CMDIFrameWnd*) (AfxGetApp()->m_pMainWnd))->MDIGetActive();

	if(!pChild)
		return NULL;

	CDocument* pDoc = pChild->GetActiveDocument();

	if(!pDoc)
		return NULL;

	return (CSerioDoc*) pDoc;
}



void CSerioDoc::CallDialog(int nDlg)
{
	if(nDlg==2)OnQuickLayout();
	if(nDlg==3)OnCellSpecs();
	//if(nDlg==4)OnInsert();
	if(nDlg==5)OnSpecifyOrient();
}

BOOL CSerioDoc::ToggleNext()
{
	if(m_dNext)m_dNext = FALSE;
	if(!m_dNext)m_dNext = TRUE;
	return TRUE;
}

BOOL CSerioDoc::GetNextVal()
{
	BOOL flag;
	flag = m_dNext;
	return flag;
}


BOOL CSerioDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	m_dViewDlgRect.left = 15;
	m_dViewDlgRect.top = 115;
	m_dViewDlgRect.right = 110;//width
	m_dViewDlgRect.bottom = 54;
	TidyUpPreviousDoc();

	return TRUE;
}

///////////////////////////////////////////////////////////////////
// Internal calculation components


void CSerioDoc::InductNewValues()
{
	CRegAspect* line;
	line = ::scratchPad.m_reg[0];
	m_dCellWidth = line->m_nSize;
	line = ::scratchPad.m_reg[1];
	m_dBlockWidth = line->m_nSize;
	line = ::scratchPad.m_reg[2];
	m_dCglomBlockWidth = line->m_nSize;
	line = ::scratchPad.m_reg[3];
	m_dLeftMarg = line->m_nSize;
	line = ::scratchPad.m_reg[4];
	m_dRightMarg = line->m_nSize;
	line = ::scratchPad.m_reg[5];
	m_dColCount = line->m_nCount;
	line = ::scratchPad.m_reg[6];
	m_dPageWidth = line->m_nSize;
	line = ::scratchPad.m_reg[7];
	m_dCellHeight = line->m_nSize;
	line = ::scratchPad.m_reg[8];
	m_dBlockHeight = line->m_nSize;
	line = ::scratchPad.m_reg[9];
	m_dCglomBlockHeight = line->m_nSize;
	line = ::scratchPad.m_reg[10];
	m_dUpperMarg = line->m_nSize;
	line = ::scratchPad.m_reg[11];
	m_dLowerMarg = line->m_nSize;
	line = ::scratchPad.m_reg[12];
	m_dRowCount = line->m_nCount;
	line = ::scratchPad.m_reg[13];
	m_dBlockCount = line->m_nCount;
	line = ::scratchPad.m_reg[14];
	m_dCBlockCount = line->m_nCount;
	line = ::scratchPad.m_reg[15];
	m_dPageCount = line->m_nCount;
	line = ::scratchPad.m_reg[16];
	m_dPageHeight = line->m_nSize;
	line = ::scratchPad.m_reg[17];
	m_dVirtualPageWidth = line->m_nSize;
	line = ::scratchPad.m_reg[18];
	m_dVirtualPageHeight = line->m_nSize;
	line = ::scratchPad.m_reg[19];
	m_dBlockCols = line->m_nCount;
	line = ::scratchPad.m_reg[20];
	m_dBlockRows = line->m_nCount;
	line = ::scratchPad.m_reg[21];
	m_dCBlockCols = line->m_nCount;
	line = ::scratchPad.m_reg[22];
	m_dCBlockRows = line->m_nCount;

	line = ::scratchPad.m_reg[23];
	m_dFCol = line->m_nSize;
	line = ::scratchPad.m_reg[24];
	m_dFRow = line->m_nSize;
	line = ::scratchPad.m_reg[25];
	m_dFBlock = line->m_nSize;
	line = ::scratchPad.m_reg[26];
	m_dFCBlock = line->m_nSize;
	 
	m_dCellCount = ::scratchPad.m_totalCells;
	m_dSL2R = ::scratchPad.m_rowFrom;
	m_dEL2R = ::scratchPad.m_rowTo;
	m_dST2B = ::scratchPad.m_colFrom;
	m_dET2B = ::scratchPad.m_colTo;
	m_dSF2L = ::scratchPad.m_blockFrom;
	m_dEF2L = ::scratchPad.m_blockTo;
	m_dSF2B = ::scratchPad.m_cBlockFrom;
	m_dEF2B = ::scratchPad.m_cBlockTo;
}

void CSerioDoc::InitRegObject(CSerioDoc* pDoc)
{
	m_sizeDoc = CSize(850,1100);
	int i;
	for(i=0; i<RGSZ; i++)
	{
		CRegAspect* ledger = new CRegAspect();
		::scratchPad.m_reg[i] = ledger;
	}
	
	RegisterAspects();
	::scratchPad.LoadCalcMembers(pDoc);
}
/*
	RegisterRectWidth(i);		//0
	RegisterBlockWidth(++i);	//1
	RegisterCBlockWidth(++i);	//2
	RegisterLeftMarg(++i);		//3	
	RegisterRightMarg(++i);		//4 
	RegisterColCount(++i);		//5	
	RegisterPageWidth(++i);		//6
	
	RegisterRectHeight(++i);	//7
	RegisterBlockHeight(++i);	//8
	RegisterCBlockHeight(++i);	//9
	RegisterUpMarg(++i);		//10
	RegisterLowMarg(++i);		//11
	RegisterRowCount(++i);		//12
	
	RegisterBlockCount(++i);	//13	per document or per c-block
	RegisterCBlockCount(++i);	//14	per document 
	RegisterPageCount(++i);		//15
	RegisterPageHeight(++i);	//16

	RegisterVirtualPageWidth(++i);	//17
	RegisterVirtualPageHeight(++i); //18
	RegisterBlockCols(++i);		//19		per page or per c-block
	RegisterBlockRows(++i);		//20		per page or per c-block
	RegisterCBlockCols(++i);	//21	per page
	RegisterCBlockRows(++i);	//22	per page

*/			


void CSerioDoc::RegisterAspects()
{	
	int id;
	for(id = 0; id<RGSZ; id++)
	{
		CRegAspect* line =	::scratchPad.m_reg[id];
		float span;
		int item;
		for(item=1;item<14;item++)
		{
			int idCode;BOOL flag;
			if(item==1)idCode = GetIDCode(id);
			if(item==2)idCode = GetIDAspectCode(id);
			if(item>3 && item<12) flag = GetAspectFlags(id,item);
			if(item>22)flag = GetAspectFlags(id,item);
			if(item==12) idCode = GetAspectCount(id);
			if(item==13) span = GetAspectSize(id);
			::scratchPad.SetContext(idCode,span,flag,item,line);
		}
		line->m_asking = FALSE;
		line->m_nNuSize = line->m_nSize;
		line->m_nNuCount = line->m_nCount;
		line->m_order = 99;
	}
	::scratchPad.m_intSync = m_flags[29];
	::scratchPad.m_rowFrom = m_dSL2R;
	::scratchPad.m_rowTo = m_dEL2R;
	::scratchPad.m_colFrom = m_dST2B;
	::scratchPad.m_colTo = m_dET2B;
	::scratchPad.m_blockFrom = m_dSF2L;
	::scratchPad.m_blockTo = m_dEF2L;
	::scratchPad.m_cBlockFrom = m_dSF2B;
	::scratchPad.m_cBlockTo = m_dEF2B;
}

int CSerioDoc::GetIDAspectCode(int id)
{
	int code = 0;
	if(id<12 && id!=5) code = 1;
	if(id>15 && id<19) code = 1;
	if(id>22 && id<27) code = 1;
	return code;
}


BOOL CSerioDoc::GetAspectFlags(int id, int item)
{
	BOOL f = FALSE;
	switch(item)
	{
	case 3:
		if(id==0)f = m_flags[58];
		if(id==1)f = m_flags[60];
		if(id==2)f = m_flags[62];
		if(id==3)f = m_flags[50];
		if(id==4)f = m_flags[52];
		if(id==5)f = m_flags[63];
		if(id==6)f = m_flags[46];
		if(id==7)f = m_flags[59];
		if(id==8)f = m_flags[61];
		if(id==9)f = m_flags[63];
		if(id==10)f = m_flags[49];
		if(id==11)f = m_flags[51];
		if(id==12)f = m_flags[63];
		if(id==13)f = m_flags[63];
		if(id==14)f = m_flags[63];
		if(id==15)f = m_flags[48];
		if(id==16)f = m_flags[47];
		if(id==17)f = m_flags[46];
		if(id==18)f = m_flags[46];
		if(id==19)f = m_dBlockColLck;
		if(id==20)f = m_dBlockRowLck;
		if(id==21)f = m_dCBlockColLck;
		if(id==22)f = m_dCBlockRowLck;

		break;
	case 4:
		if(id==0)f = m_flags[58];
		if(id==1)f = m_flags[60];
		if(id==2)f = m_flags[62];
		if(id==3)f = m_flags[50];
		if(id==4)f = m_flags[52];
		if(id==5)f = m_flags[55];
		if(id==6)f = m_flags[46];
		if(id==7)f = m_flags[59];
		if(id==8)f = m_flags[61];
		if(id==9)f = m_flags[63];
		if(id==10)f = m_flags[49];
		if(id==11)f = m_flags[51];
		if(id==12)f = m_flags[54];
		if(id==13)f = m_flags[56];
		if(id==14)f = m_flags[57];
		if(id==15)f = m_flags[48];
		if(id==16)f = m_flags[47];
		if(id==17)f = m_flags[46];
		if(id==18)f = m_flags[46];
		if(id==19)f = m_dBlockColLck;
		if(id==20)f = m_dBlockRowLck;
		if(id==21)f = m_dCBlockColLck;
		if(id==22)f = m_dCBlockRowLck;
		if(id==23)f = m_flags[26];
		if(id==24)f = m_flags[25];
		if(id==25)f = m_flags[27];
		if(id==26)f = m_flags[28];
		if(id==27)f = m_flags[44];
		if(id==28)f = m_flags[45];
		if(id==29)f = m_flags[42];
		if(id==30)f = m_flags[43];
		if(id==31)f = m_flags[40];
		if(id==32)f = m_flags[41];
		if(id==33)f = m_flags[38];
		if(id==34)f = m_flags[39];
		break;

	case 6:
		if(id<=6)f = TRUE;
		if(id>=7 && id<=16)f = FALSE;
		if(id==17 || id==19 || id==21)f = TRUE;
		if(id==18 || id==20 || id==22)f = FALSE;
		if(id==23)f = TRUE;
		if(id==24)f = FALSE;

		if(id==27)f = TRUE;
		if(id==28)f = TRUE;
		if(id==29)f = FALSE;
		if(id==30)f = FALSE;
		break;

	case 7: 
		if(id==0 || id==7)
		{
			if(m_dCellRatio || m_dIsSquare) f = TRUE;
		}
		if(id==3)//left margin
		{
			f = FALSE;
			if(m_dMargRat%5==0 || m_dMargRat%7==0 || m_dMargRat%17==0)
				f = TRUE;
		}
		if(id==4)//right margin
		{
			f = FALSE;
			if(m_dMargRat%13==0 || m_dMargRat%7==0 || m_dMargRat%3==0)
				f = TRUE;
		}
		if(id==10)//top margin
		{
			f = FALSE;
			if(m_dMargRat%17==0 || m_dMargRat%13==0 || m_dMargRat%11==0)
				f = TRUE;
		}
		if(id==11)//bottom margin
		{
			f = FALSE;
			if(m_dMargRat%5==0 || m_dMargRat%3==0 || m_dMargRat%11==0)
				f = TRUE;
		}
		break;
	default: 
		break;
	}	return f;
}


UINT CSerioDoc::GetAspectCount(int index)
{
	UINT count;
	if(index==5) count = m_dColCount;
	if(index==12) count = m_dRowCount;
	if(index==13) count = m_dBlockCount;
	if(index==14) count = m_dCBlockCount;
	if(index==15) count = m_dPageCount;
	if(index==19) count = m_dBlockCols;
	if(index==20) count = m_dBlockRows;
	if(index==21) count = m_dCBlockCols;
	if(index==22) count = m_dCBlockRows;
	if(index==27) count = m_dSL2R;
	if(index==28) count = m_dEL2R;
	if(index==29) count = m_dST2B;
	if(index==30) count = m_dET2B;
	if(index==31) count = m_dSF2L;
	if(index==32) count = m_dEF2L;
	if(index==33) count = m_dSF2B;
	if(index==34) count = m_dEF2B;

	return count;
}

float CSerioDoc::GetAspectSize(int index)
{
	float val = 0;
	if(index==0) val = m_dCellWidth;
	if(index==1) val = m_dBlockWidth;
	if(index==2) val = m_dCglomBlockWidth;
	if(index==3) val = m_dLeftMarg;
	if(index==4) val = m_dRightMarg;
	if(index==6) val = m_dPageWidth;
	if(index==7) val = m_dCellHeight;
	if(index==8) val = m_dBlockHeight;
	if(index==9) val = m_dCglomBlockHeight;
	if(index==10) val = m_dUpperMarg;
	if(index==11) val = m_dLowerMarg;
	if(index==16) val = m_dPageHeight;
	if(index==17) val = m_dVirtualPageWidth;
	if(index==18) val = m_dVirtualPageHeight;
	if(index==23) val = m_dFCol;
	if(index==24) val = m_dFRow;
	if(index==25) val = m_dFBlock;
	if(index==26) val = m_dFCBlock;
	return val;
}

int CSerioDoc::GetIDCode(int index)
{
	int code;
	if(index==0) code = 1014;
	if(index==1) code = 1022;
	if(index==2) code = 1024;
	if(index==3) code = 1017;
	if(index==4) code = 1019;
	if(index==5) code = 1064;
	if(index==6) code = 1010;
	if(index==7) code = 1025;
	if(index==8) code = 1023;
	if(index==9) code = 1026;
	if(index==10) code = 1016;
	if(index==11) code = 1018;
	if(index==12) code = 1123;
	if(index==13) code = 1122;
	if(index==14) code = 1065;
	if(index==15) code = 1065;
	if(index==16) code = 1044;
	if(index==17) code = 98;
	if(index==18) code = 99;
	if(index==19) code = 1066;
	if(index==20) code = 1064;
	if(index==21) code = 1065;
	if(index==22) code = 1064;
	if(index==23) code = 1090;
	if(index==24) code = 1092;
	if(index==25) code = 1091;
	if(index==26) code = 1096;
	return code;
}

BOOL CSerioDoc::LoadCell(int x1,int y1,int x2,int y2)
{	
	CObList &cellList =	m_cellList;
	//POSITION pos = cellList.GetHeadPosition();
	CCell* pCell = new CCell();
	pCell->m_rect.SetSize(4,4);
	
	cellList.AddTail(pCell);
	pCell->m_rect[0] = x1;
	pCell->m_rect[1] = y1;
	pCell->m_rect[2] = x2;
	pCell->m_rect[3] = y2;

	return TRUE;
}
	
/////////////////////////////////////////////////////////////////////////////
// CRegAspect

IMPLEMENT_DYNCREATE(CRegAspect, CCmdTarget)

CRegAspect::CRegAspect()
{
}

CRegAspect::~CRegAspect()
{
}


BEGIN_MESSAGE_MAP(CRegAspect, CCmdTarget)
	//{{AFX_MSG_MAP(CRegAspect)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegAspect message handlers

void CRegAspect::AcceptValue(BOOL IsInt)
{
	if(IsInt) m_nCount = m_nNuCount;
	if(!IsInt) m_nSize = m_nNuSize;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void CSerioDoc::OnAuto() 
{
	CMenu men;
	men.LoadMenu(IDR_MAINFRAME);
	((CMDIFrameWnd*) (AfxGetApp()->m_pMainWnd))->SetMenu(&men);
	((CMDIFrameWnd*) (AfxGetApp()->m_pMainWnd))->DrawMenuBar();
	men.Detach();
	m_auto = TRUE;
	m_user = FALSE;
}

void CSerioDoc::OnUpdateAuto(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_auto);
}

void CSerioDoc::OnUpdateUserControl(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_user);
}

void CSerioDoc::OnUpdateViewDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_viewDlgOn);
}

void CSerioDoc::ToggleViewDlg()
{
	if(m_viewDlgOn)m_viewDlgOn = FALSE;
	else m_viewDlgOn = TRUE;
}

void CSerioDoc::CloseViewDlg()
{
	if(m_viewDlgOn)
	{
		if(!m_dViewDlgCloseIsSimulated)
		{
			m_viewDlg->ShutDown();
			ToggleViewDlg();
		}
	}
}

void CSerioDoc::SimulateCloseViewDlg()
{
	if(m_viewDlgOn)
	{
		int width;
		int height;
		m_viewDlg->GetWindowRect(m_dViewDlgRect);
		width = m_dViewDlgRect.right - m_dViewDlgRect.left;
		height = m_dViewDlgRect.bottom - m_dViewDlgRect.top;
		m_dViewDlgRect.right = width;
		m_dViewDlgRect.bottom = height;
		m_dViewDlgCloseIsSimulated = TRUE;
		m_viewDlg->ShutDown();
	}
}

void CSerioDoc::PreventViewDlgFocus()
{
	if(m_viewDlg!=NULL)m_viewDlg->m_refuseFocus = VIEW_DLG_REFUSE_FOCUS;
		
}

void CSerioDoc::OnViewPagefinder() 
{
	if(!m_viewDlgOn)
	{	
		CMDIChildWnd* pChild = 
		((CMDIFrameWnd*) (AfxGetApp()->m_pMainWnd))->MDIGetActive();

		if(pChild->IsIconic())
		{
			m_dViewDlgCloseIsSimulated = TRUE;
		}
		else OnViewControlDlg();
		m_viewDlgOn = TRUE;
	}
	else 
	{
		if(!m_dViewDlgCloseIsSimulated)
		{
			BOOL start = TRUE;
			m_viewDlg->SignifyCloseByMenu(start);
			CloseViewDlg();
			m_viewDlg->SignifyCloseByMenu(!start);
		}
		else 
		{
			m_dViewDlgCloseIsSimulated = FALSE;
			ToggleViewDlg();
		}
	}	
}

void CSerioDoc::OnUpdateViewPagefinder(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(!m_viewDlgOn);	
	if(m_viewDlgOn)pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

void CSerioDoc::OnCloseDocument() 
{
	//CSerioDoc* pDoc = CSerioDoc::GetDoc();
	if(m_viewDlgOn && !m_dViewDlgCloseIsSimulated)
	{
		m_viewDlg->ShutDown();
		ToggleViewDlg();
	}

	//here is where we can delete the buffer for the doc specific global 
	//data objects that were created on the heap at OnOpen and OnNew
	
	CDocument::OnCloseDocument();

	GroomSuccessorWindow();
}

void CSerioDoc::GroomSuccessorWindow()
{
	BOOL iconic = FALSE;
	CSerioDoc* pDoc;
	CMDIChildWnd* pChild = 
		((CMDIFrameWnd*) (AfxGetApp()->m_pMainWnd))->MDIGetActive();

	if(((CSerioApp*)AfxGetApp())->m_noRegFile)return;
	if(pChild)
	{
		iconic = pChild->IsIconic();
		if(pDoc)
		{
			pDoc = (CSerioDoc*)pChild->GetActiveDocument();
			if(pDoc==NULL)return;
			if(pDoc->m_viewDlgOn)
			{
				if(pDoc->m_dViewDlgCloseIsSimulated && !iconic)
				{
					pDoc->RestoreViewControlDlg();
				}
			}
		}
	}
}

void CSerioDoc::OnCMYKButton() 
{
	ConvertToCMYK(m_dColorMode);
	m_dColorMode = 1;
	RegisterAspects();
	::scratchPad.LoadCalcMembers();
}

void CSerioDoc::OnCMYButton() 
{
	ConvertToCMY(m_dColorMode);	
	RegisterAspects();
	::scratchPad.LoadCalcMembers();
	m_dColorMode = 2;
}

void CSerioDoc::OnRGBButton() 
{
	ConvertToRGB(m_dColorMode);
	m_dColorMode = 0;
}
/*
void CSerioDoc::OnHelp() 
{
	//AfxMessageBox("Help unavailable from within the software.  See the User.doc file for 'how to' instructions.");
	CDocument::OnHelp();
}

void CSerioDoc::OnHelpFinder() 
{
	//AfxMessageBox("Help unavailable from within the software.  See the User.doc file for 'how to' instructions.");
	
}
*/