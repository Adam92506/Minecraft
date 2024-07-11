#pragma once

namespace Minecraft
{

	enum class ImageFormat
	{
		None = 0,
		R8,
		RG8,
		RGB8,
		RGBA8,
		RGBA32F
	};

	struct Image
	{
		uint8_t* ImageData;
		uint32_t Width, Height, Size;
		ImageFormat Format;
		std::string FilePath;

		Image(const std::string filePath, bool flipImage);
		Image(uint32_t width, uint32_t height, ImageFormat format);

		~Image();

		void FlipVerticaly();
	};

	namespace Utils
	{

		uint32_t ImageFormatToSize(ImageFormat imageFormat);

		std::string ImageFormatToString(ImageFormat imageFormat);

	}

}