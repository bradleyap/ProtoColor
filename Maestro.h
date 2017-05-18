// Maestro.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMaestro command target
class CRegistrar;

class CMaestro : public CCmdTarget
{
	DECLARE_DYNCREATE(CMaestro)

	CMaestro();    // protected constructor used by dynamic creation

// Attributes
public:
	int GetFailureCount(){return m_failureCount;}
	BOOL StoreValues(){return m_storeRegistryValues;}
	void SendPlugID();
	int GetAssociatedCountID(int id);
	BOOL TestForAnsweredRequest();
	BOOL Conduct();
	void InitializeMaestro(CRegistrar* reg);
	void ToggleAxisConcerns(void);
	void ToggleRequestSize();
	void DestroyMaestro();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrafficCop)
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_changeYetNeededBuf;
	UINT m_rowBuf;
	UINT m_colBuf;
	void ReloadPreviousValues();
	BOOL m_abortRequestRect;
	BOOL m_storeRegistryValues;
	virtual ~CMaestro();
	int InitializeRootID();
	void PrepareForNewMeasure();
	int m_plugID;
	void LoadRequestValues();
	void DetermineUltimateCountChange();
	UINT m_ultimateCountDesired;
	UINT m_ultimateCountChange;
	UINT m_changeYetNeeded;
	BOOL m_desiredCountIsIncrease;
	BOOL m_decreaseGiven;
	BOOL m_beginningOfBar;
	BOOL NextStepAutoAdjustCount();
	BOOL NextStepAutoAdjustCellCount();
	CRegistrar* m_regInfo;
	BOOL m_aTimeToGrow;
	BOOL m_pendingSpatialFormatLoaded;
	BOOL m_pendingCountLoaded;
	BOOL m_concernsAreHorizontal;
	int GetEnclosedAspectID(int id);
	int GetEnclosingAspectID(int nID);

	// Generated message map functions
	//{{AFX_MSG(CTrafficCop)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_failureCount;
	int m_baton;
};

/////////////////////////////////////////////////////////////////////////////
