#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <sstream>
#include <iostream>

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

struct VertexLight
{
	glm::vec3 Position;
	glm::vec3 Color;
};

#define INFO(class_name, message)\
std::wclog << class_name << " Info: " << message << std::endl;

#define WARNING(class_name, message)\
std::wclog << class_name << " Warning: " << message << std::endl;

#define ERROR(class_name, message)\
{\
std::stringstream m;\
m << class_name << " Error: " << message << std::endl;\
std::cerr << m.str();\
exit(1);\
}