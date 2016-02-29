#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace lihj
{
	// ע�����Create����ʱ , ֻ��ʹ�� ThreadFlagRunning/ThreadFlagSuspended
	// ��������״̬Ϊ ��ʼ��ʱ �� �߳��˳����״̬
	enum ThreadFlag
	{
		ThreadFlagNone      = 0x0000,			// ��Ч״̬
		ThreadFlagRunning   = 0x0001,			// ִ��״̬	
		ThreadFlagSuspended = 0x0002,			// ����״̬	
		ThreadFlagExit		= 0x0003,			// �߳��˳�״̬(ִ����)
	};

	class CThread
	{
	public:
		CThread();
		virtual ~CThread();

		bool Create(ThreadFlag tf = ThreadFlagRunning);
		bool Destroy();

		bool Start();
		bool Stop();

		HANDLE     GetThreadHandle();
		ThreadFlag GetThreadCurFlag();
		bool	   GetBInit();

		bool	     Enter();
		virtual bool Run() = 0;
		bool		 Exit();

	private:
		HANDLE		m_hThread;		// Thread
		ThreadFlag	m_ThreadFlag;	// ��ǰ�̵߳�״̬
		bool		m_bInit;		// �߳��Ƿ���ɳ�ʼ��
	};
}