#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "light.h"
#include "fixed_camera.h"
#include "player.h"
#include "shaders/shader.h"
#include "textures/texture.h"
#include <vector>

class Scene
{
public:
	Light light;
	Player player;
	FixedCamera camera;
//	std::vector<OtherPlayer> other_player_vec;

	Scene();
	~Scene();
	void RenderAll(const int width, const int height);
private:
	void init();
};