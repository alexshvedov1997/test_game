#include "Sprite.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/ElementBuffer.h"
#include "../Renderer/VertexBuffer.h"
#include <glad/glad.h>
#include <glm/vec3.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>

namespace Renderer {

	Sprite::Sprite(std::shared_ptr<ShaderProgram> program, 
		const std::string& initialSubTexture,
		std::shared_ptr<Texture2D> texture,
		glm::vec2 position, glm::vec2 size, 
		float rotation):m_program(program),
		m_texture(texture), m_position(position), 
		m_size(size), m_rotation(rotation)
	{

		float vertices[] = {
	-1.f , -1.f, 0.5,
	1.f, -1.f , 0.0f,
	  1.f, 1.f, 0.0f,
	  -1.f, 1.f, 0.0f
		};
		unsigned int indices[] = {
			0, 1, 3,
			1,2,3
		};
		auto subTexture = m_texture->getSubTexture2D(initialSubTexture);
		/*
		float texureCords[] = {
			1.f, 0.0f ,
			0.0f, 0.0f,
			0.0f, 1.f,
			1.0f , 1.0f,
		};
		*/
		float texureCords[] = {
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y ,
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y
		};

		m_vertexBuffer = std::make_shared<VertexBuffer>();
		m_vertexBuffer->init_veretx_buffer(vertices, 12);
		m_elementBuffer = std::make_shared<ElementBuffer>();
		m_elementBuffer->init_element_buffer(indices);
		m_textureBuffer = std::make_shared<VertexBuffer>();
		m_textureBuffer->init_veretx_buffer(texureCords, 8);
		m_vertexArray = std::make_shared<VertexArray>();
		m_vertexBuffer->bind();
		m_vertexArray->init_vertexArray(0,3, GL_FLOAT, GL_FALSE, NULL);
		m_textureBuffer->bind();
		m_vertexArray->init_vertexArray(1, 2, GL_FLOAT, GL_FALSE, NULL);

	}

	void Sprite::renderer(bool mirrored) {
		m_program->use();
		glm::mat4 model(1.f);
		model = glm::translate(model, glm::vec3(m_position, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
		model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.f));
		model = glm::scale(model, glm::vec3(m_size, 1.f));
		if (mirrored)
			model *= glm::vec4(-1.f, 1.f, 1.f, 1.f);
		m_model = model;
		glUniformMatrix4fv(glGetUniformLocation(m_program->getProgramId(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));
		m_elementBuffer->bind();
		m_vertexArray->bind();
		m_texture->bind();
	}

}
