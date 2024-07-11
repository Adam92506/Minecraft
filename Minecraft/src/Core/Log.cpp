#include "pch.h"
#include "Log.h"

namespace Minecraft
{

	Ref<spdlog::logger> Log::s_Logger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Logger = spdlog::stderr_color_mt("Minecraft");

		#ifdef MC_LOG_LEVEL_TRACE
			s_Logger->set_level(spdlog::level::trace);
		#elif MC_LOG_LEVEL_WARN
			s_Logger->set_level(spdlog::level::warn);
		#elif MC_LOG_LEVEL_INFO
			s_Logger->set_level(spdlog::level::info);
		#else
			s_Logger->set_level(spdlog::level::trace);
		#endif
	}

}