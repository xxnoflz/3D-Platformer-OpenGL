#include "player_object.h"

Objects::PlayerObject::PlayerObject(const glm::vec3& position, const glm::vec3& hitbox_size) 
	: GameObject(position, hitbox_size), m_player_score(), m_isDead(false), m_grounded(false), m_jumping(false), m_falling(false), timeAccumulator(0.0f)
{
	camera = new CameraObject(position);
}

void Objects::PlayerObject::UpdateCameraDirection(float x_position, float y_position) {
	camera->UpdateCameraDirection(x_position, y_position);
}

void Objects::PlayerObject::UpdatePlayerPosition(Keys key, float dTime) {
	glm::vec3 NewCameraDirection;
	NewCameraDirection.x = glm::cos(glm::radians(camera->GetYaw()));
	NewCameraDirection.z = glm::sin(glm::radians(camera->GetYaw()));
	glm::normalize(NewCameraDirection);

	float playerSpeed{ 10.0f * dTime };
	if (key == W)
		GetPosition() += NewCameraDirection * playerSpeed;
	else if (key == S)
		GetPosition() -= NewCameraDirection * playerSpeed;
	else if (key == A)
		GetPosition() += glm::normalize(glm::cross(camera->GetCameraUp(), camera->GetCameraDirection())) * playerSpeed;
	else if (key == D)
		GetPosition() -= glm::normalize(glm::cross(camera->GetCameraUp(), camera->GetCameraDirection())) * playerSpeed;
	else if (key == SPACE && (m_grounded || !m_falling)) {
		m_jumping = true;
		m_grounded = false;
	}

	camera->GetPosition() = GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f);
	camera->UpdateModelMatrix("cube_shader");
}

void Objects::PlayerObject::UpdatePlayer(float dTime, Objects::CubeArrayObject* gameObjects) {
	UpdatePlayerVerticalPosition(dTime);


	m_grounded = false;
	for (int iterator{}; iterator < gameObjects->GetArray().size(); ++iterator) {
		if (!gameObjects->GetArray()[iterator]->GetStatus())
			continue;

		std::tuple<bool, Physics::PhysicsEngine::MTV> collisionResult{ Physics::PhysicsEngine::CheckCollision(this, gameObjects->GetArray()[iterator]) };
		if (std::get<0>(collisionResult)) {
			m_player_score = iterator;

			GetPosition() += std::get<1>(collisionResult).overlap_axis * std::get<1>(collisionResult).overlap_distance;
			if (std::get<1>(collisionResult).overlap_axis.y == 1.0f) {
				timeAccumulator = 0.0f;
				m_falling = false;
				m_grounded = true;
			}
		}
		if (!std::get<0>(collisionResult) && iterator == m_player_score) {
			gameObjects->GetArray()[iterator]->GetStatus() = false;
			gameObjects->AddNextElement();
		}
		if (!m_grounded && !m_falling && !m_jumping) {
			timeAccumulator = 0.0f;
			m_falling = true;
			m_grounded = false;
		}
	}


	if (GetPosition().y <= -5.0f)
		m_isDead = true;
}

void Objects::PlayerObject::UpdatePlayerVerticalPosition(float dTime) {
	if(m_jumping)
		ProcessJumping(dTime);
	if (m_falling)
		ProcessFalling(dTime);
	camera->GetPosition() = GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f);
	camera->UpdateModelMatrix("cube_shader");
}

void Objects::PlayerObject::ProcessJumping(float dTime) {
	timeAccumulator += dTime;
	float jumpingVelocity{ startingJumpingSpeed - (gravityVelocity * timeAccumulator) };
	GetPosition().y += jumpingVelocity;

	if (jumpingVelocity <= 0.0f) {
		timeAccumulator = 0.0f;
		m_falling = true;
		m_jumping = false;
	}
}

void Objects::PlayerObject::ProcessFalling(float dTime) {
	timeAccumulator += dTime;
	float fallingVelocity{ -gravityVelocity * timeAccumulator };
	GetPosition().y += fallingVelocity;
}

int Objects::PlayerObject::GetScore() const {
	return m_player_score;
}

bool Objects::PlayerObject::GetDeathStatus() const {
	return m_isDead;
}