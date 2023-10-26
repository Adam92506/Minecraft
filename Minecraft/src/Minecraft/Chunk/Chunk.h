#pragma once

#include "Block.h"

#include "Minecraft/Renderer/VertexArray.h"
#include "Minecraft/Renderer/Buffer.h"

#include "Minecraft/Core/Timer.h"

#define MC_CHUNK_SIZE 16
#define MC_CHUNK_HEIGHT 256
#define MC_CHUNK_Y_LEVEL_AREA MC_CHUNK_SIZE * MC_CHUNK_SIZE
#define MC_CHUNK_AREA MC_CHUNK_Y_LEVEL_AREA * MC_CHUNK_HEIGHT

namespace Minecraft
{

	class Chunk
	{
	public:
		Chunk(glm::vec3 worldPosition = { 0.0f, 0.0f, 0.0f })
			: m_WorldPosition(worldPosition)
		{
			m_Blocks = std::vector<std::vector<std::vector<Block>>>(MC_CHUNK_SIZE, std::vector<std::vector<Block>>(MC_CHUNK_HEIGHT, std::vector<Block>(MC_CHUNK_SIZE)));
			GenerateBlockData();
		}

		void GenerateMesh();

		const Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }
		const std::vector<std::vector<std::vector<Block>>>& GetBlocks() const { return m_Blocks; }

		BlockType GetBlockType(glm::vec3 chunkPosition) const { return m_Blocks[chunkPosition.x][chunkPosition.y][chunkPosition.z].GetBlockType(); }
	
	private:
		void GenerateBlockData();

		bool CheckTopFace(glm::vec3 chunkPosition);
		bool CheckBottomFace(glm::vec3 chunkPosition);
		bool CheckLeftFace(glm::vec3 chunkPosition);
		bool CheckRightFace(glm::vec3 chunkPosition);
		bool CheckFrontFace(glm::vec3 chunkPosition);
		bool CheckRearFace(glm::vec3 chunkPosition);
	private:
		glm::vec3 m_WorldPosition;

		std::vector<std::vector<std::vector<Block>>> m_Blocks;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	public:
		static void SetTextureAtlasSize(float width, float height) 
		{ 
			s_TextureAtlasWidth = width; 
			s_TextureAtlasHeight = height;
			s_TextureSizeInitialized = true;
			Block::SetTextureAtlasSize(width, height);
		}
	private:
		static float s_TextureAtlasWidth, s_TextureAtlasHeight;
		static bool s_TextureSizeInitialized;
	};

}