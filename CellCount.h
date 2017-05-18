//CCellCount

class CCellCount
{
public:
	void ResetCount(CProgressMgr*);
	CCellCount();
protected:
	UINT m_curCount;
	UINT m_curHighCount;
	UINT m_curLowCount;
	UINT m_origCount;
	UINT m_idealCount;
	BOOL m_countIsKing;
	BOOL m_kingIncreases;
	BOOL m_bottomedOut;
	BOOL m_toppedOut;
	BOOL m_increase;
	BOOL m_countLock;
	BOOL m_increaseRelaxes;
	BOOL m_raiseCount;
public:
	UINT GetPheasibleCount(int index,CProgressMgr * mgr);
	void InitializeCellCount(UINT count,UINT iRequestVal,BOOL IsKing,
		BOOL kingIncrs,BOOL cLock);
	BOOL SetNewCount(UINT nuCount,CProgressMgr * mgr);
	BOOL RelaxKingCountRequest(CProgressMgr * mgr);
	BOOL ModifyQueenCount(CProgressMgr * mgr);
	BOOL AdjustJackCount(CProgressMgr * mgr);
	BOOL AdvanceToNextPreserveLayoutStep(CProgressMgr * mgr);
	BOOL AdvanceToNextRequestOnlyStep(CProgressMgr * mgr);
	~CCellCount();
};
