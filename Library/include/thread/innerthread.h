#pragma once

namespace lihj
{
	/*
		调用顺序
		1、Register
		2、Create
		3、Start [根据 第二步 参数决定是否调用该函数]
	*/
	template<class T>
	class CInnerThread : public CThread
	{
	private:
		typedef void (T::*ThreadFunc)(void* pParam);

	public:
		CInnerThread()
		{
			m_class_obj = NULL;
			m_pThreadFunc = NULL;
			m_pParam = NULL;
		}

		~CInnerThread(){}

		bool Register(T* class_obj, ThreadFunc pThreadFunc,void* pParam = NULL)
		{
			m_class_obj = class_obj;
			m_pThreadFunc = pThreadFunc;
			m_pParam = pParam;
			return m_pThreadFunc != NULL && m_class_obj != NULL;
		}

		bool Run()
		{
			if (m_class_obj != NULL && m_pThreadFunc != NULL)
			{
				(m_class_obj->*m_pThreadFunc)(m_pParam);
				return true;
			}
			return false;
		}

	private:
		T*		   m_class_obj; // 类实例
		ThreadFunc m_pThreadFunc;// 类方法（线程处理函数）
		void*      m_pParam;	 // 处理函数携带的参数
	};
}