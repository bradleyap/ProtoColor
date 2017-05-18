// Message.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessage

IMPLEMENT_DYNCREATE(CMessage, CCmdTarget)

CMessage::CMessage()
{
}

CMessage::~CMessage()
{
}


BEGIN_MESSAGE_MAP(CMessage, CCmdTarget)
	//{{AFX_MSG_MAP(CMessage)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessage message handlers

UINT CMessage::GetMessage()
{
	return m_message;
}

void CMessage::DestroyMessage()
{
	delete this;
}