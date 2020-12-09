#pragma once
#include <string>
#include <map>
#include <memory>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <vector>

namespace Renderer {
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
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
	static std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName, const std::string& programName,
		const std::string& textureName, glm::vec2 position, glm::vec2 size, float rotation,
		const std::string& subTextureName = "default");

	static std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

	static std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName, const std::string& programName,
		const std::string& textureName, glm::vec2 position, glm::vec2 size, float rotation,
		const std::string& subTextureName = "default");

	static std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string& animatedSpriteName);

	static std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(const std::string& textureName, 
		const std::string& path, std::vector < std::string> subTextures,
		int subTextureWidth, int subTextureHeight);
	static std::pair<float, float> getSizeObject(std::string objectName);

	private:
		static std::string m_path;
		static std::map < std::string, std::shared_ptr<Renderer::ShaderProgram>> m_shaderProgramMap;
	    static	std::map < std::string, std::shared_ptr<Renderer::Texture2D>> m_textureMap;
		static std::map < std::string, std::shared_ptr<Renderer::Sprite>> m_spriteMap;
		static std::map < std::string, std::shared_ptr<Renderer::AnimatedSprite>> m_animatedSpritesMap;
		static std::map<std::string, std::pair<float, float>> m_sizeObjectMap;
};
