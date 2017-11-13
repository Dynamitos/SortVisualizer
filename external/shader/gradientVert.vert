#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 position_VS_in;
layout(location = 0) in float data_VS_in;

layout(location = 0) out vec2 position_FS_out;
layout(location = 1) out float data_FS_out;
void main(){
	gl_Position = vec4(position_VS_in, 0, 1);
	position_FS_out = position_VS_in;
	data_FS_out = data_VS_in;
} 