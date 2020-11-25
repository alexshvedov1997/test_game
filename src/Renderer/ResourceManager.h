#pragma once
#include <string>
#include <map>
#include <memory>
#include <glad/glad.h>

namespace Renderer {
	class ShaderProgram;
	class Texture2D;
}
	class ResourceManager {
	public:
	static void load_resource(const std::string & path);
	static	std::string getFileData(const std::string fileName);
	static	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shadersProgramName, 
			const std::string& vertexShader, const std::string& fragmentShader);
	static	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shadersProgramName);
	static	std::shared_ptr<Renderer::Texture2D> loadTexture2D(const std::string& textureName,
			GLenum filter, GLenum imposition, const std::string& path);
	static	std::shared_ptr<Renderer::Texture2D> getTexture2D(const std::string& textureName);
	private:
		static std::string m_path;
		static std::map < std::string, std::shared_ptr<Renderer::ShaderProgram>> m_shaderProgramMap;
	    static	std::map < std::string, std::shared_ptr<Renderer::Texture2D>> m_textureMap;
};
