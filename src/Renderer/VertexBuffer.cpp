#include "VertexBuffer.h"


namespace Renderer{
	VertexBuffer::VertexBuffer():buffer_id(0) {
	
	}
	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &buffer_id);
	}

	void VertexBuffer::init_veretx_buffer(void* data) {
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	}
	void VertexBuffer::unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}


}