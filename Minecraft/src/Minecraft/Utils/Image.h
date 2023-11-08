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
		Image(const std::string filePath, bool flipImage);

		Image(uint32_t width, uint32_t height, ImageFormat format);

		Image(uint8_t* imageData, uint32_t width, uint32_t height, ImageFormat format)
			: ImageData(imageData), Width(width), Height(height), Format(format) {}

		~Image();

		void FlipVerticaly();

		uint8_t* ImageData;
		uint32_t Width = 0, Height = 0, Size = 0;
		ImageFormat Format = ImageFormat::None;
	};

	namespace Utils
	{

		uint32_t ImageFormatToSize(ImageFormat imageFormat);

		std::string ImageFormatToString(ImageFormat imageFormat);

	}

}