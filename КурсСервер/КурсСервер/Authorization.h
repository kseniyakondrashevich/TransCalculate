#pragma once

#include "MainDlg.h"
#include "ServerSocket.h"

// CAuthorization dialog

class CServerSocket;

class CAuthorization : public CMainDlg
{
	DECLARE_DYNAMIC(CAuthorization)

public:
	CMainDlg *a_dlg;
	CAuthorization(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAuthorization();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

public:
	void AdminMenu();
	void UserMenu();
	virtual void OnReceive();
	virtual void OnSend(CString dataBuf);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
protected:


	DECLARE_MESSAGE_MAP()
};
