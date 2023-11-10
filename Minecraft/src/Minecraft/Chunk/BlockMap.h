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


	class BlockMap
	{
	public:
		static void Init(const std::string& filePath);

		static uint32_t GetBlockID(const std::string& blockName) { return s_BlockIDMap[blockName]; }

		static const BlockProp& GetBlockProps(uint32_t blockID) { return s_BlockMap[blockID]; }

		static std::string& GetTopTexture(uint32_t blockID) { return s_BlockMap.at(blockID).TopTexture; }
		static std::string& GetBottomTexture(uint32_t blockID) { return s_BlockMap.at(blockID).BottomTexture; }
		static std::string& GetSideTexture(uint32_t blockID) { return s_BlockMap.at(blockID).SideTexture; }

		static bool IsTransparent(uint32_t blockID) { return s_BlockMap.at(blockID).IsTransparent; }
		static bool IsSolid(uint32_t blockID) { return s_BlockMap.at(blockID).IsSolid; }

	private:
		static std::unordered_map<std::string, uint32_t> s_BlockIDMap;
		static std::unordered_map<uint32_t, BlockProp> s_BlockMap;
	};

}