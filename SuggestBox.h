//Class CSuggestBox

class CSuggestBox
{
	CSuggestBox();
protected:
	BOOL m_preserveLayout;
	CString m_cue;

public:
	BOOL GetCurrentPriority(){return m_preserveLayout;}

	~CSuggestBox();

};
