#include "sql/sql_base_cmd.h"

SqlBaseCmd::SqlBaseCmd()
{
	m_pmysql = NULL;
}

SqlBaseCmd::~SqlBaseCmd()
{

}

void SqlBaseCmd::Init(MYSQL* mysql)
{
	m_pmysql = mysql;
}

void SqlBaseCmd::Uninit()
{
	m_pmysql = NULL;
}

bool SqlBaseCmd::ExecuteSqlCmd(const char* psql)
{
	return  mysql_real_query(m_pmysql, psql, strlen(psql)) == 0 ;
}

int SqlBaseCmd::GetErrorCode()
{
	return (int)mysql_errno(m_pmysql);
}

const char* SqlBaseCmd::GetErrorDesc()
{
	return mysql_error(m_pmysql);
}

MYSQL_RES* SqlBaseCmd::GetExecuteResult(bool bMysqlUseResult)
{
	// ���� mysql_store_result / mysql_use_result ������
	// http://my.oschina.net/moooofly/blog/186456
	if (bMysqlUseResult)
	{
		// ÿ��ֵ����һ������
		return mysql_use_result(m_pmysql);
	}
	else
	{
		// �������н�����ͻ��ˣ�Ҳ����˵�ͻ�����Ҫ�����Լ������ݽṹȥ�洢��Щ������� ���ڴ����Ľϴ�
		return mysql_store_result(m_pmysql);
	}
}


