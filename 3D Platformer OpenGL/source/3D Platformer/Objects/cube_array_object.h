#pragma once
#include "cube_object.h"
#include "../Utilities/shader.h"
#include "../Render/renderer.h"
#include <random>
#include <vector>

namespace Objects {

	class CubeArrayObject {
	public:
		CubeArrayObject(const glm::vec3 start_position, const uint32_t initial_size);

		void DrawCubes(Utility::Shader& shader);

		void AddNextElement();

		std::vector<Objects::CubeObject*> GetArray() const;
	private:
		std::vector<Objects::CubeObject*> m_cube_array;

		void CreateInitialArray(const glm::vec3 start_position, const uint32_t initial_size);
	};

};