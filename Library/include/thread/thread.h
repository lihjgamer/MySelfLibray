#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace lihj
{
	// 注意调用Create函数时 , 只能使用 ThreadFlagRunning/ThreadFlagSuspended
	// 其他两个状态为 初始化时 和 线程退出后的状态
	enum ThreadFlag
	{
		ThreadFlagNone      = 0x0000,			// 无效状态
		ThreadFlagRunning   = 0x0001,			// 执行状态	
		ThreadFlagSuspended = 0x0002,			// 挂起状态	
		ThreadFlagExit		= 0x0003,			// 线程退出状态(执行完)
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
		ThreadFlag	m_ThreadFlag;	// 当前线程的状态
		bool		m_bInit;		// 线程是否完成初始化
	};
}