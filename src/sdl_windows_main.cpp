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
#include "Renderer/Texture2D.h"
#include <glm/vec2.hpp>
#include "Renderer/Sprite.h"
#include <vector>
#include "Renderer/AnimatedSprite.h"
#include <vector>
#include <utility>
#include <chrono>


using namespace std;

int width = 880;
int height = 720;

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
	Game game;
	game.init();
	bool quit = false;
	SDL_Event e;

	glEnable(GL_DEPTH_TEST);
	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(width), 0.f, 
		static_cast<float>(height), -100.f, 100.f);

	//glUniformMatrix4fv(glGetUniformLocation(program->getProgramId(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	//glUniformMatrix4fv(glGetUniformLocation(program->getProgramId(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	auto last_time = std::chrono::high_resolution_clock::now();
	
	while (!quit) {	
	
		glClearColor(0, 0.23, 0.45, 2);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		auto currentTime = std::chrono::high_resolution_clock::now();
		uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - last_time).count();
		last_time = currentTime;
		//animatedSprite->update(duration);
		game.update(duration);
		
		//animatedSprite->renderer();
		//game.render();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//game.bind();
	  //  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	game.unbind_back();
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			
		}
		
		SDL_GL_SwapWindow(window);
	}
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
return 0;
}