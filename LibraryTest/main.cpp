#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "thread/thread.h"
#include "thread/innerthread.h"
#include "logger/logger.h"

#include "sql/sql_helper.h"

#include "mem_pool/mem_pool.h"

#include "sql/sql_connect.h"

#include "sql/sql_base_cmd.h"
#include "sql/sql_use_result.h"
#include "sql/sql_store_result.h"

#ifdef USE_VLD_FLAG
#include "vld.h"
#endif

int main(int argc, char** argv)
{

	SqlConnection con;
	bool bok = con.ConnectToServer("192.168.1.192", 3306, "webgame", "letmego", "mysql");
	if (!bok)
	{
		return 0;
	}


	SqlBaseCmd basecmd;
	basecmd.Init(con.get_mysql_handle());
	//printf("%s", con.get_mysql_handle()->db);

	basecmd.ExecuteSqlCmd("use mysql");
	basecmd.ExecuteSqlCmd("show tables");

	SqlUseResults useresult;
	SqlStoreResults storeresult;

	useresult.Init(basecmd.GetExecuteResult());


	std::string results;
	int nrow = 0;
	char sztemp[32] = { 0 };
	useresult._FirstRow();
	while (!useresult._IsEnd())
	{
		results.clear();
		
		for (int i = 0; i < useresult.GetCol(); i ++)
		{
			memset(sztemp, 0, 32);
			useresult.GetString(useresult._GetCurRow(), i, sztemp, 32);
			results += sztemp;
			results += '\t';
		}
		printf("%s\n", results.c_str());
		useresult._MoveNextRow();
	}

	useresult.Uninit();

	//basecmd.ExecuteSqlCmd("show databases");

	printf("%%%%%%%%%%%%%%%%\n");

	storeresult.Init(mysql_list_processes(con.get_mysql_handle()));

	for (int i = 0; i < storeresult.GetRow(); i ++)
	{
		results.clear();
		for (int j = 0; j < storeresult.GetCol(); j ++)
		{
			memset(sztemp, 0, 32);
			storeresult.GetString(i, j, sztemp, 32);

			results += sztemp;
			results += '\t';
		}
		printf("%s\n", results.c_str());
	}

	storeresult.Uninit();

	con.DisConnectServer();

	
#if 0
	lihj::CSql_Helper sqlhelper;
	lihj::Sql_Paramer sqlparamer;
	sqlparamer.host = "127.0.0.1";
	sqlparamer.dbname = "testlihj";
	sqlparamer.passwd = "letmego";
	sqlparamer.port = 3306;
	sqlparamer.user = "webgame";
#endif

	//sqlhelper.Startup(sqlparamer);


#if 0
	printf("input sql \n");
	char szsql[256] = {0};
	while (1)
	{
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin.getline(szsql,512);
		if (strlen(szsql) > 0)
		{
			szsql[strlen(szsql)] = '\0';
			sqlhelper.PushBack(szsql);
		}
	}
#endif

#if 0
	lihj::CMemPool mempools;
	mempools.init();

	char* psz1 = (char*)mempools.alloc(1000);
	char* psz2 = (char*)mempools.alloc(1000);
	char* psz3 = (char*)mempools.alloc(1000);
	char* psz4 = (char*)mempools.alloc(1000);
	char* psz5 = (char*)mempools.alloc(1000);

	mempools.free(psz1);
	mempools.free(psz3);
	mempools.free(psz2);
	mempools.free(psz5);

	char* psz6 = (char*)mempools.alloc(23);
	char* psz7 = (char*)mempools.alloc(23);
	char* psz8 = (char*)mempools.alloc(23);
	char* psz9 = (char*)mempools.alloc(23); 
	char* psz10 = (char*)mempools.alloc(23);
// 	mempools.free(psz1);
#endif



	system("pause");
	return 0;
}