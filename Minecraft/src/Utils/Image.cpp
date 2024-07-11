#include "pch.h"
#include "Image.h"

#include <stb_image.h>

namespace Minecraft
{

	Image::Image(const std::string filePath, bool flipImage)
		: FilePath(filePath)
	{
		// TODO: Validate filepath

		int width, height, channels;
		stbi_set_flip_vertically_on_load(flipImage);
		ImageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

		if (ImageData)
		{
			Width = (uint32_t)width;
			Height = (uint32_t)height;

			if (channels == 2)
			{
				Format = ImageFormat::RG8;
			}

			else if (channels == 3)
			{
				Format = ImageFormat::RGB8;
			}

			else if (channels == 4)
			{
				Format = ImageFormat::RGBA8;
			}

			else
			{
				MC_ERROR("Unable To Load Image: Image Format Not Supported");
			}
		}

		else
		{
			MC_ERROR("Failed To Load Image: {0}", filePath);
		}
	}

	Image::Image(uint32_t width, uint32_t height, ImageFormat format)
		: Width(width), Height(height), Format(format)
	{
		Size = Width * Height * Utils::ImageFormatToSize(format);
		ImageData = new uint8_t[Size];
	}

	Image::~Image()
	{
		delete[] ImageData;
	}

	void Image::FlipVerticaly()
	{
		uint32_t bufferWidth = Width * Utils::ImageFormatToSize(Format);
		uint8_t* buffer = new uint8_t[bufferWidth];

		uint32_t endIndex = Height - 1;
		for (uint32_t i = 0; i < Height / 2; i++)
		{
			memcpy(buffer, ImageData + i * bufferWidth, bufferWidth);
			memcpy(ImageData + i * bufferWidth, ImageData + (endIndex - i) * bufferWidth, bufferWidth);
			memcpy(ImageData + (endIndex - i) * bufferWidth, buffer, bufferWidth);
		}

		delete[] buffer;
	}

	namespace Utils
	{
		uint32_t ImageFormatToSize(ImageFormat imageFormat)
		{
			switch (imageFormat)
			{
				case Minecraft::ImageFormat::None:    return 0;
				case Minecraft::ImageFormat::R8:      return 1;
				case Minecraft::ImageFormat::RG8:     return 2;
				case Minecraft::ImageFormat::RGB8:    return 3;
				case Minecraft::ImageFormat::RGBA8:   return 4;
				case Minecraft::ImageFormat::RGBA32F: return 4 * sizeof(float);
				default:                              return 0;
			}
		}

		std::string ImageFormatToString(ImageFormat imageFormat)
		{
			switch (imageFormat)
			{
				case Minecraft::ImageFormat::None:    return "None";
				case Minecraft::ImageFormat::R8:      return "R8";
				case Minecraft::ImageFormat::RG8:     return "RG8";
				case Minecraft::ImageFormat::RGB8:    return "RGB8";
				case Minecraft::ImageFormat::RGBA8:   return "RGBA8";
				case Minecraft::ImageFormat::RGBA32F: return "RGBA32F";
				default:                              return "Invalid";
			}
		}

	}

}

