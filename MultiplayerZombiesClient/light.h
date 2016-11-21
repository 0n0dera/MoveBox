#pragma once

#include "entity.h"

class Light : public Entity
{
public:
	Light(glm::vec3 pos = glm::vec3(1.0f, 2.0f, -1.0f), glm::vec3 color = glm::vec3(1.0f));
	glm::vec3 GetPosition() const;
	glm::vec3 GetViewPosition(glm::mat4 view) const;
	glm::vec3 GetColor() const;
	glm::vec3 GetAmbient() const;
	glm::vec3 GetDiffuse() const;
	glm::vec3 GetSpecular() const;
	GLfloat GetShininess() const;

	void Draw(const glm::mat4 view, const glm::mat4 projection);

private:
	glm::vec3 color;
	GLfloat ambient;
	GLfloat diffuse;
	GLfloat specular;
	GLfloat shininess;
};