#pragma once

#include "Texture.h"

#include "Minecraft/Utils/Image.h"

namespace Minecraft
{

	class TextureAtlas
	{
	public:
		TextureAtlas() = default;
		TextureAtlas(const std::string& folderPath, uint32_t textureWidth, uint32_t textureHeight, ImageFormat imageFormat)
			: m_FolderPath(folderPath), m_TextureWidth(textureWidth), m_TextureHeight(textureHeight), m_ImageFormat(imageFormat), m_AtlasSize(0) {}

		void GenerateTextureAtlas();

		uint16_t GetTextureID(const std::string& textureName) { return m_TextureIDMap[textureName]; }

		uint32_t GetAtlasSize() const { return m_AtlasSize; }
		uint32_t GetTextureWidth() const { return m_TextureWidth; }
		uint32_t GetTextureHeight() const { return m_TextureHeight; }

		const Ref<Texture2D>& GetTexture() const { return m_Texture; }
	private:
		void InsertSubTexture(uint32_t index, uint8_t* atlasImage, uint8_t* subTextureImage);
	private:
		Ref<Texture2D> m_Texture;
		bool m_TextureGenerated = false;

		uint32_t m_AtlasSize;
		uint32_t m_TextureWidth, m_TextureHeight;
		ImageFormat m_ImageFormat;

		std::unordered_map<std::string, uint16_t> m_TextureIDMap;

		std::string m_FolderPath;
	};

}