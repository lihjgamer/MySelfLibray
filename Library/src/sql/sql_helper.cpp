#include "sql_helper.h"
#include <string.h>

namespace lihj
{

	CSql_Helper::CSql_Helper()
	{
		m_sql_handler = NULL;

		queue_head = NULL;
		queue_tail = NULL;

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

// 		mysql_query(m_sql_handler, "select * from rolesfirst");
// 		MYSQL_RES* pmysqlres = mysql_store_result(m_sql_handler);
// 
// 		MYSQL_FIELD* pfield = mysql_fetch_fields(pmysqlres);
// 		MYSQL_ROW mysqlrow = mysql_fetch_row(pmysqlres);
// 		MYSQL_ROW mysqlrow1 = mysql_fetch_row(pmysqlres);


		m_msgueue.clear();

		m_sql_pool.init();

		// 先不启动线程
		m_sql_thread.Register(this, &CSql_Helper::ProcessFunc, NULL);
		m_sql_thread.Init();


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
		mysql_thread_init();

		std::string fields;
		std::string row;
		for (;;)
		{
			// 
			if (queue_head == queue_tail
				&&queue_head == NULL)
			{
				Sleep(10);
				continue;
			}

			Sql_Msg* pSqlMsg = NULL;
			{
				CLock lock(m_mutex);
				pSqlMsg = queue_head;
				if (queue_tail == queue_head)
				{
					queue_head = queue_tail = NULL;
				}
			}

 			mysql_real_query(m_sql_handler, pSqlMsg->sqlrequest,pSqlMsg->sqllen);
 			printf("error msg  : %s\n", mysql_error(m_sql_handler));
 			printf("error code : %d\n", mysql_errno(m_sql_handler));

			MYSQL_RES* pRes = mysql_store_result(m_sql_handler);
			if (pRes == NULL)
			{
				continue;
			}

			int nFieldCount = mysql_field_count(m_sql_handler);
			MYSQL_FIELD* pField = mysql_fetch_fields(pRes);
			if (pField == NULL)
			{
				continue;
			}

			int nCurField = 0;
			while (nCurField < nFieldCount)
			{
				fields += pField[nCurField].org_name;
				fields += '\t';
				nCurField++;
			}

			// fields += '\n';
			printf("field : [ %s ]\n", fields.c_str());

			my_ulonglong rows_num = mysql_num_rows(pRes);

			MYSQL_ROW mysql_row;
			for (int i = 0; i < (int)rows_num; i ++)
			{
				row.clear();

				mysql_row = mysql_fetch_row(pRes);

				for (int j = 0; j < nFieldCount; j ++)
				{
					row += mysql_row[j];
					row += '\t';
				}
				printf("rows  : [ %s ]\n", row.c_str());
			}
			mysql_free_result(pRes);

			m_sql_pool.free(pSqlMsg);

			Sleep(10);
		}
	}

	bool CSql_Helper::PushMsgToQueue(const unsigned int nMark,const char* pSqlMsg, const int nSqlLen)
	{
		Sql_Msg* pMsg = (Sql_Msg*)m_sql_pool.alloc(sizeof(Sql_Msg)+nSqlLen);
		::memset(pMsg, 0, sizeof(Sql_Msg)+nSqlLen);

		pMsg->next = NULL;
		pMsg->nMark = nMark;
		pMsg->sqllen = nSqlLen;
		strcpy_s(pMsg->sqlrequest, pSqlMsg);

		// 消息队列为空
		if (queue_head == queue_tail
			&&queue_head == NULL)
		{
			CLock lock(m_mutex);
			queue_head = queue_tail = pMsg;
		}
		else
		{
			CLock lock(m_mutex);
			queue_tail->next = pMsg;
			queue_tail = pMsg;
		}
		return true;
	}


}

