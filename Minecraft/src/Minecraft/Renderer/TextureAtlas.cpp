#include "mcpch.h"
#include "TextureAtlas.h"

#include <filesystem>
#include <stb_image_write.h>

#include "Minecraft/Core/Timer.h"

namespace Minecraft
{

	void TextureAtlas::GenerateTextureAtlas()
	{
		Timer timer;

		uint32_t imageCount = 0;
		for (const auto& image : std::filesystem::directory_iterator(m_FolderPath)) { imageCount++; }

		m_AtlasSize = std::ceil(sqrtf(imageCount));
		Image atlasImage(m_AtlasSize * m_TextureWidth, m_AtlasSize * m_TextureHeight, m_ImageFormat);

		uint32_t index = 0;
		for (const auto& file : std::filesystem::directory_iterator(m_FolderPath))
		{
			Image image(file.path().generic_string(), false);

			if ((image.Format == m_ImageFormat) && (image.Width == m_TextureWidth) && (image.Height == m_TextureHeight))
			{
				InsertSubTexture(index, atlasImage.ImageData, image.ImageData);

				m_TextureIDMap.insert({ file.path().stem().generic_string(), index });

				index++;
			}

			else
			{
				MC_WARN("Unable to add texture to atlas: {0}", file.path().generic_string());
			}
		}

		if (atlasImage.ImageData)
		{
			atlasImage.FlipVerticaly();

			m_Texture = Texture2D::Create(atlasImage);
			m_TextureGenerated = true;

			MC_WARN("Generated texture atlas ({0} textures) in {1} ms", index, timer.ElapsedMillis());
		}
	}

	void TextureAtlas::InsertSubTexture(uint32_t index, uint8_t* atlasImage, uint8_t* subTextureImage)
	{
		uint32_t pixelSize = Utils::ImageFormatToSize(m_ImageFormat);
		uint32_t textureWidth = m_TextureWidth * pixelSize;
		uint32_t atlasWidth = m_AtlasSize * textureWidth;
		
		for (uint32_t y = 0; y < m_TextureHeight; y++)
		{
			uint32_t yPos = (m_AtlasSize - std::floorf(index / m_AtlasSize) - 1) * m_TextureHeight + y;
			for (uint32_t x = 0; x < textureWidth; x++)
			{
				uint32_t xPos = (index % m_AtlasSize) * textureWidth + x;

				atlasImage[xPos + (yPos * atlasWidth)] = subTextureImage[x + (y * textureWidth)];
			}
		}
	}

}