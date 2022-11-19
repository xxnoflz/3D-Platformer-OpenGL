#include "resource_manager.h"

std::map<std::string, Utility::Shader> Utility::ResourceManager::Shaders;

void Utility::ResourceManager::CreateShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name) {
	std::fstream vertexFile{ vertexPath };
	std::stringstream vertexStream;
	vertexStream << vertexFile.rdbuf();
	const std::string vertexCode{ vertexStream.str() };

	std::fstream fragmentFile{ fragmentPath };
	std::stringstream fragmentStream;
	fragmentStream << fragmentFile.rdbuf();
	const std::string fragmentCode{ fragmentStream.str() };

	Shader shader{ vertexCode, fragmentCode };
	Shaders[name] = shader;
}

Utility::Shader& Utility::ResourceManager::GetShader(const std::string& name) {
	return Shaders[name];
}