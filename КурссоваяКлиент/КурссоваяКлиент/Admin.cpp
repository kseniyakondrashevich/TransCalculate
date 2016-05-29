// Admin.cpp : implementation file
//

#include "stdafx.h"
#include " урссова€ лиент.h"
#include "Admin.h"
#include "afxdialogex.h"
#include "ControlUsers.h"

// CAdmin dialog

IMPLEMENT_DYNAMIC(CAdmin, CDialogEx)

CAdmin::CAdmin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADMINMENU, pParent)
	, flagAdmin(0)
{
}

CAdmin::~CAdmin()
{
}

void CAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CAdmin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAdmin::OnBnClickedOk)
	ON_BN_CLICKED(IDC_USERSCONTROL, &CAdmin::OnBnClickedUserscontrol)
	ON_BN_CLICKED(IDC_INSERTVALUES, &CAdmin::OnBnClickedInsertvalues)
END_MESSAGE_MAP()


// CAdmin message handlers


void CAdmin::OnBnClickedOk()
{
	CAdmin *admin;
	if (!flagAdmin)
		return;
	switch (flagAdmin)
	{
	case 1:
		{
			this->EndDialog(1);
			CControlUsers cs;
			cs.c_dlg->DoModal();
		}
		break;
	case 2:
		break;
	}
	CDialogEx::OnOK();
}


void CAdmin::OnBnClickedUserscontrol()
{
	flagAdmin = 1;
}


void CAdmin::OnBnClickedInsertvalues()
{
	flagAdmin = 2;
}
