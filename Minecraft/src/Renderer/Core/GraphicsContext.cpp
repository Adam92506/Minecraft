#include "pch.h"
#include "GraphicsContext.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>

namespace Minecraft
{

	GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MC_ASSERT(windowHandle, "Window Handle Is Null: Unable To Create Graphics Context");
	}

	void GraphicsContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MC_ASSERT(status, "Failed To Initialize GLAD");

		MC_INFO("OpenGL Info:");
		MC_INFO("	Vendor: {0}", (char*)glGetString(GL_VENDOR));
		MC_INFO("	Renderer: {0}", (char*)glGetString(GL_RENDERER));
		MC_INFO("	Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	Scope<GraphicsContext> GraphicsContext::Create(GLFWwindow* windowHandle)
	{
		return CreateScope<GraphicsContext>(windowHandle);
	}

}