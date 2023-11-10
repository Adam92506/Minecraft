#include "mcpch.h"
#include "Blocks.h"

namespace Minecraft
{

	namespace Config
	{
		std::unordered_map<std::string, uint16_t> Blocks::s_BlockIDMap;
		std::unordered_map<uint16_t, BlockProp> Blocks::s_BlockMap;

		void Blocks::Init(const std::string & filePath)
		{
			YAML::Node blocksNode = YAML::LoadFile(filePath);

			for (auto block : blocksNode)
			{
				if (!block.second["id"].IsDefined())
				{
					MC_WARN("Unabled to load block: ID not defined");
					break;
				}

				std::string name = block.first.as<std::string>();
				uint16_t id = block.second["id"].as<uint16_t>();
				s_BlockIDMap.insert({ name, id });

				BlockProp blockProp;
				blockProp.TopTexture = block.second["top"].as<std::string>();
				blockProp.BottomTexture = block.second["bottom"].as<std::string>();
				blockProp.SideTexture = block.second["side"].as<std::string>();
				blockProp.IsTransparent = block.second["isTransparent"].as<bool>();
				blockProp.IsSolid = block.second["isSolid"].as<bool>();

				s_BlockMap.insert({ id, blockProp });
			}

			MC_TRACE("Loaded block config from '{0}'", filePath);

		}
	}

}