/////////////////////////////////////////////////////////////////////////////
// CPerformLog 

class CPerformLog : public CCmdTarget
{
	DECLARE_DYNCREATE(CPerformLog)

	CPerformLog();
//Attributes
public:

//Operations
public:
	void LogCount(UINT Count);
	void LogInt(UINT i);
	void RecordNewInputVariables(UINT ival,double dval);
	//return TRUE if new data is closer to ideal
	BOOL EnterNewResults(UINT ival,double dval);
	void InitializeLog(BOOL byInt,UINT iStart,UINT iIdeal,double dStart,
		double dIdeal);
	UINT GetIntOut();
	UINT GetIntIn();
	double GetPrecOut();
	double GetPrecIn();

//data
	BOOL gaugeByInt;
	BOOL gaugeByDouble;
	double dBest;//result
	double dBestInVal;
	double dNuInVal;
	double dIdeal;
	double dStart;
	UINT iBest;//result
	UINT iBestInVal;
	UINT iNuInVal;
	UINT iIdeal;
	UINT iStart;

//Implementation
	virtual ~CPerformLog();

protected:
	// Generated message map functions
	//{{AFX_MSG(CPerformLog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};