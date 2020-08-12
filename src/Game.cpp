#include "SDL.h"

#include "Game.h"
#include "Player1.h"
#include "Player2.h"
#include "GameObject.h"
#include "StationaryObject.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Block.h"
#include "Screen.h"
#include "Collision.h"
#include "Exceptions.h"
#include "Enemy.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>

#include <iostream>
#include <fstream>

SDL_Renderer* Game::renderer = nullptr;
Screen *screen;

std::vector<GameObject*> Game::gameObjects;
std::vector<Map*> Game::maps;

std::vector<SDL_Texture*> Game::blockTextures;
std::vector<SDL_Texture*> Game::playerTextures;
/*
bool GetIsDead(GameObject& obj) {
  return obj.isDead();
}
*/
Game::Game() {
	gameState = GameState::menu;
}

Game::~Game() {}

void Game::init(bool fullscreen) {
	int flags = 0;

	if(fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, flags);
	renderer = SDL_CreateRenderer(window, -1, 0);

	if(window && renderer) {
		std::cout << "Window and renderer created\n";
		isRunning = true;

		//init visuals
		screen = new Screen(WIDTH, HEIGHT);
		std::cout << "Screen created\n";

		textures = {
			{ "background 1", nullptr },
			{ "background 2", nullptr },
			{ "game over background", nullptr },
			{ "game win 1 background", nullptr },
			{ "game win 2 background", nullptr },
			{ "game menu background", nullptr }
		};

		textures.at("background 1") = TextureManager::loadTexture("assets/bcg1.png");
		textures.at("background 2") = TextureManager::loadTexture("assets/bcg2.png");
		textures.at("game over background") = TextureManager::loadTexture("assets/goBcg.png");
		textures.at("game win 1 background") = TextureManager::loadTexture("assets/go1Bcg.png");
		textures.at("game win 2 background") = TextureManager::loadTexture("assets/go2Bcg.png");
		textures.at("game menu background") = TextureManager::loadTexture("assets/gmBcg.png");

		blockTextures.push_back(TextureManager::loadTexture("assets/block1.png")); //0
	  blockTextures.push_back(TextureManager::loadTexture("assets/block2.png")); //1
	  blockTextures.push_back(TextureManager::loadTexture("assets/block3.png")); //2
	  blockTextures.push_back(TextureManager::loadTexture("assets/block4.png")); //3

		playerTextures.push_back(TextureManager::loadTexture("assets/player1.png")); //0
		playerTextures.push_back(TextureManager::loadTexture("assets/player2.png")); //1
		playerTextures.push_back(TextureManager::loadTexture("assets/player_hit.png")); //2

		heartTextures.first = TextureManager::loadTexture("assets/heart_red.png");
		heartTextures.second = TextureManager::loadTexture("assets/heart_green.png");
		std::cout << "Textures loaded\n";

		for(int i = 0; i < 3; i++) {
			player1Lives.push_back(new LifeHeart(heartTextures.first, 10 + 21 * i, 11));
			player2Lives.push_back(new LifeHeart(heartTextures.second, 1270 - 21 * i, 11));
		}

		Player1* player1 = new Player1(playerTextures[0]);
		std::cout << "Player 1 created:\n";

		Player2* player2 = new Player2(playerTextures[1]);
		std::cout << "Player 2 created:\n";

		playersLeft = 2;
		winner = 0;

		addGameObject(player1);
		addGameObject(player2);

		Enemy* enemy = new Enemy(TextureManager::loadTexture("assets/enemy.png"));
		addGameObject(enemy);

		maps.push_back(new Map("assets/maps/1.map"));
		maps.push_back(new Map("assets/maps/2.map"));
		maps.push_back(new Map("assets/maps/3.map"));
		std::cout << "Maps loaded\n";

		srand(time(NULL));
  	int nRandom = rand() % 3 + 1;
		std::cout << "Map " << nRandom << " selected!\n";
		createMap(nRandom-1);
		std::cout << "Map " << nRandom << " created!\n";
	}
	else {
		throw game_init_fail();
		clean();
	}
}

void Game::loop() {
	std::cout << "Game loop starting!\n";

	int frameCount = 0;

	while(running()) {
		frameStart = SDL_GetTicks();
		frameCount++;

		if(frameCount % 200 == 0) {
			//std::swap(static_cast<FallingObject*>(gameObjects[0])->getPosition(), static_cast<FallingObject*>(gameObjects[1])->getPosition());
		}

		updatePhysics();
		checkCollision();

		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - frameStart;
		if(frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	std::cout << "Game loop ended!\n";
	clean();
}

void Game::handleEvents() {
	InputHandler::Instance()->update();

	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		isRunning = false;
		std::cout << "Quitting game!\n";
	}

	if(gameState == GameState::menu) {
		if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
			gameState = GameState::game;
			std::cout << "Starting game!\n";
		}
	}
	else if(gameState == GameState::gameOver) {
		if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
			gameRestart();
		}
	}
	else if(gameState == GameState::game) {
		if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_C)) {
			std::cout << "Player1 position: \n";
	    std::cout << static_cast<FallingObject*>(gameObjects[0])->getPosition() << "\n";

			std::cout << "Player2 position: \n";
		  std::cout << static_cast<FallingObject*>(gameObjects[1])->getPosition() << "\n";

			std::cout << "Enemy position: \n";
			std::cout << static_cast<FallingObject*>(gameObjects[2])->getPosition() << "\n";
		}
		checkCollision();
	}
}

void Game::update() {
	if(gameState == GameState::game) {
		checkCollision();

		for(auto obj : gameObjects) {
			obj->update();
		}

		checkCollision();

		if(static_cast<FallingObject*>(gameObjects[0])->getLives() == 0) {
			playersLeft -= 1;
			winner = 2;
		}
		if(static_cast<FallingObject*>(gameObjects[1])->getLives() == 0) {
			playersLeft -= 1;
			winner = 1;
		}

		deleteIfNeeded();
		if(playersLeft <= 1) { gameOver(); }
	}
}

void Game::render() {
	SDL_RenderClear(renderer);

	switch(gameState) {
	case GameState::game :
		checkCollision();
		SDL_RenderCopy(renderer, textures.at("background 1"), NULL, NULL);

		for(int i = 3; i < (int)gameObjects.size(); i++) {
			gameObjects[i]->render();
		}

		for(int i = 0; i < static_cast<FallingObject*>(gameObjects[0])->getLives(); i++) {
			player1Lives[i]->render();
		}
		for(int i = 0; i < static_cast<FallingObject*>(gameObjects[1])->getLives(); i++) {
			player2Lives[i]->render();
		}

		gameObjects[2]->render();
		gameObjects[1]->render();
		gameObjects[0]->render();
		break;
	case GameState::menu :
		SDL_RenderCopy(renderer, textures.at("background 1"), NULL, NULL);
		SDL_RenderCopy(renderer, textures.at("game menu background"), NULL, screen->getBody());
		break;
	case GameState::gameOver :
		SDL_RenderCopy(renderer, textures.at("background 1"), NULL, NULL);
		if(winner == 1) { SDL_RenderCopy(renderer, textures.at("game win 1 background"), NULL, screen->getBody()); }
		else { SDL_RenderCopy(renderer, textures.at("game win 2 background"), NULL, screen->getBody()); }
		break;
	default:
		break;
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	try {
		SDL_DestroyWindow(window);
		std::cout << "Window destroyed!\n";
		SDL_DestroyRenderer(renderer);
		std::cout << "Renderer destroyed!\n";

		int size = (int)gameObjects.size();
		for(int i = size; i > 0; i--) {
	    removeGameObject(gameObjects[i-1]);
	  }
		std::cout << "gameObjects destroyed!\n";
		for(auto t : textures) {
			SDL_DestroyTexture(t.second);
		}
		std::cout << "textures destroyed!\n";
		for(auto t : blockTextures) {
			SDL_DestroyTexture(t);
		}
		std::cout << "blockTextures destroyed!\n";
		for(auto t : playerTextures) {
			SDL_DestroyTexture(t);
		}
		std::cout << "playerTextures destroyed!\n";

		std::cout << "Game cleaned!\n";
	}
	catch(...) {
		throw object_error(SDL_GetError());
	}
}

void Game::updatePhysics() {
	if(gameState == GameState::game) {
		checkCollision();

		for(auto obj : gameObjects) {
			obj->updatePhysics();
		}

		checkCollision();
	}
}

void Game::addGameObject(GameObject* obj) {
  gameObjects.push_back(obj);

	std::cout << "GameObject " << (int)gameObjects.size() << " added: ";
	if(dynamic_cast<FallingObject*>(obj)) {
		std::cout << "Player\n";
	}
	else if(dynamic_cast<Block*>(obj)) {
		std::cout << "Block\n";
	}

}

void Game::removeGameObject(GameObject* obj) {
	for(int i = 0; i < (int)gameObjects.size(); i++) {
    if(gameObjects[i] == obj) {
      gameObjects.erase(gameObjects.begin() + i);

			std::cout << "GameObject " << i << " destoyed: ";
			if(dynamic_cast<FallingObject*>(obj)) {
				std::cout << "Player\n";
			}
			else if(dynamic_cast<Block*>(obj)) {
				std::cout << "Block\n";
			}
    }
  }

	try {
		delete obj;
	}
	catch(exception& e) {
		throw e;
	}
}

void Game::gameOver() {
  gameState = GameState::gameOver;
	std::cout << "GameOver!\n";
}

void Game::gameRestart() {
	//clean();
	//init(false);
	//gameState = GameState::game;

	isRunning = false;
}

void Game::checkCollision() {
	Collision colManager;

	for(int i = 3; i < (int)gameObjects.size(); i++) {
		if(colManager.AABB(gameObjects[0]->getBody(), gameObjects[i]->getBody())) { // player1 collision with block
			if(colManager.onTopOf(gameObjects[0]->getBody(), gameObjects[i]->getBody())) {
				static_cast<FallingObject*>(gameObjects[0])->stopFalling();
				static_cast<FallingObject*>(gameObjects[0])->placeOnTop(gameObjects[i]->getBody());
			}
		}
		else {
			static_cast<FallingObject*>(gameObjects[0])->startFalling();
		}
	}

	for(int i = 3; i < (int)gameObjects.size(); i++) {
		if(colManager.AABB(gameObjects[1]->getBody(), gameObjects[i]->getBody())) { // player2 collision with block
			if(colManager.onTopOf(gameObjects[1]->getBody(), gameObjects[i]->getBody())) {
				static_cast<FallingObject*>(gameObjects[1])->stopFalling();
				static_cast<FallingObject*>(gameObjects[1])->placeOnTop(gameObjects[i]->getBody());
			}
		}
		else {
			static_cast<FallingObject*>(gameObjects[1])->startFalling();
		}
	}

	// PLAYER ON PLAYER COLLISION

	if(colManager.onTopOf(gameObjects[0]->getBody(), gameObjects[1]->getBody())) {
		if(static_cast<FallingObject*>(gameObjects[0])->getSpeedY() > 0) {
			static_cast<FallingObject*>(gameObjects[1])->takeHit();
		}
	}

	if(colManager.onTopOf(gameObjects[1]->getBody(), gameObjects[0]->getBody())) {
		if(static_cast<FallingObject*>(gameObjects[1])->getSpeedY() > 0) {
			static_cast<FallingObject*>(gameObjects[0])->takeHit();
		}
	}

	// PLAYER AND ENEMY COLLISION

	if(colManager.AABB(gameObjects[0]->getBody(), gameObjects[2]->getBody())) { // player1 collision with enemy
		static_cast<FallingObject*>(gameObjects[0])->takeHit();
	}

	if(colManager.AABB(gameObjects[1]->getBody(), gameObjects[2]->getBody())) { // player1 collision with enemy
		static_cast<FallingObject*>(gameObjects[1])->takeHit();
	}

	// OFFSCREEN TELEPORT

	if(static_cast<FallingObject*>(gameObjects[0])->getPosition().getX() <= 0 - 24) {
		Vector2D pos = static_cast<FallingObject*>(gameObjects[0])->getPosition();
		pos.setX(static_cast<FallingObject*>(gameObjects[0])->getPosition().getX() + screen->getBody()->w);

		static_cast<FallingObject*>(gameObjects[0])->setPosition(pos);
	}
	else if(static_cast<FallingObject*>(gameObjects[0])->getPosition().getX() >= screen->getBody()->w + 24) {
		Vector2D pos = static_cast<FallingObject*>(gameObjects[0])->getPosition();
		pos.setX(static_cast<FallingObject*>(gameObjects[0])->getPosition().getX() - screen->getBody()->w);

		static_cast<FallingObject*>(gameObjects[0])->setPosition(pos);
	}

	if(static_cast<FallingObject*>(gameObjects[1])->getPosition().getX() <= 0 - 24) {
		Vector2D pos = static_cast<FallingObject*>(gameObjects[1])->getPosition();
		pos.setX(static_cast<FallingObject*>(gameObjects[1])->getPosition().getX() + screen->getBody()->w);

		static_cast<FallingObject*>(gameObjects[1])->setPosition(pos);
	}
	else if(static_cast<FallingObject*>(gameObjects[1])->getPosition().getX() >= screen->getBody()->w + 24) {
		Vector2D pos = static_cast<FallingObject*>(gameObjects[1])->getPosition();
		pos.setX(static_cast<FallingObject*>(gameObjects[1])->getPosition().getX() - screen->getBody()->w);

		static_cast<FallingObject*>(gameObjects[1])->setPosition(pos);
	}
}

void Game::createMap(int i) {
  Block* block;

	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			int c;
			try {
				c = maps[i]->getBlock(y, x);
			}
			catch(exception& e) {
				c = 0;
				throw e;
			}

			int xPos = x * 40 + 20; // offset from center
			int yPos = y * 40 + 20;

      if(c == 1) {
        block = new Block(blockTextures[0], xPos, yPos);
        addGameObject(block);
      }
      else if(c== 2) {
        block = new Block(blockTextures[1], xPos, yPos);
        addGameObject(block);
      }
      else if(c == 3) {
        block = new Block(blockTextures[2], xPos, yPos);
        addGameObject(block);
      }
      else if(c == 4) {
        block = new Block(blockTextures[3], xPos, yPos);
        addGameObject(block);
      }

		}
	}
}

void Game::deleteIfNeeded() {
	for(int i = 0; i < (int)gameObjects.size(); i++) {

		if(dynamic_cast<FallingObject*>(gameObjects[i])) { // IF CURRENT OBJECT IS PLAYER
			if(!SDL_HasIntersection(screen->getBody(), gameObjects[i]->getBody())) { // IF PLAYER IS OFFSCREEN
				if(gameObjects[i]->getBody()->y > screen->getBody()->h) { // IF PLAYER IS UNDER SCREEN
					std::cout << "Reseting offscreen player!\n";
					static_cast<FallingObject*>(gameObjects[i])->takeHit();
				}
			}

			//gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.begin(), GetIsDead), gameObjects.end());

			if(gameObjects[i]->isDead()) {
				std::cout << "player is dead\n";
			}
		}
	}
}
