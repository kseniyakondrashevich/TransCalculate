
// MainDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "КурссоваяКлиент.h"
#include "MainDlg.h"
//#include "afxsock.h"
#include "afxdialogex.h"


using namespace std;

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
	, login(_T(""))
	, password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LOGIN, login);
	DDV_MaxChars(pDX, login, 20);
	DDX_Text(pDX, IDC_PASSWORD, password);
	DDV_MaxChars(pDX, password, 20);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CMainDlg::OnBnClickedConnect)
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
	m_pConnectSocket.SetParentDlg(this);
	m_pConnectSocket.Create();
	if (m_pConnectSocket.Connect("127.0.0.1", 2000))
	{
		/*MessageBox("Подключение установлено",
			"Подключено", MB_OK | MB_ICONINFORMATION);*/
	}
	else
	{
		MessageBox("Ошибка подключения",
			"Ошибка", MB_OK | MB_ICONERROR);
	}
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
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

void CMainDlg::OnReceive()
{
	data.Empty();
	char *pBuf = new char[1025];
	int iLen;
	iLen = m_pConnectSocket.Receive(pBuf, 1024);
	if (iLen == SOCKET_ERROR)
	{
		MessageBox("Данные не получены",
			"Ошибка!", MB_OK | MB_ICONERROR);
	}
	else
	{
		pBuf[iLen] = '\0';
		data = pBuf;

		if (data == "admin") {
			this->EndDialog(1);
			CAdmin admin;
			admin.DoModal();
		}
		else if (data == "user") {
			this->EndDialog(1);
		}
		else if (data == "guest") {
			MessageBox("Неверный логин или пароль",
				"Внимание", MB_OK | MB_ICONINFORMATION);
			UpdateData(TRUE);
			login = "";
			password = "";
			UpdateData(FALSE);
		}
	}

	delete pBuf;
}

void CMainDlg::OnSend(CString dataBuf)
{
	char *Buf = new char[1024];
	int iLen;
	iLen = dataBuf.GetLength()+1;
	strcpy_s(Buf, 1024, ((string)dataBuf).c_str());
	Buf[iLen] = '\0';
	m_pConnectSocket.Send(Buf, iLen);
}


void CMainDlg::OnBnClickedConnect()
{
	UpdateData(TRUE);
	CString ss = login + ' ' + password;
	UpdateData(FALSE);
	m_pConnectSocket.m_Dlg->OnSend(ss);
}
