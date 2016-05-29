
// MainDlg.cpp : файл реализации
//

#include <string>
#include "stdafx.h"
#include "КурсСервер.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "Authorization.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CMainDlg



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, connectStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATUS, connectStatus);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// обработчики сообщений CMainDlg

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	this->init();
	m_pListenSocket= new CServerSocket();
	m_pListenSocket->SetParentDlg(this);
	m_pConnectSocket->SetParentDlg(this);
	m_pListenSocket->Create(2000);
	if (m_pListenSocket->Listen() == TRUE)
	{
		UpdateData(TRUE);
		connectStatus = "Сервер готов к работе";
		UpdateData(FALSE);
	}
	else
	{
		MessageBox("Невозможно начать слушать этот порт",
			"Ошибка!", MB_OK | MB_ICONERROR);
		m_pListenSocket->Close();
		this->EndDialog(1);
	}

	hAuth = CreateEvent(NULL, FALSE, FALSE, "Authorization");

	/*dbUsers dbU;
	dbU.addUser("admin", "admin");
	dbU.addUser("111", "111");*/
	/*stringstream ss;
	ss << users.size();
	string str;
	ss >> str;
	connectStatus = (CString)str.c_str();*/
	/*for (it = users.begin(); it != users.end(); it++) {
	data = ((CString)(it->login.c_str())+"  "+ (CString)(it->password.c_str()));
	}
	UpdateData(FALSE);*/

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMainDlg::init() {
	m_pConnectSocket = new CServerSocket();
	m_pConnectSocket->SetParentDlg(this);
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMainDlg::OnAccept()
{
	CString strIP;
	UINT port;
	if (m_pListenSocket->Accept(*m_pConnectSocket))
	{
		m_pConnectSocket->GetSockName(strIP, port);
		UpdateData(TRUE);
		connectStatus = "Подключен клиент, IP :" + strIP;
		UpdateData(FALSE);
	}
	else
	{
		MessageBox("Ошибка подключения",
			"Ошибка!", MB_OK | MB_ICONERROR);
		m_pConnectSocket->Close();
	}
}

void CMainDlg::OnSend(CString dataBuf)
{

	MessageBox(dataBuf,
		"BUF!", MB_OK | MB_ICONERROR);
	char *Buf = new char[1025];
	int iLen;
	iLen = dataBuf.GetLength() + 1;
	strcpy_s(Buf, 1025, ((string)dataBuf).c_str());
	Buf[iLen] = '\0';
	m_pConnectSocket->Send(Buf, iLen);
}

void CMainDlg::OnReceive()
{
	char *pBuf = new char[256];
	int iLen;
	iLen = m_pConnectSocket->Receive(pBuf, 255);
	if (iLen == SOCKET_ERROR)
	{
		MessageBox("Данные не получены",
			"Ошибка!", MB_OK | MB_ICONERROR);
	}
	else
	{
		pBuf[iLen] = NULL;
		data = pBuf;
		delete pBuf;
		dbUsers _db;
		Authoriz(&_db);
	}
}

void CMainDlg::Authoriz(dbUsers *db)
{
	CAuthorization ath;
	db->SelectUsers();
	list<Users> users = db->GetUsers();
	list<Users>::iterator it;

	CString login = data.Left(data.Find(' '));
	CString password = data.Right((((string)data).length()) - data.Find(' ') - 1);

	for (it = users.begin(); it != users.end(); it++)
	{
		if (it->login == (string)login && it->password == (string)password)
		{
			if (it->login == ADMIN_NAME && it->password == ADMIN_NAME)
			{
				m_pConnectSocket->m_Dlg->OnSend("admin");
				ath.AdminMenu();
				return;
			}
			else
			{
				m_pConnectSocket->m_Dlg->OnSend("user");
				//ath.UserMenu();
				return;
			}
		}
	}
	m_pConnectSocket->m_Dlg->OnSend("guest");
}
