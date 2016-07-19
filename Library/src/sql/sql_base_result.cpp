#include "sql/sql_base_result.h"

void SqlBaseResults::Init(MYSQL_RES* pMysqlResult)
{
	m_p_sql_results = pMysqlResult;
	m_nSumCols = mysql_num_fields(m_p_sql_results);
	m_nSumRows = 0;
}

void SqlBaseResults::Uninit()
{
	mysql_free_result(m_p_sql_results);
	m_p_sql_results = NULL;
	m_nSumRows = m_nSumCols = 0;
}

int SqlBaseResults::GetString(const int nRow, const int nCol, char szResult[], int nSize)
{
	return 0;
}

int SqlBaseResults::GetInter(const int nRow, const int nCol, int& nResult)
{
	return 0;
}

SqlBaseResults::SqlBaseResults()
{
	m_p_sql_results = NULL;
	m_nSumRows = m_nSumCols = 0;
}

SqlBaseResults::~SqlBaseResults()
{

}
