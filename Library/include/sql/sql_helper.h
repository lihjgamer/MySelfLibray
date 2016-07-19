#pragma once

#ifdef WIN32
#include <winsock2.h>
#endif
#include <string>
#include <list>
#include <vector>

#include "mysql.h"
#include "thread/thread.h"
#include "thread/innerthread.h"
#include "thread/mutex.h"
#include "mem_pool/mem_pool.h"
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

		bool PushMsgToQueue(const unsigned int nMark, const char* pSqlMsg, const int nSqlLen);

		void ProcessFunc(void* pParamer);

	protected:


	private:
		typedef struct Sql_Msg 
		{
			Sql_Msg* next;
			unsigned int nMark;
			unsigned short int sqllen;
			char         sqlrequest[1];

			Sql_Msg()
				: next(NULL),
				  nMark(0),
				  sqllen(0)
			{
				sqlrequest[0] = '\0';
			}
		}Sql_Msg;

		typedef std::list<std::string> msgqueue;

		Sql_Msg* queue_head;
		Sql_Msg* queue_tail;


		CMemPool m_sql_pool;

		MYSQL*						m_sql_handler;
		Sql_Paramer					m_sql_paramer;
		CInnerThread<CSql_Helper>	m_sql_thread;

		msgqueue					m_msgueue;

		CLMutex						m_mutex;
	};

	class CSql_Result
	{
	public:
		CSql_Result();
		~CSql_Result();

	public:
		MYSQL_RES* m_mysql_result;



	};
}