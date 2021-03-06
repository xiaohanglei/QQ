// ZhuCe.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "ZhuCe.h"
#include "Tookit.h"
#include "MysqlOperator.h"
#include "afxdialogex.h"


// ZhuCe 对话框

IMPLEMENT_DYNAMIC(ZhuCe, CDialogEx)

ZhuCe::ZhuCe(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZhuCe::IDD, pParent)
{


}

ZhuCe::~ZhuCe()
{
}

void ZhuCe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, COMBO_Year, m_year);
	DDX_Control(pDX, COMBO_Month, m_month);
	DDX_Control(pDX, COMBO_Day, m_day);
}


BEGIN_MESSAGE_MAP(ZhuCe, CDialogEx)
	ON_BN_CLICKED(BUTTON_WanCheng, &ZhuCe::OnBnClickedButton2)
	ON_BN_CLICKED(BUTTON_QuXiao, &ZhuCe::OnBnClickedQuxiao)
	ON_CBN_SELCHANGE(COMBO_Month, &ZhuCe::OnCbnSelchangeMonth)
	ON_CBN_SELCHANGE(COMBO_Year, &ZhuCe::OnCbnSelchangeYear)
END_MESSAGE_MAP()


// ZhuCe 消息处理程序


void ZhuCe::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	
	//获取控件信息

	CString cstr_user;
	CString cstr_password;
	CString cstr_password_1;
	CString cstr_nicheng;
	

	CString cstr_year,cstr_month,cstr_day;

	this->GetDlgItemTextW(EDIT_Z_User, cstr_user);
	this->GetDlgItemTextW(EDIT_Z_Password, cstr_password);
	this->GetDlgItemTextW(EDIT_Z_Password1, cstr_password_1);
	this->GetDlgItemTextW(EDIT_Z_NiCheng, cstr_nicheng);


	int nIndex = m_year.GetCurSel();
	m_year.GetLBText(nIndex, cstr_year);

	nIndex = m_month.GetCurSel();
	m_month.GetLBText(nIndex, cstr_month);

	nIndex = m_day.GetCurSel();
	m_day.GetLBText(nIndex, cstr_day);


	char *p_user = CTookit::Zhongwen(cstr_user);
	char *p_password = CTookit::Zhongwen(cstr_password);
	char *p_nicheng = CTookit::Zhongwen(cstr_nicheng);
	char *p_year = CTookit::Zhongwen(cstr_year);
	char *p_month = CTookit::Zhongwen(cstr_month);
	char *p_day = CTookit::Zhongwen(cstr_day);


	//判断信息是否完整
	if (cstr_user == "" || cstr_password == "" || cstr_password_1 == "" 
		|| cstr_nicheng == "" || cstr_day == "" || cstr_year == "" || cstr_day == "")
	{
		MessageBox(L"请将信息填写完整！", L"提示");
	}
	else if (cstr_password != cstr_password_1)
	{
		MessageBox(L"两次密码不一致！", L"提示");
	}
	else
	{
		//将信息写入数据库
		CMysqlOperator *mysqlOperator = new CMysqlOperator();
		//连接数据库
		char *host = HOST;
		char* user = USER;
		char* port = PORT;
		char* passwd = PASSWD;
		char* dbname = DBNAME;    //这是数据库
		char* charset = CHARSET;
		char* Msg = "";

		if (mysqlOperator->ConnMysql(host, port, dbname, user, passwd, charset, Msg) == 0)
			//MessageBox(_T("连接数据库成功！", _T("提示!")));
			;
			
		else
			MessageBox(_T("连接数据库失败！", _T("提示!")));
			
		
		//检测用户名是否重复
		char SQL[2048] = { '0' };
		sprintf_s(SQL, "SELECT user from heihei where user = '%s'", p_user);

		string str = mysqlOperator->SelectData(SQL, 2, Msg);
		if (str.length() > 0)
		{
			MessageBox(L"注册失败，已存在该用户名", L"提示");
		}
		else
		{				
			//插入
			sprintf_s(SQL, "Insert into heihei(user,password,nicheng,date,state,ip) values('%s','%s','%s','%s-%s-%s',0,'0');"
				, p_user, p_password,p_nicheng,p_year,p_month,p_day);
			if (mysqlOperator->InsertData(SQL, Msg) == 0)
			{
				MessageBox(L"注册成功！", L"提示");
				CDialogEx::OnOK();
			}
			else
				MessageBox(L"注册失败！", L"提示");
		}
		mysqlOperator->CloseMysqlConn();			
	}
}

void ZhuCe::OnBnClickedQuxiao()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL ZhuCe::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	
	CString cstr;
	int n = 0;
	char buf[5] = {'0'};
	// TODO:  在此添加额外的初始化
	//年
	for (int i = 1930; i < 2030; i++)
	{
		cstr = itoa(i,buf,10);
		m_year.AddString(cstr);
	}
	m_year.SetCurSel(70);
	
	


	//月

	for (int i = 1; i < 13; i++)
	{
		//cstr = itoa(i, buf, 10);
		cstr.Format(_T("%d"), i);
		m_month.AddString(cstr);
	}
	
	m_month.SetCurSel(0);
	//日


	switch (1)
	{
		case 2:
		{
			break;
		}
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			n = 32;
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11:
		{
			n = 31;
			break;
		}
		default:
		{
			MessageBox(L"啧啧啧", L"提示");
			break;
		}

	}
	for (int i = 1; i < n; i++)
	{
		cstr = itoa(i, buf, 10);
		m_day.AddString(cstr);
	}
	m_day.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void ZhuCe::OnCbnSelchangeMonth()
{
	int n = 0;
	int nIndex = m_month.GetCurSel();
	CString cstr;
	m_month.GetLBText(nIndex, cstr);
	int mm = atoi(CTookit::Zhongwen(cstr));


	switch (mm)
	{
	case 2:
	{
		//判断是否为闰年 
		int nIndex = m_year.GetCurSel();
		m_year.GetLBText(nIndex, cstr);
		int yy = atoi(CTookit::Zhongwen(cstr));
		if ((yy % 4 == 0 && yy % 100 != 0 )|| yy % 400 == 0)
		{
			n = 30;
		}
		else
		{
			n = 29;
		}

		break;
	}
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		n = 32;
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11:
	{
		n = 31;
		break;
	}
	default:
	{
		MessageBox(L"啧啧啧", L"提示");
		break;
	}

	}
	m_day.ResetContent();//清空原来的列表项


	char buf[5] = { '0' };
	for (int i = 1; i < n; i++)
	{
		cstr = itoa(i, buf, 10);
		m_day.AddString(cstr);
	}
	m_day.SetCurSel(0);

	// TODO:  在此添加控件通知处理程序代码
}


void ZhuCe::OnCbnSelchangeYear()
{
	int n = 0;
	int nIndex = 0;
	nIndex = m_month.GetCurSel();
	CString cstr_month;
	m_month.GetLBText(nIndex, cstr_month);
	int mm = atoi(CTookit::Zhongwen(cstr_month));
	if (mm == 2)
	{
		int nIndex = m_year.GetCurSel();
		CString cstr;
		m_year.GetLBText(nIndex, cstr);
		int yy = atoi(CTookit::Zhongwen(cstr));
		if ((yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0)
		{
			n = 30;
		}
		else
		{
			n = 29;
		}

		m_day.ResetContent();//清空原来的列表项
		char buf[5] = { '0' };
		for (int i = 1; i < n; i++)
		{
			cstr = itoa(i, buf, 10);
			m_day.AddString(cstr);
		}
		m_day.SetCurSel(0);

	}
	// TODO:  在此添加控件通知处理程序代码
}
