#include "mcpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Minecraft
{

	Scope<RendererAPI> RendererAPI::Create()
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateScope<OpenGLRendererAPI>();
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}