#include "mcpch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Minecraft
{

	Ref<Texture2D> Texture2D::Create(Image& image)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateRef<OpenGLTexture2D>(image);
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateRef<OpenGLTexture2D>(filepath);
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}