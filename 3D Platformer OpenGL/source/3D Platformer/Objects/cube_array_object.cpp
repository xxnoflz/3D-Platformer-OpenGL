#include "cube_array_object.h"

Objects::CubeArrayObject::CubeArrayObject(const glm::vec3 start_position, const uint32_t initial_size) {
	CreateInitialArray(start_position, initial_size);
}

void Objects::CubeArrayObject::DrawCubes(Utility::Shader& shader) {
	for (int iterator{}; iterator < m_cube_array.size(); ++iterator) {
		Render::Renderer::DrawCube(m_cube_array[iterator], shader);
	}
}

void Objects::CubeArrayObject::CreateInitialArray(const glm::vec3 start_position, const uint32_t initial_size) {
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_real_distribution<float> dis{ 1.0f, 4.5f };

	glm::vec3 previousGround{ start_position };
	m_cube_array.push_back(new Objects::CubeObject(start_position, glm::vec3(3.0f, 1.0f, 3.0f), 0.0f, glm::vec3(0.0f)));
	for (uint32_t iterator{}; iterator < initial_size; ++iterator) {
		glm::vec3 currentGround{};
		currentGround.x = previousGround.x + (dis(gen) * 2.5f);
		currentGround.y = previousGround.y + (dis(gen) * 0.25f);
		currentGround.z = previousGround.z + (dis(gen) * 1.5f);
		m_cube_array.push_back(new Objects::CubeObject(currentGround, glm::vec3(3.0f, 1.0f, 3.0f), 0.0f, glm::vec3(0.0f)));
		previousGround = currentGround;
	}
}

std::vector<Objects::CubeObject*> Objects::CubeArrayObject::GetArray() const {
	return m_cube_array;
}

void Objects::CubeArrayObject::AddNextElement() {
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_real_distribution<float> dis{ 1.0f, 4.5f };
	glm::vec3 currentGround{};
	currentGround.x = m_cube_array[m_cube_array.size() - 1]->GetPosition().x + (dis(gen) * 2.5f);
	currentGround.y = m_cube_array[m_cube_array.size() - 1]->GetPosition().y + (dis(gen) * 0.25f);
	currentGround.z = m_cube_array[m_cube_array.size() - 1]->GetPosition().z + (dis(gen) * 1.5f);
	m_cube_array.push_back(new Objects::CubeObject(currentGround, glm::vec3(3.0f, 1.0f, 3.0f), 0.0f, glm::vec3(0.0f)));
}