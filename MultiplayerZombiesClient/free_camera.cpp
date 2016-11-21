#include "free_camera.h"
#include <iostream>

FreeCamera::FreeCamera(glm::vec3 pos, glm::vec3 target, glm::vec3 world_up)
	: Position(pos), Front(-glm::normalize(pos - target)), Up(), Right(), WorldUp(world_up), Target(target), Yaw(YAW), Pitch(PITCH), MoveSpeed(SPEED), MouseSens(SENSITIVTY), ZoomAmount(ZOOM)
{
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
	update_camera_vectors();
}

void FreeCamera::Zoom(GLfloat zoom)
{
	if (ZoomAmount >= 10.0f && ZoomAmount <= 60.0f)
	{
		ZoomAmount -= zoom;
	}
	if (ZoomAmount >= 60.0f)
	{
		ZoomAmount = 60.0f;
	}
	if (ZoomAmount <= 10.0f)
	{
		ZoomAmount = 10.0f;
	}
}

void FreeCamera::Rotate(GLfloat yaw, GLfloat pitch)
{
	Yaw += yaw * MouseSens;
	Pitch += pitch * MouseSens;
	update_camera_vectors();
}

void FreeCamera::Move(Camera_Movement direction, GLfloat delta)
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

glm::mat4 FreeCamera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, WorldUp);
}

void FreeCamera::update_camera_vectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}
