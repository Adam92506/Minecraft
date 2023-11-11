#include "mcpch.h"
#include "Application.h"

#include "Timestep.h"
#include "Timer.h"

#include "Minecraft/Utils/Utils.h"

#include "Minecraft/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Minecraft/World/Block.h"
#include "Minecraft/Config/Config.h"

#include "Minecraft/World/Chunk.h"

namespace Minecraft
{
	Application* Application::s_Instance = nullptr;
	TextureAtlas* Application::s_TextureAtlas = nullptr;
	
	Application::Application()
	{
		MC_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(MC_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiWindow = CreateRef<ImGuiWindow>();
		m_ImGuiWindow->Init();

		m_Position = { 0.0f, 0.0f, 0.0f };

		Config::Init("assets/config/Blocks.yaml");

		s_TextureAtlas = new TextureAtlas("assets/textures/block/", 32, 32, ImageFormat::RGBA8);
		s_TextureAtlas->GenerateTextureAtlas();

		m_Chunk = new Chunk({ 0.0f, 0.0f, 0.0f });
		m_Chunk->GenerateBlockData();
		m_Chunk->GenerateRenderData();

		m_Shader = Shader::Create("assets/shaders/Quad.glsl");

		this->Run();
	}

	Application::~Application()
	{
		delete m_Chunk;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MC_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(MC_BIND_EVENT_FN(Application::OnWindowResize));

		m_CameraController.OnEvent(e);
		m_ImGuiWindow->OnEvent(e);
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
			m_Shader->SetUInt2("u_AtlasSize", { s_TextureAtlas->GetAtlasSize(), s_TextureAtlas->GetAtlasSize() });
			m_Shader->SetUInt2("u_TextureSize", { s_TextureAtlas->GetTextureWidth(), s_TextureAtlas->GetTextureHeight() });
			Renderer::Submit(m_Shader, m_Chunk->GetVertexArray(), s_TextureAtlas->GetTexture(), transform);

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

				ImGui::Text("Vertex Buffer: %i/%i KiB", (m_Chunk->GetVertexCount() * sizeof(uint32_t)) / 1000, (m_Chunk->GetBufferSize() * sizeof(uint32_t)) / 1000);

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