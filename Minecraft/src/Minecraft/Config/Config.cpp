#include "mcpch.h"
#include "Config.h"

namespace Minecraft
{

	namespace Config
	{

		void Init(const std::string& blocksFilePath)
		{
			Blocks::Init(blocksFilePath);
		}

	}

}