// Registrar.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CRegistrar command target
class CRegAspect;
class CBellows;

class CRegistrar : public CCmdTarget
{
	DECLARE_DYNCREATE(CRegistrar)

	CRegistrar();           // protected constructor used by dynamic creation

// Attributes
public:
	void ChangeAxisMode(BOOL horiz);
	void DestroyRegistry();
	int GetColorMode(){return m_colorMode;}
	int GetColumnID(){return m_colID;}
	UINT GetCurrentColumnCount();
	UINT GetCurrentCount();
	int GetRootHeightID(){return m_heightID;}
	int GetRootWidthID(){return m_widthID;}
	int GetRequestLevel(){return m_level;}
	CRegAspect * GetEntryLine(int entryID);
	UINT GetTotalPages(){return m_totalPages;}
	UINT GetCurrentRowCount();
	UINT GetRequestedCount();
	int GetRequestIndex() {return m_requestIndex;}
	int GetRowID(){return m_rowID;}
	void SetCurrentColumnCount(UINT cols);
	void SetCurrentCount(UINT nuCount);
	void SendPlugID(int plugID);
	void SetCurrentRowCount(UINT rows);
	void SetTotalPages(UINT total){m_totalPages = total;}
	void SetPageTotal(UINT total);
	void SetRequestInfo(CRegAspect *);
	void SetRowInfo(CRegAspect * rLine);
	void SetColumnInfo(CRegAspect * cLine);
	BOOL IsInitialRequestImpactHorizontal()
		{return m_requestImpactIsHorizontal;}
	BOOL IsRequestLevelOne();
	void InitializeRegistry(int index,unsigned long count,int colrMode,
		UINT * cols,UINT * rows,CBellows* bellows);

// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistrar)
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT* m_curRowCountPtr;
	UINT* m_curColCountPtr;
	UINT m_requestedCount;
	UINT m_totalPages;
	UINT m_curRows;
	UINT m_curColumns;
	int m_colorMode;
	CRegAspect * m_requestLine;
	BOOL m_requestImpactIsHorizontal;
	BOOL m_levelOneRequest;
	int m_curRequestID;
	CRegAspect* m_columnLine;
	CRegAspect * m_rowLine;
	int m_outLevel;
	int m_heightID;
	int m_widthID;
	int m_requestIndex;
	virtual ~CRegistrar();
	int m_colID;
	int m_rowID;
	int m_inID;
	int m_outID;
	int m_level;
	CRegAspect* m_inline;

	// Generated message map functions
	//{{AFX_MSG(CRegistrar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CBellows * m_bellows;
};

/////////////////////////////////////////////////////////////////////////////
