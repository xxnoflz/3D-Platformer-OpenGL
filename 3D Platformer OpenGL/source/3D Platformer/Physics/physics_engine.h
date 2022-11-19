#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "../Objects/player_object.h"
#include "../Objects/cube_object.h"

namespace Physics {

	class PhysicsEngine {
	public:
		struct Projection {
			float minProjection;
			float maxProjection;
		};
		struct MTV {
			float overlap_distance;
			glm::vec3 overlap_axis;
		};

		static std::tuple<bool, MTV> CheckCollision(Objects::GameObject* first, Objects::GameObject* second);
	private:
		static std::vector<std::vector<glm::vec3>> GetPoints(Objects::GameObject* object);
		static std::vector<std::vector<glm::vec3>> GetPointsForNormals(Objects::GameObject* object);
		static std::vector<glm::vec3> GetNormals(Objects::GameObject* object);
		static Projection GetProjection(std::vector<std::vector<glm::vec3>>& object_points, glm::vec3& axis);
	};

};