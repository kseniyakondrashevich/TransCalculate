// ControlUsers.cpp : implementation file
//

#include "stdafx.h"
#include "КурссоваяКлиент.h"
#include "ControlUsers.h"
#include "afxdialogex.h"
#include "MainDlg.h"
#include <list>


// CControlUsers dialog

IMPLEMENT_DYNAMIC(CControlUsers, CDialogEx)

CControlUsers::CControlUsers(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WORKS_USERS, pParent)
{

}

CControlUsers::~CControlUsers()
{
}

void CControlUsers::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, user_list);
}


BEGIN_MESSAGE_MAP(CControlUsers, CDialogEx)
END_MESSAGE_MAP()


// CControlUsers message handlers


BOOL CControlUsers::OnInitDialog()
{
	__super::OnInitDialog();
	_dlg->m_pConnectSocket.OnReceive(0);
	_dlg->MessageBox("AdminMenu",
		"Îøèáêà!", MB_OK | MB_ICONERROR);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
