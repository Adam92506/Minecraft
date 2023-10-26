#pragma once

#include <glm/glm.hpp>

#define MC_ATLAS_GRASS_TOP            0.0f, 15.0f
#define MC_ATLAS_STONE                1.0f, 15.0f
#define MC_ATLAS_DIRT                 2.0f, 15.0f
#define MC_ATLAS_GRASS_SIDE           3.0f, 15.0f
#define MC_ATLAS_WOOD_PLANK           4.0f, 15.0f
#define MC_ATLAS_BRICK                7.0f, 15.0f
#define MC_ATLAS_COBLESTONE           0.0f, 14.0f
#define MC_ATLAS_BEDROCK              1.0f, 14.0f
#define MC_ATLAS_SAND                 2.0f, 14.0f
#define MC_ATLAS_GRAVEL               3.0f, 14.0f
#define MC_ATLAS_WOOD_LOG_SIDE        4.0f, 14.0f
#define MC_ATLAS_WOOD_LOG_TOP         5.0f, 14.0f
#define MC_ATLAS_IRON_BLOCK           6.0f, 14.0f
#define MC_ATLAS_GOLD_BLOCK           7.0f, 14.0f
#define MC_ATLAS_DIAMOND_BLOCK        8.0f, 14.0f
#define MC_ATLAS_CHEST_TOP            9.0f, 14.0f
#define MC_ATLAS_CHEST_SIDES          10.0f, 14.0f
#define MC_ATLAS_CHEST_FRONT          11.0f, 14.0f
#define MC_ATLAS_GOLD_ORE             0.0f, 13.0f
#define MC_ATLAS_IRON_ORE             1.0f, 13.0f
#define MC_ATLAS_COAL_ORE             2.0f, 13.0f
#define MC_ATLAS_DIAMOND_ORE          2.0f, 12.0f
#define MC_ATLAS_CRAFTING_TABLE_TOP   11.0f, 12.0f
#define MC_ATLAS_CRAFTING_TABLE_SIDES 11.0f, 11.0f
#define MC_ATLAS_CRAFTING_TABLE_FRONT 12.0f, 12.0f

namespace Minecraft
{

	enum class Face : uint8_t
	{
		None = 0,
		Top = 1,
		Bottom = 2,
		Left = 4,
		Right = 8,
		Front = 16,
		Rear = 32
	};

	enum class BlockType : uint8_t
	{
		None = 0,
		Air,
		Grass,
		Dirt,
		Stone,
		WoodPlank,
		Brick,
		Coblestone,
		Bedrock,
		Sand,
		Gravel,
		WoodLog,
		IronBlock,
		GoldBlock,
		DiamondBlock,
		Chest,
		GoldOre,
		IronOre,
		CoalOre,
		DiamondOre,
		CraftingTable
	};

	glm::vec2 GetTexturePosFromID(BlockType blockType, Face face);

}