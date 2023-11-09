#include "mcpch.h"
#include "Buffer.h"

#ifdef MC_PLATFORM_WINDOWS
#include "Platform/OpenGL/OpenGLBuffer.h"
#endif

namespace Minecraft {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateRef<OpenGLVertexBuffer>(size);
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

	Ref<VertexBuffer> VertexBuffer::Create(void* verticies, uint32_t size)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateRef<OpenGLVertexBuffer>(verticies, size);
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indecies, uint32_t count)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateRef<OpenGLIndexBuffer>(indecies, count);
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}