#pragma once

#ifdef WIN32
#include <winsock2.h>
#endif
#include "mysql.h"
#include <stdio.h>

#include <string.h>
#include <string>
/*
	BaseCmd : sql �������
	�������: MYSQL ָ�룬mysql ���
	��������: MYSQL_RES ָ�룬���಻�����ͷ� ���ڴ棬��ȡ��Ӧ�ֶ��ͷ�
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