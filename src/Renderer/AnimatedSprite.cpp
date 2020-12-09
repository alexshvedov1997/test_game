#include "Sprite.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/ElementBuffer.h"
#include "../Renderer/VertexBuffer.h"
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "AnimatedSprite.h"
#include <iostream>
#include "../Renderer/Texture2D.h"

namespace Renderer {

	AnimatedSprite::AnimatedSprite(std::shared_ptr<ShaderProgram> program, 
		const std::string& initialSubTexture,
		std::shared_ptr<Texture2D> texture,
		glm::vec2 position, glm::vec2 size, 
		float rotation):Sprite(program, initialSubTexture, texture, position,
			size, rotation)
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
		m_currentAnimationDurations = m_statesMap.end();
	}


	void AnimatedSprite::update(uint64_t delta) {
		if (m_currentAnimationDurations != m_statesMap.end()) {
			m_currentAnimationTime += delta;
			while (m_currentAnimationTime >= m_currentAnimationDurations->second[m_currentFrame].second) {
				m_currentAnimationTime -= m_currentAnimationDurations->second[m_currentFrame].second;
				++m_currentFrame;
				m_dirty = true;

				if (m_currentFrame == m_currentAnimationDurations->second.size()) {
					m_currentFrame = 0;
				}
			}
			
			
		}
		m_dirty = true;
	}

	void AnimatedSprite::setState(std::string newState) {
		auto it = m_statesMap.find(newState);
		if (it == m_statesMap.end()) {
			std::cerr << "Can't found animated sprite:: " << newState << std::endl;
			return;
		}
		if (it != m_currentAnimationDurations) {
			m_currentAnimationTime = 0;
			m_currentFrame = 0;
			m_currentAnimationDurations = it;
			m_dirty = true;
		}
	}


	void AnimatedSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTextureDuartion) {
		m_statesMap.emplace(state, subTextureDuartion);
		
	}

	void AnimatedSprite::renderer(bool mirrored, float level) {
		if (m_dirty) {
			auto subTexture = m_texture->getSubTexture2D(m_currentAnimationDurations->second[m_currentFrame].first);

			float texureCords[] = {
				subTexture.rightTopUV.x, subTexture.leftBottomUV.y ,
				subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
				subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
				subTexture.rightTopUV.x, subTexture.rightTopUV.y
			};
			m_textureBuffer->updateBuffer(texureCords, 8);
			m_vertexBuffer->unbind();
			m_dirty = false;
		}
		Sprite::renderer(mirrored, level);
	}

}
