#include "mcpch.h"
#include "GraphicsContext.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Minecraft
{

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}