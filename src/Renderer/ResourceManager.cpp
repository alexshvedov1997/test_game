#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Renderer/ShaderProgram.h"
#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Resource/stb_image.h"

std::string  ResourceManager::m_path;
std::map < std::string, std::shared_ptr<Renderer::ShaderProgram>>  ResourceManager::m_shaderProgramMap;
std::map < std::string, std::shared_ptr<Renderer::Texture2D>>  ResourceManager::m_textureMap;


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


