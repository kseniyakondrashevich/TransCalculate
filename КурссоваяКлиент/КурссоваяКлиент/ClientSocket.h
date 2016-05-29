#pragma once

class CMainDlg;

class CClientSocket : public CSocket
{
public:
	CMainDlg *m_Dlg;
	CClientSocket();
	virtual void SetParentDlg(CMainDlg * pDlg);
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
};


