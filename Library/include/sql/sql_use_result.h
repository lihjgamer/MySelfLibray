#pragma once

#include "sql/sql_base_result.h"

/*
	处理 mysql_use_result 返回的结果
	每一行只能处理一次，且是递增处理，不可逆
*/
class SqlUseResults : public SqlBaseResults
{
public:
	virtual void Init(MYSQL_RES* pMysqlResult);
	virtual void Uninit();

	virtual int			GetString(const int nRow, const int nCol,char szResult[],int nSize);
	virtual int			GetInter(const int nRow, const int nCol,int& nResult);

	SqlUseResults();
	~SqlUseResults();

public:
	inline int _GetCurRow() const
	{
		return m_nCurRow;
	}

	int _FirstRow();
	int _MoveNextRow();

	bool _IsEnd();

private:

	void _GoToRow(const int nDestRow);
private:
	MYSQL_ROW   m_cur_row;
	int			m_nCurRow;
};