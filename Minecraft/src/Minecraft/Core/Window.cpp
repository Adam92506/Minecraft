#include "mcpch.h"
#include "Window.h"

#ifdef MC_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Minecraft
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef MC_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			MC_ASSERT(false, "Renderer: No supported rendering API");
			return nullptr;
		#endif
	}

}