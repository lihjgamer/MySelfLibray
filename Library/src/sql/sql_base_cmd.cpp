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
	// 介绍 mysql_store_result / mysql_use_result 的区别
	// http://my.oschina.net/moooofly/blog/186456
	if (bMysqlUseResult)
	{
		// 每次值检索一天数据
		return mysql_use_result(m_pmysql);
	}
	else
	{
		// 保存所有结果到客户端，也就是说客户端需要建立自己的数据结构去存储这些检索结果 （内存消耗较大）
		return mysql_store_result(m_pmysql);
	}
}


