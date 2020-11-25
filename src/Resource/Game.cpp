#include "Game.h"
#include "background.h"

Game::Game() {
	m_background = std::make_unique<Background>("D:\\projectC++\\testGame\\res\\shaders\\ret", 
		"backgroundVertex.txt", "backgroundFragment.txt",
		"background.png");
}

void Game::init() {

}

void Game::bind() {
	m_background->bind();
}