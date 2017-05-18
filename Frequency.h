//CFrequency

class CFrequency
{
public:
	void ResetFrequency(CProgressMgr * mgr);
	CFrequency();
protected:
	double m_curFrequency;
	double m_origFrequency;
	double m_idealFreq;
	double m_fractionalPart;
	BOOL m_frequencyIsKing;
	BOOL m_increase;
	BOOL m_incrsRelaxes;
	BOOL m_freqLock;
	BOOL m_toppedOut;
	BOOL m_bottomedOut;
	BOOL m_oddCall;

public:
	void InitializeFrequency(double freq,double dRequestVal,
									 BOOL whoIsKing,BOOL kingIncrs,
									 BOOL fLock);
	double GetPheasibleFrequency(int index,CProgressMgr *mgr);
	BOOL RelaxKingFrequencyRequest(CProgressMgr * mgr);
	BOOL ModifyQueenFrequency(CProgressMgr * mgr);
	BOOL AdjustJackFrequency(CProgressMgr * mgr);
	BOOL SetNewFrequency(double nuFreq,CProgressMgr * mgr);
	~CFrequency();
};



