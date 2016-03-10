#include "sql_helper.h"
#include <string.h>
namespace lihj
{

	CSql_Helper::CSql_Helper()
	{
		m_sql_handler = NULL;
	}

	CSql_Helper::~CSql_Helper()
	{

	}

	bool CSql_Helper::Startup(const Sql_Paramer& sql_paramer)
	{
		m_sql_handler = mysql_init(m_sql_handler);
		if (m_sql_handler == NULL)
		{
			printf("mysql_init error,error code : %s\n", mysql_error(m_sql_handler));
			return false;
		}

		MYSQL* pMysql = mysql_real_connect(m_sql_handler,
			sql_paramer.host.c_str(),
			sql_paramer.user.c_str(),
			sql_paramer.passwd.c_str(),
			sql_paramer.dbname.c_str(),
			sql_paramer.port,
			NULL, 0);
		if (pMysql != m_sql_handler)
		{
			printf("mysql_init error,error code : %s\n", mysql_error(m_sql_handler));
			return false;
		}
		//mysql_connect()

		m_sql_paramer = sql_paramer;

		mysql_query(m_sql_handler, "select * from rolesfirst");
		MYSQL_RES* pmysqlres = mysql_store_result(m_sql_handler);

		MYSQL_ROW mysqlrow = mysql_fetch_row(pmysqlres);
		
		m_sql_thread.Register(this, &CSql_Helper::ProcessFunc, NULL);
		m_sql_thread.Create();


		return true;
	}

	bool CSql_Helper::Shutdown()
	{
		mysql_server_end();
		mysql_close(m_sql_handler);
		return true;
	}


	void CSql_Helper::ProcessFunc(void* pParamer)
	{

	}




}

