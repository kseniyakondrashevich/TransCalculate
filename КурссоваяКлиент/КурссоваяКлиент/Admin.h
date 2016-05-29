#pragma once


// CAdmin dialog

class CAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CAdmin)

public:
	CAdmin(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdmin();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINMENU };
#endif
private:
	int flagAdmin;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedUserscontrol();
	afx_msg void OnBnClickedInsertvalues();
};
