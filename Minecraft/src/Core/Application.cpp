#include "pch.h"
#include "Application.h"

#include "Renderer/Renderer.h"

#include "World/World.h"

#include "Utils/Time.h"

#include "Renderer/TextureAtlas.h"

namespace Minecraft
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		MC_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		WindowProps props;
		m_Window = Window::Create(props);
		m_Window->SetEventCallback(MC_BIND_EVENT_FN(Application::OnEvent));

		m_ThreadPool = ThreadPool::Create();

		Renderer::Init();
		Renderer::LoadShaders();

		World::Init();

		TextureAtlas textureAtlas(ImageFormat::RGBA8);
		textureAtlas.LoadTextures("Minecraft/assets/textures/blocks");
		textureAtlas.CreateAtlas();

		this->Run();
	}

	Application::~Application()
	{
		World::Shutdown();

		Renderer::Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MC_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(MC_BIND_EVENT_FN(Application::OnWindowResize));

		World::OnEvent(e);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			World::OnUpdate(timestep);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;

			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		
		return true;
	}

}