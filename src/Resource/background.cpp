#include "background.h"

Background::Background(const std::string& path, const std::string& vertex_path,
	const std::string& fragment_path, const std::string& background_path){

	float vertices[] = {
	-1.f , -1.f, 0.,
	1.f, -1.f , 0.0f,
	  1.f, 1.f, 0.0f,
	  -1.f, 1.f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1,2,3
	};

	float texureCords[] = {
		1.f, 0.0f ,
		0.0f, 0.0f,
		0.0f, 1.f,
		1.0f , 1.0f,
	};

//	ResourceManager::load_resource("D:\\projectC++\\testGame\\res\\shaders\\ret");
	ResourceManager::load_resource(path);
//	ResourceManager::loadShaders("Background", "vertexShader.txt", "fragmentShader.txt");
	ResourceManager::loadShaders("Background", vertex_path, fragment_path);
	ResourceManager::loadTexture2D("Texture2D", GL_CLAMP_TO_EDGE, GL_NEAREST, background_path);
	m_program = ResourceManager::getShaderProgram("Background");
	Renderer::VertexBuffer vertexBuffer;
	Renderer::VertexBuffer textureBuffer;
	vertexBuffer.init_veretx_buffer(vertices, 12);
	m_elemenBuffer = std::make_shared<Renderer::ElementBuffer>();
	m_elemenBuffer->init_element_buffer(indices);
	textureBuffer.init_veretx_buffer(texureCords, 8);
	puts("Success");
	vertexBuffer.bind();
	m_texture = ResourceManager::getTexture2D("Texture2D");
	m_vertexArray = std::make_shared<Renderer::VertexArray>();
	m_vertexArray->init_vertexArray(0, 3, GL_FLOAT, false, NULL);
	m_texture->bind();
	textureBuffer.bind();
	m_vertexArray->init_vertexArray(1, 2, GL_FLOAT, false, NULL);


}

void Background::bind(){
	m_program->use();
	m_texture->bind();
	m_vertexArray->bind();
	m_elemenBuffer->bind();
}