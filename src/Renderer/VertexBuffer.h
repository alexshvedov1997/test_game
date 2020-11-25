#pragma once
#include <glad/glad.h>
namespace Renderer{
	class VertexBuffer {
	public:
		VertexBuffer();
		~VertexBuffer();
		void init_veretx_buffer(void * data, unsigned int count_element);
		void bind();
		void unbind();

	private:
		GLuint buffer_id;


	};



}