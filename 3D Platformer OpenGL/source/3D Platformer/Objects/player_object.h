#pragma once
#include "game_object.h"
#include "cube_array_object.h"

#include "camera_object.h"
#include "../Physics/physics_engine.h"

namespace Objects {

	class PlayerObject : public GameObject {
	public:
		enum Keys {
			W = 87,
			S = 83,
			A = 65,
			D = 68,
			SPACE = 32
		};

		PlayerObject(const glm::vec3& position, const glm::vec3& hitbox_size);

		void UpdatePlayer(float dTime, Objects::CubeArrayObject* gameObjects);

		void UpdateCameraDirection(float x_position, float y_position);

		void UpdatePlayerPosition(Keys key, float dTime);

		int GetScore() const;
		bool GetDeathStatus() const;
	private:
		CameraObject* camera;

		const float startingJumpingSpeed{ 0.5f };
		const float gravityVelocity{ 1.0f };

		int m_player_score;
		bool m_isDead;

		bool m_grounded;
		bool m_jumping;
		bool m_falling;

		void UpdatePlayerVerticalPosition(float dTime);
		void ProcessJumping(float dTime);
		void ProcessFalling(float dTime);
		float timeAccumulator;
	};

}