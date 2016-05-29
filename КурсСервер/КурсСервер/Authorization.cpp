// Authorization.cpp : implementation file
//

#include "stdafx.h"
#include "КурсСервер.h"
#include "Authorization.h"
#include "afxdialogex.h"


// CAuthorization dialog

IMPLEMENT_DYNAMIC(CAuthorization, CDialogEx)

CAuthorization::CAuthorization(CWnd* pParent /*=NULL*/)
{

}

CAuthorization::~CAuthorization()
{
}

void CAuthorization::AdminMenu()
{
	dbUsers *db = new dbUsers();
	db->SelectUsers();
	list<Users> users = db->GetUsers();
	list<Users>::iterator it;

	string ss;

	this->init();
	
	for (it = users.begin(); it != users.end(); it++)
	{
		ss.clear();
		ss = it->login + " " + it->password;
		MessageBox(ss.c_str(),
			"BUF!", MB_OK | MB_ICONERROR);
		m_pConnectSocket->m_Dlg->OnSend((CString)ss.c_str());
	}
}

void CAuthorization::UserMenu()
{
	//m_pConnectSocket.SetParentDlg(this);
	//m_pConnectSocket.m_Dlg->OnSend("2");

	SQLiteDatabase _db;
}

void CAuthorization::OnReceive()
{
	char *pBuf = new char[256];
	int iLen;
	iLen = m_pConnectSocket->Receive(pBuf, 255);
	pBuf[iLen] = NULL;
	data = pBuf;
	delete pBuf;
}

void CAuthorization::OnSend(CString dataBuf)
{
	char *Buf = new char[1025];
	int iLen;
	iLen = dataBuf.GetLength() + 1;
	strcpy_s(Buf, 1025, ((string)dataBuf).c_str());
	Buf[iLen] = '\0';
	m_pConnectSocket->Send(Buf, iLen);
}

void CAuthorization::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAuthorization, CDialogEx)
END_MESSAGE_MAP()


// CAuthorization message handlers
