#include "sql/sql_store_result.h"

SqlStoreResults::SqlStoreResults()
{

}

SqlStoreResults::~SqlStoreResults()
{

}

void SqlStoreResults::Init(MYSQL_RES* pMysqlResult)
{
	SqlBaseResults::Init(pMysqlResult);
	m_nSumRows = (int)mysql_num_rows(m_p_sql_results);
}

void SqlStoreResults::Uninit()
{
	SqlBaseResults::Uninit();
}

int SqlStoreResults::GetString(const int nRow, const int nCol, char szResult[], int nSize)
{
	_GoToRow(nRow);

	MYSQL_ROW mysql_row = mysql_fetch_row(m_p_sql_results);
	unsigned long* pfieldlength = mysql_fetch_lengths(m_p_sql_results);

	return memcpy_s(szResult, nSize, mysql_row[nCol], pfieldlength[nCol]);
}

int SqlStoreResults::GetInter(const int nRow, const int nCol, int& nResult)
{
	_GoToRow(nRow);

	MYSQL_ROW mysql_row = mysql_fetch_row(m_p_sql_results);
	unsigned long* pfieldlength = mysql_fetch_lengths(m_p_sql_results);

	return atoi(mysql_row[nCol]);
}

void SqlStoreResults::_GoToRow(const int nDestRow)
{
	mysql_data_seek(m_p_sql_results, my_ulonglong(nDestRow));
}


