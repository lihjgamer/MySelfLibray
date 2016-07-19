#pragma once

#include "sql/sql_base_result.h"

/*
	���� mysql_use_result ���صĽ��
	ÿһ��ֻ�ܴ���һ�Σ����ǵ�������������
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