#pragma once

#include <glm/glm.hpp>

#define VERTEX_UV_X_BITMASK  0x80000000
#define VERTEX_UV_Y_BITMASK  0x40000000
#define VERTEX_TEXID_BITMASK 0x3FFF0000
#define VERTEX_POS_X_BITMASK 0xF000
#define VERTEX_POS_Y_BITMASK 0xFF
#define VERTEX_POS_Z_BITMASK 0xF

struct Vertex
{
	uint32_t Data;

	Vertex(glm::ivec2 texCoord, uint16_t textureID, glm::ivec3 position)
	{

	}
};