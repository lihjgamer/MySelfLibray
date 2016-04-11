#include <winsock2.h>
#include "net_def.h"

namespace lihj
{

	class CClientSession
	{
	public:
		CClientSession();
		~CClientSession();

		bool Init(int index,int max_recieve_buffer,int max_send_buffer);

		void  PreAccept();
	public:
		int    m_session_id;	// 用于上层回调
		int    m_socket_status; // 记录套接字状态
		SOCKET m_socket_client; // 客户端连接的套接字

		noverlappedex m_accept;
		noverlappedex m_read;
		noverlappedex m_write;

		char   m_buffer_recieve[1024];
// 		char*  m_sz_recieve_buffer;
// 		char*  m_sz_recieve_begin;
// 		char*  m_sz_recieve_end;

	};
}

