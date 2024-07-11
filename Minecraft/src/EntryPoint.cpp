#include "pch.h"

#include "Core/Application.h"

#ifdef MC_PLATFORM_WINDOWS

int main()
{
	Minecraft::Log::Init();
	MC_INFO("Initialized Log!");

	Minecraft::Application application;

	return 0;
}

#endif