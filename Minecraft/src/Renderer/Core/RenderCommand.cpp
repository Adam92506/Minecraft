#include "pch.h"
#include "RenderCommand.h"

namespace Minecraft
{

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}