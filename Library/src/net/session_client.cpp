#include "net/session_client.h"
#include "net/net_def.h"
#include <MSWSock.h>
#pragma warning(disable:4996)

namespace lihj
{

	CClientSession::CClientSession()
	{

	}

	CClientSession::~CClientSession()
	{

	}

	bool CClientSession::Init(int index, int max_recieve_buffer, int max_send_buffer)
	{
		m_session_id = 0x0000FFFF & index;
		m_socket_status = NetNone;
		// m_socket_client = socket(AF_INET, SOCK_STREAM, 0);

		return true;
	}

	void CClientSession::PreAccept()
	{
		m_socket_status = NetNone;
		m_socket_client = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL,0,WSA_FLAG_OVERLAPPED);
		m_accept.status = IOCS_ACCEPT;

	}

}

