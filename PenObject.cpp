// PenObject.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "PenObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPenObject

IMPLEMENT_DYNCREATE(CPenObject, CCmdTarget)

CPenObject::CPenObject()
{

}

CPenObject::~CPenObject()
{
}


BEGIN_MESSAGE_MAP(CPenObject, CCmdTarget)
	//{{AFX_MSG_MAP(CPenObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPenObject message handlers

BOOL CPenObject::SetStyle(DWORD styl)
{
	penOb.lopnStyle = styl;
	return TRUE;
}

BOOL CPenObject::SetWidth(int w)
{
	POINT p = {w,0};
	penOb.lopnWidth = p;
	return TRUE;
}

BOOL CPenObject::SetColor(COLORREF c)
{
	penOb.lopnColor = c;
	return TRUE;
}
