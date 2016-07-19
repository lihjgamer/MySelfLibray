#include "sql/sql_use_result.h"

SqlUseResults::SqlUseResults()
{
	m_cur_row = NULL;
	m_nCurRow = -2;
}

SqlUseResults::~SqlUseResults()
{

}

void SqlUseResults::Init(MYSQL_RES* pMysqlResult)
{
	SqlBaseResults::Init(pMysqlResult);
	//_FirstRow();
}

void SqlUseResults::Uninit()
{
	SqlBaseResults::Uninit();
	m_cur_row = NULL;
	m_nCurRow = -2;
}

int SqlUseResults::GetString(const int nRow, const int nCol, char szResult[], int nSize)
{
	_GoToRow(nRow);

	if (m_nCurRow == nRow)
	{
		unsigned long* pfieldlength = mysql_fetch_lengths(m_p_sql_results);
		return memcpy_s(szResult, nSize, m_cur_row[nCol], pfieldlength[nCol]);
	}
	else
	{
#ifdef _DEBUG
		fprintf(stderr, "can't find %d row\n", nRow);
#endif
		return 0;
	}
}

int SqlUseResults::GetInter(const int nRow, const int nCol, int& nResult)
{
	_GoToRow(nRow);
	if (m_nCurRow == nRow)
	{
		unsigned long* pfieldlength = mysql_fetch_lengths(m_p_sql_results);
		return atoi(m_cur_row[nCol]);
	}
	else
	{
#ifdef _DEBUG
		fprintf(stderr, "can't find %d row\n", nRow);
#endif
		return 0;
	}

}

void SqlUseResults::_GoToRow(const int nDestRow)
{
	while (!_IsEnd() && nDestRow != m_nCurRow)
	{
		_MoveNextRow();
	}
}

int SqlUseResults::_FirstRow()
{
	m_cur_row = mysql_fetch_row(m_p_sql_results);

	if (!mysql_eof(m_p_sql_results))
	{
		m_nCurRow = 0;
		return m_nCurRow;
	}
	m_cur_row = NULL;
	m_nCurRow = -1;
	return m_nCurRow;
}

int SqlUseResults::_MoveNextRow()
{
	m_cur_row = mysql_fetch_row(m_p_sql_results);

	if (!mysql_eof(m_p_sql_results))
	{
		m_nCurRow ++;
		return m_nCurRow;
	}
	m_nCurRow = -1;
	m_cur_row = NULL;
	return m_nCurRow;
}

bool SqlUseResults::_IsEnd()
{
	return m_nCurRow == -1;
}




