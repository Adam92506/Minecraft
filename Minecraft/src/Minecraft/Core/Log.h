#pragma once

#include "Minecraft/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Minecraft
{

	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

// Log Macros
#define MC_TRACE(...) ::Minecraft::Log::GetLogger()->trace(__VA_ARGS__)
#define MC_INFO(...) ::Minecraft::Log::GetLogger()->info(__VA_ARGS__)
#define MC_WARN(...) ::Minecraft::Log::GetLogger()->warn(__VA_ARGS__)
#define MC_ERROR(...) ::Minecraft::Log::GetLogger()->error(__VA_ARGS__)
#define MC_CRITICAL(...) ::Minecraft::Log::GetLogger()->critical(__VA_ARGS__)