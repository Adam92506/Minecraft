#include "mcpch.h"
#include "Chunk.h"

namespace Minecraft
{

	bool Chunk::s_TextureSizeInitialized = false;
	float Chunk::s_TextureAtlasWidth = 0.0f, Chunk::s_TextureAtlasHeight = 0.0f;

	void Chunk::GenerateMesh()
	{
		Timer time;

		std::vector<float> verticies;
		std::vector<uint32_t> indecies;

		for (float y = 0.0f; y < MC_CHUNK_HEIGHT; y++)
		{
			for (float z = 0.0f; z < MC_CHUNK_SIZE; z++)
			{
				for (float x = 0.0f; x < MC_CHUNK_SIZE; x++)
				{
					Block& block = m_Blocks[x][y][z];

					if (block.GetBlockType() != BlockType::Air)
					{
						FaceAttributes faceAttributes(
							CheckTopFace({ x, y, z }), CheckBottomFace({ x, y, z }), CheckLeftFace({ x, y, z }),
							CheckRightFace({ x, y, z }), CheckFrontFace({ x, y, z }), CheckRearFace({ x, y, z }));

						
						BlockMesh blockMesh = block.GenerateMesh(faceAttributes, verticies.size() / 5);

						verticies.insert(verticies.end(), blockMesh.Verticies.begin(), blockMesh.Verticies.end());
						indecies.insert(indecies.begin(), blockMesh.Indecies.begin(), blockMesh.Indecies.end());
					};
				}
			}
		}

		m_VertexBuffer = VertexBuffer::Create(verticies.data(), verticies.size() * sizeof(float));
		m_VertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});

		m_IndexBuffer = IndexBuffer::Create(indecies.data(), indecies.size());

		m_VertexArray = VertexArray::Create();
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		MC_WARN("Generated chunk mesh in {0}ms:", time.ElapsedMillis());
		MC_WARN("   Verticies: {0}", verticies.size() / 5);
		MC_WARN("   Faces: {0}", indecies.size() / 6);
		MC_WARN("   Indecies: {0}", indecies.size());
	}

	void Chunk::GenerateBlockData()
	{
		for (float y = 0.0f; y < MC_CHUNK_HEIGHT; y++)
		{
			for (float z = 0.0f; z < MC_CHUNK_SIZE; z++)
			{
				for (float x = 0.0f; x < MC_CHUNK_SIZE; x++)
				{
					if (y == 0)
					{
						m_Blocks[x][y][z] = Block(BlockType::Bedrock, { x, y, z });
					}

					else if (y > 0 && y <= 80)
					{
						m_Blocks[x][y][z] = Block(BlockType::Stone, { x, y, z });
					}

					else if (y > 80 && y <= 84)
					{
						m_Blocks[x][y][z] = Block(BlockType::Dirt, { x, y, z });
					}

					else if (y == 85)
					{
						m_Blocks[x][y][z] = Block(BlockType::Grass, { x, y, z });
					}

					else
					{
						m_Blocks[x][y][z] = Block(BlockType::Air, { x, y, z });
					}

				}
			}
		}
	}

	bool Chunk::CheckTopFace(glm::vec3 chunkPosition)
	{
		float yOffset = chunkPosition.y + 1.0f;

		if (!(yOffset < 0 || yOffset >= MC_CHUNK_HEIGHT))
		{
			if (m_Blocks[chunkPosition.x][yOffset][chunkPosition.z].GetBlockType() == BlockType::Air)
			{
				return true;
			}

			return false;
		}

		return true;
	}

	bool Chunk::CheckBottomFace(glm::vec3 chunkPosition)
	{
		float yOffset = chunkPosition.y - 1.0f;

		if (!(yOffset < 0 || yOffset >= MC_CHUNK_HEIGHT))
		{
			if (m_Blocks[chunkPosition.x][yOffset][chunkPosition.z].GetBlockType() == BlockType::Air)
			{
				return true;
			}

			return false;
		}

		return true;
	}

	bool Chunk::CheckLeftFace(glm::vec3 chunkPosition)
	{
		float xOffset = chunkPosition.x + 1.0f;

		if (!(xOffset < 0 || xOffset >= MC_CHUNK_SIZE))
		{
			if (m_Blocks[xOffset][chunkPosition.y][chunkPosition.z].GetBlockType() == BlockType::Air)
			{
				return true;
			}

			return false;
		}

		return true;
	}

	bool Chunk::CheckRightFace(glm::vec3 chunkPosition)
	{
		float xOffset = chunkPosition.x - 1.0f;

		if (!(xOffset < 0 || xOffset >= MC_CHUNK_SIZE))
		{
			if (m_Blocks[xOffset][chunkPosition.y][chunkPosition.z].GetBlockType() == BlockType::Air)
			{
				return true;
			}

			return false;
		}

		return true;
	}

	bool Chunk::CheckFrontFace(glm::vec3 chunkPosition)
	{
		float zOffset = chunkPosition.z + 1.0f;

		if (!(zOffset < 0 || zOffset >= MC_CHUNK_SIZE))
		{
			if (m_Blocks[chunkPosition.x][chunkPosition.y][zOffset].GetBlockType() == BlockType::Air)
			{
				return true;
			}

			return false;
		}

		return true;
	}

	bool Chunk::CheckRearFace(glm::vec3 chunkPosition)
	{
		float zOffset = chunkPosition.z - 1.0f;

		if (!(zOffset < 0 || zOffset >= MC_CHUNK_SIZE))
		{
			if (m_Blocks[chunkPosition.x][chunkPosition.y][zOffset].GetBlockType() == BlockType::Air)
			{
				return true;
			}

			return false;
		}

		return true;
	}

}