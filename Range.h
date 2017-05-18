class CRange
{
public:
	CRange();
protected:
	UINT m_curLowVal;
	UINT m_curHighVal;
	UINT m_curRangeVal;
public:
	void InitializeRange(UINT lv,UINT hv);
	UINT GetHighVal(void){return m_curHighVal;}
	UINT GetLowVal(void){return m_curLowVal;}
	UINT GetRange(void){return m_curRangeVal;}
	BOOL DoesValueFallWithinRange(UINT val);
	BOOL SetNewUpperBound(UINT val);
	BOOL SetNewLowerBound(UINT val);

	~CRange();
};
