#include "sql/sql_connect.h"


SqlConnection::SqlConnection()
{
	m_pSqlHandle = NULL;
}

SqlConnection::~SqlConnection()
{

}

bool SqlConnection::ConnectToServer(const char* ip, const unsigned int port, const char* user, const char* password, const char* db)
{
	m_pSqlHandle = mysql_init(m_pSqlHandle);

	printf("mysql_init error,error code : %s\n", mysql_error(m_pSqlHandle));

	m_pSqlHandle = mysql_real_connect(m_pSqlHandle, ip, user, password, db, port, NULL, 0);

	return m_pSqlHandle == NULL ? false : true;
}

bool SqlConnection::DisConnectServer()
{
	if (m_pSqlHandle != NULL)
	{
		mysql_close(m_pSqlHandle);
	}
	return true;
}


