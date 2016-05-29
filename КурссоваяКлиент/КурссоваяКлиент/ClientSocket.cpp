// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include " урссова€ лиент.h"
#include "ClientSocket.h"
#include "MainDlg.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

void CClientSocket::SetParentDlg(CMainDlg * pDlg)
{
	m_Dlg = pDlg;
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket member functions


//void CClientSocket::OnReceive(int nErrorCode)
//{
//	wchar_t recstr[1000];
//	int r = Receive(recstr, 1000);
//	recstr[r] = '\0';
//	//m_Dlg->SetDlgItemText(IDC_STATIC, recstr);
//
//	CSocket::OnReceive(nErrorCode);
//}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	m_Dlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}

