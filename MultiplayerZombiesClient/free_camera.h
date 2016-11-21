#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLEW_STATIC
#include <GL/glew.h>

class FreeCamera
{
public:

	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Default camera values
	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = 0.0f;
	const GLfloat SPEED = 5.0f;
	const GLfloat SENSITIVTY = 0.1f;
	const GLfloat ZOOM = 45.0f;

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	glm::vec3 Target;

	GLfloat Yaw;
	GLfloat Pitch;

	GLfloat MoveSpeed;
	GLfloat MouseSens;
	GLfloat ZoomAmount;

	FreeCamera(glm::vec3 pos, glm::vec3 target, glm::vec3 world_up);
	void Zoom(GLfloat zoom);
	void Rotate(GLfloat yaw, GLfloat pitch);
	void Move(Camera_Movement direction, GLfloat delta);
	glm::mat4 GetViewMatrix();
		
private:
	void update_camera_vectors();
};