
// QQDlg.h : ͷ�ļ�
//

#pragma once


// CQQDlg �Ի���
class CQQDlg : public CDialogEx
{
// ����
public:
	CQQDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	BOOL PreTranslateMessage(MSG* pMsg);
	bool GetLocalIP(char* ip);
	void senduser();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDenglu();
	afx_msg void OnBnClickedZhuce();
};
