#include "Text.h"
#include "Game.h"

#include <iostream>

using namespace std;

Text::Text(const char* _message) {
  font = TTF_OpenFont("assets/Sans.ttf", 24);
  color = {255, 255, 255, 255};

  SDL_Surface* messageSurface = TTF_RenderText_Solid(font, _message, color);
  messageTexture = SDL_CreateTextureFromSurface(Game::renderer, messageSurface);
}

Text::Text(const char*  _message, Uint8 r, Uint8 g, Uint8 b) {
  font = TTF_OpenFont("assets/Sans.ttf", 24);
  color = {r, g, b, 255};

  SDL_Surface* messageSurface = TTF_RenderText_Solid(font, _message, color);
  messageTexture = SDL_CreateTextureFromSurface(Game::renderer, messageSurface);
}

Text::~Text() {
  SDL_DestroyTexture(messageTexture);
}

SDL_Rect* Text::getBody() {
	SDL_Rect* body = new SDL_Rect();

	body->x = centerPos.getX() - (width / 2);
	body->y = centerPos.getY() - (height / 2);

	body->w = width;
	body->h = height;

	return body;
}

void Text::render() {
  SDL_RenderCopy(Game::renderer, messageTexture, NULL, getBody());
}
