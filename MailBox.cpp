// MailBox.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailBox

IMPLEMENT_DYNCREATE(CMailBox, CCmdTarget)

CMailBox::CMailBox()
{
	m_messageCount = 0;
}

CMailBox::~CMailBox()
{
}


BEGIN_MESSAGE_MAP(CMailBox, CCmdTarget)
	//{{AFX_MSG_MAP(CMailBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailBox message handlers

BOOL CMailBox::CheckMessageBox(UINT msg, BOOL leaveMessage)
{
	//messages stored in a 'linked list'
	BOOL msgFound = FALSE;
	int it;
	CMessage* currentMessage = m_rootMessage;
	for(it=0;it<m_messageCount;it++)
	{
		if(currentMessage->GetMessage()==msg)
		{
			msgFound = TRUE;
			if(!leaveMessage)DeleteMessage(msg);
		}
		currentMessage = currentMessage->GetNextMessage();
	}
	return msgFound;
}

BOOL CMailBox::DepositMessage(UINT msg)
{
	BOOL cando = TRUE;//eventually to support runtime check for adequate mem
	if(!CheckMessageBox(msg,TRUE))
	{
		CMessage* nuMessage = CreateNewMessage(msg);
		if(m_messageCount==0)
		{
			m_lastMessage = nuMessage;
			m_rootMessage = m_lastMessage;
		}
		else
		{
			m_lastMessage->SetNextMessage(nuMessage);
			m_lastMessage = nuMessage;
		}
		m_messageCount++;
	}
	return cando;
}

CMessage* CMailBox::CreateNewMessage(UINT msg)
{
	CMessage* nuMessage = new CMessage();
	nuMessage->RecordMessage(msg);
	return nuMessage;
}

void CMailBox::DeleteMessage(UINT msg)
{
	//messages stored in a 'linked list'
	int it;
	CMessage* currentMessage = m_rootMessage;
	CMessage* previousMessage = m_rootMessage;
	CMessage* nextMessage;
	if(m_rootMessage!=m_lastMessage)nextMessage = m_rootMessage->GetNextMessage();

	for(it=0;it<m_messageCount;it++)
	{
		if(currentMessage->GetMessage()==msg)
		{
			if(m_lastMessage!=currentMessage)
			{
				previousMessage->SetNextMessage(nextMessage);
			}
			else m_lastMessage = previousMessage;
			currentMessage->DestroyMessage();
			m_messageCount--;
			break;
		}
		previousMessage = currentMessage;
		currentMessage = nextMessage;
		nextMessage = nextMessage->GetNextMessage();
	}
}

void CMailBox::DeleteMessage(CMessage* messObject,CMessage* previousMsgObject)
{
	m_messageCount--;
	if(m_messageCount>0)
	{

	}
	messObject->DestroyMessage();
}

void CMailBox::DestroyMailBox()
{
	if(m_messageCount!=0)DestroyAllMessages();
	delete this;
}

void CMailBox::DestroyAllMessages()
{
	int it;
	CMessage* currentMessage = m_rootMessage;
	CMessage* nextMessage;
	for(it=0;it<m_messageCount;it++)
	{
		if(currentMessage!=m_lastMessage)
			nextMessage = currentMessage->GetNextMessage();
		currentMessage->DestroyMessage();
		currentMessage = nextMessage;
	}
}
