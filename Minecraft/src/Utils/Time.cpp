#include "pch.h"
#include "Time.h"

#include <GLFW/glfw3.h>

namespace Minecraft
{

	float Time::GetTime()
	{
		return (float)glfwGetTime();
	}

}