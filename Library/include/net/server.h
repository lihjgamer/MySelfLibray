#pragma once

#include <WinSock2.h>
#include <string>
#include "thread/thread.h"
#include "thread/innerthread.h"
#include "net/session_client.h"


#include <list>
#pragma comment(lib,"ws2_32.lib")


namespace lihj
{
	class CNetServer
	{
	public:
		CNetServer();
		~CNetServer();

		bool Start(std::string ip,int port,int max_thread,int max_client);

	protected:

		void WorkThread(void* param);
		void Async_Accept();

		void Return_Session(CClientSession* pSession);
		CClientSession* Get_Available_Session();


		void HandleAccept(DWORD last_error, CClientSession* pSession);
		void HandleRead();
		void HandleWrite();
	private:
		HANDLE m_complete_port;
		SOCKET m_socket_listen;

		CClientSession* m_session_client;
		std::list<CClientSession*> m_available_sessions;

		int          m_max_accept;
		volatile int m_sync_accept;
	private:
		// 网络工作线程
		CInnerThread<CNetServer>* m_thread_worker;
		int						* m_pParamIndex;
	};

}
