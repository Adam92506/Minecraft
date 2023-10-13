#include "mcpch.h"
#include "Utils.h"

#include <ShlObj.h>

namespace Minecraft
{

	namespace Utils
	{

		std::string ReadFile(const std::string filepath)
		{
			std::string result;
			std::ifstream in(filepath, std::ios::in | std::ios::binary);

			if (in)
			{
				in.seekg(0, std::ios::end);
				size_t size = in.tellg();
				if (size != -1)
				{
					result.resize(size);
					in.seekg(0, std::ios::beg);
					in.read(&result[0], size);
				}
				else
				{
					MC_ERROR("Could not read from file '{0}'", filepath);
				}
			}
			else
			{
				MC_ERROR("Could not open file '{0}'", filepath);
			}

			return result;
		}

	}

}