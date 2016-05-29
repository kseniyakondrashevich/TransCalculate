#pragma once

// CServerSocket command target
#include "MainDlg.h"

class CMainDlg;

class CServerSocket : public CSocket
{
public:
	CMainDlg *m_Dlg;
	CServerSocket();;
	virtual ~CServerSocket();;
	void SetParentDlg(CMainDlg * pDlg);
	void OnReceive(int nErrorCode);
	void OnAccept(int nErrorCode);
};




