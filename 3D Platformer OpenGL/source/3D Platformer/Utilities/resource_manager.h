#pragma once
#include <string>
#include <fstream>
#include <sstream>

#include <map>

#include "shader.h"

namespace Utility {

	class ResourceManager {
	public:
		static void CreateShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name);
		static Utility::Shader& GetShader(const std::string& name);
	private:
		static std::map<std::string, Utility::Shader> Shaders;
	};

}