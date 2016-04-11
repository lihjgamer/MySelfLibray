#pragma once

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

namespace lihj
{
	class CNet_Init
	{
	public:
		CNet_Init()
		{
			WSADATA data;
			if (::WSAStartup(MAKEWORD(2,2),&data))
			{
			}
		}


		~CNet_Init()
		{
			::WSACleanup();
		}
	};

	static CNet_Init g_st_net_init;
}
