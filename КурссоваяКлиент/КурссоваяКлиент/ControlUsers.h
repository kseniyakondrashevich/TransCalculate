#pragma once

#include "MainDlg.h"
#include "afxwin.h"
// CControlUsers dialog
class CMainDlg;

class CControlUsers : public CDialogEx, public CMainDlg
{
	DECLARE_DYNAMIC(CControlUsers)

public:
	CMainDlg *_dlg;
	CControlUsers(CWnd* pParent = NULL);   // standard constructor
	virtual ~CControlUsers();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORKS_USERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMainDlg *c_dlg;
	virtual BOOL OnInitDialog();
	CListBox user_list;

};
