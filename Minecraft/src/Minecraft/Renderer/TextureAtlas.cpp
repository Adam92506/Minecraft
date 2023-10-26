#include "mcpch.h"
#include "TextureAtlas.h"

namespace Minecraft
{

	TextureAtlas::TextureAtlas(const std::string& filepath, float textureWidth, float textureHeight)
		: m_Filepath(filepath), m_TextureWidth(textureWidth), m_TextureHeight(textureHeight)
	{
		m_Texture = Texture2D::Create(filepath);

		m_AtlasWidth = m_Texture->GetWidth();
		m_AtlasHeight = m_Texture->GetHeight();
	}

}