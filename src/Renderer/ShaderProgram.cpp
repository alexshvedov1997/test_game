#include "ShaderProgram.h"
#include <iostream>
#include<glad/glad.h>
#include <glm/mat4x4.hpp>

namespace Renderer {

	ShaderProgram::ShaderProgram(const char* vertexShader,const  char* fragmentShader) {
		if (!createShader(vertexShader, GL_VERTEX_SHADER, m_vertexShader)) {
			puts("ERROR::Vertex Shader \n");
		}
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, m_fragmentShader)) {
			puts("ERROR::Fragment Shader \n");
		}
		m_id = glCreateProgram();
		glAttachShader(m_id, m_vertexShader);
		glAttachShader(m_id, m_fragmentShader);
		glLinkProgram(m_id);
		GLint success;
		char infoLog[512];
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_id, 512, NULL, infoLog);
			std::cerr << "Can't complie program" << std::endl;
			return;
		}
		m_isCompiled = true;
	
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_id);
	}

	void ShaderProgram::ShaderProgram::use() {
		glUseProgram(m_id);
	}

	bool ShaderProgram::createShader(const char* data, GLenum type, GLuint& shader) {
		shader = glCreateShader(type);
		glShaderSource(shader, 1, &data, NULL);
		glCompileShader(shader);
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cerr << "Can't create shader " << infoLog << std::endl;
			return false;
		}
		return true;
	}

	void ShaderProgram::setMatrix4(const std::string name, const glm::mat4& matrix) {
		
		glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1,GL_FALSE, glm::value_ptr(matrix));
	}

};