#pragma once
#include <glad/glad.h>

namespace Renderer{
	class ShaderProgram {
	public:
		ShaderProgram(const char* veretxShader,const char *fragmentShader);
		~ShaderProgram();
		void use();
		bool createShader(const char* data, GLenum type, GLuint& shader);
		bool isCompiled() { return m_isCompiled; }

	private:
		unsigned int m_id;
		GLuint m_vertexShader;
		GLuint m_fragmentShader;
		bool m_isCompiled = false;
	};


}