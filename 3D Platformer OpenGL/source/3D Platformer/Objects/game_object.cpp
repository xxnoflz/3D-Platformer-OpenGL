#include "game_object.h"

Objects::GameObject::GameObject(const glm::vec3& position, const glm::vec3& size, const float degree, const glm::vec3& rotation_axes) 
	: m_position(position), m_size(size), m_degree(degree), m_rotation_axes(rotation_axes)
{

}

glm::vec3& Objects::GameObject::GetPosition() {
	return m_position;
}

glm::vec3& Objects::GameObject::GetSize() {
	return m_size;
}

float& Objects::GameObject::GetDegree() {
	return m_degree;
}

glm::vec3& Objects::GameObject::GetRotationAxes() {
	return m_rotation_axes;
}