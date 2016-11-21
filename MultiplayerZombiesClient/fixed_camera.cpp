#include "fixed_camera.h"

FixedCamera::FixedCamera(Player& player, glm::vec3 distance)
	:player(player), distance(distance), ZoomAmount(ZOOM)
{
	
}

glm::mat4 FixedCamera::GetViewMatrix()
{
	glm::vec3 position = player.Position + player.Right * distance.x - player.Front * distance.z + player.Up * distance.y;
	return glm::lookAt(position, player.Position, player.WorldUp);
}

void FixedCamera::Zoom(GLfloat zoom)
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