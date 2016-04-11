#include "server.h"
#include <MSWSock.h>
#pragma warning(disable:4996)

namespace lihj
{


	CNetServer::CNetServer()
	{
		m_socket_listen = INVALID_SOCKET;
		m_complete_port = INVALID_HANDLE_VALUE;
		m_thread_worker = NULL;
	}

	CNetServer::~CNetServer()
	{

	}

	bool CNetServer::Start(std::string ip, int port, int max_thread, int max_client)
	{

		m_session_client = new CClientSession[max_client];
		if (m_session_client == NULL)
		{
			return false;
		}

		for (int i = 0; i < max_client; i ++)
		{
			if (m_session_client[i].Init(i + 1,1024,1024))
			{
				Return_Session(m_session_client + i);
			}
		}


		m_socket_listen = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

		sockaddr_in address;
		ZeroMemory(&address, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr(ip.c_str());
		address.sin_port = htons(port);

		int result = ::bind(m_socket_listen, (sockaddr*)&address, sizeof(address));
		if (result != 0)
		{
			return false;
		}

		result = ::listen(m_socket_listen, SOMAXCONN);

		m_complete_port = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, (ULONG_PTR)0, NULL);

		::CreateIoCompletionPort((HANDLE)m_socket_listen, m_complete_port, (ULONG_PTR)0, 0);

		m_thread_worker = new CInnerThread<CNetServer>[max_thread];
		m_pParamIndex = new int[max_thread];

		m_sync_accept = max_thread;

		for (int i = 0; i < max_thread; i ++)
		{
			m_pParamIndex[i] = i;
			m_thread_worker[i].Register(this, &CNetServer::WorkThread, m_pParamIndex + i);
			m_thread_worker[i].Init();
		}

		for (int i = 0; i < max_thread; i ++)
		{
			Async_Accept();
		}

		return true;
	}

	void CNetServer::WorkThread(void* param)
	{
		BOOL ok = 0;
		DWORD last_error = 0;
		DWORD bytes = 0;
		LPOVERLAPPED pOverlapped = NULL;
		DWORD_PTR completion_key = 0;
		for (;;)
		{
			::WSASetLastError(0);
			ok = ::GetQueuedCompletionStatus(m_complete_port, &bytes, &completion_key, &pOverlapped, 500);
			last_error = ::WSAGetLastError();

			if (!ok && pOverlapped == NULL)
			{
				if (last_error == WAIT_TIMEOUT)
				{
					continue;
				}
				else
				{
					break;
				}
			}
			else
			{

			}
		}
	}

	void CNetServer::Async_Accept()
	{
		CClientSession* pSession = Get_Available_Session();
		if (pSession == NULL)
		{
			return;
		}

		DWORD bytes = 0;
		DWORD last_error = 0;
		BOOL  result = FALSE;

		result = ::AcceptEx(m_socket_listen,
			pSession->m_socket_client,
			pSession->m_buffer_recieve,
			0,
			sizeof(sockaddr_in)+16,
			sizeof(sockaddr_in)+16,
			&bytes,
			(LPOVERLAPPED)&pSession->m_accept);
		last_error = ::WSAGetLastError();

		if (!result && ERROR_IO_PENDING != last_error)
		{
			// 这里要处理连接
		}
	}

	void CNetServer::Return_Session(CClientSession* pSession)
	{
		m_available_sessions.push_back(pSession);
	}

	void CNetServer::HandleAccept(DWORD last_error)
	{

	}

	void CNetServer::HandleRead()
	{

	}

	void CNetServer::HandleWrite()
	{

	}

	CClientSession* CNetServer::Get_Available_Session()
	{
		if (m_available_sessions.empty())
		{
			return NULL;
		}

		CClientSession* sessiontmp = m_available_sessions.front();
		m_available_sessions.pop_front();
		sessiontmp->PreAccept();
		return sessiontmp;
	}

}

