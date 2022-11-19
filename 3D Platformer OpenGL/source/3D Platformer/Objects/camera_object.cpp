#include "camera_object.h"

Objects::CameraObject::CameraObject(const glm::vec3& position) 
	: GameObject(position), m_pitch(0.0f), m_yaw(-90.0f),
	m_camera_direction(glm::vec3(0.0f, 0.0f, -1.0f)), m_camera_up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_mouse_position_x(0.0f), m_mouse_position_y(0.0f)
{
	UpdateModelMatrix("cube_shader");
	UpdateCameraDirection(0, 0);
}

void Objects::CameraObject::UpdateCameraDirection(float mouse_position_x, float mouse_position_y) {
	float x_diff{ mouse_position_x - m_mouse_position_x };
	float y_diff{ m_mouse_position_y - mouse_position_y };

	x_diff *= 0.1f;
	y_diff *= 0.1f;

	m_mouse_position_x = mouse_position_x;
	m_mouse_position_y = mouse_position_y;

	m_yaw += x_diff;
	m_pitch += y_diff;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	else if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	CalculateNewCameraDirection();
}

void Objects::CameraObject::CalculateNewCameraDirection() {
	glm::vec3 NewCameraDirection;
	NewCameraDirection.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	NewCameraDirection.y = glm::sin(glm::radians(m_pitch));
	NewCameraDirection.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	m_camera_direction = glm::normalize(NewCameraDirection);

	UpdateModelMatrix("cube_shader");
}

void Objects::CameraObject::UpdateModelMatrix(const std::string shader_name) {
	Utility::ResourceManager::GetShader(shader_name).Use();
	glm::mat4 view{ glm::lookAt(GetPosition(), GetPosition() + m_camera_direction, m_camera_up) };
	Utility::ResourceManager::GetShader(shader_name).SetMat4("view", view);
}

glm::vec3 Objects::CameraObject::GetCameraUp() const {
	return m_camera_up;
}

glm::vec3 Objects::CameraObject::GetCameraDirection() const {
	return m_camera_direction;
}

float Objects::CameraObject::GetPitch() const {
	return m_pitch;
}

float Objects::CameraObject::GetYaw() const {
	return m_yaw;
}