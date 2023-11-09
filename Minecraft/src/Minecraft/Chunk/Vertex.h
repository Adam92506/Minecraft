#pragma once

#include <glm/glm.hpp>

namespace Minecraft
{

	namespace Vertex
	{

		uint32_t CompressVertexData(const glm::uvec3& position, uint16_t textureID, const glm::uvec2 uv);

	}
	
};