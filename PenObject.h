// PenObject.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CPenObject command target

class CPenObject : public CCmdTarget
{
	DECLARE_DYNCREATE(CPenObject)

	CPenObject();           // protected constructor used by dynamic creation

// Attributes
public:
	BOOL SetColor(COLORREF c);
	BOOL SetWidth(int w);
	BOOL SetStyle(DWORD styl);

	LOGPEN penOb;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPenObject)
	//}}AFX_VIRTUAL
// Implementation
	virtual ~CPenObject();

protected:


	// Generated message map functions
	//{{AFX_MSG(CPenObject)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
