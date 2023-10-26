#include "mcpch.h"
#include "Application.h"

#include "Timestep.h"
#include "Timer.h"

#include "Minecraft/Utils/Utils.h"

#include "Minecraft/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Minecraft
{
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		MC_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(MC_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiWindow = CreateRef<ImGuiWindow>();
		m_ImGuiWindow->Init();

		m_TextureAtlas = CreateRef<TextureAtlas>("Resources/Textures/texture_atlas.png", 16, 16);

		m_Shader = Shader::Create("Resources/Shaders/Block.glsl");

		m_Position = { 0.0f, 0.0f, 0.0f };

		Chunk::SetTextureAtlasSize(m_TextureAtlas->GetAtlasWidth(), m_TextureAtlas->GetAtlasHeight());

		m_Chunk.GenerateMesh();

		this->Run();
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MC_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(MC_BIND_EVENT_FN(Application::OnWindowResize));

		m_CameraController.OnEvent(e);
		m_ImGuiWindow->OnEvent(e);
	}

	void Application::MainLoop()
	{

	}

	void Application::Run()
	{
		Renderer::Init();

		while (m_Running)
		{
			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			m_CameraController.OnUpdate(timestep);

			RenderCommand::SetClearColor({ 0.3f, 0.4f, 0.7f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene(m_CameraController.GetCamera());

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position); 
			Renderer::Submit(m_Shader, m_Chunk.GetVertexArray(), m_TextureAtlas->GetTexture(), transform);

			if (!m_Minimized)
			{	

				m_ImGuiWindow->Begin();

				ImGui::Begin("Debug Window");

				if (ImGui::CollapsingHeader("Camera"))
				{
					glm::vec3 position = m_CameraController.GetCamera().GetPosition();
					glm::vec3 rotation = m_CameraController.GetCamera().GetRotation();
					ImGui::Text("Camera Position: %f, %f, %f", position.x, position.y, position.z);
					ImGui::Text("Camera Rotation: %f, %f, %f", rotation.x, rotation.y, rotation.z);
				}

				ImGui::End();

				m_ImGuiWindow->End();
			}
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

		return false;
	}


}