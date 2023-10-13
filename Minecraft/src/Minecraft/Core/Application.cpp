#include "mcpch.h"
#include "Application.h"

#include "Minecraft/Renderer/Shader.h"
#include "Minecraft/Renderer/VertexArray.h"
#include "Minecraft/Renderer/Buffer.h"
#include "Minecraft/Renderer/RenderCommand.h"

namespace Minecraft
{
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		MC_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(MC_BIND_EVENT_FN(Application::OnEvent));

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
	}

	void Application::MainLoop()
	{

	}

	void Application::Run()
	{
		RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

		Ref<Shader> shader = Shader::Create("Resources/Shaders/Shader.glsl");
		shader->Bind();

		float verticies[] = {
			-0.5, -0.5,
			-0.5, 0.5,
			0.5, 0.5,
			0.5, -0.5
		};

		uint32_t indecies[] = {
			0, 3, 1,
			1, 3, 2
		};

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(verticies, sizeof(verticies));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" }
		};
		vertexBuffer->SetLayout(layout);

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indecies, sizeof(indecies) / sizeof(uint32_t));

		Ref<VertexArray> vertexArray = VertexArray::Create();
		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);

		RenderCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

		while (m_Running)
		{
			this->MainLoop();

			if (!m_Minimized)
			{	
				RenderCommand::Clear();
				RenderCommand::DrawIndexed(vertexArray);
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

		return false;
	}


}