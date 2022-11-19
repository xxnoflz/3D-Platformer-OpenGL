#pragma once
#include "game_object.h"
#include "../Utilities/resource_manager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Objects {

	class CameraObject : public GameObject{
	public:
		CameraObject(const glm::vec3& position);

		void UpdateCameraDirection(float mouse_position_x, float mouse_position_y);

		void UpdateModelMatrix(const std::string shader_name);

		glm::vec3 GetCameraUp() const;
		glm::vec3 GetCameraDirection() const;
		float GetPitch() const;
		float GetYaw() const;
	private:
		float m_pitch;
		float m_yaw;

		float m_mouse_position_x;
		float m_mouse_position_y;

		glm::vec3 m_camera_up;
		glm::vec3 m_camera_direction;

		void CalculateNewCameraDirection();
	};

}