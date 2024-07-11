#include "pch.h"
#include "ThreadPool.h"

namespace Minecraft
{

	ThreadPool::ThreadPool()
	{
		Init(std::thread::hardware_concurrency());
	}

	ThreadPool::~ThreadPool()
	{
		Shutdown();
	}


	void ThreadPool::ThreadLoop()
	{
		// Aquire lock
		std::unique_lock<std::mutex> lock(m_Mutex);

		while (!m_Shutdown || (m_Shutdown && !m_Queue.empty()))
		{
			// Wait for task or shutdown
			m_ConditionVariable.wait(lock, [this]
				{
					return m_Shutdown || !m_Queue.empty();
				});

			// Check if there is a task in the queue
			if (!m_Queue.empty())
			{
				// Get task from queue
				auto function = m_Queue.front();
				m_Queue.pop();

				m_BusyThreads++;

				lock.unlock();
				function();
				lock.lock();

				m_BusyThreads--;
			}
		}
	}

	uint32_t ThreadPool::BusyThreads() const
	{
		uint32_t busyCount;

		{
			std::lock_guard<std::mutex> lock(m_Mutex);

			busyCount = m_BusyThreads;
		}

		return busyCount;
	}

	void ThreadPool::Init(uint32_t threadCount)
	{
		for (uint32_t i = 0; i < threadCount; i++)
		{
			m_Threads.push_back(std::thread(&ThreadPool::ThreadLoop, this));
		}

		m_TotalThreads = threadCount;

		MC_INFO("Initialized Thread Pool [{0} threads]", m_TotalThreads);
	}

	void ThreadPool::Shutdown()
	{
		{
			std::lock_guard<std::mutex> lock(m_Mutex);

			m_Shutdown = true;
			m_ConditionVariable.notify_all();
		}

		for (uint32_t i = 0; i < m_TotalThreads; i++)
		{
			if (m_Threads[i].joinable())
			{
				m_Threads[i].join();
			}
		}
	}

	Ref<ThreadPool> ThreadPool::Create()
	{
		return CreateRef<ThreadPool>();
	}

}