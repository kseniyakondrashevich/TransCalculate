
// MainDlg.h : ���� ���������
//

#pragma once
#include "����������.h"
#include "ServerSocket.h"
#include "dbUsers.h"

#define ADMIN_NAME "admin"

class CServerSocket;

// ���������� ���� CMainDlg
class CMainDlg : public CDialogEx
{
// ��������
public:
	CServerSocket *m_pConnectSocket;
	CServerSocket *m_pListenSocket;
	CMainDlg(CWnd* pParent = NULL);	// ����������� �����������
	void init();
// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	HANDLE hAuth;
	
	DECLARE_MESSAGE_MAP()
public:
	CString connectStatus;
	CString data;
	void OnAccept();
	virtual void OnSend(CString dataBuf);
	virtual void OnReceive();
	void Authoriz(dbUsers * db);
};
