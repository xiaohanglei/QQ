#pragma once
#include "string"
#include "list"
#include "udp.h"
#include "afxwin.h"
using namespace std;

// ZhuJieMian 对话框

class ZhuJieMian : public CDialogEx
{
	DECLARE_DYNAMIC(ZhuJieMian)

public:
	ZhuJieMian(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ZhuJieMian();

public:
	 string str_name;
	void Set_name(string name);
// 对话框数据
	enum { IDD = IDD_ZhuJieMian };

	 list<string> m_listUser;//用户列表，

	 list<string> m_listMsg;//消息列表

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	static void Receive(void* p);
	static void ThreadUser(void *p);
	void updatemsg();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	 CListBox m_listUserCtrl;

	 afx_msg void OnClose();
	 afx_msg void OnLbnSelchangeZaixianliebiao();
	 afx_msg void OnBnClickedButton2();
	 afx_msg void OnBnClickedOk();
};
