// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "КурсСервер.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}


CServerSocket::~CServerSocket()
{
}

void CServerSocket::SetParentDlg(CMainDlg * pDlg)
{
	m_Dlg = pDlg;
}

void CServerSocket::OnReceive(int nErrorCode)
{
	m_Dlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}

void CServerSocket::OnAccept(int nErrorCode)
{
	m_Dlg->OnAccept();
	CSocket::OnAccept(nErrorCode);
}

