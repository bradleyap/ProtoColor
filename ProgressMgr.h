///////////////////////////////////////////////////////////////////
//CProgressMgr 
//class for tracking and managing process of requests in CCalc
//#include "ProgressBar.h"
class CProgressMgr
{
public:
	UINT GetQueensProgress();
	UINT GetKingsProgress();
	UINT GetKingsJourneyLeft();
	UINT GetQueensJourneyLeft();
	CMailBox* m_jacksMailBox;
	CMailBox * m_queensMailBox;
	CMailBox * m_kingsMailBox;
	CProgressMgr();
protected:
	//private data
	BOOL m_normal;
	BOOL m_forCells;
	BOOL m_greenLight;
	BOOL m_proceed;
	BOOL m_takeAHint;
	BOOL m_incr;
	BOOL m_kingIsCount;
	BOOL m_kingIsFrequency;
	BOOL m_kingIsRange;
	BOOL m_queenIsCount;
	BOOL m_queenIsFrequency;
	BOOL m_queenIsRange;
	BOOL m_jackIsCount;
	BOOL m_jackIsFrequency;
	BOOL m_jackIsRange;
	BOOL m_jackHasMail;
	BOOL m_queenHasMail;
	BOOL m_kingHasMail;
	BOOL m_startRangeLock;
	BOOL m_endRangeLock;
	BOOL m_frequencyLock;
	BOOL m_queenIsExhausted;
	BOOL m_kingHasMadeBid;
	BOOL m_intSync;
	UINT m_idealCount;
	UINT m_idealRange;
	UINT m_idealToZero;
	UINT m_idealToTop;
	UINT m_curCount;
	UINT m_curRange;
	UINT m_curToZero;
	UINT m_curToTop;
	UINT m_origCount;
	UINT m_origRange;
	UINT m_origToZero;
	UINT m_origToTop;
	UINT m_countMail;
	UINT m_startRangeMail;
	UINT m_endRangeMail;
	UINT m_failureNotices;//for diagnosing problems
	double m_idealFreq;
	double m_curFreq;
	double m_origFreq;
	double m_frequencyMail;
	int kingID;//requesting aspect
	int queenID;//preserved aspect
	int jackID;//least critical aspect
	int countID;
	int rangeID;
	int startID;
	int endID;
	int freqID;
	int m_calcIntent;
	unsigned long m_flags;
	//CProgressBar* m_progBar;
public:
	//Interface
	BOOL InitializeProgressMgr(int requestID,double dReqVal,UINT iReqVal,
					UINT range,UINT count,double freq,UINT botColor,
					UINT topColor,BOOL startLock,BOOL endLock);
	void RegisterFrequencyLock(BOOL freqLock)
		{m_frequencyLock = freqLock;}
	void LoadCountID(int ctDex)
	{
		if(m_kingIsCount)kingID = ctDex;
		if(m_queenIsCount)queenID = ctDex;
		if(m_jackIsCount)jackID = ctDex;
		countID = ctDex;
		if(ctDex==5 || ctDex==12)m_forCells = TRUE;
		else m_forCells = FALSE;
	}

	void LoadFreqID(int frqDex)
	{
		if(m_kingIsFrequency)kingID = frqDex;
		if(m_queenIsFrequency)queenID = frqDex;
		if(m_jackIsFrequency)jackID = frqDex;
		freqID = frqDex;
	}

	void LoadRangeID(int startDex, int endDex)
	{
		if(m_kingIsRange)kingID = startDex;
		if(m_queenIsRange)queenID = startDex;
		if(m_jackIsRange)jackID = startDex;
		rangeID = startDex;
		startID = startDex;
		endID = endDex;
	}

	BOOL IsKingCount(void){return m_kingIsCount;}
	BOOL IsKingRange(void){return m_kingIsRange;}
	BOOL IsKingFrequency(void){return m_kingIsFrequency;}
	BOOL ResetKing();
	BOOL HasKingMadeHisBid(void);
	void KingHasMadeHisBid(void){m_kingHasMadeBid=TRUE;}
	BOOL IsQueenCount(void){return m_queenIsCount;}
	BOOL IsQueenRange(void){return m_queenIsRange;}
	BOOL IsQueenFrequency(void){return m_queenIsFrequency;}
	BOOL IsQueenExhausted(void);
	void QueenIsExhausted(void){m_queenIsExhausted=TRUE;}
	BOOL IsQueenAuthorizedToAdapt();
	BOOL IsJackCount(void){return m_jackIsCount;}
	BOOL IsJackRange(void){return m_jackIsRange;}
	BOOL IsJackFrequency(void){return m_jackIsFrequency;}
	BOOL IsFrequencyLocked(){return m_frequencyLock;}
	BOOL IsForCells(void){return m_forCells;}
	BOOL IsThereAHint(int subjectID);
	BOOL DoesTheKingRequestAnIncrease();
	BOOL AssessNewValues();
	int GetKingID(void){return kingID;}
	int GetQueenID(void){return queenID;}
	int GetJackID(void){return jackID;}
	int GetCountID(void){return countID;}
	int GetRangeID(void){return rangeID;}
	int GetFreqID(void){return freqID;}
	int GetStartID(void){return startID;}
	int GetEndID(void){return endID;}
	int GetCalculationIntent(void){return m_calcIntent;}
	void SetCalculationIntent(int itnt){m_calcIntent = itnt;}
	UINT GetStartColor(void){return m_curToZero;}
	UINT GetEndColor(){return m_curToTop;}
	UINT GetRange(){return m_curRange;}
	UINT GetCount(){return m_curCount;}
	void NotifyOfConcern(UINT failCode);
	void DetermineNatureOfProblem();
	UINT DecipherFrequencyRequestNotices();
	UINT DecipherRangeRequestNotices();
	UINT DecipherCountRequestNotices();
	double TakeHint(int id);
	void SendHintToCount(UINT suggVal);
	void SendHintToFrequency(double suggVal);
	void SendHintToRange(UINT suggStartVal,UINT suggEndVal);
	double GetFrequency();
	unsigned long GetFlags(){return m_flags;}
	void SetNewCount(UINT count);
	BOOL SetNewStartColor(UINT clr);
	BOOL SetNewEndColor(UINT clr);
	BOOL AdjustRange();
	BOOL AdjustCount();
	BOOL AdjustFrequency();
	void SetNewFrequency(double freq);
	void RestoreOriginalValues();
	void ResetJackValues();
	void ResetQueenJackValues();
	void RestoreOrigValues();
	void SetFlag(int f);
	~CProgressMgr();
};