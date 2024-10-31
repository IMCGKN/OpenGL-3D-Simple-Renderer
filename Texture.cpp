#include "Texture.h"

void Texture::Init(const std::string& FileLoc, int format)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data;
	data = stbi_load(FileLoc.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		WARNING("Texture", "Could not open " << FileLoc.c_str() << " texture.");
	}
	stbi_image_free(data);
}

void Texture::Use()
{
	if (!isUsed)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		isUsed = true;
	}
}

void Texture::Unuse()
{
	if (isUsed)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		isUsed = false;
	}
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
