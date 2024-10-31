#version 410 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 iColor;

void main()
{
	FragColor = vec4(iColor, 1.0);
}