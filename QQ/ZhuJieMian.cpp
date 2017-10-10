// ZhuJieMian.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "ZhuJieMian.h"
#include "Tookit.h"
#include "afxdialogex.h"


// ZhuJieMian 对话框

IMPLEMENT_DYNAMIC(ZhuJieMian, CDialogEx)

SOCKET g_clientSock = 0;	//和服务器连接的SOCKET
CMysqlOperator *mysqlOperator2 = new CMysqlOperator();
HANDLE Thread_1;
DWORD pp = NULL;

ZhuJieMian::ZhuJieMian(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZhuJieMian::IDD, pParent)
{

}

ZhuJieMian::~ZhuJieMian()
{
	
}

void ZhuJieMian::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LIST_ZaiXianLieBiao, m_listUserCtrl);
}


void ZhuJieMian::Set_name(string name)
{
	str_name = name;
}

BEGIN_MESSAGE_MAP(ZhuJieMian, CDialogEx)
	ON_WM_CLOSE()
	ON_LBN_SELCHANGE(LIST_ZaiXianLieBiao, &ZhuJieMian::OnLbnSelchangeZaixianliebiao)
	ON_BN_CLICKED(IDC_BUTTON2, &ZhuJieMian::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &ZhuJieMian::OnBnClickedOk)
END_MESSAGE_MAP()


// ZhuJieMian 消息处理程序


BOOL ZhuJieMian::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);

	CString cstr_name(str_name.c_str());
	this->SetDlgItemTextW(STATIC_NiCheng, cstr_name);

	// TODO:  在此添加额外的初始化



	//============================================连接数据库
	//char* host = "127.0.0.1";
	char *host = HOST;
	char* user = USER;
	char* port = PORT;
	char* passwd = PASSWD;
	char* dbname = DBNAME;    //这是数据库
	char* charset = CHARSET;
	char* Msg = "";

	if (mysqlOperator2->ConnMysql(host, port, dbname, user, passwd, charset, Msg) != 0)
	{
		MessageBox(_T("连接数据库失败！", _T("提示!")));

		AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}
	//============================================连接数据库

	//启动 更新在线用户列表的线程
	_beginthread(&ZhuJieMian::ThreadUser, 0, this);

	//启动 接收消息的线程
	_beginthread(&ZhuJieMian::Receive, 0, this);
	
	//Thread_1 = CreateThread(NULL, 0, ThreadUser,this,0,&pp);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void ZhuJieMian::Receive(void* p)
{
	ZhuJieMian * a = (ZhuJieMian *)p;

	myudp udp;
	char srcip[50] = { 0 };
	char buf[1024] = { 0 };
	if (udp.socket_bind(8080) > -1)
	{
		while (1)
		{
			memset(buf, 0, sizeof(buf));
			memset(srcip, 0, sizeof(srcip));
			int n = udp.socket_recv(buf, sizeof(buf), srcip);
			if (n == -1)
			{
				_endthread();
				return;
			}
			//接收成功以后
			buf[n] = '\0';


			//查找ip对应的昵称
			char * Msg1 = "";
			char SQL[2048] = { '0' };

			sprintf_s(SQL, "SELECT nicheng from heihei where ip = '%s'", srcip);
			string src_ip = mysqlOperator2->SelectData(SQL, 1, Msg1, 1);//获得聊天对象的ip
			//string src_ip = srcip;

			string recv_msg(buf);
			string r_msg = src_ip + "   对你说：  ";
			r_msg = r_msg + recv_msg;
			a->m_listMsg.push_back(r_msg);

			CEdit* pedit = (CEdit*)a->GetDlgItem(EDIT_XiaoXiJiLu);
			pedit->LineScroll(pedit->GetLineCount());
			a->updatemsg();
		}
	}
	return;
}

void ZhuJieMian::ThreadUser(void *p)
{
	ZhuJieMian * a = (ZhuJieMian *)p;
	
	char SQL[2048] = { '0' };
	char* Msg = "";
	int i = 0;
	//查询在线人数
	while (true)
	{
		//更新之前，先清空在线用户列表里边的用户

		a->m_listUserCtrl.ResetContent();
		sprintf_s(SQL, "SELECT COUNT(USER) AS 在线人数 FROM heihei WHERE state = 1;");
		string str ;
		str = mysqlOperator2->SelectData(SQL, 1, Msg, 1);
		int n = atoi(str.c_str());
		
		//将在线用户的昵称显示在列表中
		for (int i = 0; i < n; i++)
		{
			sprintf_s(SQL, "SELECT nicheng FROM heihei WHERE state = 1 LIMIT %d,1;", i);

			//str = "测试";

			str = mysqlOperator2->SelectData(SQL, 1, Msg, 1);

			a->m_listUser.push_back(str);//将该用户列表压入栈中

			CString cstr_listuser(str.c_str());
			CString cstr_name(a->str_name.c_str());
			if (cstr_listuser != cstr_name)
			{
				a->m_listUserCtrl.AddString(cstr_listuser);
			}
			
		}

		Sleep(3000);
		//break;
	}
	_endthread();
}

void ZhuJieMian::updatemsg()
{
	if (this->m_listMsg.size() > 200)
	{
		this->m_listMsg.pop_front();
	}
	string strText;
	for (list<string>::iterator it = this->m_listMsg.begin();
		it != this->m_listMsg.end(); it++)
	{
		strText = strText + (*it) + "\r\n";
	}
	CString strt(strText.c_str());
	this->SetDlgItemText(EDIT_XiaoXiJiLu, strt);
}

void ZhuJieMian::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	MessageBox(_T("要退出咯！", _T("提示!")));


	delete mysqlOperator2;

	CDialogEx::OnClose();
}

void ZhuJieMian::OnLbnSelchangeZaixianliebiao()
{
	//this->SetDlgItemTextW(STATIC_LiaoTianDuiXiang, L"测试");
	int n = 0;
	int nIndex = m_listUserCtrl.GetCurSel();
	if (nIndex != -1)
	{
		CString cstr;
		m_listUserCtrl.GetText(nIndex, cstr);
		this->SetDlgItemTextW(STATIC_LiaoTianDuiXiang, cstr);
	}
	else
	{
		;
	}
	// TODO:  在此添加控件通知处理程序代码
}

void ZhuJieMian::OnBnClickedButton2()
{
	CString LiaoTianDuiXiang;
	CString Msg;
	CString send;
	this->GetDlgItemTextW(STATIC_LiaoTianDuiXiang, LiaoTianDuiXiang);

	if (LiaoTianDuiXiang == "")
	{
		MessageBox(_T("你还没有选择聊天对象，请在右侧列表中选择一个聊天对象！", _T("提示!")));
		return;
	}
	this->GetDlgItemTextW(EDIT_Msg, Msg);

	//确定发送对象并查找相应的IP地址
	
	char *send_user = CTookit::Zhongwen(LiaoTianDuiXiang);

	char * Msg1 = "";
	char SQL[2048] = { '0' };

	sprintf_s(SQL, "SELECT ip from heihei where nicheng = '%s'", send_user);
	string str2 = mysqlOperator2->SelectData(SQL, 1, Msg1, 1);//获得聊天对象的ip
	char ip[32] = { '0' };
	strcpy(ip, str2.c_str());

	char *p_msg = CTookit::Zhongwen(Msg);

	//执行发送函数

	myudp udp;
	//char a[1024] = { '0' }; 
	
	udp.socket_send(ip, p_msg,strlen(p_msg));

	send = L"你对  （" + LiaoTianDuiXiang + L"）  说：" + Msg;
	string st;
	st = CTookit::Zhongwen(send);
	m_listMsg.push_back(st);
	updatemsg();
	this->SetDlgItemTextW(EDIT_Msg, L"");//发送成功以后，将输入框清空;

	// TODO:  在此添加控件通知处理程序代码
}
void ZhuJieMian::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	OnBnClickedButton2();
}
