// PinRect.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CPinRect 

class CPinRect : public CRect
{
//	DECLARE_DYNCREATE(CPinRect)
public:
	CPinRect();           // protected constructor used by dynamic creation

// Attributes

	double x;
	double y;
	//double x1;
	//double x2;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPinRect)
	//}}AFX_VIRTUAL
	virtual ~CPinRect();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPinRect)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

};

/////////////////////////////////////////////////////////////////////////////
