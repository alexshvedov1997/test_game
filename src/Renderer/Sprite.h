#pragma once
#include <memory>
#include <glm\vec2.hpp>
#include <string>
#include <glm/mat4x4.hpp>

namespace Renderer {
	class Texture2D;
	class ShaderProgram;
	class ElementBuffer;
	class VertexBuffer;
	class VertexArray;

	class Sprite {
	public:
		struct  sizeObjectInSpace {
			float leftBottom;
			float leftTop;
			float rightBottom;
			float rightTop;
			sizeObjectInSpace():leftBottom(0.f),leftTop(0.f),
				rightBottom(0.f),rightTop(0.f){}
		};

		Sprite(std::shared_ptr<ShaderProgram> program, 
			const std::string& initialSubTexture,
			std::shared_ptr<Texture2D> texture,
			glm::vec2 position, glm::vec2 size, float rotation = 0);
		void setPosition(glm::vec2 position) { m_position = position; }
		void setRotation(float rotation) { m_rotation = rotation; }
		void setSize(glm::vec2 size) { m_size = size; }
		virtual void renderer(bool mirrored = false, float level = 0.1f);
		glm::mat4x4 getModelMatrix() { return m_model; }
		std::shared_ptr<ShaderProgram> getSpriteShaderProgram() { return m_program; }
		glm::vec2 getPosition() { return m_position; }
		sizeObjectInSpace getObjectSize() { return object_size;  }
		glm::vec2 getScale() { return m_size; }
		
	protected:
		glm::vec2 m_position;
		float m_rotation;
		glm::vec2 m_size;
		std::shared_ptr<ShaderProgram> m_program;
		std::shared_ptr<Texture2D> m_texture;
		std::shared_ptr<ElementBuffer> m_elementBuffer;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<VertexBuffer> m_textureBuffer;
		glm::mat4x4 m_model;
		sizeObjectInSpace object_size;
	};

}