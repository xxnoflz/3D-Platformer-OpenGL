#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace Objects {

	class GameObject {
	public:
		GameObject(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& size = glm::vec3(0.0f), const float degree = 0.0f, const glm::vec3& rotation_axes = glm::vec3(0.0f));

		glm::vec3& GetPosition();
		glm::vec3& GetSize();
		float& GetDegree();
		glm::vec3& GetRotationAxes();
	private:
		glm::vec3 m_position;
		glm::vec3 m_size;
		float m_degree;
		glm::vec3 m_rotation_axes;
	};

}