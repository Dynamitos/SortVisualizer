#version 410
layout(location = 0) in vec2 position_FS_in;
layout(location = 1) in float data_FS_in;
layout(location = 0) out vec4 color;
vec3 hsv2rgb(vec3 c)
{
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}
void main(){
	vec3 hsv = vec3(data_FS_in/length(position_FS_in), 1.f, 1.f);
	color = vec4(hsv2rgb(hsv), 1.f);
}