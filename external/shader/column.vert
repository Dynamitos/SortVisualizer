#version 450
layout(location = 0) in vec2 position_VS_in;
layout(location = 1) in float transform_VS_in;
layout(location = 2) in float data_VS_in;

void main()
{
	gl_Position = vec4(position_VS_in.x+transform_VS_in, position_VS_in.y*data_VS_in-(1-data_VS_in), 0, 1);
}