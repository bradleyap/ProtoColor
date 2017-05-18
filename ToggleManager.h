// ToggleManager.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CToggleManager command target
//class CMaestro;
//extern class CMaestro;
class CToggleManager : public CCmdTarget
{
	DECLARE_DYNCREATE(CToggleManager)

	CToggleManager();           // protected constructor used by dynamic creation

// Attributes
public:
	void DestroyToggler();
	void Reset(UINT nuCount);
	void SetUpForCueMonitoring(UINT togVal,UINT stagVal);
	void SetUpForAutoTracking(UINT togVal,UINT togOffset,UINT stagVal,
		UINT stagOffsetVal);
	BOOL Report(UINT optionalCueValue);
	void SetStaggerInterval(UINT interVal);
	void SetToggleInterval(UINT togVal);
	void SetTrackBasis(int cueSource);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToggleManager)
	//}}AFX_VIRTUAL

// Implementation
	virtual ~CToggleManager();
protected:
	UINT m_count;

	// Generated message map functions
	//{{AFX_MSG(CToggleManager)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_toggleOffsetValue;
	int m_staggerOffsetValue;
	UINT m_lastTimeToggled;
	UINT m_lastTimeStaggered;
	UINT m_toggleInterval;
	UINT m_toggleCue;
	UINT m_staggerCue;
	UINT m_staggerInterval;
	UINT m_eventBasis;
};

/////////////////////////////////////////////////////////////////////////////
