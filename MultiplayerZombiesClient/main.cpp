// includes
#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// SOIL
#include <SOIL.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// header includes
#include "shaders/shader.h"
#include "window_manager.h"
#include "scene.h"
#include "network.h"

void do_movement(GLfloat deltaTime, Scene& scene);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

const GLuint WIDTH = 800, HEIGHT = 600;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool keys[1024];
double last_x = WIDTH/2, last_y = HEIGHT/2;

int main()
{
	WindowManager window_manager;
	GLFWwindow* window = window_manager.GetWindow();

	// Set key callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glEnable(GL_DEPTH_TEST);

	Scene scene;
	Network network;

	glfwSetWindowUserPointer(window, &scene);

	while (!glfwWindowShouldClose(window))
	{
		network.SendPositionInfo(scene.player);
		network.ReceiveInfo(scene);
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// Events
		glfwPollEvents();
		do_movement(deltaTime, scene);
		// Render
		// Set clear color
		glClearColor(0.1f, 0.3f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.RenderAll(WIDTH, HEIGHT);

		// Swap buffer
		glfwSwapBuffers(window);
	}

	return 0;
}

void do_movement(GLfloat deltaTime, Scene& scene)
{
	if (keys[GLFW_KEY_W])
	{
		scene.player.Move(Player::FORWARD, deltaTime);
	}
	else if (keys[GLFW_KEY_S])
	{
		scene.player.Move(Player::BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A])
	{
		scene.player.Move(Player::LEFT, deltaTime);
	}
	else if (keys[GLFW_KEY_D])
	{
		scene.player.Move(Player::RIGHT, deltaTime);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
}

bool first_mouse = true;
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	Scene* scene = reinterpret_cast<Scene*>(glfwGetWindowUserPointer(window));
	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}
	//camera.Rotate(x_pos - last_x, last_y - y_pos);
	scene->player.Rotate(last_x - x_pos, y_pos - last_y);
	last_x = x_pos;
	last_y = y_pos;
}

/* glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));*/

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
	Scene* scene = reinterpret_cast<Scene*>(glfwGetWindowUserPointer(window));
	scene->camera.Zoom(y_offset);
}