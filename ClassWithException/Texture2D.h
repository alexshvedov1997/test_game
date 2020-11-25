#pragma once
#include <glad/glad.h>

namespace Renderer {

	class Texture2D {
	public:
		Texture2D(int width, int height,
			unsigned char* data, GLenum filter = GL_CLAMP_TO_EDGE 
			, GLenum imposition = GL_NEAREST, int chanels = 3);
		void bind();
		~Texture2D();
		void unbind();
	private:
		int m_width = 0;
		int m_height = 0;
		unsigned int m_ID;
	};

}