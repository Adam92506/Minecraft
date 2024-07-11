#pragma once

#include "Window.h"
#include "ThreadPool.h"

#include "Events/ApplicationEvent.h"

namespace Minecraft
{

	class Application
	{
	public:
		Application();
		~Application();

		void OnEvent(Event& e);

		Ref<ThreadPool>& GetThreadPool() { return m_ThreadPool; }

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;

		Ref<ThreadPool> m_ThreadPool;

		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime;
	private:
		static Application* s_Instance;
	};

}