#pragma once

namespace Minecraft
{

	class ThreadPool
	{
	public:
		ThreadPool();
		~ThreadPool();

		void ThreadLoop();

		uint32_t BusyThreads() const;

		template <typename F, typename... Args>
		auto QueueTask(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
		{
			using returnType = typename std::result_of<F(Args...)>::type;

			auto function = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
			auto task = std::make_shared<std::packaged_task<returnType()>>(function);
			auto taskWrapper = [task]() { (*task)(); };

			{
				std::lock_guard<std::mutex> lock(m_Mutex);

				m_Queue.push(taskWrapper);

				m_ConditionVariable.notify_one();
			}

			return task->get_future();
		}
	public:
		static Ref<ThreadPool> Create();
	private:
		void Init(uint32_t threadCount);
		void Shutdown();
	private:
		mutable std::mutex m_Mutex;
		std::condition_variable m_ConditionVariable;

		std::vector<std::thread> m_Threads;

		bool m_Shutdown = false;

		uint32_t m_BusyThreads = 0;
		uint32_t m_TotalThreads = 0;

		std::queue<std::function<void()>> m_Queue;
	};

}