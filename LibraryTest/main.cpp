#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "innerthread.h"
#include "logger.h"

class ThreadTest : public lihj::CThread
{
public:
	
protected:
private:

	virtual bool Run()
	{
		int i = 100;
		while (i > 0)
		{
			printf("%d\n", i--);
		}
		return true;
	}

};

class TestThreadInner
{
public:

	void testinnerthread(void* pParam = NULL)
	{
		int n = 100;
		while (n)
		{
			printf("%d\n", n--);
		}
	}

	void Register()
	{
		m_innerthread.Register(this, &TestThreadInner::testinnerthread);
		m_innerthread.Create();
		WaitForSingleObject(m_innerthread.GetThreadHandle(), INFINITE);
	}
	public:
	lihj::CInnerThread<TestThreadInner> m_innerthread;
};

int main(int argc, char** argv)
{
	ThreadTest test;
	//test.Create();
	//WaitForSingleObject(test.GetThreadHandle(), INFINITE);

	TestThreadInner innert;
	innert.Register();
	lihj::LogInfo("thread flag %d\n", test.GetThreadCurFlag());
	lihj::LogDebug("thread flag %d\n", test.GetThreadCurFlag());
	lihj::g_logger.SetIntensifyColor(false);
	lihj::LogError("thread flag %d\n", test.GetThreadCurFlag());
	lihj::LogFatal("thread flag %d\n", test.GetThreadCurFlag());
	system("pause");
	return 0;
}