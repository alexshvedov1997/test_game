#pragma once
#include <string>
#include <map>
#include <memory>

namespace Renderer {
	class ShaderProgram;
}
	class ResourceManager {
	public:
		ResourceManager(const std::string& path);
		std::string getFileData(const std::string fileName);
		std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shadersProgramName, const std::string& vertexShader, const std::string& fragmentShader);
		std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shadersProgramName);
	private:
		std::string m_path;
		std::map < std::string, std::shared_ptr<Renderer::ShaderProgram>> m_shaderProgramMap;
};
