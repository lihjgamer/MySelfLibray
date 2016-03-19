#include "thread.h"
#include <assert.h>

namespace lihj
{
	DWORD _stdcall ThreadProc(void* pParam);

	CThread::CThread()
	{
		m_hThread = NULL;
		m_bInit = false;
		m_ThreadFlag = ThreadFlagNone;
	}
	
	CThread::~CThread()
	{
		
	}
	
	bool CThread::Create(ThreadFlag tf)
	{
		assert(m_bInit == false);
		int nThreadFlag[] = { 0, 4 };
		(tf == ThreadFlagRunning || tf == ThreadFlagSuspended) ? true : (tf = ThreadFlagRunning, true);
		m_hThread = CreateThread(NULL,
			0,
			ThreadProc,
			this,
			nThreadFlag[(int)tf - 1],
			NULL);

		if (m_hThread != NULL)
		{
			m_bInit = true;
			m_ThreadFlag = tf;
		}
		
		return m_bInit;

	}
	
	bool CThread::Destroy()
	{
		if (TerminateThread(m_hThread, 0))
		{
			m_hThread = NULL;
			m_bInit = false;
			m_ThreadFlag = ThreadFlagExit;
			return true;
		}
		return false;
	}
	
	bool CThread::Start()
	{
		if (ResumeThread(m_hThread))
		{
			m_ThreadFlag = ThreadFlagRunning;
			return true;
		}
		return false;
	}
	
	bool CThread::Stop()
	{
		if (SuspendThread(m_hThread))
		{
			m_ThreadFlag = ThreadFlagSuspended;
			return true;
		}
		return false;
	}

	void CThread::Sleep(unsigned long dwMillisecondes)
	{
#ifdef WIN32
		::Sleep(dwMillisecondes);
#else
#endif
	}

	ThreadFlag CThread::GetThreadCurFlag()
	{
		return m_ThreadFlag;
	}

	bool CThread::GetBInit()
	{
		return m_bInit;
	}

	bool CThread::Enter()
	{
		return true;
	}

	bool CThread::Exit()
	{
		m_ThreadFlag = ThreadFlagExit;
		return true;
	}

	HANDLE CThread::GetThreadHandle()
	{
		return m_hThread;
	}



	DWORD _stdcall ThreadProc(void* pParam)
	{
		assert(pParam != NULL);
		CThread* pThreadObj = static_cast<CThread*>(pParam);
		assert(pThreadObj != NULL);
		if (pThreadObj != NULL)
		{
			pThreadObj->Enter();
			pThreadObj->Run();
			pThreadObj->Exit();
		}
		return 0;
	}
}

