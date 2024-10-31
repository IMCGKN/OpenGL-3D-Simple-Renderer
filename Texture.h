#pragma once

#include <string>

#include <glad/glad.h>

#include <stb/stb_image.h>

#include "Prerequisites.h"

class Texture
{
public:
	void Init(const std::string& FileLoc, int format);

	void Use();
	void Unuse();

	void Delete();
private:
	unsigned int ID;
	bool isUsed = false;

	int width = 0, height = 0, nrChannels = 0;
};