#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <utility>
#include "shaders/shader.h"
#include "textures/texture.h"

class Entity
{
public:

	const static GLfloat YAW;
	const static GLfloat PITCH;

	glm::vec3 Position;
	GLfloat Yaw;
	GLfloat Pitch;

	GLuint VAO;
	GLuint EBO;
	GLuint Shader;
	GLuint NumVertices;
	std::vector<std::pair<GLuint, const char*>> Textures;

	Entity(glm::vec3 position, GLfloat yaw = YAW, GLfloat pitch = PITCH);

	virtual void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& lightPos, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular);
};