#pragma once

#define WIN32_LEAN_AND_MEAN	// ��д�� ����ʱ���������������� Ӧ������һ��ͳһ���ļ��У�����������ֺ��ظ�����
#include <windows.h>
namespace lihj
{
	class CLMutex
	{
	public:
		CLMutex()
		{
			::InitializeCriticalSection(&m_cs);
		}

		~CLMutex()
		{
			::DeleteCriticalSection(&m_cs);
		}

		void Lock()
		{
			::EnterCriticalSection(&m_cs);
		}

		void UnLock()
		{
			::LeaveCriticalSection(&m_cs);
		}
	protected:
	private:
		CRITICAL_SECTION m_cs;
	};

	class CLock
	{
	public:
		CLock(CLMutex & mt)
			:m_mutex(mt)
		{
			m_mutex.Lock();
		}

		~CLock()
		{
			m_mutex.UnLock();
		}
	protected:
	private:
		CLMutex &m_mutex;
	};
}