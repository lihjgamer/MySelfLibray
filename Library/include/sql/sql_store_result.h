#pragma once

#include "sql/sql_base_result.h"

/*
���� mysql_store_result ���صĽ��
���Դ����� SqlStoreResults
*/
class SqlStoreResults : public SqlBaseResults
{
public:
	virtual void Init(MYSQL_RES* pMysqlResult);
	virtual void Uninit();

	virtual int			GetString(const int nRow, const int nCol, char szResult[], int nSize);
	virtual int			GetInter(const int nRow, const int nCol, int& nResult);

	int					GetString(const int nRow, const char szField[], char szResult[], int nSize);
	int					GetInter(const int nRow, const char szField[], int& nResult);

	SqlStoreResults();
	~SqlStoreResults();

private:
 	void _GoToRow(const int nDestRow);
// 
// 	int _FirstRow();
// 	int _MoveNextRow();
// 	bool _IsEnd();
private:
	MYSQL_ROW   m_cur_row;
	int			m_nCurRow;
};