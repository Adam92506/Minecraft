#pragma once

namespace Minecraft
{

	class Time
	{
	public:
		static float GetTime();
	};

	namespace Utils
	{

		std::string ReadFile(const std::string filepath);

	}

}