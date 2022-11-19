#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vendor/Dear ImGui/imgui.h"
#include "vendor/Dear ImGui/imgui_impl_glfw.h"
#include "vendor/Dear ImGui/imgui_impl_opengl3.h"

#include "Utilities/resource_manager.h"
#include "Render/renderer.h"
#include "Objects/cube_array_object.h"
#include "Objects/player_object.h"

namespace Game {

	class Platformer_3D {
	public:
		struct TimeHandler {
			float dTime;
			float currentFrame;
			float lastFrame;
		};
		Platformer_3D(const uint32_t window_width, const uint32_t window_height);

		Objects::PlayerObject* GetPlayerObject() const;

		void Run();

		void RestartGame();
	private:
		GLFWwindow* m_window;

		uint32_t m_window_width;
		uint32_t m_window_height;

		Objects::CubeArrayObject* m_gameObjects;
		Objects::PlayerObject* m_player;
		TimeHandler time;

		void Init();
		void InitOpenGL();

		void UpdateTime();
		void Update();
		void UpdateKeyboardInput();

		void BeginImGui();
		void EndImGui();
	};

}