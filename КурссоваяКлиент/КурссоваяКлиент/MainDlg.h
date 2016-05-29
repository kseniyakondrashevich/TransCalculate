#pragma once

#include "afxwin.h"

// MainDlg.h : файл заголовка
//
#include <string>
#include "ClientSocket.h"
#include "Admin.h"

class CClientSocket;

// диалоговое окно CMainDlg
class CMainDlg : public CDialogEx
{
// Создание
public:
	CClientSocket m_pConnectSocket;
	CString data;
	CMainDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	HANDLE hAuth;
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnReceive();
	virtual void OnSend(CString dataBuf);
	afx_msg void OnBnClickedConnect();
	CString login;
	CString password;
};
