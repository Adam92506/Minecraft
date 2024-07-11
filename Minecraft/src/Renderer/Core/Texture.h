#pragma once

#include "Utils/Image.h"

#include <glad/glad.h>

namespace Minecraft
{

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual const std::string& GetFilepath() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool IsLoaded() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D(Image& image);
		Texture2D(const std::string& filepath);
		virtual ~Texture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; };
		virtual uint32_t GetRendererID() const override { return m_RendererID; };

		virtual const std::string& GetFilepath() const override { return m_Filepath; };

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool IsLoaded() const override { return m_IsLoaded; }
	public:
		static Ref<Texture2D> Create(Image& image);
		static Ref<Texture2D> Create(const std::string& filepath);
	private:
		void CreateTexture(Image& image);
	private:
		std::string m_Filepath;
		bool m_IsLoaded = false;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat,m_DataFormat;
	};

}