// Calc.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCalc command target
//#include "ProgressBar.h"

class CMessDlg;
class CRegAspect;
class CRegistrar;
class CCalc : public CCmdTarget
{
	DECLARE_DYNCREATE(CCalc)

	CCalc();           // protected constructor used by dynamic creation

// Attributes
public:
	int m_freeFiles;
	int m_freePrintouts;
	void InitializeProgressBar(CProgressMgr* pMgr, CDialog* pDlg);
	unsigned long m_pDoc; //points to the doc instance for which CCalc data 
					   //is held
	BOOL m_firstInit; //indicates that the inital call to CSerioDoc::
					  //OnNewDocument has been called
	BOOL changingOfTheGuard;//allows new Documents to be known
	//margin variables
	double m_cellFactor;
	double m_boostMargAmt;
	double m_boostMarg2ndaryAmt;//second channel for escaping 0" margin
	double m_frontM1Rate;//amount of adj caused by cell constrain
	double m_frontM2Rate;
	double m_backFrameDerivative;//new frame necessitated by GetMaxIncrease 
								//or by GetMaxDecrease
	double m_m3;//for backSide margin changes that happen incidentally
	double m_m4;//for backSide margin changes that happen incidentally
	BOOL m_backSideMargChangeAtForRect;//indicates that the m_m3 && m_m4 should be discounted
	//within CCalc::ChangeAssociatedMarginSizes()
	UINT m_maxCount;
	BOOL m_carryOutFrAdjOnly;//used to modify getMaxIncrease() & 
			//getMaxDecrease so that margin & page issues are ignored
	BOOL m_backsideArb;//indicates that margins can be re-adjusted 
	BOOL m_largeMarg1;//tells GetBacksideMargRate()how to refigure rates
	BOOL m_boostMarg;//signals infinite margin factor to boost aspect
	BOOL m_boostMarg2ndary;//signals infinite factor to change other m
	BOOL m_direct2ndaryBoost;//if 'FALSE': an unhitched marg forced boost
	BOOL m_untiedMgnIsAsset;//front mgn re-positioning possibly an asset
	BOOL m_frontMgnOptionsExist;//re-adjustments do not diminish results
	BOOL m_m1isHighYield;//tells which set of margins resizes efficiently
	BOOL m_uniCount;
	BOOL m_deriveCells;
	BOOL m_rangeInvolve;//count alterations and freqs can alter range
	BOOL m_intSync;//the number of steps per cell is not a fraction
	BOOL m_syncAll;
	//app-wide flags and variables
	BOOL m_registered;//printing is disabled if app was not registered
	//flow control switches
	BOOL m_noAccept; 
	BOOL m_countDenial;
	BOOL m_pageDenial;
	BOOL m_reOpt;
	BOOL m_flagReporting;//message box enable or disable
	BOOL m_fixRCellChange;
	BOOL m_mgnChange;
	BOOL m_change;

	BOOL m_derivePages; //MODE: derive page counts from layout
	BOOL m_case1;
	BOOL m_case2;
	BOOL m_case3;
	BOOL m_case4;
	BOOL m_case5;
	BOOL m_case8;
	BOOL m_case9;
	BOOL m_case10;
	BOOL m_case11;
	BOOL m_case12;
	BOOL m_case13;
	BOOL m_case14;
	BOOL m_case15;
	BOOL m_case16;
	BOOL m_case17;
	BOOL m_case18;
	BOOL m_case19;
	BOOL m_case20;
	BOOL m_case21;
	BOOL m_case22;
	BOOL m_case2M;
	BOOL m_case3M;
	BOOL m_case4M;
	BOOL m_case8M;
	BOOL m_case11M;
	BOOL m_case3C;
	BOOL m_case8C;
	BOOL m_case9C;
	BOOL m_case11C;
	BOOL m_case16C;
	BOOL m_case13FCR;
	BOOL m_case14FCR;

	CString cs1;
	CString cs2;
	CString cs3;
	CString cs4;
	CString cs5;
	CString cs6;
	CString cs7;
	CString cs8;
	CString cs9;
	CString cs10;
	CString cs11;
	CString cs12;
	CString cs13;
	CString cs14;
	CString cs15;
	CString cs16;
	CString cs17;
	CString cs18;
	CString cs19;
	CString cs20;
	CString cs21;
	CString cs22;
	CString GetAdvisoryStrings();
	int m_backFrCase;//m_case3(1),m_case11(2),m_case16(4)
	int m_xppi;
	int m_yppi;
	int m_colorMode;
	int m_calcIntent;
	int m_instigatorCount;
	int m_boostMargID;
	int m_boostMarg2ndaryID;
	int m_untiedMgnID;//front margin re-positioning possibly an asset 
	UINT m_totalCells;
	UINT m_totalPages;
	UINT m_pageCellsPerRow;
	UINT m_pageCellsPerCol ;
	UINT m_vCountC;
	UINT m_vCountB;
	UINT m_vCountCB;
	UINT m_hCountC;
	UINT m_hCountB;
	UINT m_hCountCB;
	UINT m_CountB;
	UINT m_CountCB;
	UINT m_rowFrom;
	UINT m_rowTo;
	UINT m_colFrom;
	UINT m_colTo;
	UINT m_blockFrom;
	UINT m_blockTo;
	UINT m_cBlockFrom;
	UINT m_cBlockTo;
	UINT m_colF;
	UINT m_colT;
	UINT m_rowF;
	UINT m_rowT;
	UINT m_blockF;
	UINT m_blockT;
	UINT m_cBlockF;
	UINT m_cBlockT;
	CRect m_drawRect;//drawing clue to FastForward() 
	CPinRect m_blockFrame;
	CPinRect m_cBlockFrame;
	double m_hSpace;
	double m_vSpace;
	double m_rem;
	double m_virtPageH;
	double m_virtPageW;
	double m_pageC;
	double m_pageH;
	double m_pageW;
	double m_cBlockH;
	double m_cBlockW;
	double m_blockH;
	double m_blockW;
	double m_rectH;
	double m_rectW;
	double m_topM;
	double m_botM;
	double m_leftM;
	double m_rightM;
	double m_colFreq;
	double m_rowFreq;
	double m_blkFreq;
	double m_cBlkFreq;
	BOOL m_cmyk;
	UINT m_bColsPer;
	UINT m_bRowsPer;
	UINT m_cBColsPer;
	UINT m_cBRowsPer;
	UINT m_colsPer;
	UINT m_rowsPer;
	UINT m_blockCount;
	UINT m_cBlockCount;
	UINT m_blockCols;
	UINT m_blockRows;
	UINT m_cBlockCols;
	UINT m_cBlockRows;
	double m_cBRowSpace;
	double m_cBColSpace;
	double m_bRowSpace;
	double m_bColSpace;
	double m_colSpace;
	double m_rowSpace;
	int rowTracker;
	int m_arker;
	double m_left;
	double m_top;
	double m_right;
	double m_bottom;
	double m_maxFactor;
	int m_cutOff;
	//POSITION pos;
	int outerBound;
	int innerBound;
	BOOL m_excludeDC; //"derive count" excluded
	BOOL m_layToCount;// "derive counts from layout" active
	BOOL m_cellR; //cell ratios are constrained indicator
	BOOL m_cellSqR; //cell ratios are square indicator
	BOOL m_colorRanLock; //prevents counts from changing allows reporting
	BOOL RequestRectAsp(BOOL w);
	BOOL RequestBlockAsp(BOOL w,int levels);
	BOOL RequestCBAsp(BOOL w,int levels);
	BOOL RequestPageAsp(BOOL w, int levels);
	BOOL ResolveRectAsp(BOOL w,double max);
	BOOL ResolveBlockAsp(BOOL w, int levels,double max);
	BOOL ResolveCBAsp(BOOL w, int levels, double max);
	BOOL ResolvePageAsp(BOOL w, int levels, double max);

	//assisting view in drawing
	UINT GetCurrentCount(int dimens, UINT page);
	void GetNextFrame(UINT oldHCountCB, UINT oldVCountCB);
	int GetIntervalCycle();
	UINT GetPageCount();
	void FastForward(UINT * count,UINT page);
	void PassInViewSize(CRect vSRect);
	void PassInScrollPosition(CPoint pt);
	BOOL IncrementCounters(UINT count,UINT pageNum);
	void InitializeCoords(UINT nPage);
	int TransformRect(int marker);
	void SetScale(int xppi, int yppi);
	double GetNextSpacingVal(BOOL bDim, int cycle);
	BOOL IsPageWSmaller(int nAspCode);
	BOOL IsPageHSmaller(int nAspCode);
	UINT GetPageCellCount(UINT nPage);
	int FeedCoords(UINT count, UINT page);

	//initializing calculator object
	BOOL LoadCalcMembers();
	BOOL LoadCalcMembers(CDocument* pDoc);
	CRegAspect* SetContext(int nCode, float fCode,
		BOOL lockState, int member,CRegAspect* entry);
	CRegAspect* m_reg[35];
	double DivideF(double dividend, double divisor);
	int GetSize(void);

	//Manipulations
	BOOL m_processAgain;
	CString GetResultingValueString(int i);
	CString GetAspectString(int i);
	CString GetInitialRequestString(int i);
	double InteriorAbilityForFrameChange(BOOL shrink,BOOL horiz);
	double AvailableCellChange(double factor,int index,int level,
		double maxFrAdj);
	//BOOL ValidateChangeSet(BOOL Cblock);
	BOOL UnderTheTableChange(float nuSize, int nID);
	BOOL UnderTheTableChange(UINT nuCount, int nID);
	void SaveAtStartComputeSettings();
	void RestoreAtStartComputeSettings();
	//margin manipulations
	BOOL RequestMargin(int index);
	double FindFullCircleMarginChange(int index,int sibID,int m3id,
									int m4id,BOOL m3Is,double change,
									double backFrChange,
									double frameChange,double * fFChange,
									double * bFChange,
									BOOL bigger,BOOL * bkFInverse,
									BOOL * frFInverse,
									double * nuM3,
									double * nuM4);
	void ClearMargCaseFlags();
	void ApplyMargCaseFlags();
	BOOL ReportMarginInvolvement(int mgnID);
	double GetOptimumMarginRate(int mID,double nuMargTotal,BOOL lck12,
								BOOL lck13,BOOL lck14,BOOL lck23,
								BOOL lck24,BOOL lck34);
	double GetBacksideMarginRate(int mID,double absoMax,double maxFrAdj,
								double * optRM1,double * optRM2,
								double * mR3,BOOL lck12,BOOL lck13,
								BOOL lck14,BOOL lck23,BOOL lck24,
								BOOL lck34);
	double GetCompatibleMargRate(double optR1,int mgnID,double * optR2,
									double maxR3,double maxR4,BOOL squeeze,
									BOOL lck13,BOOL lck14,BOOL lck12,
									BOOL lck23,BOOL lck24,double nuFrame,
									double nuMarg,double maxFrAdj);
	double ChangeAssociatedMarginSizes(BOOL horiz);	
	BOOL CheckMarginMobility(int mID, int qCode, BOOL squeeze);
	void CalcMarginSqueezeRates(double * optRM1,double * optRM2,int mID,
								int mID2,int mID3,int mID4,double absoMax,
								double maxFAdj, double nuM,double minBackM,
								BOOL squeeze, double nuFr,double nuP);
	void CalcMarginExpandRates(double * optRM1,double * optRM2,int mID,
								int mID2,int mID3,int mID4,double absoMax,
								double maxFAdj, double nuM,double minBackM,
								BOOL squeeze, double nuFr,double nuP);
	BOOL AscertainBoostValidity(int index,int sibID,int m3ID,int m4ID);

	//page count
	BOOL RequestPageCount();

	//higher-level management functions
	//if range=request(k): count=preserved(q), frequency=inconsequential(j)
	//if count=request(k): range=preserved(q), frequency=inconsequential(j)
	//if frequency=request(k): range=preserved(q), count=inconsequential(j)
	BOOL HandleHighLevelRequest(int index);//Port of entry 
											//for count,range,frequency	
	BOOL GetComplianceFromJack(CProgressMgr * mgr,CColorRange* r,
								  CCellCount * c,CFrequency * f);
	BOOL GetComplianceFromQueen(CProgressMgr * mgr,CColorRange* r,
								  CCellCount * c,CFrequency * f,CDialog* pDlg);
	//helper functions
	void AcceptChanges();
	void RejectChanges();
	BOOL AcceptAllChanges();

	BOOL DetermineInterlock(int m1,int m2);
	double ChangeAspectSize(double fact,int id,int level);
	double ChangeAspectSize(double fact,int id,int level,
		double maxFrAdj,double maxCFact,BOOL prelim,BOOL forC);
	double GetMaxIncrease(double fact, int id, int level,double maxFrAdj,
							 double maxCFact,BOOL prelim,BOOL forCell);
	double GetMaxDecrease(double fact, int id, int level,double maxFrAdj,
							 double maxCFact,BOOL prelim,BOOL forCell);
	int FigureWeldsAndRamifications(int level,int countID,BOOL suckOut,
									int startID, BOOL margInsuff,int id,
									BOOL fixMarg,BOOL fixMarg2,BOOL fix,
									double * nuAspect,double * factor,
									double * maxCellFact,
									BOOL * outSideWeld, BOOL minMax);
	
	//General request gatways
	BOOL RequestRect(int index,BOOL imperative);
	BOOL RequestCountChange(int index, BOOL fromMainLoop);
	BOOL RequestBlockCount(int index,int freqID,UINT range);
	BOOL AchieveCountChange(int id,unsigned long c);
	BOOL RequestCellCount(int index,int freqID,UINT range);
	BOOL RequestBlockFormatChange(int index);
	BOOL RequestCBlockFormatChange(int index);
	BOOL RequestFrequencyChange(int index);
	double ChangeAssociatedRectSize(double fact,int id,double deltaFr);

	//count adjustment & helper functions
	UINT GetMaxCountChange(BOOL incrs,int id,UINT nuCount,UINT count,
							UINT * r,double stepsPerCell,
							UINT maxLtdChange);
	BOOL AutoAdjustCount(unsigned long * change,BOOL incrs,
							  BOOL curAspectIsHoriz,unsigned long * cols,
							  unsigned long * rows);
	BOOL AutoAdjustCellCount(unsigned long * changeAmt,BOOL incrs,
							  BOOL curAspectIsHoriz,unsigned long * cols,
							  unsigned long * rows);
	BOOL TestRangeAdjustments(UINT nuCount,UINT *range,BOOL incrs,
									double test,BOOL botLock,BOOL topLock,
									UINT *toZ,UINT *toT);			
	BOOL TestContractibility(int level,BOOL horiz);
	BOOL TestExpandibility(int level,BOOL horiz);
	void LoadCountChangeRegistryValues(CRegistrar * regis);

	//high level processing control functions
	int RequestPageSizeChanges();
	int ProcessNewCountRequests();
	BOOL DirectChangeRequests(int i);
	BOOL ProcessChangeRequests();
	void ResetChangeRequestProcessingLoop();
	void ResetForReProcessing();
	void RetractInstigatingLine(int i);
	void SetProcessingOrder();
	BOOL InstigateChange(float val, int nIDCode);
	BOOL InstigateChange(UINT val, int nIDCode);
	BOOL InstigateFrequency(float val, int nIDCode);
	void ChangeLocksAndFlags(int nID,BOOL flag);

	//diagnostic functions
	void ClearCaseFlags();
	void ClearCellCaseFlags();
	void ApplyCellCaseFlags();
	void ApplyFreqCaseFlags();
	void ClearFreqCaseFlags();
	void AddOriginalFlags(BOOL flags [],int sz);
	void LegitimizeCurrentFlags();
	void StoreRestoreCurrentFlags(BOOL store,BOOL flags [],int sz);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalc)
	//}}AFX_VIRTUAL

// Implementation

	virtual ~CCalc();
protected:

	//low level utility functions
	int GetLevel(int id);
	int GetAssociatedSizeID(int id);
	int GetAssociatedCountID(int id);
	int GetEnclosedAspectID(int id);
	int GetEnclosingAspectID(int id);
	int GetSiblingMarginID(int id);
	void StoreOrRemoveNewRegValues(CRegAspect * pLines[],BOOL save);
	void StoreOrRestoreOriginalReqValues(CRegAspect * pLines[],BOOL store);

	int ModifyAspectIndex(int dex);
	// Generated message map functions
	//{{AFX_MSG(CCalc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// CRegAspect command target

class CRegAspect : public CCmdTarget
{
	DECLARE_DYNCREATE(CRegAspect)

	CRegAspect();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
		
	int m_nCode;	//resource symbol numeric ID
	int m_nType;	//count:0 or dimension:1
	int m_order;
	BOOL m_locked;
	BOOL m_horiz;
	BOOL m_fixedRatio;
	BOOL m_instigating;
	BOOL m_asking;
	BOOL m_alt;
	BOOL m_minSet;//explicit requests only, ie, m_instigating=1
	BOOL m_maxSet;//explicit requests only, ie, m_instigating=1
	BOOL m_minSetCur;
	BOOL m_maxSetCur;
	BOOL m_applied;//changes flaged m_instigating honored only if applied
	BOOL m_processed;
	BOOL m_accepted;
	BOOL m_histAlt;
	unsigned long m_nCount;
	unsigned long m_nNuCount;
	unsigned long m_nLastCount;
	unsigned long m_origReqCount;
	float m_nSize;
	float m_nConting;
	float m_nNuSize;
	float m_nLastSize;
	float m_origReqSize;
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegAspect)
	//}}AFX_VIRTUAL

// Implementation
	void AcceptValue(BOOL IsInt);
	virtual ~CRegAspect();
protected:
	// Generated message map functions
	//{{AFX_MSG(CRegAspect)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

