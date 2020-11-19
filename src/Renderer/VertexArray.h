#pragma once
#include <glad/glad.h>

namespace Renderer {
	class VertexArray {
	public:
		VertexArray();
		void bind();
		void unbind();
		void init_vertexArray(unsigned int layout, unsigned int size, GLenum type, bool normalized, void* offset);
		~VertexArray();
	private:
		unsigned int vertexArray_id;

	};
}