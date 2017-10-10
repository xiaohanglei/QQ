#pragma once
#include "stdafx.h"
#include <windows.h>
#include<winsock.h>
#include<mysql.h>

#include<string>

using namespace std;
#pragma comment(lib,"libmysql.dll")

class CMysqlOperator
{
public:
	//±‰¡ø
	MYSQL mysql;

	CMysqlOperator();
	~CMysqlOperator();

	int ConnMysql(char* host, char* port, char* Db, char* user, char* passwd, char* charset, char* Msg);
	int DeleteData(char* SQL, char* Msg);

	string CMysqlOperator::SelectData(char* SQL, int Cnum, char* Msg,int x = 0);

	int CMysqlOperator::UpdateData(char* SQL, char* Msg);
	int CMysqlOperator::InsertData(char* SQL, char* Msg);


	void CloseMysqlConn();


};
