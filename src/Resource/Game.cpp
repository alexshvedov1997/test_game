#include "Game.h"
#include<iostream>
#include"../Physics/PhysicsManager.h"
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
	std::vector<std::string> subTextures = { "run1", "run2", "run3", "run4", "run5","run6" };
	//ResourceManager::loadTexture2D("spriteTexture", GL_CLAMP_TO_EDGE, GL_NEAREST, "hero2.png");

	auto pTextureAtlas = ResourceManager::loadTextureAtlas("HeroTextureAtlas", "hero.png", subTextures, 160, 205);
	auto program = ResourceManager::getShaderProgram("spriteProgram");
	auto animatedSprite = ResourceManager::loadAnimatedSprite("HeroSprite", "spriteProgram",
		"HeroTextureAtlas", glm::vec2(-0.1f, 0.1f), glm::vec2(0.05f, 0.07f), 0, "run1");
	if (!animatedSprite) {
		std::cout << "Can't create sprite" << std::endl;
	}
	std::vector<std::pair<std::string, uint64_t>> runVector;
	runVector.emplace_back(std::make_pair("run1", 300000000));
	runVector.emplace_back(std::make_pair("run2", 300000000));
	runVector.emplace_back(std::make_pair("run3", 300000000));
	runVector.emplace_back(std::make_pair("run4", 300000000));
	runVector.emplace_back(std::make_pair("run5", 300000000));
	runVector.emplace_back(std::make_pair("run6", 300000000));
	animatedSprite->insertState("heroRightState", runVector);
	std::vector<std::pair<std::string, uint64_t>> standVector;
	standVector.emplace_back(std::make_pair("run6", 30000000));
	animatedSprite->insertState("heroStand", standVector);
	animatedSprite->setPosition(glm::vec2(0.f, 0.f));
	animatedSprite->setState("heroRightState");
	//m_Hero = std::make_unique<hero>(animatedSprite, 0.05, glm::vec2(0.f, 0.f));
	m_Hero = std::make_shared<hero>(animatedSprite, 0.0000000004, glm::vec2(0.f, 0.f));
	std::vector<std::string> subTextureGround = { "ground1", "ground2", "ground3", "ground4" };
	ResourceManager::loadShaders("groundProgram", "vSprite.txt", "fSprite.txt");
	ResourceManager::loadTextureAtlas("GroundTextureAtlas", "object.png", subTextureGround, 180, 180);
	auto groundSprite = ResourceManager::loadAnimatedSprite("GroundSprite", "spriteProgram",
		"GroundTextureAtlas", glm::vec2(-0.1f, 0.f), glm::vec2(0.07f, 0.07f), 0, "ground1");
	groundSprite->setPosition(glm::vec2(-0.5f, 0.f));
	auto animatedSprite2 = ResourceManager::getAnimatedSprite("GroundSprite");
	glm::vec2 pos = animatedSprite2->getPosition();
	glm::vec2 sz = animatedSprite2->getScale();
		std::pair<glm::vec2, glm::vec2> size_cord = PhysicsManager::loadObjectSizeCords("GroundTextureAtlas", pos, sz);
		std::cout << "First coords:: " << size_cord.first.x << " :: " << size_cord.first.y << std::endl;
		std::cout << "Second coords:: " << size_cord.second.x << " :: " << size_cord.second.y << std::endl;
}

//}

void Game::bind() {
	m_background->bind();
}

void Game::unbind_back() {
	m_background->unbind();
}

void Game::intersectObject() {
	auto animatedSprite = ResourceManager::getAnimatedSprite("GroundSprite");
	float an_x = animatedSprite->getPosition().x;
	float an_y = animatedSprite->getPosition().y;
	float hero_x = m_Hero->getPosition().x;
	float hero_y = m_Hero->getPosition().y;
	//std::cout << "Hero x = " << hero_x << " y= " << hero_y << std::endl;
	//std::cout << "Sprite x = " << an_x << " y=" << an_y << std::endl;
	if ((animatedSprite->getPosition().x > m_Hero->getPosition().x) && (m_Hero->getPosition().x < animatedSprite->getPosition().x + 0.1))
		std::cout << "Collision" << std::endl;
}

void Game::render() {
	auto animatedSprite = ResourceManager::getAnimatedSprite("GroundSprite");
	animatedSprite->renderer();
	//m_Hero->render();
}

void Game::update(float delta) {
	//auto animatedSprite = ResourceManager::getAnimatedSprite("HeroSprite");
	//animatedSprite->update(delta);

	SDL_Event e;
	if (m_Hero) {
		
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
				//	m_mirrored = false;
					m_Hero->setOrientation(hero::eOrientation::Left);
					m_Hero->move(true);
					break;
				case  SDLK_LEFT:
				//	m_mirrored = true;
					m_Hero->setOrientation(hero::eOrientation::Right);
					m_Hero->move(true);
					break;

				}
		}
			else if (e.type != SDL_KEYDOWN) {
				m_Hero->setOrientation(hero::eOrientation::Stand);
				m_Hero->move(true);
			}
			else if (e.type == SDL_QUIT) {
				m_quit = true;
			}
			else{
				m_Hero->setOrientation(hero::eOrientation::Stand);
				m_Hero->move(true);
				
			}
		}
	}
	m_Hero->update(delta);
	m_Hero->render(false, 0.01);
}