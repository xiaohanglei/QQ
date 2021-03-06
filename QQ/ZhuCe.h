#pragma once
#include "afxwin.h"


// ZhuCe 对话框

class ZhuCe : public CDialogEx
{
	DECLARE_DYNAMIC(ZhuCe)

public:
	ZhuCe(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ZhuCe();

// 对话框数据
	enum { IDD = IDD_ZhuCe };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedQuxiao();
	// 年份
	CComboBox m_year;
	virtual BOOL OnInitDialog();
	CComboBox m_month;
	CComboBox m_day;
	afx_msg void OnCbnSelchangeMonth();
	afx_msg void OnCbnSelchangeYear();
};
