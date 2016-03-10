#pragma once

#ifdef WIN32
#include <winsock2.h>
#endif
#include "mysql.h"
#include "thread.h"
#include "innerthread.h"
#include <string>

namespace lihj
{
	struct Sql_Paramer
	{
		std::string host;
		std::string user;
		std::string passwd;
		std::string dbname;
		int			port;

		Sql_Paramer()
		   : host(""),
			 user(""),
			 passwd(""),
			 dbname(""),
			 port(0)
		{}
	};
	class CSql_Helper
	{
	public:
		CSql_Helper();
		~CSql_Helper();

		bool Startup(const Sql_Paramer& sql_paramer);
		bool Shutdown();

		bool PushBack(const char* szSql, const int nSqlLength);
		bool PopFront();

		void ProcessFunc(void* pParamer);
	protected:
	private:
		MYSQL* m_sql_handler;
		Sql_Paramer m_sql_paramer;
		CInnerThread<CSql_Helper> m_sql_thread;
	};
}