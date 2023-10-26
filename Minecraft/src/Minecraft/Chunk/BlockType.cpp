#include "mcpch.h"
#include "BlockType.h"

namespace Minecraft
{

	glm::vec2 GetTexturePosFromID(BlockType blockType, Face face)
	{
		switch (blockType)
		{
			case BlockType::Grass:
			{
				if (face != Face::Top && face != Face::Bottom)
				{
					return { MC_ATLAS_GRASS_SIDE };
				}
				else if (face == Face::Top)
				{
					return { MC_ATLAS_GRASS_TOP };
				}
				else
				{
					return { MC_ATLAS_DIRT };
				}
			}
			case BlockType::Dirt:
			{
				return { MC_ATLAS_DIRT };
			}
			case BlockType::Stone:
			{
				return { MC_ATLAS_STONE };
			}
			case BlockType::WoodPlank:
			{
				return { MC_ATLAS_WOOD_PLANK };
			}
			case BlockType::Brick:
			{
				return { MC_ATLAS_BRICK };
			}
			case BlockType::Coblestone:
			{
				return { MC_ATLAS_COBLESTONE };
			}
			case BlockType::Bedrock:
			{
				return { MC_ATLAS_BEDROCK };
			}
			case BlockType::Sand:
			{
				return { MC_ATLAS_SAND };
			}
			case BlockType::Gravel:
			{
				return { MC_ATLAS_GRAVEL };
			}
			case BlockType::WoodLog:
			{
				if (face != Face::Top && face != Face::Bottom)
				{
					return { MC_ATLAS_WOOD_LOG_SIDE };
				}
				else
				{
					return { MC_ATLAS_WOOD_LOG_TOP };
				}
			}
			case BlockType::IronBlock:
			{
				return { MC_ATLAS_IRON_BLOCK };
			}
			case BlockType::GoldBlock:
			{
				return { MC_ATLAS_GOLD_BLOCK };
			}
			case BlockType::DiamondBlock:
			{
				return { MC_ATLAS_DIAMOND_BLOCK };
			}
			case BlockType::Chest:
			{
				if (face == Face::Front)
				{
					return { MC_ATLAS_CHEST_FRONT };
				}
				else if (face == Face::Top || face == Face::Bottom)
				{
					return { MC_ATLAS_CHEST_TOP };
				}
				else
				{
					return { MC_ATLAS_CHEST_SIDES };
				}
			}
			case BlockType::GoldOre:
			{
				return { MC_ATLAS_GOLD_ORE };
			}
			case BlockType::IronOre:
			{
				return { MC_ATLAS_IRON_ORE };
			}
			case BlockType::CoalOre:
			{
				return { MC_ATLAS_COAL_ORE };
			}
			case BlockType::DiamondOre:
			{
				return { MC_ATLAS_DIAMOND_ORE };
			}
			case BlockType::CraftingTable:
			{
				if (face == Face::Top)
				{
					return { MC_ATLAS_CRAFTING_TABLE_TOP };
				}
				else if (face == Face::Front)
				{
					return { MC_ATLAS_CRAFTING_TABLE_FRONT };
				}
				else
				{
					return { MC_ATLAS_CRAFTING_TABLE_SIDES };
				}
			}
		}
		return { 0.0f, 0.0f };
	}

}