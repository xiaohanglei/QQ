
// QQ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "MysqlOperator.h"

// CQQApp: 
// �йش����ʵ�֣������ QQ.cpp
//
//���ݿⲿ��
#define HOST "127.0.0.1"
#define USER "root";
#define PORT "3306";
#define PASSWD "";
#define DBNAME  "dddd";    //�������ݿ�
#define CHARSET  "utf8";

//����������

#define IP "127.0.0.1"
#define PPORT 1986


class CQQApp : public CWinApp
{
public:
	CQQApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQQApp theApp;