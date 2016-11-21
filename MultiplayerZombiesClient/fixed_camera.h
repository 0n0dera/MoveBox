#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "player.h"

class FixedCamera
{
public:
	const GLfloat ZOOM = 45.0f;

	GLfloat ZoomAmount;

	FixedCamera(Player& player, glm::vec3 distance = glm::vec3(0.0f, 1.0f, 5.0f));
	glm::mat4 GetViewMatrix();
	void Zoom(GLfloat zoom);
private:
	Player& player;
	glm::vec3 distance;
};