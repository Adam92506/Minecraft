#pragma once

#include "Texture.h"

namespace Minecraft
{

	class TextureAtlas
	{
	public:
		TextureAtlas() = default;
		TextureAtlas(const std::string& filepath, float textureWidth, float textureHeight);

		const Ref<Texture2D>& GetTexture() const { return m_Texture; }

		const float GetAtlasWidth() const { return m_AtlasWidth; }
		const float GetAtlasHeight() const { return m_AtlasHeight; }
		const float GetTextureWidth() const { return m_TextureWidth; }
		const float GetTextureHeight() const { return m_TextureHeight; }
	private:
		float m_AtlasWidth, m_AtlasHeight;
		float m_TextureWidth, m_TextureHeight;

		Ref<Texture2D> m_Texture;

		std::string m_Filepath;
	};

}