#include "physics_engine.h"

std::tuple<bool, Physics::PhysicsEngine::MTV> Physics::PhysicsEngine::CheckCollision(Objects::GameObject* first, Objects::GameObject* second) {
	std::vector<std::vector<glm::vec3>> first_points{ GetPoints(first) };
	std::vector<std::vector<glm::vec3>> second_points{ GetPoints(second) };

	std::vector<glm::vec3> first_normals{ GetNormals(first) };
	std::vector<glm::vec3> second_normals{ GetNormals(second) };

	std::vector<glm::vec3> axes{
		first_normals[0],
		first_normals[1],
		first_normals[2],

		second_normals[0],
		second_normals[1],
		second_normals[2],
	};
	MTV mtv{ std::numeric_limits<float>::max() };

	for (int axes_iterator{}; axes_iterator < axes.size(); ++axes_iterator) {
		Projection first_object_projection{ GetProjection(first_points, axes[axes_iterator]) };
		Projection second_object_projection{ GetProjection(second_points, axes[axes_iterator]) };

		if (first_object_projection.maxProjection < second_object_projection.minProjection ||
			second_object_projection.maxProjection < first_object_projection.minProjection)
			return std::make_tuple(false, MTV{ });

		float overlap_test{std::min(first_object_projection.maxProjection, second_object_projection.maxProjection) - std::max(first_object_projection.minProjection, second_object_projection.minProjection)};
		if (mtv.overlap_distance > overlap_test) {
			mtv.overlap_distance = overlap_test;
			mtv.overlap_axis = axes[axes_iterator];
		}
	}
	glm::vec3 direction{ first->GetPosition() - second->GetPosition() };
	if (glm::dot(mtv.overlap_axis, direction) < 0.0f)
		mtv.overlap_axis *= -1.0f;
	return std::make_tuple(true, mtv);
}

std::vector<std::vector<glm::vec3>> Physics::PhysicsEngine::GetPoints(Objects::GameObject* object) {
	std::vector<std::vector<glm::vec3>> object_points(4);

	std::vector<std::vector<glm::vec4>> vertices{
		//FRONT
		{
			glm::vec4(0.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		0.0f,	0.0f,	1.0f)
		},
		//LEFT
		{
			glm::vec4(0.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	-1.0f,	1.0f),
			glm::vec4(0.0f,		0.0f,	-1.0f,	1.0f)
		},
		//RIGHT
		{
			glm::vec4(1.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	-1.0f,	1.0f),
			glm::vec4(1.0f,		0.0f,	-1.0f,	1.0f)
		},
		//BACK
		{
			glm::vec4(0.0f,		0.0f,	-1.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	-1.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	-1.0f,	1.0f),
			glm::vec4(1.0f,		0.0f,	-1.0f,	1.0f)
		}
	};

	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, object->GetPosition());
	if (object->GetRotationAxes() != glm::vec3(0.0f))
		model = glm::rotate(model, glm::radians(object->GetDegree()), object->GetRotationAxes());
	model = glm::scale(model, object->GetSize());

	for (int row_iterator{}; row_iterator < vertices.size(); ++row_iterator) {
		for (int point_iterator{}; point_iterator < vertices[row_iterator].size(); ++point_iterator) {
			vertices[row_iterator][point_iterator] = model * vertices[row_iterator][point_iterator];
			
			object_points[row_iterator].push_back(glm::vec3(vertices[row_iterator][point_iterator]));
		}
	}
	return object_points;
}

std::vector<std::vector<glm::vec3>> Physics::PhysicsEngine::GetPointsForNormals(Objects::GameObject* object) {
	std::vector<std::vector<glm::vec3>> points_for_normals(3);

	std::vector<std::vector<glm::vec4>> vertices{
		//Right-Left Axis
		{
			glm::vec4(0.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	-1.0f,	1.0f)
		},
		//Up-Down Axis
		{
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	-1.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	0.0f,	1.0f)
		},
		//Front-Back Axis
		{
			glm::vec4(0.0f,		0.0f,	0.0f,	1.0f),
			glm::vec4(0.0f,		1.0f,	0.0f,	1.0f),
			glm::vec4(1.0f,		1.0f,	0.0f,	1.0f)
		}
	};

	glm::mat4 model{ glm::mat4(1.0f) };
	model = glm::translate(model, object->GetPosition());
	if (object->GetRotationAxes() != glm::vec3(0.0f))
		model = glm::rotate(model, glm::radians(object->GetDegree()), object->GetRotationAxes());
	model = glm::scale(model, object->GetSize());

	for (int row_iterator{}; row_iterator < vertices.size(); ++row_iterator) {
		for (int point_iterator{}; point_iterator < vertices[row_iterator].size(); ++point_iterator) {
			vertices[row_iterator][point_iterator] = model * vertices[row_iterator][point_iterator];

			points_for_normals[row_iterator].push_back(glm::vec3(vertices[row_iterator][point_iterator]));
		}
	}
	return points_for_normals;
}

std::vector<glm::vec3> Physics::PhysicsEngine::GetNormals(Objects::GameObject* object) {
	std::vector<glm::vec3> object_normals;
	std::vector<std::vector<glm::vec3>> points_for_normals{ GetPointsForNormals(object) };

	for (int row_iterator{}; row_iterator < points_for_normals.size(); ++row_iterator) {
		glm::vec3 neighbour_one{ points_for_normals[row_iterator][1] - points_for_normals[row_iterator][0] };
		glm::vec3 neighbour_two{ points_for_normals[row_iterator][2] - points_for_normals[row_iterator][0] };

		object_normals.push_back(glm::normalize(glm::cross(neighbour_one, neighbour_two)));
	}
	return object_normals;
}

Physics::PhysicsEngine::Projection Physics::PhysicsEngine::GetProjection(std::vector<std::vector<glm::vec3>>& object_points, glm::vec3& axis) {
	Projection projection;
	projection.minProjection = glm::dot(object_points[0][0], axis);
	projection.maxProjection = projection.minProjection;

	for (int row_iterator{}; row_iterator < object_points.size(); ++row_iterator) {
		for (int point_iterator{}; point_iterator < object_points[row_iterator].size(); ++point_iterator) {
			float currentProjection{ glm::dot(object_points[row_iterator][point_iterator], axis) };
			if (projection.minProjection > currentProjection)
				projection.minProjection = currentProjection;
			if (projection.maxProjection < currentProjection)
				projection.maxProjection = currentProjection;
		}
	}
	return projection;
}