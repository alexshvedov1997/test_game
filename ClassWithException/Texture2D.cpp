#include "Texture2D.h"

namespace Renderer {
	Texture2D::Texture2D( int width,  int height,
		unsigned char* data, GLenum filter ,
		GLenum imposition ,  int chanels ):m_width(width),m_height(height) {

		
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,0);
		
	}

	void Texture2D::bind() {
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_ID);
	}


}