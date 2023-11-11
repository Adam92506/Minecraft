#pragma once

#include "Minecraft/Renderer/VertexArray.h"
#include "Minecraft/Renderer/Buffer.h"

#include "Block.h"

#define MC_CHUNK_BUFFER_SIZE 15000
#define MC_CHUNK_SIZE_X 16
#define MC_CHUNK_SIZE_Y 255
#define MC_CHUNK_SIZE_Z 16

namespace Minecraft
{

	class Chunk
	{
	public:
		Chunk() = default;
		Chunk(const glm::ivec3& chunkPosition);
		
		~Chunk();

		Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }

		void GenerateRenderData();

		// Temp
		void GenerateBlockData();

		const Block& GetBlock(const glm::ivec3& position) const;

		uint32_t GetVertexCount() const { return m_VertexCount; }
		uint32_t GetBufferSize() const { return m_BufferSize; }

	private:
		void AddBlockVerticies(const glm::ivec3& position, bool topFace, bool bottomFace,
			bool frontFace, bool rearFace, bool leftFace, bool rightFace, Block& block);

		void ResizeBuffer(uint32_t size, bool saveMem = false);

		const Block& GetAdjactentBlock(const glm::ivec3& position, Face face) const;

		bool IsBlockInChunk(const glm::ivec3& position) const;
	private:
		glm::ivec3 m_ChunkPosition = {0, 0, 0};

		uint32_t m_BufferSize = 0;
		uint32_t m_VertexCount = 0;
		uint32_t* m_Verticies = nullptr;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;

		Block* m_BlockData = nullptr;
	};

}