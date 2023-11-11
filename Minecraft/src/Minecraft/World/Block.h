#pragma once

#include "Minecraft/Config/Config.h"

namespace Minecraft
{

	enum class Face : uint8_t
	{
		None = 0,
		Top,     // +Y Dir
		Bottom,  // -Y Dir
		Front,   // +Z Dir
		Rear,    // -Z Dir
		Right,   // +X Dir
		Left     // -X Dir
	};

	namespace Vertex
	{

		uint32_t CompressVertexData(const glm::uvec3& position, uint16_t textureID, const glm::uvec2 uv);

	}

	struct Block
	{
		uint16_t BlockType;

		Block() = default;
		Block(const char* blockType)
			: BlockType(Config::Blocks::GetBlockID(blockType)) {}
		Block(uint16_t blockType)
			: BlockType(blockType) {}

		const std::string& GetTopTexture()
		{
			return Config::Blocks::GetTopTexture(BlockType);
		}

		const std::string& GetBottomTexture()
		{
			return Config::Blocks::GetBottomTexture(BlockType);
		}
		const std::string& GetSideTexture()
		{
			return Config::Blocks::GetSideTexture(BlockType);
		}

		bool IsTransparent() const
		{
			return Config::Blocks::IsTransparent(BlockType);
		}

		bool IsSolid() const
		{
			return Config::Blocks::IsSolid(BlockType);
		}

		bool operator==(Block& block) const
		{
			return BlockType == block.BlockType;
		}

		bool operator!=(Block& block) const
		{
			return BlockType != block.BlockType;
		}

		bool operator==(const char* block) const
		{
			return BlockType == Config::Blocks::GetBlockID(block);
		}

		bool operator!=(const char* block) const
		{
			return BlockType != Config::Blocks::GetBlockID(block);
		}
	};
	
};