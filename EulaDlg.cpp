// EulaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtoColor.h"
#include "EulaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEulaDlg dialog


CEulaDlg::CEulaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEulaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEulaDlg)
	m_text = _T("");
	//}}AFX_DATA_INIT
}


void CEulaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEulaDlg)
	DDX_Text(pDX, IDC_EULA_EDIT, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEulaDlg, CDialog)
	//{{AFX_MSG_MAP(CEulaDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEulaDlg message handlers

BOOL CEulaDlg::OnInitDialog() 
{
	CString lb = "lb";
	lb.SetAt(0,13);
	lb.SetAt(1,10);
	m_text = "ProtoColor 1.0 End User Liscence Agreement";
	m_text += lb;
	m_text += lb;
	m_text += "This End User Liscence Agreement shall govern the use of ProtoColor 1.0 (the \"Software\") by an individual end User.  Use of the Software will indicate that the User has agreed to the terms stated herein.  To any single User of this Software, a specifically defined right is granted under this Agreement for running said Software, and for generating physical output or digital files thereby.  The use of this Software during the Trial Period defined below is limited to rights and usage detailed for the Fully Enabled software described below with the following exceptions:";  
	m_text += lb;
	m_text += lb;
	m_text += "Fully Enabled versions of ProtoColor are not subject to a time period restriction whereas the Partially Enabled versions will be functional for a Trial Period consisting of 15 days.  Only Fully Enabled versions of this Software will be capable of unlimited print output and file output.";
	m_text += lb;
	m_text += lb;
	m_text += "Partially Enabled versions may be copied and distributed provided the following restrictions are observed:";
	m_text += lb;
	m_text += lb;
	m_text += "1)Copies must be made only for back-up or evaluation purposes.";
	m_text += lb;
	m_text += "2)Such copies must be made available free of charge.";
	m_text += lb;
	m_text += "3)'authorization codes' shall not be sold, distributed, or in any way made available with or without any version of this Software.";
	m_text += lb;
	m_text += lb;
	m_text += "A Trial Period is defined as 15 days from the date the Software is first run on the User's machine.  Some of the functionality of the Fully Enabled Software will be absent from the Partially Enabled version:  specifically, unlimited printable output and unlimited \"save\" operations.";
	m_text += lb;
	m_text += lb;
	m_text += "After the Trial Period the User agrees to either purchase an 'authorization code' to fully enable the Software or agrees to stop using the Software.";
	m_text += lb;
	m_text += lb;
	m_text += "Purchase of an 'authorization code'and the Registration of the User's identity with Highway 65 Software, Inc. entitles the User to use the Fully Enabled Software on any machine at one time. Running Fully Enabled Software on various machines cannot involve multiple users unless this is provided for specifically under a Commercial Agreement or under a separate End User Agreement for each other user.  If the Fully Enabled Software is migrated to a different machine, the User agrees to purchase another 'authorization code' or to cease using ProtoColor on any prior machines.  Migrating back and forth between machines is allowable provided this does not involve any User's not authorized as a sole User by a separate end user Agreement or authorized by a separate Commercial Agreement with Highway 65 Software, Inc. or Assigns.";
	m_text += lb;
	m_text += lb;
	m_text += "Under this Agreement, ownership of an original copy and any number of backup copies is conferred upon the User.  No authorization is granted by this Agreement to make copies of this Software for the purpose of profiting from distribution or from resale of this product.  Distribution and resale of the 'authorization code' is prohibited.";
	m_text += lb;
	m_text += lb;
	m_text += "The User is granted permission to port, send, tranmit or transport the individual chart configurations (ie,.SAC files) to as many output machines and systems as desired.";
	m_text += lb;
	m_text += lb;
	m_text += "No guarantee of support or technical help is contained in this Agreement nor implied by the purchase of an 'authorization code', other than the technical information contained in the \"User's.doc\" file if it is available.  Any information contained within \"User's.doc\" is provided \"as is\", without any representation being made as to the accuracy and helpfulness of its content.";
	m_text += lb;
	m_text += lb;
	m_text += "No authorization is granted by this agreement to allow remote operation of the Software via the world wide web or similar networks other than to transport chart configurations (ie .SAC files), derived by the Software locally, to remote locations for output and/or storage.";
	m_text += lb;
	m_text += lb;
	m_text += "No authorization is conferred herein to modify this Software to run as an application on a network or network server, whereby others may operate the software remotely.";
	m_text += lb;
	m_text += lb;
	m_text += "No warrantees are made or implied herein or by the sale of the Software, other than the following: If some Critical Aspect of the software is functionally defective AND if Highway 65 Software, Inc. is given notice within 10 business days of purchase of the 'authorization code' that such is the case, a complete refund of the purchase price shall be granted.  A defect shall be deemed Critical if it completely hinders the User from creating or printing a specific color chart AND if no simple workaround solution can be achieved.";
	m_text += lb;
	m_text += lb;
	m_text += "Highway 65 Software, Inc. shall in no wise be held responsible for damages arising out of the use or misuse of this software, beyond our previously stated refund policy.";
	m_text += lb;
	m_text += lb;
	m_text += "All literary references to the name \"ProtoColor\" shall be made only with the express written or oral consent of Highway 65 Software, Inc. or Assigns.";
	//m_text += lb;
	/*	

	CEdit* ed = (CEdit*)GetDlgItem(IDC_EULA_EDIT);
	ed->SetReadOnly();*/
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
