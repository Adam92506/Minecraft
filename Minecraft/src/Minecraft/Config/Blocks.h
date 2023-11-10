#pragma once

#include <yaml-cpp/yaml.h>

namespace Minecraft
{

	struct BlockProp
	{
		std::string TopTexture;
		std::string BottomTexture;
		std::string SideTexture;

		bool IsTransparent;
		bool IsSolid;
	};

	namespace Config
	{
		class Blocks
		{
		public:
			static void Init(const std::string& filePath);

			static uint16_t GetBlockID(const std::string& blockName) { return s_BlockIDMap[blockName]; }

			static const BlockProp& GetBlockProps(uint16_t blockID) { return s_BlockMap[blockID]; }

			static std::string& GetTopTexture(uint16_t blockID) { return s_BlockMap.at(blockID).TopTexture; }
			static std::string& GetBottomTexture(uint16_t blockID) { return s_BlockMap.at(blockID).BottomTexture; }
			static std::string& GetSideTexture(uint16_t blockID) { return s_BlockMap.at(blockID).SideTexture; }

			static bool IsTransparent(uint16_t blockID) { return s_BlockMap.at(blockID).IsTransparent; }
			static bool IsSolid(uint16_t blockID) { return s_BlockMap.at(blockID).IsSolid; }

		private:
			static std::unordered_map<std::string, uint16_t> s_BlockIDMap;
			static std::unordered_map<uint16_t, BlockProp> s_BlockMap;
		};
	}

}