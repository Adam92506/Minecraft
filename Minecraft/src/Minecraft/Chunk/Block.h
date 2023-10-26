#pragma once

#include "BlockType.h"

#include "Minecraft/Renderer/TextureAtlas.h"

namespace Minecraft
{

	struct BlockMesh
	{
		std::vector<float> Verticies;
		std::vector<uint32_t> Indecies;
	};

	struct FaceAttributes
	{
		uint8_t DisabledFaces = 0;

		FaceAttributes() = default;
		FaceAttributes(std::initializer_list<Face> disabledFaces)
		{
			for (auto& faceID : disabledFaces)
			{
				DisabledFaces = DisabledFaces | (uint8_t)faceID;
			}
		}
		FaceAttributes(bool drawTopFace, bool drawBottomFace, bool drawLeftFace, bool drawRightFace, bool drawFrontFace, bool drawRearFace)
		{
			if (!drawTopFace)
			{
				DisabledFaces |= 1;
			}

			if (!drawBottomFace)
			{
				DisabledFaces |= 2;
			}

			if (!drawLeftFace)
			{
				DisabledFaces |= 4;
			}

			if (!drawRightFace)
			{
				DisabledFaces |= 8;
			}

			if (!drawFrontFace)
			{
				DisabledFaces |= 16;
			}

			if (!drawRearFace)
			{
				DisabledFaces |= 32;
			}
		}

		bool IsFaceEnabled(Face faceID)
		{
			return !(DisabledFaces & (uint8_t)faceID);
		}
	};

	class Block
	{
	public:
		Block(BlockType blockType = BlockType::None, glm::vec3 chunkPosition = { 0.0f, 0.0f, 0.0f })
			: m_BlockType(blockType), m_ChunkPosition(chunkPosition)
		{
		}

		BlockMesh GenerateMesh(FaceAttributes faceAttributes, uint32_t indexOffset);

		void SetBlockType(BlockType blockType) { m_BlockType = blockType; }

		BlockType GetBlockType() { return m_BlockType; }
		const BlockType GetBlockType() const { return m_BlockType; }
	private:
		std::vector<float> GetTopFace();
		std::vector<float> GetBottomFace();
		std::vector<float> GetLeftFace();
		std::vector<float> GetRightFace();
		std::vector<float> GetFrontFace();
		std::vector<float> GetRearFace();
	private:
		BlockType m_BlockType = BlockType::None;
		glm::vec3 m_ChunkPosition = {0.0f, 0.0f, 0.0f};
	public:
		static void SetTextureAtlasSize(float width, float height) { s_TextureAtlasWidth = width; s_TextureAtlasHeight = height; s_TextureSizeInitialized = true; }
	private:
		static float s_TextureAtlasWidth, s_TextureAtlasHeight;
		static bool s_TextureSizeInitialized;
	};


}