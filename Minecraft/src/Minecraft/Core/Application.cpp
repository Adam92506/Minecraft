#include "mcpch.h"
#include "Application.h"

#include "Timestep.h"
#include "Timer.h"

#include "Minecraft/Utils/Utils.h"

#include "Minecraft/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Minecraft/Chunk/Block.h"
#include "Minecraft/Chunk/BlockMap.h"

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

		m_Position = { 0.0f, 0.0f, 0.0f };

		BlockMap::Init("assets/config/Blocks.yaml");

		m_TextureAtlas = TextureAtlas("assets/textures/block/", 32, 32, ImageFormat::RGBA8);
		m_TextureAtlas.GenerateTextureAtlas();

		BlockProp blockProp = BlockMap::GetBlockProps(BlockMap::GetBlockID("grass_block"));

		uint16_t texID = m_TextureAtlas.GetTextureID(blockProp.BottomTexture);

		uint32_t vertices[4];
		vertices[0] = Vertex::CompressVertexData({ 0, 0, 0 }, texID, { 0, 0 });
		vertices[1] = Vertex::CompressVertexData({ 1, 0, 0 }, texID, { 1, 0 });
		vertices[2] = Vertex::CompressVertexData({ 1, 1, 0 }, texID, { 1, 1 });
		vertices[3] = Vertex::CompressVertexData({ 0, 1, 0 }, texID, { 0, 1 });

		uint32_t indecies[6]
		{
			2, 3, 0, 0, 1, 2
		};

		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		m_VertexBuffer->SetLayout({
			{ ShaderDataType::UInt, "a_CompressedData" }
			});

		m_IndexBuffer = IndexBuffer::Create(indecies, sizeof(indecies) / sizeof(float));
		
		m_VertexArray = VertexArray::Create();
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Shader = Shader::Create("assets/shaders/Quad.glsl");

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

	void Application::Run()
	{
		int32_t texID = 0;
		bool drawFullAtlas = false;

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
			m_Shader->SetUInt2("u_AtlasSize", { m_TextureAtlas.GetAtlasSize(), m_TextureAtlas.GetAtlasSize() });
			m_Shader->SetUInt2("u_TextureSize", { m_TextureAtlas.GetTextureWidth(), m_TextureAtlas.GetTextureHeight() });
			m_Shader->SetUInt("u_TexID", (uint32_t)texID);
			m_Shader->SetUInt("u_DrawFullAtlas", drawFullAtlas);
			Renderer::Submit(m_Shader, m_VertexArray, m_TextureAtlas.GetTexture(), transform);

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

				ImGui::InputInt("Texture ID", &texID);
				ImGui::Checkbox("Draw Full Atlas", &drawFullAtlas);

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