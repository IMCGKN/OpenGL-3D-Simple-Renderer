#version 410 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iColor;

layout (location = 0) out vec3 oColor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	gl_Position = Projection * View * Model * vec4(iPosition, 1.0);
	oColor = iColor;
}