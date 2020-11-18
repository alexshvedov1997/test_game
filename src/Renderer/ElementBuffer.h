#pragma once

 namespace Renderer{

	 class ElementBuffer {
	 public:
		 ElementBuffer();
		 void init_element_buffer(void* data);
		 void bind();
		 void unbind();
		 ~ElementBuffer();
	 private:
		 unsigned int buffer_id;
	 };
 
 }