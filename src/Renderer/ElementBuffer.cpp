#include <glad/glad.h>
#include "ElementBuffer.h"
#include <iostream>

namespace Renderer {
	ElementBuffer::ElementBuffer() :buffer_id(0){}
	void ElementBuffer::init_element_buffer(void* data) {
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
	}
	void ElementBuffer::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
	}
	void ElementBuffer::unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	ElementBuffer::~ElementBuffer() {
		glDeleteBuffers(1, &buffer_id);
	}

}