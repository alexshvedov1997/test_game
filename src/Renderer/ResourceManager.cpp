#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Renderer/ShaderProgram.h"
#include "Texture2D.h"
#include "Sprite.h"
#include <glm/vec2.hpp>
#include "AnimatedSprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Resource/stb_image.h"

std::string  ResourceManager::m_path;
std::map < std::string, std::shared_ptr<Renderer::ShaderProgram>>  ResourceManager::m_shaderProgramMap;
std::map < std::string, std::shared_ptr<Renderer::Texture2D>>  ResourceManager::m_textureMap;
std::map < std::string, std::shared_ptr<Renderer::Sprite>> ResourceManager::m_spriteMap;
std::map < std::string, std::shared_ptr<Renderer::AnimatedSprite>> ResourceManager::m_animatedSpritesMap;
std::map<std::string, std::pair<float, float>> ResourceManager::m_sizeObjectMap;

void ResourceManager::load_resource(const std::string& path) {
		size_t pos = path.find_last_of("\\");
		m_path = path.substr(0, pos);
	}

	std::string ResourceManager::getFileData(const std::string fileName) {
		std::ifstream file;
		file.open(m_path + "\\" + fileName, std::ios_base::in | std::ios_base::binary);
		std::cout << "Path program : " << m_path + "\\" + fileName << std::endl;
		if (!file.is_open()) {
			std::cerr << "Can't open file" << std::endl;
			return "Error"; //исправить потом тут выкидывать ошибку через throw или создать сво класс ошибок
		}
		std::stringstream bufferData;
		bufferData << file.rdbuf();
		return bufferData.str();
	}

	std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shadersProgramName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		std::string vertexShaderStr = getFileData(vertexShaderPath);		
		if (vertexShaderStr.empty()) {
			std::cerr << "Resource Manager :: Vertex Shaders empty" << std::endl;
			return NULL;
		}
		std::string fragmentShaderStr = getFileData(fragmentShaderPath);
		if (fragmentShaderStr.empty()) {
			std::cerr << "Resource Manager :: Fragmemt Shaders empty" << std::endl;
			return NULL;
		}
		const char* vertexShader = vertexShaderStr.c_str();
		const char* fragmentShader = fragmentShaderStr.c_str();
		std::shared_ptr<Renderer::ShaderProgram>& newSahder = m_shaderProgramMap.emplace(shadersProgramName,
			std::make_shared< Renderer::ShaderProgram>(vertexShader, fragmentShader)).first->second;
		if (!newSahder) {
			std::cerr << "ResourceManager :: empty  new shaderProgarm" << std::endl;
			return NULL;
		}
		return newSahder;

	}

	std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shadersProgramName) {
		std::map< std::string, std::shared_ptr<Renderer::ShaderProgram>>::const_iterator it = m_shaderProgramMap.find(shadersProgramName);
		if (it == m_shaderProgramMap.end()) {
			std::cerr << "Resource managre :: Program didn't find shader program: " << shadersProgramName << std::endl;
			return NULL;
		}
		return it->second;
	}

	std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture2D(const std::string& textureName,
		GLenum filter, GLenum imposition, const std::string& path) {
		 int width = 0;
	 int height = 0;
		 int chanels = 0;
		 stbi_set_flip_vertically_on_load(true);

		std::string texturePath = m_path + "\\" + path;
		std::cout << "Texture path: " << texturePath << std::endl;
		unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &chanels, 0);
		if (!data) {
			std::cout << "Can't load texture: " << textureName << std::endl;
			return NULL;
		}
		std::shared_ptr<Renderer::Texture2D> newTexture = m_textureMap.emplace(textureName,
			std::make_shared<Renderer::Texture2D>(width, height, data, chanels, GL_CLAMP_TO_EDGE, GL_LINEAR)).first->second;
		if (!newTexture) {
			std::cout << "Can't load texture: " << textureName << std::endl;
			return NULL;
		}
		stbi_image_free(data);
		return newTexture;
	}

	std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture2D(const std::string& textureName) {
		std::map < std::string, std::shared_ptr<Renderer::Texture2D>>::const_iterator it = m_textureMap.find(textureName);
		if (it == m_textureMap.end()) {
			std::cout << "Can't find texture in map: " << textureName << std::endl;
			return NULL;
		}
		return it->second;
	}

std::shared_ptr<Renderer::Sprite> ResourceManager::loadSprite(const std::string& spriteName, const std::string& programName,
		const std::string& textureName, glm::vec2 position, glm::vec2 size, float rotation, const std::string& subTextureName) {
		auto pTexture = getTexture2D(textureName);
		if (!pTexture) {
			std::cout << "Can't get texture (loadSprite) : " << textureName << std::endl;
			return NULL;
		}
		auto pShader = getShaderProgram(programName);
		if (!pShader) {
			std::cout << "Can't get shader (loadSprite) : " << programName << std::endl;
			return NULL;
		}
		auto newSprite = m_spriteMap.emplace(spriteName, std::make_shared<Renderer::Sprite>(pShader, subTextureName, pTexture,
			position, size, rotation  )).first->second;
		if (!pShader) {
			std::cout << "Can't create spriter (spriteName) : " << programName << std::endl;
			return NULL;
		}
		return newSprite;
	}

std::shared_ptr<Renderer::Sprite> ResourceManager::getSprite(const std::string& spriteName) {
	std::map < std::string, std::shared_ptr<Renderer::Sprite>>::const_iterator it = m_spriteMap.find(spriteName);
	if (it == m_spriteMap.end()) {
		std::cout << "Can't find sprite in map: " << spriteName << std::endl;
		return NULL;
	}
	return it->second;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTextureAtlas(const std::string& textureName,
	const std::string& path,
	std::vector < std::string> subTextures,
	int subTextureWidth,
	int subTextureHeight) {
	 auto pTexture = loadTexture2D(textureName, GL_CLAMP_TO_EDGE, GL_LINEAR, path);
	 if (pTexture) {
		 const unsigned int  textureWidth = pTexture->width();
		 const unsigned int textureHeight = pTexture->height();
		 unsigned int currentSubTextureOffsetX = 0;
		 unsigned int currentSubTextureOffsetY = textureHeight;
		 m_sizeObjectMap.emplace(textureName, std::make_pair(static_cast<float>(subTextureWidth),
			 static_cast<float>(subTextureHeight)));
		 for (const auto& currentSubTextureName : subTextures) {
			 glm::vec2 leftBottomUV(static_cast<float>(currentSubTextureOffsetX) / textureWidth,
				 static_cast<float>(currentSubTextureOffsetY - subTextureHeight) / textureHeight);
			 glm::vec2 rightTopUV(static_cast<float>(currentSubTextureOffsetX + subTextureWidth) / textureWidth,
				 static_cast<float>(currentSubTextureOffsetY) / textureHeight);
			 pTexture->addSubTexture(currentSubTextureName, leftBottomUV, rightTopUV);
			 currentSubTextureOffsetX += subTextureWidth;
			 if (currentSubTextureOffsetX >= textureWidth) {
				 currentSubTextureOffsetY -= subTextureHeight;
				 currentSubTextureOffsetX = 0;
			 }
		 }
	 }
	 return pTexture;
}


std::shared_ptr<Renderer::AnimatedSprite> ResourceManager::getAnimatedSprite(const std::string& animatedSpriteName) {
	std::map < std::string, std::shared_ptr<Renderer::AnimatedSprite>>::const_iterator it 
		= m_animatedSpritesMap.find(animatedSpriteName);
	if (it == m_animatedSpritesMap.end()) {
		std::cout << "Can't find sprite in map:: " << animatedSpriteName << std::endl;
		return NULL;
	}
	return it->second;
 }

std::shared_ptr<Renderer::AnimatedSprite> ResourceManager::loadAnimatedSprite(const std::string& animatedSpriteName, 
	const std::string& programName,
	const std::string& textureName, glm::vec2 position, glm::vec2 size, float rotation,
	const std::string& subTextureName) {
	auto pTexture = getTexture2D(textureName);
	if (!pTexture) {
		std::cout << "Can't get texture (loadSprite) : " << textureName << std::endl;
		return NULL;
	}
	auto pShader = getShaderProgram(programName);
	if (!pShader) {
		std::cout << "Can't get shader (loadSprite) : " << programName << std::endl;
		return NULL;
	}
	auto newSprite = m_animatedSpritesMap.emplace(animatedSpriteName, std::make_shared<Renderer::AnimatedSprite>(pShader,
		subTextureName, pTexture,
		position, size, rotation)).first->second;
	if (!pShader) {
		std::cout << "Can't create spriter (spriteName) : " << programName << std::endl;
		return NULL;
	}
	return newSprite;
}

std::pair<float, float> ResourceManager::getSizeObject(std::string objectName) {
	static std::map<std::string, std::pair<float, float>>::const_iterator it = m_sizeObjectMap.find(objectName);
	if (it == m_sizeObjectMap.end()) {
		std::cerr << "Can't find size object" << std::endl;
		return std::pair<float, float>(0.f, 0.f);
	}
	return it->second;
}


