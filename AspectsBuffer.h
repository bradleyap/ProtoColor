//////////////////////////////////////////////////////////////////////////
//CAspectsBuffer

class CAspectsBuffer
{
public:
	CAspectsBuffer();

	double m_cellW;
	double m_cellH;
	double m_blockW;
	double m_blockH;
	double m_cBlockW;
	double m_cBlockH;
	unsigned long m_cols;
	unsigned long m_rows;
	unsigned long m_blocks;
	unsigned long m_cBlocks;
	double m_fRow;
	double m_fCol;
	double m_fBlk;
	double m_fCBlk;

	~CAspectsBuffer();
};