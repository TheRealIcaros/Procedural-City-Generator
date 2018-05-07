#ifndef TEXTURE_H
#define TEXTURE_H


#include "shaderCreater.h"
#include "Camera.h"
#include "../../Logic/header/Array.h"

#include <cstdlib>
#include <string>

//#include <glm.hpp>

#define DDS_MAGIC_NUMBER 0x20534444 // 'DDS ' in hex
#define ID_DXT1 0x31545844
#define ID_DXT3 0x33545844
#define ID_DXT5 0x35545844

struct DDS_PIXELFORMAT
{
	int32_t size;
	int32_t flags;
	int32_t fourCC;
	int32_t bitCount;
	int32_t rMask;
	int32_t gMask;
	int32_t bMask;
	int32_t aMask;
};

struct DDS_HEADER
{
	int32_t           size;
	int32_t           flags;
	int32_t           height;
	int32_t           width;
	int32_t           pitchOrLinearSize;
	int32_t           depth;
	int32_t           mipMaps;
	int32_t           reserved1[11];
	DDS_PIXELFORMAT	  format;
	int32_t           caps1;
	int32_t           caps2;
	int32_t           caps3;
	int32_t           caps4;
	int32_t           reserved2;
};

class Texture
{
public:
	Texture();
	~Texture();

	bool load(const std::string& path);
	void unload();
	void upload();
	void bind(GLenum target = GL_TEXTURE0);

	GLuint getID() const;
	int getWidth() const;
	int getHeight() const;

private:
	GLuint id;
	int width, height, size;
	GLenum format;
	GLbyte* pixels;
};

#endif
