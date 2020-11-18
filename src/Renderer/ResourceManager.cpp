#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Renderer/ShaderProgram.h"


	ResourceManager::ResourceManager(const std::string& path) {
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
		std::cout << "resource Manager VertexShader Data: " << vertexShaderStr << std::endl;
		if (vertexShaderStr.empty()) {
			std::cerr << "Resource Manager :: Vertex Shaders empty" << std::endl;
			return NULL;
		}

		std::string fragmentShaderStr = getFileData(fragmentShaderPath);
		std::cout << "resource Manager Fragmenthader Data: " << fragmentShaderStr << std::endl;
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
