#include "mcpch.h"
#include "Shader.h"

#ifdef MC_PLATFORM_WINDOWS
#include "Platform/OpenGL/OpenGLShader.h"
#endif

namespace Minecraft {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateRef<OpenGLShader>(filepath);
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API")
			return nullptr;
		#endif
	}

}