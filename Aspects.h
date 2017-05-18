//CAspects/////////////////////////////////////////////////
class CAspects : public CObject
{
public:
	static CString m_Units;
	CAspects();
protected:
	DECLARE_SERIAL(CAspects);
public:
	CArray<float,float> m_asp;
	//CArray<int,int> m_spec;
	//Operations
public:
	virtual void Serialize(CArchive& ar);

};
