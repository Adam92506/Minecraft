#pragma once

#include "Core.h"

#include "Minecraft/Events/Event.h"
#include "Minecraft/Events/ApplicationEvent.h"

#include "Window.h"

namespace Minecraft {

	class Application
	{
	public:
		Application();
		~Application();

		void MainLoop();

		void OnEvent(Event& e);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

}