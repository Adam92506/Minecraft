#include "mcpch.h"
#include "Block.h"

#include "Minecraft/Core/Timer.h"

#include "Minecraft/Renderer/TextureAtlas.h"

#define MC_FACE_VERTEX_COUNT 4

namespace Minecraft
{

	bool Block::s_TextureSizeInitialized = false;
	float Block::s_TextureAtlasWidth = 0.0f, Block::s_TextureAtlasHeight = 0.0f;

	const uint32_t FaceIndecies[6] = {
			0, 2, 3, 1, 2, 0
	};

	std::vector<float> Block::GetTopFace()
	{
		glm::vec2 texturePos = GetTexturePosFromID(m_BlockType, Face::Top);

		std::vector<float> verticies = {
			m_ChunkPosition.x, (m_ChunkPosition.y + 1.0f), m_ChunkPosition.z, (texturePos.x * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), (m_ChunkPosition.y + 1.0f), m_ChunkPosition.z, ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), (m_ChunkPosition.y + 1.0f), (m_ChunkPosition.z + 1.0f), ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
			m_ChunkPosition.x, (m_ChunkPosition.y + 1.0f), (m_ChunkPosition.z + 1.0f), (texturePos.x * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
		};

		return verticies;
	}

	std::vector<float> Block::GetBottomFace()
	{
		glm::vec2 texturePos = GetTexturePosFromID(m_BlockType, Face::Bottom);

		std::vector<float> verticies = {
			m_ChunkPosition.x, m_ChunkPosition.y, (m_ChunkPosition.z + 1.0f), (texturePos.x * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), m_ChunkPosition.y, (m_ChunkPosition.z + 1.0f), ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), m_ChunkPosition.y, m_ChunkPosition.z, ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
			m_ChunkPosition.x, m_ChunkPosition.y, m_ChunkPosition.z, (texturePos.x * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
		};

		return verticies;
	}

	std::vector<float> Block::GetLeftFace()
	{
		glm::vec2 texturePos = GetTexturePosFromID(m_BlockType, Face::Right);

		std::vector<float> verticies = {
			(m_ChunkPosition.x + 1.0f), m_ChunkPosition.y, m_ChunkPosition.z, (texturePos.x * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), m_ChunkPosition.y, (m_ChunkPosition.z + 1.0f), ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), (m_ChunkPosition.y + 1.0f), (m_ChunkPosition.z + 1.0f), ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), (m_ChunkPosition.y + 1.0f), m_ChunkPosition.z, (texturePos.x * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
		};

		return verticies;
	}

	std::vector<float> Block::GetRightFace()
	{
		glm::vec2 texturePos = GetTexturePosFromID(m_BlockType, Face::Left);

		std::vector<float> verticies = {
			m_ChunkPosition.x, m_ChunkPosition.y, (m_ChunkPosition.z + 1.0f), (texturePos.x * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			m_ChunkPosition.x, m_ChunkPosition.y, m_ChunkPosition.z, ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			m_ChunkPosition.x, (m_ChunkPosition.y + 1.0f), m_ChunkPosition.z, ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
			m_ChunkPosition.x, (m_ChunkPosition.y + 1.0f), (m_ChunkPosition.z + 1.0f), (texturePos.x * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
		};

		return verticies;
	}

	std::vector<float> Block::GetFrontFace()
	{
		glm::vec2 texturePos = GetTexturePosFromID(m_BlockType, Face::Front);

		std::vector<float> verticies = {
			(m_ChunkPosition.x + 1.0f), m_ChunkPosition.y, (m_ChunkPosition.z + 1.0f), (texturePos.x * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			m_ChunkPosition.x, m_ChunkPosition.y, (m_ChunkPosition.z + 1.0f), ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			m_ChunkPosition.x, (m_ChunkPosition.y + 1.0f), (m_ChunkPosition.z + 1.0f), ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), (m_ChunkPosition.y + 1.0f), (m_ChunkPosition.z + 1.0f), (texturePos.x * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
		};

		return verticies;
	}

	std::vector<float> Block::GetRearFace()
	{
		glm::vec2 texturePos = GetTexturePosFromID(m_BlockType, Face::Rear);

		std::vector<float> verticies = {
			m_ChunkPosition.x, m_ChunkPosition.y, m_ChunkPosition.z, (texturePos.x * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), m_ChunkPosition.y, m_ChunkPosition.z, ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, (texturePos.y * 16) / s_TextureAtlasHeight,
			(m_ChunkPosition.x + 1.0f), (m_ChunkPosition.y + 1.0f), m_ChunkPosition.z, ((texturePos.x + 1) * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
			m_ChunkPosition.x, (m_ChunkPosition.y + 1.0f), m_ChunkPosition.z, (texturePos.x * 16) / s_TextureAtlasHeight, ((texturePos.y + 1) * 16) / s_TextureAtlasHeight,
		};

		return verticies;
	}

	BlockMesh Block::GenerateMesh(FaceAttributes faceAttributes, uint32_t indexOffset)
	{
		MC_ASSERT(s_TextureSizeInitialized, "Cannot Generate Block Mesh: Texture Atlas Had Not Been Initialized")

		uint32_t faceIndexOffset = 0;

		BlockMesh blockMesh;
		std::vector<float> faceVerticies;

		if (faceAttributes.IsFaceEnabled(Face::Top))
		{
			faceVerticies = GetTopFace();
			blockMesh.Verticies.insert(blockMesh.Verticies.end(), faceVerticies.begin(), faceVerticies.end());

			for (int i = 0; i < 6; i++)
			{
				blockMesh.Indecies.push_back(FaceIndecies[i] + faceIndexOffset + indexOffset);
			}

			faceIndexOffset += MC_FACE_VERTEX_COUNT;
		}

		if (faceAttributes.IsFaceEnabled(Face::Bottom))
		{
			faceVerticies = GetBottomFace();
			blockMesh.Verticies.insert(blockMesh.Verticies.end(), faceVerticies.begin(), faceVerticies.end());

			for (int i = 0; i < 6; i++)
			{
				blockMesh.Indecies.push_back(FaceIndecies[i] + faceIndexOffset + indexOffset);
			}

			faceIndexOffset += MC_FACE_VERTEX_COUNT;
		}

		if (faceAttributes.IsFaceEnabled(Face::Left))
		{
			faceVerticies = GetLeftFace();
			blockMesh.Verticies.insert(blockMesh.Verticies.end(), faceVerticies.begin(), faceVerticies.end());

			for (int i = 0; i < 6; i++)
			{
				blockMesh.Indecies.push_back(FaceIndecies[i] + faceIndexOffset + indexOffset);
			}

			faceIndexOffset += MC_FACE_VERTEX_COUNT;
		}

		if (faceAttributes.IsFaceEnabled(Face::Right))
		{
			faceVerticies = GetRightFace();
			blockMesh.Verticies.insert(blockMesh.Verticies.end(), faceVerticies.begin(), faceVerticies.end());

			for (int i = 0; i < 6; i++)
			{
				blockMesh.Indecies.push_back(FaceIndecies[i] + faceIndexOffset + indexOffset);
			}

			faceIndexOffset += MC_FACE_VERTEX_COUNT;
		}

		if (faceAttributes.IsFaceEnabled(Face::Front))
		{
			faceVerticies = GetFrontFace();
			blockMesh.Verticies.insert(blockMesh.Verticies.end(), faceVerticies.begin(), faceVerticies.end());

			for (int i = 0; i < 6; i++)
			{
				blockMesh.Indecies.push_back(FaceIndecies[i] + faceIndexOffset + indexOffset);
			}

			faceIndexOffset += MC_FACE_VERTEX_COUNT;
		}

		if (faceAttributes.IsFaceEnabled(Face::Rear))
		{
			faceVerticies = GetRearFace();
			blockMesh.Verticies.insert(blockMesh.Verticies.end(), faceVerticies.begin(), faceVerticies.end());

			for (int i = 0; i < 6; i++)
			{
				blockMesh.Indecies.push_back(FaceIndecies[i] + faceIndexOffset + indexOffset);
			}

			faceIndexOffset += MC_FACE_VERTEX_COUNT;
		}

		return blockMesh;
	}

}