#include<iostream>
#include <SDL.h>
#include <glad/glad.h>
#include <string>
#include "Resource/background.h"
#include "Resource/Game.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;

int width = 880;
int height = 720;
/*
float vertices[] = {
	-1.f , -0.2f, 0.5f,
	0.3f, 0.8f , 0.5f,
	  0.f, .2f, 0.5f
	
};
*/

float vertices[] = {
	100.f , 300.f, 0.5f,
	230.f, 180.f , 0.5f,
	  400.f, 120.f, 0.5f

};


int SDL_main(int argc, char* argv[]) {
	cout << "Path " << argv[0];
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Crash" << endl;
		return - 1;
}
	SDL_Window* window = SDL_CreateWindow("Fist OpenGL project", 100, 100, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!gladLoadGL()) {
		cout << "Can't initialize gl" << endl;
		return -1;
	}
	ResourceManager::load_resource("D:\\projectC++\\testGame\\res\\shaders\\ret");
	ResourceManager::loadShaders("defaultShader", "vertexShader.txt", "fragmentShader.txt");
	auto program = ResourceManager::getShaderProgram("defaultShader");
	Renderer::VertexBuffer vertexBuffer;
	vertexBuffer.init_veretx_buffer(vertices, 9);
	Renderer::VertexArray vertexArray;
	vertexBuffer.bind();
	vertexArray.init_vertexArray(0, 3, GL_FLOAT, false, NULL);
	Game game;
	bool quit = false;
	SDL_Event e;
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);

		//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	
	glm::mat4 modelMatrix = glm::mat4(1.f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(100.f, 50.f, 0.f));
	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(width), 0.f, 
		static_cast<float>(height), -100.f, 100.f);
	
	program->use();
	glUniformMatrix4fv(glGetUniformLocation(program->getProgramId(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program->getProgramId(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//	program->setMatrix4("modelMatrix", modelMatrix);
	//program->setMatrix4("projectionMatrix ", projectionMatrix);
	while (!quit) {	
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}	
		}
		glClearColor(0, 0.23, 0.45, 2);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program->use();
		vertexArray.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		game.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
return 0;
}