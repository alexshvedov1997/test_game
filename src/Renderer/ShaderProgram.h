#pragma once
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <string>

namespace Renderer{
	class ShaderProgram {
	public:
		ShaderProgram(const char* veretxShader,const char *fragmentShader);
		~ShaderProgram();
		void use();
		bool createShader(const char* data, GLenum type, GLuint& shader);
		bool isCompiled() { return m_isCompiled; }
		void setMatrix4(const std::string name, const glm::mat4& matrix);
		int getProgramId() { return m_id; }

	private:
		unsigned int m_id;
		GLuint m_vertexShader;
		GLuint m_fragmentShader;
		bool m_isCompiled = false;
	};


}