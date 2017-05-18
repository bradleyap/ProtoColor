// MailBox.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMailBox command target

class CMailBox : public CCmdTarget
{
	DECLARE_DYNCREATE(CMailBox)

	CMailBox();           // protected constructor used by dynamic creation

// Attributes
public:
	void DestroyMailBox();
	BOOL DepositMessage(UINT msg);
	BOOL CheckMessageBox(UINT msg,BOOL leaveMessage);
	void DeleteMessage(CMessage* messObject,CMessage* previousMsgObject);
	void DeleteMessage(UINT msg);
private:
	void DestroyAllMessages();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailBox)
	//}}AFX_VIRTUAL

// Implementation
protected:
	unsigned long m_messageCount;
	CMessage* CreateNewMessage(UINT msg);
	CMessage* m_lastMessage;
	CMessage* m_rootMessage;
	virtual ~CMailBox();

	// Generated message map functions
	//{{AFX_MSG(CMailBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
