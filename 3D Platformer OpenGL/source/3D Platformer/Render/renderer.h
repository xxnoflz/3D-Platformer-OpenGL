#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Utilities/shader.h"

#include "../Objects/cube_object.h"

namespace Render {

	class Renderer {
	public:
		static void DrawCube(Objects::CubeObject* cube, Utility::Shader& shader);
	};

}