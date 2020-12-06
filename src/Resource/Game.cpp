#include "Game.h"
#include<iostream>

#include <glad/glad.h>
#include <string>
#include "../Resource/background.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/ShaderProgram.h"
//#include <glm/gtmatrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Renderer/Texture2D.h"
#include <glm/vec2.hpp>
#include "../Renderer//Sprite.h"
#include <vector>
#include "../Renderer/AnimatedSprite.h"
#include <vector>
#include <utility>
#include <chrono>
#include "../Resource/Hero.h"

Game::Game() {
	m_background = std::make_unique<Background>("D:\\projectC++\\testGame\\res\\shaders\\ret", 
		"backgroundVertex.txt", "backgroundFragment.txt",
		"background.png");
}

void Game::init() {
	ResourceManager::load_resource("D:\\projectC++\\testGame\\res\\shaders\\ret");
	ResourceManager::loadShaders("spriteProgram", "vSprite.txt", "fSprite.txt");
	std::vector<std::string> subTextures = { "run1", "run2", "run3", "run4", "run5" };
	ResourceManager::loadTexture2D("spriteTexture", GL_CLAMP_TO_EDGE, GL_NEAREST, "hero.png");
	auto pTextureAtlas = ResourceManager::loadTextureAtlas("HeroTextureAtlas", "hero.png", subTextures, 150, 210);
	auto program = ResourceManager::getShaderProgram("spriteProgram");
	auto animatedSprite = ResourceManager::loadAnimatedSprite("HeroSprite", "spriteProgram",
		"HeroTextureAtlas", glm::vec2(-0.1f, 0.1f), glm::vec2(0.07f, 0.07f), 0, "run1");
	if (!animatedSprite) {
		std::cout << "Can't create sprite" << std::endl;
	}
	std::vector<std::pair<std::string, uint64_t>> runVector;
	runVector.emplace_back(std::make_pair("run1", 30000000));
	runVector.emplace_back(std::make_pair("run2", 30000000));
	runVector.emplace_back(std::make_pair("run3", 30000000));
	runVector.emplace_back(std::make_pair("run4", 30000000));
	runVector.emplace_back(std::make_pair("run5", 30000000));
	animatedSprite->insertState("heroRightState", runVector);
	animatedSprite->setPosition(glm::vec2(0.f, 0.f));
	animatedSprite->setState("heroRightState");
	//m_Hero = std::make_unique<hero>(animatedSprite, 0.05, glm::vec2(0.f, 0.f));
	m_Hero = std::make_shared<hero>(animatedSprite, 0.000000004, glm::vec2(0.f, 0.f));
	
}

void Game::bind() {
	m_background->bind();
}

void Game::unbind_back() {
	m_background->unbind();
}

void Game::render() {
	//auto animatedSprite = ResourceManager::getAnimatedSprite("HeroSprite");
	//animatedSprite->renderer();
	m_Hero->render();
}

void Game::update(float delta) {
	//auto animatedSprite = ResourceManager::getAnimatedSprite("HeroSprite");
	//animatedSprite->update(delta);

	SDL_Event e;
	if (m_Hero) {
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
				//	m_mirrored = false;
					m_Hero->setOrientation(hero::eOrientation::Left);
					m_Hero->move(true);
					break;
				case SDLK_RIGHT:
				//	m_mirrored = true;
					m_Hero->setOrientation(hero::eOrientation::Right);
					m_Hero->move(true);
					break;

				}
			}
			m_Hero->update(delta);
			m_Hero->render();
		}
	}
}