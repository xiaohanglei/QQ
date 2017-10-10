
// QQ.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "MysqlOperator.h"

// CQQApp: 
// 有关此类的实现，请参阅 QQ.cpp
//
//数据库部分
#define HOST "127.0.0.1"
#define USER "root";
#define PORT "3306";
#define PASSWD "";
#define DBNAME  "dddd";    //这是数据库
#define CHARSET  "utf8";

//服务器部分

#define IP "127.0.0.1"
#define PPORT 1986


class CQQApp : public CWinApp
{
public:
	CQQApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CQQApp theApp;