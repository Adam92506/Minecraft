#type vertex
#version 430 core

#define VERTEX_POS_X_BITMASK uint(0x1F)
#define VERTEX_POS_Y_BITMASK uint(0x1FE0)
#define VERTEX_POS_Z_BITMASK uint(0x3E000)
#define VERTEX_TEXID_BITMASK uint(0x3FFC0000)
#define VERTEX_UV_X_BITMASK  uint(0x40000000)
#define VERTEX_UV_Y_BITMASK  uint(0x80000000)

layout(location = 0) in uint a_CompressedData;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

uniform uvec2 u_AtlasSize;
uniform uvec2 u_TextureSize;

out vec2 v_TexCoord;

void CalculateTexCoord(in uvec2 uv, in uint texID, out vec2 texCoord)
{
    uint startX = texID % u_AtlasSize.x;
    uint startY = texID / u_AtlasSize.y;

    uint xPos = startX + uv.x;
    uint yPos = startY + uv.y;

    texCoord.x = float(xPos) / float(u_AtlasSize.x);
    texCoord.y = float(yPos) / float(u_AtlasSize.y);
}

void ExtractVertexData(in uint compressedData, out uvec3 position, out vec2 texCoord)
{
    // Extract Position
    position.x = (compressedData & VERTEX_POS_X_BITMASK);
    position.y = (compressedData & VERTEX_POS_Y_BITMASK) >> 5;
    position.z = (compressedData & VERTEX_POS_Z_BITMASK) >> 13;

    // Extract Texture ID
    uint texID = (compressedData & VERTEX_TEXID_BITMASK) >> 18;

    // Extract UV
    uvec2 uv;
    uv.x = (compressedData & VERTEX_UV_X_BITMASK) >> 30;
    uv.y = (compressedData & VERTEX_UV_Y_BITMASK) >> 31;
    CalculateTexCoord(uv, texID, texCoord);
}

void main()
{
    uvec3 position;
    ExtractVertexData(a_CompressedData, position, v_TexCoord);

    gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
};

#type fragment
#version 430 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_TexCoord);
};