#pragma once

#include "Core.h"

#include "Minecraft/Events/Event.h"
#include "Minecraft/Events/ApplicationEvent.h"

#include "Minecraft/ImGui/ImGuiWindow.h"

#include "Window.h"

#include "Minecraft/Renderer/Shader.h"
#include "Minecraft/Renderer/Buffer.h"
#include "Minecraft/Renderer/Texture.h"
#include "Minecraft/Renderer/VertexArray.h"
#include "Minecraft/Renderer/CameraController.h"

#include "Minecraft/Renderer/TextureAtlas.h"

namespace Minecraft {

	class Application
	{
	public:
		Application();
		~Application();

		void OnEvent(Event& e);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		Ref<ImGuiWindow> m_ImGuiWindow;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
	private:
		glm::vec3 m_Position;
		CameraController m_CameraController;
		TextureAtlas m_TextureAtlas;

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

}