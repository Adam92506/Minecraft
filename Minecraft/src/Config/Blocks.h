#pragma once

namespace Minecraft
{

	struct BlockProps
	{
		std::string Name;
		std::string DebugName;

		uint16_t ID;

		std::string TopTexture;
		std::string BottomTexture;
		std::string SideTexture;

		bool IsTransparent;
		bool IsSolid;
	};

	class Blocks
	{
	public:
		static void Init(const std::string& filePath);

		static uint16_t GetBlockID(const std::string& blockName) { return s_BlockIDMap.at(blockName); };

		static BlockProps& GetBlockProps(const std::string& blockName) { return s_BlockPropsMap.at(GetBlockID(blockName)); };
		static BlockProps& GetBlockProps(uint16_t blockID) { return s_BlockPropsMap.at(blockID); };

		static std::string& GetTopTexture(const std::string& blockName) { return s_BlockPropsMap.at(GetBlockID(blockName)).TopTexture; };
		static std::string& GetTopTexture(uint16_t blockID) { return s_BlockPropsMap.at(blockID).TopTexture; };

		static std::string& GetBottomTexture(const std::string& blockName) { return s_BlockPropsMap.at(GetBlockID(blockName)).BottomTexture; };
		static std::string& GetBottomTexture(uint16_t blockID) { return s_BlockPropsMap.at(blockID).BottomTexture; };

		static std::string& GetSideTexture(const std::string& blockName) { return s_BlockPropsMap.at(GetBlockID(blockName)).SideTexture; };
		static std::string& GetSideTexture(uint16_t blockID) { return s_BlockPropsMap.at(blockID).SideTexture; };

		static bool IsTransparent(const std::string& blockName) { return s_BlockPropsMap.at(GetBlockID(blockName)).IsTransparent; }
		static bool IsTransparent(uint16_t blockID) { return s_BlockPropsMap.at(blockID).IsTransparent; }

		static bool IsSolid(const std::string& blockName) { return s_BlockPropsMap.at(GetBlockID(blockName)).IsSolid; }
		static bool IsSolid(uint16_t blockID) { return s_BlockPropsMap.at(blockID).IsSolid; }
	private:
		static std::unordered_map<std::string, uint16_t> s_BlockIDMap;
		static std::unordered_map<uint16_t, BlockProps> s_BlockPropsMap;

	};

}