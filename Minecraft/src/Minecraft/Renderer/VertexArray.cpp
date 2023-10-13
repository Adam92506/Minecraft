#include "mcpch.h"
#include "VertexArray.h"

#ifdef MC_PLATFORM_WINDOWS
#include "Platform/OpenGL/OpenGLVertexArray.h"
#endif

namespace Minecraft {

	Ref<VertexArray> VertexArray::Create()
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateRef<OpenGLVertexArray>();
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}