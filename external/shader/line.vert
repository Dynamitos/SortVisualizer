#version 410
layout(location = 0) in vec2 position_VS_in;
uniform float transform[16];

void main()
{
	gl_Position = vec4(position_VS_in.x, position_VS_in.y+(transform[gl_VertexID]), 0, 1);
}