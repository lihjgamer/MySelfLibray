#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "thread.h"
#include "innerthread.h"
#include "logger.h"

#include "sql_helper.h"

#include "mem_pool.h"

int main(int argc, char** argv)
{


	lihj::CSql_Helper sqlhelper;
	lihj::Sql_Paramer sqlparamer;
	sqlparamer.host = "127.0.0.1";
	sqlparamer.dbname = "testlihj";
	sqlparamer.passwd = "letmego";
	sqlparamer.port = 3306;
	sqlparamer.user = "webgame";

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



	system("pause");
	return 0;
}