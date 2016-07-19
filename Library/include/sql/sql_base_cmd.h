#pragma once

#ifdef WIN32
#include <winsock2.h>
#endif
#include "mysql.h"
#include <stdio.h>

#include <string.h>
#include <string>
/*
	BaseCmd : sql 命令基类
	传入参数: MYSQL 指针，mysql 语句
	传出参数: MYSQL_RES 指针，该类不负责释放 该内存，获取后应手动释放
*/

class SqlBaseCmd
{
public:
	void			Init(MYSQL* mysql);
	void			Uninit();

	bool			ExecuteSqlCmd(const char* psql);

	int				GetErrorCode();
	const char*		GetErrorDesc();

	MYSQL_RES*		GetExecuteResult(bool bMysqlUseResult = true);

	SqlBaseCmd();
	~SqlBaseCmd();
protected:
	inline bool _IsValid()
	{
		return m_pmysql != NULL;
	}
private:
	MYSQL* m_pmysql;
};