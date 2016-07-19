#pragma once

#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <winsock2.h>
#endif

#include "mysql.h"


class SqlBaseResults 
{
public:
	virtual void Init(MYSQL_RES* pMysqlResult);
	virtual void Uninit();

	virtual int			GetString(const int nRow, const int nCol,char szResult[],int nSize);
	virtual int			GetInter(const int nRow, const int nCol,int& nResult);

	inline  int			GetRow()
	{
		return m_nSumRows;
	}

	inline  int			GetCol()
	{
		return m_nSumCols;
	}

	SqlBaseResults();
	~SqlBaseResults();
protected:
	MYSQL_RES* m_p_sql_results;
	int		   m_nSumRows;
	int		   m_nSumCols;
};