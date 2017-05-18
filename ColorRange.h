///////////////////////////////////////////////////////////////////
//CRange

class CColorRange
{
public:
	CColorRange();
protected:
	UINT m_curRange;
	UINT m_curStartColor;
	UINT m_curEndColor;
	UINT m_origStartColor;
	UINT m_origEndColor;
	UINT m_idealStartColor;
	UINT m_idealEndColor;
	BOOL m_rangeIsKing;
	BOOL m_increase;
	BOOL m_startLock;
	BOOL m_endLock;
	BOOL m_topsMove;
	BOOL m_rangeReqOffset;
	BOOL m_startChangeMoreDrastic;
	BOOL m_bottomedOut;
	BOOL m_normal;
	BOOL m_singleRequest;
	BOOL m_startColorIsFree;
public:
	void InitializeColorRange(UINT range,UINT iRequestBotVal,
		UINT iRequestTopVal,int whoIsKing,BOOL kingIncrs,UINT botColor,
		UINT topColor,BOOL startClrLock,BOOL endClrLock,CProgressMgr * mgr);
	UINT GetCurrentRange(){return m_curRange;}
	UINT GetPheasibleRange(int index,CProgressMgr * mgr);
	UINT GetOriginalRange();
	BOOL RelaxKingRangeRequest(CProgressMgr * mgr);
	BOOL ModifyQueenRange(CProgressMgr * mgr);
	BOOL AdjustJackRange(CProgressMgr * mgr);
	void ResetRange(CProgressMgr * mgr);
	BOOL SetNewStartColor(UINT nuClr,CProgressMgr * mgr);
	BOOL SetNewEndColor(UINT nuClr,CProgressMgr * mgr);
	UINT GetMaxRangeIncrease();
	UINT GetMaxRangeDecrease();
	BOOL AdvanceToNextRequestOnlyStep(CProgressMgr * mgr);
	BOOL FindPreserveLayoutValues(CProgressMgr * mgr);
	BOOL AdvanceToNextRangeAspectStep(CProgressMgr * mgr);


	~CColorRange();
};
