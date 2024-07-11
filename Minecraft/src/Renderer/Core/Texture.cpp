#include "pch.h"
#include "Texture.h"

namespace Minecraft
{

	namespace Utils
	{

		static GLenum MinecraftImageFormatToGLDataFormat(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::RG8:	   return GL_RG;
			case ImageFormat::RGB8:	   return GL_RGB;
			case ImageFormat::RGBA8:   return GL_RGBA;
			case ImageFormat::RGBA32F: return GL_RGBA;
			}

			MC_ASSERT(false, "Image format not supported");
			return 0;
		}

		static GLenum MinecraftImageFormatToGLInternalFormat(ImageFormat format)
		{
			switch (format)
			{
			case ImageFormat::RG8:     return GL_RG8;
			case ImageFormat::RGB8:    return GL_RGB8;
			case ImageFormat::RGBA8:   return GL_RGBA8;
			case ImageFormat::RGBA32F: return GL_RGBA32F;
			}

			MC_ASSERT(false, "Image format not supported");
			return 0;
		}

	}

	Texture2D::Texture2D(Image& image)
	{
		if (image.ImageData)
		{
			CreateTexture(image);
		}
	}

	Texture2D::Texture2D(const std::string& filepath)
	{
		Image image(filepath, true);

		if (image.ImageData)
		{
			CreateTexture(image);
		}
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void Texture2D::CreateTexture(Image& image)
	{
		m_Width = image.Width;
		m_Height = image.Height;

		m_InternalFormat = Utils::MinecraftImageFormatToGLInternalFormat(image.Format);
		m_DataFormat = Utils::MinecraftImageFormatToGLDataFormat(image.Format);

		MC_ASSERT(m_InternalFormat & m_DataFormat, "Unable To Create Texture: Format Not Supported");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, image.ImageData);

		m_IsLoaded = true;
	}

	Ref<Texture2D> Texture2D::Create(Image& image)
	{
		return CreateRef<Texture2D>(image);
	}

	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		return CreateRef<Texture2D>(filepath);
	}

}