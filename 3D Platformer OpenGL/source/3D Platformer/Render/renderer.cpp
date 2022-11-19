#include "renderer.h"

void Render::Renderer::DrawCube(Objects::CubeObject* cube, Utility::Shader& shader) {
	if (!cube->GetStatus())
		return;
	shader.Use();

	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, cube->GetPosition());
	if (cube->GetRotationAxes() != glm::vec3(0.0f))
		model = glm::rotate(model, glm::radians(cube->GetDegree()), cube->GetRotationAxes());
	model = glm::scale(model, cube->GetSize());

	shader.SetMat4("model", model);

	glBindVertexArray(cube->GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36); // REWRITE
	glBindVertexArray(0);
}