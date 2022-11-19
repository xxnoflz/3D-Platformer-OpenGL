#include "shader.h"

Utility::Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode) {
	CreateShader(vertexCode, fragmentCode);
}

void Utility::Shader::CreateShader(const std::string& vertexCode, const std::string& fragmentCode) {
	const char* vertexCode_c{ vertexCode.c_str() };
	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertexCode_c, nullptr);
	glCompileShader(vertexShader);

	const char* fragmentCode_c{ fragmentCode.c_str() };
	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragmentCode_c, nullptr);
	glCompileShader(fragmentShader);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Utility::Shader::Use() const {
	glUseProgram(m_ID);
}

void Utility::Shader::SetMat4(const std::string& name, glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, false, &value[0][0]);
}