#include "VertexArray.h"


namespace Renderer {

	VertexArray::VertexArray():vertexArray_id(0) {
		glGenVertexArrays(1, &vertexArray_id);
	}
	void VertexArray::bind() {
		glBindVertexArray(vertexArray_id);
	}
	void VertexArray::unbind() {
		glBindVertexArray(0);
	}
	void VertexArray::init_vertexArray(unsigned int layout,   unsigned int size , GLenum type, bool normalized, void * offset) {
		glBindVertexArray(vertexArray_id);
		glEnableVertexAttribArray(layout);
		glVertexAttribPointer(layout, size, type, normalized, size * sizeof(float), offset);
		glBindVertexArray(0);
	}

	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &vertexArray_id);
	}

}