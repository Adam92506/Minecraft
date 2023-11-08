#type vertex
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;

void main()
{
    v_Color = a_Color;
    gl_Position = vec4(a_Position, 0.0f, 0.0f);
};

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

uniform sampler2D u_Texture;

void main()
{
    color = v_Color;
};