#pragma once
#include <glad/glad.h>

#include <vector>

#include "game_object.h"

namespace Objects {

	class CubeObject : public GameObject {
	public:
		CubeObject(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& size = glm::vec3(0.0f), const float degree = 0.0f, const glm::vec3& rotation_axes = glm::vec3(0.0f));
		GLuint& GetVAO();

		bool& GetStatus();
	private:
		std::vector<float> m_vertices;
		GLuint m_VAO;
		GLuint m_VBO;

		bool m_active;

		void Init();
	};

}