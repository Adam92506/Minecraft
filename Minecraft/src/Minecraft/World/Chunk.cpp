#include "mcpch.h"
#include "Chunk.h"

#include "Minecraft/Config/Config.h"

#include "Minecraft/Core/Application.h"

namespace Minecraft
{

	Chunk::Chunk(const glm::ivec3& chunkPosition)
		: m_ChunkPosition(chunkPosition)
	{
		ResizeBuffer(MC_CHUNK_BUFFER_SIZE);

		m_VertexArray = VertexArray::Create();
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_BlockData = new Block[MC_CHUNK_SIZE_X * MC_CHUNK_SIZE_Y * MC_CHUNK_SIZE_Z];
	}

	Chunk::~Chunk()
	{
		delete[] m_Verticies;
		delete[] m_BlockData;
	}

	void Chunk::GenerateRenderData()
	{
		m_VertexCount = 0;

		
		for (uint32_t y = 0; y < MC_CHUNK_SIZE_Y; y++)
		{
			for (uint32_t z = 0; z < MC_CHUNK_SIZE_Z; z++)
			{
				for (uint32_t x = 0; x < MC_CHUNK_SIZE_X; x++)
				{
					Block block = GetBlock({ x, y, z });

					if (!block.IsTransparent())
					{
						bool drawTopFace = false;
						bool drawBottomFace = false;
						bool drawFrontFace = false;
						bool drawRearFace = false;
						bool drawLeftFace = false;
						bool drawRightFace = false;

						if (GetAdjactentBlock({ x, y, z }, Face::Top).IsTransparent())
							drawTopFace = true;

						if (GetAdjactentBlock({ x, y, z }, Face::Bottom).IsTransparent())
							drawBottomFace = true;

						if (GetAdjactentBlock({ x, y, z }, Face::Front).IsTransparent())
							drawFrontFace = true;

						if (GetAdjactentBlock({ x, y, z }, Face::Rear).IsTransparent())
							drawRearFace = true;

						if (GetAdjactentBlock({ x, y, z }, Face::Left).IsTransparent())
							drawLeftFace = true;

						if (GetAdjactentBlock({ x, y, z }, Face::Right).IsTransparent())
							drawRightFace = true;


						if (m_VertexCount + (6 * 4 * sizeof(uint32_t)) >= m_BufferSize)
						{
							ResizeBuffer(m_BufferSize + 1000, true);
						}

						AddBlockVerticies({ x, y, z }, drawTopFace, drawBottomFace, drawFrontFace, drawRearFace, drawLeftFace, drawRightFace, block);

					}
				}
			}
		}
		
		//Block block = GetBlock({ 0, 0, 0 });
		//AddBlockVerticies({ 0, 0, 0 }, false, false, false, true, false, false, block);

		m_VertexBuffer->SetData(m_Verticies, m_BufferSize * sizeof(uint32_t));
	}

	void Chunk::GenerateBlockData()
	{
		for (uint32_t y = 0; y < MC_CHUNK_SIZE_Y; y++)
		{
			for (uint32_t z = 0; z < MC_CHUNK_SIZE_Z; z++)
			{
				for (uint32_t x = 0; x < MC_CHUNK_SIZE_X; x++)
				{
					if (y == 0)
					{
						m_BlockData[x + (z * MC_CHUNK_SIZE_X) + (y * MC_CHUNK_SIZE_X * MC_CHUNK_SIZE_Z)] = Block("bedrock");
					}

					else if (y > 0 && y <= 60)
					{
						m_BlockData[x + (z * MC_CHUNK_SIZE_X) + (y * MC_CHUNK_SIZE_X * MC_CHUNK_SIZE_Z)] = Block("stone");
					}

					else if (y > 60 && y <= 64)
					{
						m_BlockData[x + (z * MC_CHUNK_SIZE_X) + (y * MC_CHUNK_SIZE_X * MC_CHUNK_SIZE_Z)] = Block("dirt");
					}

					else if (y == 65)
					{
						m_BlockData[x + (z * MC_CHUNK_SIZE_X) + (y * MC_CHUNK_SIZE_X * MC_CHUNK_SIZE_Z)] = Block("grass_block");
					}

					else
					{
						m_BlockData[x + (z * MC_CHUNK_SIZE_X) + (y * MC_CHUNK_SIZE_X * MC_CHUNK_SIZE_Z)] = Block("air_block");
					}
				}
			}
		}
	}

	const Block& Chunk::GetBlock(const glm::ivec3& position) const
	{
		uint32_t index = position.x + (position.z * MC_CHUNK_SIZE_X) + (position.y * MC_CHUNK_SIZE_X * MC_CHUNK_SIZE_Z);
		return m_BlockData[index];
	}

	void Chunk::AddBlockVerticies(const glm::ivec3& position, bool topFace, bool bottomFace,
		bool frontFace, bool rearFace, bool leftFace, bool rightFace, Block& block)
	{
		TextureAtlas& textureAtlas = Application::GetTextureAtlas();

		uint16_t topTexID = textureAtlas.GetTextureID(block.GetTopTexture());
		uint16_t bottomTexID = textureAtlas.GetTextureID(block.GetBottomTexture());
		uint16_t sideTexID = textureAtlas.GetTextureID(block.GetSideTexture());

		if (topFace)
		{
			m_Verticies[m_VertexCount + 0] = Vertex::CompressVertexData({ position.x + 1, position.y + 1, position.z + 0 }, topTexID, { 0, 0 });
			m_Verticies[m_VertexCount + 1] = Vertex::CompressVertexData({ position.x + 0, position.y + 1, position.z + 0 }, topTexID, { 1, 0 });
			m_Verticies[m_VertexCount + 2] = Vertex::CompressVertexData({ position.x + 0, position.y + 1, position.z + 1 }, topTexID, { 1, 1 });
			m_Verticies[m_VertexCount + 3] = Vertex::CompressVertexData({ position.x + 1, position.y + 1, position.z + 1 }, topTexID, { 0, 1 });

			m_VertexCount += 4;
		}

		if (bottomFace)
		{
			m_Verticies[m_VertexCount + 0] = Vertex::CompressVertexData({ position.x + 1, position.y + 0, position.z + 1 }, bottomTexID, { 0, 0 });
			m_Verticies[m_VertexCount + 1] = Vertex::CompressVertexData({ position.x + 0, position.y + 0, position.z + 1 }, bottomTexID, { 1, 0 });
			m_Verticies[m_VertexCount + 2] = Vertex::CompressVertexData({ position.x + 0, position.y + 0, position.z + 0 }, bottomTexID, { 1, 1 });
			m_Verticies[m_VertexCount + 3] = Vertex::CompressVertexData({ position.x + 1, position.y + 0, position.z + 0 }, bottomTexID, { 0, 1 });

			m_VertexCount += 4;
		}

		if (frontFace)
		{
			m_Verticies[m_VertexCount + 0] = Vertex::CompressVertexData({ position.x + 0, position.y + 0, position.z + 1 }, sideTexID, { 0, 0 });
			m_Verticies[m_VertexCount + 1] = Vertex::CompressVertexData({ position.x + 1, position.y + 0, position.z + 1 }, sideTexID, { 1, 0 });
			m_Verticies[m_VertexCount + 2] = Vertex::CompressVertexData({ position.x + 1, position.y + 1, position.z + 1 }, sideTexID, { 1, 1 });
			m_Verticies[m_VertexCount + 3] = Vertex::CompressVertexData({ position.x + 0, position.y + 1, position.z + 1 }, sideTexID, { 0, 1 });

			m_VertexCount += 4;
		}

		if (rearFace)
		{
			m_Verticies[m_VertexCount + 0] = Vertex::CompressVertexData({ position.x + 1, position.y + 0, position.z + 0 }, sideTexID, { 0, 0 });
			m_Verticies[m_VertexCount + 1] = Vertex::CompressVertexData({ position.x + 0, position.y + 0, position.z + 0 }, sideTexID, { 1, 0 });
			m_Verticies[m_VertexCount + 2] = Vertex::CompressVertexData({ position.x + 0, position.y + 1, position.z + 0 }, sideTexID, { 1, 1 });
			m_Verticies[m_VertexCount + 3] = Vertex::CompressVertexData({ position.x + 1, position.y + 1, position.z + 0 }, sideTexID, { 0, 1 });

			m_VertexCount += 4;
		}

		if (rightFace)
		{
			m_Verticies[m_VertexCount + 0] = Vertex::CompressVertexData({ position.x + 0, position.y + 0, position.z + 0 }, sideTexID, { 0, 0 });
			m_Verticies[m_VertexCount + 1] = Vertex::CompressVertexData({ position.x + 0, position.y + 0, position.z + 1 }, sideTexID, { 1, 0 });
			m_Verticies[m_VertexCount + 2] = Vertex::CompressVertexData({ position.x + 0, position.y + 1, position.z + 1 }, sideTexID, { 1, 1 });
			m_Verticies[m_VertexCount + 3] = Vertex::CompressVertexData({ position.x + 0, position.y + 1, position.z + 0 }, sideTexID, { 0, 1 });

			m_VertexCount += 4;
		}

		if (leftFace)
		{
			m_Verticies[m_VertexCount + 0] = Vertex::CompressVertexData({ position.x + 1, position.y + 0, position.z + 1 }, sideTexID, { 0, 0 });
			m_Verticies[m_VertexCount + 1] = Vertex::CompressVertexData({ position.x + 1, position.y + 0, position.z + 0 }, sideTexID, { 1, 0 });
			m_Verticies[m_VertexCount + 2] = Vertex::CompressVertexData({ position.x + 1, position.y + 1, position.z + 0 }, sideTexID, { 1, 1 });
			m_Verticies[m_VertexCount + 3] = Vertex::CompressVertexData({ position.x + 1, position.y + 1, position.z + 1 }, sideTexID, { 0, 1 });

			m_VertexCount += 4;
		}
	}

	void Chunk::ResizeBuffer(uint32_t size, bool saveMem)
	{
		if (m_BufferSize != size)
		{
			if (!m_VertexBuffer)
			{
				m_VertexBuffer = VertexBuffer::Create(size * sizeof(uint32_t));
				m_VertexBuffer->SetLayout({
					{ ShaderDataType::UInt, "a_CompressedData" }
					});
			}
			else
			{
				m_VertexBuffer->Resize(size * sizeof(uint32_t));
			}

			uint32_t* verticies = new uint32_t[size];

			if (saveMem)
			{
				memcpy(verticies, m_Verticies, m_VertexCount * sizeof(uint32_t));
			}

			if (m_Verticies)
			{
				delete[] m_Verticies;
			}
			m_Verticies = verticies;

			uint32_t indexCount = (size / 4) * 6;
			uint32_t* indecies = new uint32_t[indexCount];

			uint32_t indexOffset = 0;
			for (uint32_t i = 0; i < indexCount; i += 6)
			{
				indecies[i + 0] = 0 + indexOffset;
				indecies[i + 1] = 1 + indexOffset;
				indecies[i + 2] = 2 + indexOffset;

				indecies[i + 3] = 2 + indexOffset;
				indecies[i + 4] = 3 + indexOffset;
				indecies[i + 5] = 0 + indexOffset;

				indexOffset += 4;
			}

			if (!m_IndexBuffer)
			{
				m_IndexBuffer = IndexBuffer::Create(indecies, indexCount);
			}
			else
			{
				m_IndexBuffer->Resize(indecies, indexCount);
			}
			delete[] indecies;

			m_BufferSize = size;
		}
	}

	const Block& Chunk::GetAdjactentBlock(const glm::ivec3& position, Face face) const
	{
		glm::ivec3 blockPosition;

		switch (face)
		{
			case Face::Top: 
				blockPosition = position + glm::ivec3(0, 1, 0); break;
			case Face::Bottom: 
				blockPosition = position + glm::ivec3(0, -1, 0); break;
			case Face::Front: 
				blockPosition = position + glm::ivec3(0, 0, 1); break;
			case Face::Rear: 
				blockPosition = position + glm::ivec3(0, 0, -1); break;
			case Face::Left: 
				blockPosition = position + glm::ivec3(1, 0, 0); break;
			case Face::Right: 
				blockPosition = position + glm::ivec3(-1, 0, 0); break;
			default: blockPosition = position;
		};

		if (!IsBlockInChunk(blockPosition))
		{
			return Block("air_block");
		}

		return GetBlock(blockPosition);
	}

	bool Chunk::IsBlockInChunk(const glm::ivec3& position) const
	{
		if ((position.x < 0 || position.x >= MC_CHUNK_SIZE_X) ||
			(position.y < 0 || position.y >= MC_CHUNK_SIZE_Y) ||
			(position.z < 0 || position.z >= MC_CHUNK_SIZE_Z))
		{
			return false;
		}

		return true;
	}

}