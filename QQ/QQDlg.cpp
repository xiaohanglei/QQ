
// QQDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

CMysqlOperator *mysqlOperator = new CMysqlOperator();

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CQQDlg �Ի���



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


// CQQDlg ��Ϣ�������

BOOL CQQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//�������ݿ�
	//char* host = "127.0.0.1";
	char *host = HOST;
	char* user = USER;
	char* port = PORT;
	char* passwd = PASSWD;
	char* dbname = DBNAME;    //�������ݿ�
	char* charset = CHARSET;
	char* Msg = "";
	
	if (mysqlOperator->ConnMysql(host, port, dbname, user, passwd, charset, Msg) != 0)
	{
		MessageBox(_T("�������ݿ�ʧ�ܣ�", _T("��ʾ!")));

		AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CQQDlg::OnBnClickedDenglu()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������\

	//��ȡ�û���������

	CString cstr_user, cstr_password;
	this->GetDlgItemTextW(EDIT_User, cstr_user);
	this->GetDlgItemTextW(EDIT_Password, cstr_password);
	//ת���� char *

	char *p_user = CTookit::Zhongwen(cstr_user);
	char *p_password = CTookit::Zhongwen(cstr_password);

	//��ѯ���û����Ƿ������ݿ���

	char * Msg = "";
	char SQL[2048] = { '0' };

	sprintf_s(SQL, "SELECT * from heihei where user = '%s' and password = '%s'", p_user, p_password);

	string str1 = mysqlOperator->SelectData(SQL,4, Msg);
	string str;
	if (str1.length() > 0)
	{
		sprintf_s(SQL, "SELECT state from heihei where user = '%s'", p_user);
		string str2 = mysqlOperator->SelectData(SQL, 1, Msg,1);
		if (str2 == "0")//״̬Ϊ����
		{
			MessageBox(L"��½�ɹ���", L"��ʾ");

			//�����û������ݿ��б��Ϊ����
			sprintf_s(SQL, "UPDATE heihei SET state = 1 WHERE USER = '%s';", p_user);
			str = mysqlOperator->UpdateData(SQL, Msg);
			
			//��ip���

			char ip[32] = { '0' };
			GetLocalIP(ip);
			sprintf_s(SQL, "UPDATE heihei SET ip = '%s' WHERE USER = '%s';",ip, p_user);
			str = mysqlOperator->UpdateData(SQL, Msg);

			this->ShowWindow(SW_HIDE);

			ZhuJieMian dlg;

			dlg.Set_name(str1);//����û���
			//dlg.DoModal();
			INT_PTR nResponse = dlg.DoModal();
			if (nResponse == IDOK)
			{
				int i = 0;
				// TODO: �ڴ˷��ô����ʱ��
				//  ��ȷ�������رնԻ���Ĵ���
				//this->ShowWindow(SW_SHOW);
				//AfxGetMainWnd()->SendMessage(WM_CLOSE);
			}
			else if (nResponse == IDCANCEL)
			{
				// TODO: �ڴ˷��ô����ʱ��
				//  ��ȡ�������رնԻ���Ĵ���
				//this->ShowWindow(SW_SHOW);

				//�������ݿ⣬�����û���״̬����Ϊ����

				sprintf_s(SQL, "UPDATE heihei SET state = 0 WHERE USER = '%s';", p_user);
				str = mysqlOperator->UpdateData(SQL, Msg);
				//��IP����Ϊ0
				sprintf_s(SQL, "UPDATE heihei SET ip = 0 WHERE USER = '%s';", p_user);
				str = mysqlOperator->UpdateData(SQL, Msg);
				
			}
		}
		else//����Ϊ�Ѿ�����
		{
			MessageBox(L"���û��Ѿ���¼��", L"��ʾ");
		}
	}
	else
	{

		MessageBox(L"�û��������������", L"��ʾ");
	}
	mysqlOperator->CloseMysqlConn();
	delete mysqlOperator;
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}

bool CQQDlg::GetLocalIP(char* ip)
{
	//1.��ʼ��wsa  
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0)
	{
		return false;
	}
	//2.��ȡ������  
	char hostname[256];
	ret = gethostname(hostname, sizeof(hostname));
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	//3.��ȡ����ip  
	HOSTENT* host = gethostbyname(hostname);
	if (host == NULL)
	{
		return false;
	}
	//4.ת��Ϊchar*����������  
	strcpy(ip, inet_ntoa(*(in_addr*)*host->h_addr_list));
	return true;
}

void CQQDlg::OnBnClickedZhuce()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
			if (pMsg->wParam == VK_RETURN)//�����¼�Ϊ�س���ʱ
			{
				CQQDlg::OnBnClickedDenglu();//���ð�ť����
				return TRUE;
			}
	return CDialog::PreTranslateMessage(pMsg);
}