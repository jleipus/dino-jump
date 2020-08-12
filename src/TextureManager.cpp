#include "TextureManager.h"

#include "Game.h"

SDL_Texture* TextureManager::loadTexture(const char* path) {
	SDL_Surface* tmpSurface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	//Game::textures.push_back(texture);
	return texture;
}
