#pragma once

#include "Minecraft/Events/ApplicationEvent.h"
#include "Minecraft/Events/KeyEvent.h"
#include "Minecraft/Events/MouseEvent.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Minecraft
{

	class ImGuiWindow
	{
	public:
		ImGuiWindow();
		~ImGuiWindow() = default;

		void Init();
		void Shutdown();
		void OnEvent(Event& e);

		void Begin();
		void End();
	};

}