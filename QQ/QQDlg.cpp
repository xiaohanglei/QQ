
// QQDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "QQDlg.h"
//
#include "Tookit.h"
#include "ZhuCe.h"
#include "ZhuJieMian.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

CMysqlOperator *mysqlOperator = new CMysqlOperator();

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQQDlg 对话框



CQQDlg::CQQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQQDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CQQDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BUTTON_DengLu, &CQQDlg::OnBnClickedDenglu)
	ON_BN_CLICKED(BUTTON_ZhuCe, &CQQDlg::OnBnClickedZhuce)
END_MESSAGE_MAP()


// CQQDlg 消息处理程序

BOOL CQQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	//连接数据库
	//char* host = "127.0.0.1";
	char *host = HOST;
	char* user = USER;
	char* port = PORT;
	char* passwd = PASSWD;
	char* dbname = DBNAME;    //这是数据库
	char* charset = CHARSET;
	char* Msg = "";
	
	if (mysqlOperator->ConnMysql(host, port, dbname, user, passwd, charset, Msg) != 0)
	{
		MessageBox(_T("连接数据库失败！", _T("提示!")));

		AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CQQDlg::OnBnClickedDenglu()
{
	// TODO:  在此添加控件通知处理程序代码\

	//获取用户名和密码

	CString cstr_user, cstr_password;
	this->GetDlgItemTextW(EDIT_User, cstr_user);
	this->GetDlgItemTextW(EDIT_Password, cstr_password);
	//转换成 char *

	char *p_user = CTookit::Zhongwen(cstr_user);
	char *p_password = CTookit::Zhongwen(cstr_password);

	//查询该用户名是否在数据库中

	char * Msg = "";
	char SQL[2048] = { '0' };

	sprintf_s(SQL, "SELECT * from heihei where user = '%s' and password = '%s'", p_user, p_password);

	string str1 = mysqlOperator->SelectData(SQL,4, Msg);
	string str;
	if (str1.length() > 0)
	{
		sprintf_s(SQL, "SELECT state from heihei where user = '%s'", p_user);
		string str2 = mysqlOperator->SelectData(SQL, 1, Msg,1);
		if (str2 == "0")//状态为离线
		{
			MessageBox(L"登陆成功！", L"提示");

			//将该用户在数据库中标记为在线
			sprintf_s(SQL, "UPDATE heihei SET state = 1 WHERE USER = '%s';", p_user);
			str = mysqlOperator->UpdateData(SQL, Msg);
			
			//将ip填充

			char ip[32] = { '0' };
			GetLocalIP(ip);
			sprintf_s(SQL, "UPDATE heihei SET ip = '%s' WHERE USER = '%s';",ip, p_user);
			str = mysqlOperator->UpdateData(SQL, Msg);

			this->ShowWindow(SW_HIDE);

			ZhuJieMian dlg;

			dlg.Set_name(str1);//获得用户名
			//dlg.DoModal();
			INT_PTR nResponse = dlg.DoModal();
			if (nResponse == IDOK)
			{
				int i = 0;
				// TODO: 在此放置处理何时用
				//  “确定”来关闭对话框的代码
				//this->ShowWindow(SW_SHOW);
				//AfxGetMainWnd()->SendMessage(WM_CLOSE);
			}
			else if (nResponse == IDCANCEL)
			{
				// TODO: 在此放置处理何时用
				//  “取消”来关闭对话框的代码
				//this->ShowWindow(SW_SHOW);

				//连接数据库，将该用户的状态设置为离线

				sprintf_s(SQL, "UPDATE heihei SET state = 0 WHERE USER = '%s';", p_user);
				str = mysqlOperator->UpdateData(SQL, Msg);
				//将IP设置为0
				sprintf_s(SQL, "UPDATE heihei SET ip = 0 WHERE USER = '%s';", p_user);
				str = mysqlOperator->UpdateData(SQL, Msg);
				
			}
		}
		else//否者为已经在线
		{
			MessageBox(L"该用户已经登录！", L"提示");
		}
	}
	else
	{

		MessageBox(L"用户名或者密码错误！", L"提示");
	}
	mysqlOperator->CloseMysqlConn();
	delete mysqlOperator;
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

bool CQQDlg::GetLocalIP(char* ip)
{
	//1.初始化wsa  
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		return false;
	}
	//2.获取主机名  
	char hostname[256];
	ret = gethostname(hostname, sizeof(hostname));
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	//3.获取主机ip  
	HOSTENT* host = gethostbyname(hostname);
	if (host == NULL)
	{
		return false;
	}
	//4.转化为char*并拷贝返回  
	strcpy(ip, inet_ntoa(*(in_addr*)*host->h_addr_list));
	return true;
}

void CQQDlg::OnBnClickedZhuce()
{
	// TODO:  在此添加控件通知处理程序代码

	ZhuCe dlg;
	dlg.DoModal();
}

void senduser()
{

}

BOOL CQQDlg::PreTranslateMessage(MSG* pMsg)
{
	//if (!AfxGetMainWnd()->GetFocus())
	//{
	//	AfxGetMainWnd()->SetFocus();
	//}
			if (pMsg->wParam == VK_RETURN)//当按下键为回车键时
			{
				CQQDlg::OnBnClickedDenglu();//调用按钮函数
				return TRUE;
			}
	return CDialog::PreTranslateMessage(pMsg);
}