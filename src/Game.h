#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Map.h"
#include "LifeHeart.h"

#include <vector>
#include <map>
#include <string>

#define WIDTH 1280
#define HEIGHT 720

enum GameState {
	game,
	menu,
	gameOver
};

class Block;

class Game {
public:
	Game();
	~Game();

	void init(bool fullscreen); // throws a fuckton
	void loop();

	void handleEvents();
	void update();
	void render();
	void clean();

	void updatePhysics();

	bool running() { return isRunning; }

	void addGameObject(GameObject* obj);
	 void removeGameObject(GameObject* obj);

	void gameOver();
	void gameRestart();

	static SDL_Renderer *renderer;

	static std::vector<SDL_Texture*> blockTextures;
	static std::vector<SDL_Texture*> playerTextures;

	static std::vector<GameObject*> gameObjects;
	static std::vector<Map*> maps;

	static	void checkCollision();

	GameState gameState;

private:
	std::map<std::string, SDL_Texture*> textures;
	std::pair<SDL_Texture*, SDL_Texture*> heartTextures;

	std::vector<LifeHeart*> player1Lives;
	std::vector<LifeHeart*> player2Lives;

	bool isRunning = false;

	SDL_Window *window;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	int winner;

	void createMap(int i); // throws invalid map format

	int playersLeft;
	void deleteIfNeeded();
};

template <class T>
bool GetIsDead(const T& obj);

#endif //GAME_H
