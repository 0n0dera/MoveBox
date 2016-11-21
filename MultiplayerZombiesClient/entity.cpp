#include "entity.h"

const GLfloat Entity::YAW = -90.0f;
const GLfloat Entity::PITCH = 0.0f;

Entity::Entity(glm::vec3 position, GLfloat yaw, GLfloat pitch)
	: Position(position), Yaw(yaw), Pitch(pitch), VAO(), EBO(), Shader(), NumVertices(), Textures()
{
}

void Entity::Draw(const glm::mat4 & view, const glm::mat4 & projection, const glm::vec3 & lightPos, const glm::vec3 & lightAmbient, const glm::vec3 & lightDiffuse, const glm::vec3 & lightSpecular)
{
	glUseProgram(Shader);
	glm::mat4 model, normal_mat;
	model = glm::translate(model, Position);
	model = glm::rotate(model, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	normal_mat = glm::transpose(glm::inverse(view * model));
	glUniformMatrix4fv(glGetUniformLocation(Shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(Shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(Shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(Shader, "normal_mat"), 1, GL_FALSE, glm::value_ptr(normal_mat));
	// textures
	for (int i = 0; i < Textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Textures[i].first);
		glUniform1i(glGetUniformLocation(Shader, Textures[i].second), i);
	}
	glUniform1f(glGetUniformLocation(Shader, "material.shininess"), 32.0f);

	// light colors
	glUniform3f(glGetUniformLocation(Shader, "light.ambient"), lightAmbient.x, lightAmbient.y, lightAmbient.z);
	glUniform3f(glGetUniformLocation(Shader, "light.diffuse"), lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
	glUniform3f(glGetUniformLocation(Shader, "light.specular"), lightSpecular.x, lightSpecular.y, lightSpecular.z);
	// light location
	glUniform3f(glGetUniformLocation(Shader, "light.position"), lightPos.x, lightPos.y, lightPos.z);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glBindVertexArray(0);
}

