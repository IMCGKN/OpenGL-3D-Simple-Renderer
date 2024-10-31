#version 410 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec2 iTexCoords;
layout (location = 2) in vec3 iNormal;

layout (location = 0) out vec2 oTexCoords;
layout (location = 1) out vec3 oNormal;
layout (location = 2) out vec3 oFragPos;
layout (location = 3) out vec3 oColor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	gl_Position = Projection * View * Model * vec4(iPosition, 1.0);
	oTexCoords = iTexCoords;
	oNormal = iNormal;
	oFragPos = vec3(Model * vec4(iPosition, 1.0));
}