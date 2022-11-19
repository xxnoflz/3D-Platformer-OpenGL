#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

namespace Utility {

	class Shader {
	public:
		Shader(const std::string& vertexCode = "", const std::string& fragmentCode = "");
		void Use() const;
		void SetMat4(const std::string& name, glm::mat4& value);
	private:
		GLuint m_ID;

		void CreateShader(const std::string& vertexCode, const std::string& fragmentCode);
	};

}