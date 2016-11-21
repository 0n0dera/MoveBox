#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <SOIL.h>

class Texture
{
public:
	GLuint Id;
	Texture(const char* file);
};