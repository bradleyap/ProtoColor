// BlockDragStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "SerioDoc.h"
//#include "BlockDragStatic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlockDragStatic

CBlockDragStatic::CBlockDragStatic()
{
	CSerioDoc* pDcmt;
	pDcmt = CSerioDoc::GetDoc();
	InitializeGraphicComponants(FALSE);
	m_calledByDlg = FALSE;
}

CBlockDragStatic::~CBlockDragStatic()
{
}


BEGIN_MESSAGE_MAP(CBlockDragStatic, CStatic)
	//{{AFX_MSG_MAP(CBlockDragStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlockDragStatic message handlers

void CBlockDragStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnLButtonDown(nFlags, point);
}

void CBlockDragStatic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnLButtonUp(nFlags, point);
}

void CBlockDragStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CStatic::OnMouseMove(nFlags, point);
}

void CBlockDragStatic::OnPaint() 
{
	CPaintDC dc(this);
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	CRect r;
	GetClientRect(&r);
	CBrush* olbr;
	olbr = dc.SelectObject(&brush);
	dc.Rectangle(r);
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	CPen* oldPen = dc.SelectObject(&pen);
	dc.Rectangle(m_BoundingRect);//

	//paint individual blocks
	CBrush brush2;
	brush2.CreateSolidBrush(RGB(255,255,255));
	CBrush* obs = dc.SelectObject(&brush2);
	obs->DeleteObject();


	UINT blockTotal;
	blockTotal = GetBlockTotal();
	//draw loop
	int count,x,y,x1,y1;
	for(count=0;count<blockTotal;count++)
	{
		int elem;
		for(elem=0;elem<4;elem++)
		{
			m_coords[elem] = GetCoordinate(elem,count);
		}
		x = m_coords[0];
		y = m_coords[1];
		x1 = m_coords[2];
		y1 = m_coords[3];
		dc.Rectangle(x,y,x1,y1);
	}
	// Do not call CStatic::OnPaint() for painting messages
	if(m_calledByDlg)
	{
		CString m_addStr;
		if(!extra) m_addStr = "Please add more columns or rows so that the format may accomodate the intended number of blocks.";
		if(extra)m_addStr = "The present format uses at least one too many columns or rows than is necessary to accomodate the number of blocks.  Please reduce the 'format-columns' or '-rows' to re-claim the space.";
		int response = ::MessageBox(
			NULL,m_addStr,"Prompt Box",MB_OKCANCEL);
		if(response==IDCANCEL)
		{
			CWnd* pwnd = GetParent();
			pwnd->SendMessage(WM_CLOSE,NULL,NULL);
		}
		m_calledByDlg = FALSE;
	}
}

extern CCalc scratchPad;

void CBlockDragStatic::InitializeGraphicComponants(BOOL internal)
{
	CRegAspect* line;
	CSerioDoc* p;
	p = CSerioDoc::GetDoc();
	BOOL cglomDlg;
	cglomDlg = p->m_dIfServCglom;
	m_colorMode = p->m_dColorMode;
	if(!internal && cglomDlg)
	{
		m_blockCols = p->m_dCBlockCols;
		m_blockRows = p->m_dCBlockRows;
		m_blockWidth = p->m_dCglomBlockWidth;
		m_blockHeight = p->m_dCglomBlockHeight;
		if(m_calledByDlg)
		{	
			line = ::scratchPad.m_reg[21];
			m_blockCols = line->m_nNuCount;
			line = ::scratchPad.m_reg[22];
			m_blockRows = line->m_nNuCount;
			line = ::scratchPad.m_reg[2];
			m_blockWidth = line->m_nNuSize;
			line = ::scratchPad.m_reg[9];
			m_blockHeight = line->m_nNuSize;
		}
	}
	if(!internal && !cglomDlg)
	{
		m_blockCols = p->m_dBlockCols;
		m_blockRows = p->m_dBlockRows;
		m_blockWidth = p->m_dBlockWidth;
		m_blockHeight = p->m_dBlockHeight;
		if(m_calledByDlg)
		{	
			line = ::scratchPad.m_reg[19];
			m_blockCols = line->m_nNuCount;
			line = ::scratchPad.m_reg[20];
			m_blockRows = line->m_nNuCount;
			line = ::scratchPad.m_reg[1];
			m_blockWidth = line->m_nNuSize;
			line = ::scratchPad.m_reg[8];
			m_blockHeight = line->m_nNuSize;
		}
	}

	m_bColCount = 1;

	CRect r1;
	r1.SetRect(0,0,293,163);

	float x,y;
	x = r1.Width();
	y = r1.Height();
	float halfx = x / 2;
	float halfy = y / 2;

	r1.InflateRect(-3,-3);
	x = r1.Width();
	y = r1.Height();
	

	float W,H,x2,y2;
	if(!internal)
	{
		if(m_colorMode==1 && cglomDlg)
		{
			m_W = p->m_dVirtualPageWidth;	//pageFrame
			m_H = p->m_dVirtualPageHeight;	//pageFrame
			if(m_calledByDlg)
			{
				line = ::scratchPad.m_reg[17];
				m_W = line->m_nNuSize;
				line = ::scratchPad.m_reg[18];
				m_H = line->m_nNuSize;
			}
		}
		if(m_colorMode==1 && !cglomDlg)
		{
			m_W = p->m_dCglomBlockWidth;
			m_H = p->m_dCglomBlockHeight;
			if(m_calledByDlg)
			{
				line = ::scratchPad.m_reg[2];
				m_W = line->m_nNuSize;
				line = ::scratchPad.m_reg[9];
				m_H = line->m_nNuSize;
			}
		}
		if(m_colorMode!=1)
		{
			m_W = p->m_dVirtualPageWidth;	//pageFrame
			m_H = p->m_dVirtualPageHeight;	//pageFrame
			if(m_calledByDlg)
			{
				line = ::scratchPad.m_reg[17];
				m_W = line->m_nNuSize;
				line = ::scratchPad.m_reg[18];
				m_H = line->m_nNuSize;
			}
		}
	}
	//see if widths can be used to derive altitude
	y2 = (x * m_H) / m_W; 	
	if(y2<=y) x2 = x; //derive y2 from x,cbH,cbW
	if(y2>y) //derive x2 from y,cbH,cbW
	{
		y2 = y;
		x2 = (y * m_W) / m_H;
	}
	int x3,y3,x4,y4;
	x3 = (int) (halfx - (x2 / 2));
	y3 = (int) (halfy - (y2 / 2));
	x4 = (int) (halfx + (x2 / 2));
	y4 = (int) (halfy + (y2 / 2));
	r1.SetRect(x3,y3,x4,y4);
	m_BoundingRect = r1;
	double div;
	if((m_blockRows - 1)>0) div = m_blockRows - 1;
	if((m_blockRows - 1)==0) div = 1;

	m_rowSpace = (m_H - (m_blockHeight * m_blockRows))
		/ div;
	if(m_rowSpace<.000001)m_rowSpace = 0.0;

	if((m_blockCols - 1)>0) div = m_blockCols - 1;
	if((m_blockCols - 1)==0) div = 1;

	m_colSpace = (m_W - (m_blockWidth * m_blockCols))
		/ div;
	if(m_colSpace<.000001)m_colSpace = 0.0;

}

UINT CBlockDragStatic::GetBlockTotal()
{
	UINT total = m_blockCols * m_blockRows;
	return total;
}

int CBlockDragStatic::GetCoordinate(int element, UINT block)
{
	int val;
	BOOL reset = FALSE, newRow = FALSE;
	if(element==0 && block==0)InitializeCoordinates();
	if((m_bColCount - 1)==m_blockCols) 
		newRow = TRUE;
	if(newRow && element==0 && block>0)
		reset = TRUE;
	if(reset)
	{
		IncreaseY1Y2();
		ResetX1X2();
	}
	val = TranslateVal(element);
	if(element==3 && !reset) IncreaseX1X2();
	return val;
}

void CBlockDragStatic::InitializeCoordinates()
{
	m_left = 0;
	m_top = 0;
	m_right = m_left + m_blockWidth;
	m_bottom = m_top + m_blockHeight;
}

void CBlockDragStatic::IncreaseY1Y2()
{
	m_top = m_bottom + m_rowSpace;
	m_bottom = m_top + m_blockHeight;
}

void CBlockDragStatic::IncreaseX1X2()
{
	m_left = m_right + m_colSpace;
	m_right = m_left + m_blockWidth;
	m_bColCount++;
}

void CBlockDragStatic::ResetX1X2()
{
	m_left = 0;
	m_right = m_left + m_blockWidth;
	m_bColCount = 1;
}

int CBlockDragStatic::TranslateVal(int element)
{
	double valdbl;
	int val;
	CPoint tl;
	tl = m_BoundingRect.TopLeft();
	int W = m_BoundingRect.Width();
	int H = m_BoundingRect.Height();
	int x = tl.x;
	int y = tl.y;
	if(element==0)
	{
		valdbl = (((double)W) * m_left) / m_W;
		val = ((int)valdbl) + x;
	}
	if(element==1)
	{
		valdbl = (((double)H) * m_top) / m_H;
		val = ((int)valdbl) + y;
	}
	if(element==2)
	{
		valdbl = (((double)W) * m_right) / m_W;
		val = ((int)valdbl) + x;
	}
	if(element==3)
	{
		valdbl = (((double)H) * m_bottom) / m_H;
		val = ((int)valdbl) + y;
	}

	return val;
}


/////////////////////////////////////////////////////////////////////
// Manipulations from dialog

extern CCalc scratchPad;

void CBlockDragStatic::Invalidate()
{
	InvalidateRect(NULL,FALSE);
}

BOOL CBlockDragStatic::ChangeFloatValue(float val, int item)
{	
	BOOL valid = TRUE;
	if(item==1) //frame height
	{	
		if(val<m_H)
		{
			double gauge = ((double)m_blockRows * m_blockHeight);
			if(m_blockRows==0)
			{
				AfxMessageBox("Invalid number of rows!");
				return FALSE;
			}
			if(gauge>val) m_blockHeight = val / m_blockRows;	
		}
		if(m_blockRows==1) m_blockHeight = val;
		m_H = (double)val;
	}
	if(item==2) //frame width
	{
		if(val<m_W)
		{
			double gauge = ((double)m_blockCols * m_blockWidth);
			if(m_blockCols==0)
			{
				AfxMessageBox("Invalid number of columns!");
				return FALSE;
			}
			if(gauge>val) m_blockWidth = val / m_blockCols;	
		}
		if(m_blockCols==1) m_blockWidth = val;
		m_W = (double)val;

	}
	if(item==3) //block height
	{
		if(val>m_blockHeight)
		{
			double gauge = ((double)m_blockRows * (double)val);
			if(gauge>m_H) m_H = (double)val * (double)m_blockRows;	
		}
		m_blockHeight = val;
		if(m_blockRows==1) m_H = m_blockHeight;
	
	}
	if(item==4) //block width
	{
		if(val>m_blockWidth)
		{
			double gauge = ((double)m_blockCols * (double)val);
			if(gauge>m_W) m_W = (double)val * (double)m_blockCols;	
		}
		m_blockWidth = val;
		if(m_blockCols==1) m_W = m_blockWidth;
		
	}
	//column spacing attempts to change blocks rather than frame
	if(item==5) 
			
	{
		if(m_blockCols==1) 
		{
			AfxMessageBox("Zero is the required spacing for a single-column layout");
			return FALSE;
		}
		if(val>m_colSpace)
		{ 
			double space = (((double)m_blockCols) 
				- 1) * (double)val;
			if(space>=(m_W - 1)) //bump frame
			{
				if(m_blockCols==0)
				{
					AfxMessageBox("Invalid number of columns!");
					return FALSE;
				}
				m_blockWidth = 1 / (double)m_blockCols;
				m_W = space + 1;
			}

			if(space<(m_W - 1)) //fit to frame
			{
				double solid = m_W - space;
				m_blockWidth = solid / (double)m_blockCols;
			}
			m_colSpace = val;
		}
		if(val<m_colSpace)
		{
			double space = (((double)m_blockCols) - 1) *
				(double)val;
			double solid = m_W - space;
			m_blockWidth = solid / (double)m_blockCols;
		}
		m_colSpace = val;
	}
	//row spacing attempts to change blocks rather than frame
	if(item==6) 
	{
		if(m_blockRows==1)
		{
			AfxMessageBox("Zero is the required spacing for a single-row layout");
			return FALSE;
		}
		if(val>m_rowSpace)
		{ 
			double space = (((double)m_blockRows) 
				- 1) * (double)val;
			if(space>=(m_H - 1)) //bump frame
			{
				if(m_blockRows==0)
				{
					AfxMessageBox("Invalid number of rows!");
					return FALSE;
				}
				m_blockHeight = 1 / (double)m_blockRows;
				m_H = space + 1;
			}

			if(space<(m_H - 1)) //fit to frame
			{
				double solid = m_H - space;
				m_blockHeight = solid / (double)m_blockRows;
			}
		}
		if(val<m_rowSpace)
		{
			double space = (((double)m_blockRows) - 1) *
				(double)val;
			double solid = m_H - space;
			m_blockHeight = solid / (double)m_blockRows;
		}
		m_rowSpace = val;
	}
	return valid;
}

BOOL CBlockDragStatic::ChangeIntValue(int val, int item)
{
	BOOL valid = TRUE;
	if(item==1) //block columns
	{
		if(val==0)
		{
			AfxMessageBox("Invalid number of columns!");
			return FALSE;
		}
		double solid = m_blockWidth * (double)m_blockCols;
		//double space = m_W - solid;

		m_blockWidth = solid / (double)val;

		if(val==1) { m_colSpace = 0; m_blockWidth = m_W;}
		m_blockCols = val;

	}
	if(item==2) //block rows
	{
		if(val==0)
		{
			AfxMessageBox("Invalid number of rows!");
			return FALSE;
		}
		double solid = m_blockHeight * (double)m_blockRows;
		//double space = m_H - solid;

		m_blockHeight = solid / (double)val;

		if(val==1){m_blockHeight = m_H; m_rowSpace = 0;}
		m_blockRows = val;
	}
	return valid;
}

void CBlockDragStatic::PassToCalc()
{
	int val = 0;
	BOOL valid = TRUE;
	valid = ::scratchPad.InstigateChange(m_blockRows,20);
	if(valid) m_blockWidth = val;
}

float CBlockDragStatic::GetFrameW()
{
	return (float) m_W;
}

float CBlockDragStatic::GetFrameH()
{
	return (float) m_H;
}

float CBlockDragStatic::GetBlockWidth()
{
	return (float) m_blockWidth;
}

float CBlockDragStatic::GetBlockHeight()
{
	return (float) m_blockHeight;
}

UINT CBlockDragStatic::GetBlockCols()
{
	return (UINT) m_blockCols;
}

UINT CBlockDragStatic::GetBlockRows()
{
	return (UINT)m_blockRows;
}

float CBlockDragStatic::GetColSpace()
{
	return m_colSpace;
}

float CBlockDragStatic::GetRowSpace()
{
	return m_rowSpace;
}

void CBlockDragStatic::SetBlockHeight(float bheight)
{
	m_blockHeight = bheight;
}

void CBlockDragStatic::SetBlockWidth(float bWidth)
{
	m_blockWidth = bWidth;
}

void CBlockDragStatic::SetCols(UINT nCol)
{
	m_blockCols = nCol;
}

void CBlockDragStatic::SetRows(UINT nRow)
{
	m_blockRows = nRow;
}

void CBlockDragStatic::SetFrameHeight(float h)
{
	m_H = h;
}

void CBlockDragStatic::SetFrameWidth(float w)
{
	m_W = w;
}

