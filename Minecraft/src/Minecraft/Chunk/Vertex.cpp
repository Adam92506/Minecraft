#include "mcpch.h"
#include "Vertex.h"

#define VERTEX_POS_X_BITMASK 0xF
#define VERTEX_POS_Y_BITMASK 0xFF0
#define VERTEX_POS_Z_BITMASK 0xF000
#define VERTEX_TEXID_BITMASK 0x3FFF0000
#define VERTEX_UV_X_BITMASK  0x40000000
#define VERTEX_UV_Y_BITMASK  0x80000000

namespace Minecraft
{

	namespace Vertex
	{

		uint32_t Vertex::CompressVertexData(const glm::uvec3& position, uint16_t textureID, const glm::uvec2 uv)
		{
			uint32_t data = 0;

			// Encode Position Data
			data = (VERTEX_POS_X_BITMASK & position.x);
			data = (VERTEX_POS_Y_BITMASK & (position.y << 4)) | data;
			data = (VERTEX_POS_Z_BITMASK & (position.z << 12)) | data;

			// Encode Texture ID
			data = (VERTEX_TEXID_BITMASK & (textureID << 16)) | data;

			// Encode UV
			data = (VERTEX_UV_X_BITMASK & (uv.x << 30)) | data;
			data = (VERTEX_UV_Y_BITMASK & (uv.y << 31)) | data;

			return data;
		}

	}

}