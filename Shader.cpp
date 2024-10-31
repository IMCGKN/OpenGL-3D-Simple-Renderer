#include "Shader.h"

void Shader::Init(const std::string& vFileLoc, const std::string& fFileLoc)
{
	std::ifstream vFile(vFileLoc);
	std::ifstream fFile(fFileLoc);

	if (vFile.is_open() && fFile.is_open())
	{
		INFO("Shader", "Succesfully opened vertex: " << vFileLoc.c_str() << " and fragment: " << fFileLoc.c_str());
		std::string vShaderSource, fShaderSource;

		std::stringstream vSstr;
		std::stringstream fSstr;

		vSstr << vFile.rdbuf();
		fSstr << fFile.rdbuf();

		vShaderSource = vSstr.str();
		fShaderSource = fSstr.str();

		const char* vSource = vShaderSource.c_str();
		const char* fSource = fShaderSource.c_str();
		
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vSource, nullptr);
		glCompileShader(vertex);
		CheckCompileShaderError(vertex, "Vertex");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fSource, nullptr);
		glCompileShader(fragment);
		CheckCompileShaderError(fragment, "Fragment");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		vFile.close();
		fFile.close();
	}
	else
	{
		ERROR("Shader", vFileLoc << "/" << fFileLoc << " could not be opened!");
	}
}

void Shader::Use()
{
	if (!isUsed)
	{
		glUseProgram(ID);
		isUsed = true;
	}
}

void Shader::Unuse()
{
	if (isUsed)
	{
		glUseProgram(0);
		isUsed = false;
	}
}

void Shader::SetMat4(const std::string& name, const glm::mat4& v)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
}

void Shader::SetVec4(const std::string& name, const glm::vec4& v)
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& v)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}

void Shader::SetVec2(const std::string& name, const glm::vec2& v)
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}

void Shader::SetFloat(const std::string& name, float v)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), v);
}

void Shader::SetInt(const std::string& name, int v)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), v);
}

void Shader::SetBool(const std::string& name, bool v)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), v);
}

void Shader::Destroy()
{
	glDeleteProgram(ID);
}

void Shader::CheckCompileShaderError(unsigned int shaderID, const std::string& nameType)
{
	int success;
	char infoLog[1024];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
		WARNING("\nShader", nameType.c_str() << " shader failed compiling. Error log: \n" << infoLog);
	}
	else
	{
		INFO("\nShader", nameType.c_str() << " compiled succesfully.");
	}
}
