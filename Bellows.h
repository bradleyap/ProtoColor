// Bellows.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CBellows command target
class CMaestro;

class CBellows : public CCmdTarget
{
	DECLARE_DYNCREATE(CBellows)

	CBellows();           // protected constructor used by dynamic creation

// Attributes
public:
	void SetPlugID(int plugID);
	BOOL ExploreChartAspectResize();
	void DestroyBellows();
	void SetUpManipulations(CMaestro* maestro);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBellows)
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_requestForIncrease;
	BOOL PreImplantNewCount();
	int m_plugID;
	BOOL GetCueFromConductor();
	double GetTargetSize();
	double m_targetSize;
	BOOL m_cellLevelRequest;
	CMaestro* m_conductor;
	virtual ~CBellows();

	// Generated message map functions
	//{{AFX_MSG(CBellows)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
