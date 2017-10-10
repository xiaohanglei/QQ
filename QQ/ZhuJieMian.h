#pragma once
#include "string"
#include "list"
#include "udp.h"
#include "afxwin.h"
using namespace std;

// ZhuJieMian �Ի���

class ZhuJieMian : public CDialogEx
{
	DECLARE_DYNAMIC(ZhuJieMian)

public:
	ZhuJieMian(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ZhuJieMian();

public:
	 string str_name;
	void Set_name(string name);
// �Ի�������
	enum { IDD = IDD_ZhuJieMian };

	 list<string> m_listUser;//�û��б�

	 list<string> m_listMsg;//��Ϣ�б�

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
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
