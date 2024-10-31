#pragma once

#include "Prerequisites.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

class Shader
{
public:
	void Init(const std::string& vFileLoc, const std::string& fFileLoc);

	void Use();
	void Unuse();

	void SetMat4(const std::string& name, const glm::mat4& v);
	void SetVec4(const std::string& name, const glm::vec4& v);
	void SetVec3(const std::string& name, const glm::vec3& v);
	void SetVec2(const std::string& name, const glm::vec2& v);
	void SetFloat(const std::string& name, float v);
	void SetInt(const std::string& name, int v);
	void SetBool(const std::string& name, bool v);

	void Destroy();
private:
	unsigned int ID;
	bool isUsed = false;

	void CheckCompileShaderError(unsigned int ID, const std::string& nameType);
};
