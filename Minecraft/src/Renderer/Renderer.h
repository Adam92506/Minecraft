#pragma once

#include "Core/Shader.h"
#include "Core/Texture.h"
#include "Core/VertexArray.h"
#include "Core/RenderCommand.h"

#include "Camera.h"

namespace Minecraft
{

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void LoadShaders();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(const Camera& camera);
		static void EndScene();
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};

}