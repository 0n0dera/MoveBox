#include "player.h"
Player::Player(glm::vec3 pos, glm::vec3 dir, glm::vec3 world_up)
	: Entity(pos), Front(glm::normalize(dir)), WorldUp(world_up), MoveSpeed(SPEED), MouseSens(SENS)
{
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
	update_direction_vectors();
}

void Player::Move(Player_Movement direction, GLfloat delta)
{
	GLfloat velocity = delta * MoveSpeed;
	switch (direction)
	{
	case FORWARD:
		Position += Front * velocity;
		break;
	case BACKWARD:
		Position -= Front * velocity;
		break;
	case RIGHT:
		Position += Right * velocity;
		break;
	case LEFT:
		Position -= Right * velocity;
		break;
	}
}

void Player::Rotate(GLfloat yaw, GLfloat pitch)
{
	pitch = 0;
	Yaw += yaw * MouseSens;
	Pitch += pitch * MouseSens;
	update_direction_vectors();
}

void Player::update_direction_vectors()
{
	glm::vec3 front;
	front.x = -cos(glm::radians(Yaw));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}
