#include "../header/Texture.h"
#include <GL\glew.h>

Texture::Texture()
	: id(0), width(0), height(0), format(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT), pixels(nullptr)
{
}

Texture::~Texture()
{
}

bool Texture::load(const std::string& path)
{
	bool result = false;

	FILE* file = fopen(path.c_str(), "rb");
	if (file)
	{
		int32_t magicNumber;
		fread(&magicNumber, sizeof(magicNumber), 1, file);

		if (magicNumber == DDS_MAGIC_NUMBER)
		{
			DDS_HEADER header;
			fread(&header, sizeof(header), 1, file);

			width = header.width;
			height = header.height;
			size = header.pitchOrLinearSize;

			switch (header.format.fourCC)
			{
				default:
				case ID_DXT1: format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
				case ID_DXT3: format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
				case ID_DXT5: format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
			}

			pixels = new GLbyte[size];
			fread(pixels, sizeof(GLbyte), size, file);

			result = true;
		}

		fclose(file);
	}

	return result;
}

void Texture::unload()
{
	if (id)
	{
		glDeleteTextures(1, &id);
	}

	id = 0;
	width = height = 0;

	if (pixels)
	{
		delete[] pixels;
		pixels = nullptr;
	}
}

void Texture::upload()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glCompressedTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, size, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] pixels;
	pixels = nullptr;
}

void Texture::bind(GLenum target)
{
	glActiveTexture(target);
	glBindTexture(GL_TEXTURE_2D, id);
}

GLuint Texture::getID() const
{
	return id;
}

int Texture::getWidth() const
{
	return width;
}

int Texture::getHeight() const
{
	return height;
}