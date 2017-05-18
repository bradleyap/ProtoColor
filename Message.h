// Message.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMessage command target

class CMessage : public CCmdTarget
{
	DECLARE_DYNCREATE(CMessage)

	CMessage();           // protected constructor used by dynamic creation

// Attributes
public:
	void SetNextMessage(CMessage* msg){m_nextMessage = msg;}
	CMessage* GetNextMessage(){return m_nextMessage;}
	void RecordMessage(UINT msg){m_message = msg;}
	UINT GetMessage();
	void DestroyMessage();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessage)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMessage* m_nextMessage;
	UINT m_message;
	virtual ~CMessage();

	// Generated message map functions
	//{{AFX_MSG(CMessage)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
