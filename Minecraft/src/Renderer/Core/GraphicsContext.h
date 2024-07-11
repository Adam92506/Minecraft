#pragma once

#include <GLFW/glfw3.h>

namespace Minecraft
{

	class GraphicsContext
	{
	public:
		GraphicsContext(GLFWwindow* windowHandle);

		void Init();
		void SwapBuffers();
	public:
		static Scope<GraphicsContext> Create(GLFWwindow* windowHandle);
	private:
		GLFWwindow* m_WindowHandle;
	};

}