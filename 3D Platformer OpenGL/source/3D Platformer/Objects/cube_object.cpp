#include "cube_object.h"

Objects::CubeObject::CubeObject(const glm::vec3& position, const glm::vec3& size, const float degree, const glm::vec3& rotation_axes)
	: GameObject(position, size, degree, rotation_axes), m_active(true)
{
	Init();
}

void Objects::CubeObject::Init() {
	m_vertices = {
		//FRONT
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,	0.0f,

		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		//BACK
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f,
		0.0f, 1.0f,	-1.0f,

		1.0f, 1.0f, -1.0f,
		0.0f, 1.0f, -1.0f,
		1.0f, 0.0f, -1.0f,
		//UP
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, -1.0f,

		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,
		0.0f, 1.0f, -1.0f,
		//DOWN
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		//LEFT
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		//RIGHT
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, -1.0f,
		1.0f, 1.0f, 0.0f,

		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 0.0f, -1.0f,
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint& Objects::CubeObject::GetVAO() {
	return m_VAO;
}

bool& Objects::CubeObject::GetStatus() {
	return m_active;
}
