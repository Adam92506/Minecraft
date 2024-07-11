#pragma once

#include "VertexArray.h"

namespace Minecraft
{

	class RendererAPI
	{
	public:
		void Init();
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		void SetClearColor(const glm::vec4& color);
		void Clear();

		void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount);
		void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t indexCount);

		void SetLineWidth(float width);

		static Scope<RendererAPI> Create();
	};

}