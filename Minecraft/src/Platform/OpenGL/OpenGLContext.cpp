#include "mcpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Minecraft/Core/Core.h"
#include "Minecraft/Core/Log.h"

namespace Minecraft {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MC_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MC_ASSERT(status, "Failed to initialize Glad");

		MC_INFO("OpenGL Info:");
		MC_INFO("   Vendor: {0}", (char*)glGetString(GL_VENDOR));
		MC_INFO("   Renderer: {0}", (char*)glGetString(GL_RENDERER));
		MC_INFO("   Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}