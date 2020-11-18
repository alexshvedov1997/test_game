#include<iostream>
#include <SDL.h>
#include <glad/glad.h>
#include "Renderer/VertexBuffer.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/ResourceManager.h"
#include <string>
#include "Renderer/ResourceManager.h"

using namespace std;

int width = 600;
int height = 800;

float vertices[] = {
	-0.5f , -0.5f, 0.0,
	0.5f, -0.5f , 0.0f,
	0.0f, 0.5f, 0.0f
};


const char* vertexShaderSource = "#version 430 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main() \n"
"{\n"
"gl_Position  = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


const char* fragmentShaderSource = "#version 430 core\n"
"out vec4 FragColor ;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 1.0f, 0.65f, 1.0f); "

"}\0";


int SDL_main(int argc, char* argv[]) {

	cout << "Path " << argv[0];
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Crash" << endl;
		return - 1;
}
	
	SDL_Window* window = SDL_CreateWindow("Fist OpenGL project", 100, 100, width, height, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (!gladLoadGL()) {
		cout << "Can't initialize gl" << endl;
		return -1;
	}
	
	
	ResourceManager manager("D:\\projectC++\\testGame\\res\\shaders\\ret");
	manager.loadShaders("DefaultProgram" ,"vertexShader.txt", "fragmentShader.txt");
	auto program = manager.getShaderProgram("DefaultProgram");
	Renderer::VertexBuffer vertexBuffer;
	vertexBuffer.init_veretx_buffer(vertices);
	puts("Success");
	vertexBuffer.bind();
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	bool quit = false;
	SDL_Event e;
	while (!quit) {	
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}	
		}
		glClearColor(0, 0.23, 0.45, 2);
		glClear(GL_COLOR_BUFFER_BIT);
		program->use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
return 0;
}