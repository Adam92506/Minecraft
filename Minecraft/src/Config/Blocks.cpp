#include "pch.h"
#include "Blocks.h"

#include <yaml-cpp/yaml.h>

#include "Core/Timer.h"

namespace Minecraft
{

	std::unordered_map<std::string, uint16_t> Blocks::s_BlockIDMap;
	std::unordered_map<uint16_t, BlockProps> Blocks::s_BlockPropsMap;

	void Blocks::Init(const std::string& filePath)
	{
		Timer timer;

		YAML::Node blocksNode = YAML::LoadFile(filePath);

		for (auto block : blocksNode)
		{

			BlockProps blockProps;

			blockProps.DebugName = block.first.as<std::string>();

			// Load ID
			if (!block.second["id"].IsDefined())
			{
				MC_WARN("Unable to load block [{0}]: ID not defined", blockProps.DebugName);
				continue;
			}
			else
			{
				blockProps.ID = block.second["id"].as<uint16_t>();
			}

			// Load Name
			if (!block.second["name"].IsDefined())
			{
				MC_WARN("Unable to load block [{0}]: Name not defined", blockProps.DebugName);
				continue;
			}
			else
			{
				blockProps.Name = block.second["name"].as<std::string>();
			}

			// Load Texture Names
			if (block.second["top"].IsDefined() && !block.second["bottom"].IsDefined() && !block.second["side"].IsDefined())
			{
				std::string texture = block.second["top"].as<std::string>();

				blockProps.TopTexture = texture;
				blockProps.BottomTexture = texture;
				blockProps.SideTexture = texture;
			}

			else if (block.second["top"].IsDefined() && block.second["bottom"].IsDefined() && !block.second["side"].IsDefined())
			{
				std::string topTexture = block.second["top"].as<std::string>();

				blockProps.TopTexture = topTexture;
				blockProps.BottomTexture = block.second["bottom"].as<std::string>();
				blockProps.SideTexture = topTexture;
			}

			else if (block.second["top"].IsDefined() && block.second["bottom"].IsDefined() && block.second["side"].IsDefined())
			{
				blockProps.TopTexture = block.second["top"].as<std::string>();
				blockProps.BottomTexture = block.second["bottom"].as<std::string>();
				blockProps.SideTexture = block.second["side"].as<std::string>();
			}

			else
			{
				MC_WARN("Unable to load block [{0}]: Texture not defined", blockProps.DebugName);
			}

			s_BlockIDMap.insert({ blockProps.DebugName, blockProps.ID });
			s_BlockPropsMap.insert({ blockProps.ID, blockProps });
		}

		float time = timer.ElapsedMillis();

		MC_INFO("Loaded {0} block configs from '{1}' in {2}ms", s_BlockIDMap.size(), filePath, time);
	}

}