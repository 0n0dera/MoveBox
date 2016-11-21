#pragma once
#include "entity.h"

class Player : public Entity
{
public:

	enum Player_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const GLfloat SPEED = 4.0f;
	const GLfloat SENS = 0.1;

	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	GLfloat MoveSpeed;
	GLfloat MouseSens;
	
	Player(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 dir = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f));

	void Move(Player_Movement direction, GLfloat delta);
	void Rotate(GLfloat yaw, GLfloat pitch);

private:
	void update_direction_vectors();
};