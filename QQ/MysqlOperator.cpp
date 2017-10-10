#include "StdAfx.h"

#include "MysqlOperator.h"
#include <iostream>

#include <string.h>

using namespace std;

CMysqlOperator::CMysqlOperator() {}

CMysqlOperator::~CMysqlOperator() {}

int CMysqlOperator::ConnMysql(char* host, char* port, char* Db, char* user, char* passwd, char* charset, char* Msg)
{
	if (mysql_init(&mysql) == NULL)
	{
		Msg = "inital mysql handle error!";
		return 1;
	}

	if (mysql_real_connect(&mysql, host, user, passwd, Db, 0, NULL, 0) == NULL)
	{
		Msg = "Failed to connect to database:Error!";
		return 1;
	}
	if (mysql_set_character_set(&mysql, "GBK") != 0)
	{
		Msg = "mysql_set_charater_set_Error!";
		return 1;
	}
	return 0;
}

string CMysqlOperator::SelectData(char* SQL, int Cnum, char* Msg, int x)
{

	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	char sql[2048];
	sprintf_s(sql, SQL);
	int rnum = 0;
	char rg = '\n'; //�и���
	char cg = '\t'; //�ֶθ���

	if (mysql_query(&mysql, sql) != 0)
	{
		Msg = "select ps_info_Error!";

		return "";
	}
	m_res = mysql_store_result(&mysql);

	if (m_res == NULL)
	{
		Msg = "select Error!";

		return "";
	}

	string str("");
	string nicheng("");//�ǳ�
	string ip("");//ip
	while (m_row = mysql_fetch_row(m_res))
	{
		for (int i = 0; i < Cnum; i++)
		{
			str += m_row[i];
			if (i == 2)
			{
				nicheng = m_row[i];
			}	
		}
		rnum++;
	}

	mysql_free_result(m_res);
	//str = nicheng;
	if (x == 1)
		return str;
	else
		return nicheng;
}


//��������
int CMysqlOperator::InsertData(char* SQL, char* Msg)
{
	char sql[2048];
	sprintf_s(sql, SQL);

	if (mysql_query(&mysql, sql) != 0)
	{
		Msg = "Insert Data Error!";
		return 1;
	}
	return 0;
}

//��������
int CMysqlOperator::UpdateData(char* SQL, char* Msg)
{
	char sql[2048];
	sprintf_s(sql, SQL);
	if (mysql_query(&mysql, sql) != 0)
	{
		Msg = "Update Data Error!";
		return 1;
	}
	return 0;
}

//ɾ������
int CMysqlOperator::DeleteData(char* SQL, char* Msg)
{
	char sql[2048];
	sprintf_s(sql, SQL);
	if (mysql_query(&mysql, sql) != 0)
	{
		Msg = "Delete Data Error!";
		return 1;
	}
	return 0;
}

//�ر����ݿ�����
void CMysqlOperator::CloseMysqlConn()
{
	mysql_close(&mysql);

}