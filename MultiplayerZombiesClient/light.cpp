#include "light.h"

Light::Light(glm::vec3 pos, glm::vec3 color)
	: Entity(pos), color(color), ambient(0.1f), diffuse(0.6f), specular(1.0f), shininess(32.0f)
{
}

glm::vec3 Light::GetPosition() const
{
	return Position;
}

glm::vec3 Light::GetViewPosition(glm::mat4 view) const
{
	return glm::vec3(view * glm::vec4(Position, 1.0f));
}

glm::vec3 Light::GetColor() const
{
	return color;
}

glm::vec3 Light::GetAmbient() const
{
	return color * ambient;
}

glm::vec3 Light::GetDiffuse() const
{
	return color * diffuse;
}

glm::vec3 Light::GetSpecular() const
{
	return color * specular;
}

GLfloat Light::GetShininess() const
{
	return shininess;
}

void Light::Draw(const glm::mat4 view, const glm::mat4 projection)
{
	glUseProgram(Shader);
	glm::mat4 model;
	model = glm::translate(model, Position);
	model = glm::scale(model, glm::vec3(0.2f));
	glUniformMatrix4fv(glGetUniformLocation(Shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(Shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(Shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(glGetUniformLocation(Shader, "lightColor"), color.x, color.y, color.z);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glBindVertexArray(0);
}
