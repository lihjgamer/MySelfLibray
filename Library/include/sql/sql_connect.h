#pragma once

#ifdef WIN32
#include <winsock2.h>
#endif
#include <string>
#include <list>
#include <vector>

#include "mysql.h"

class SqlConnection
{
public:
	bool ConnectToServer(const char* ip,
		const unsigned int port,
		const char* user,
		const char* password,
		const char* db);
	bool DisConnectServer();

	inline MYSQL* get_mysql_handle()
	{
		return m_pSqlHandle;
	}

	SqlConnection();
	~SqlConnection();
protected:
private:
	MYSQL* m_pSqlHandle;
};

