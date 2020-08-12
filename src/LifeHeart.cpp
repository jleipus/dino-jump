#include "LifeHeart.h"
#include "Game.h"

LifeHeart::LifeHeart(SDL_Texture *texture, int x, int y) {
  centerPos.setX(x);
  centerPos.setY(y);

  width = 20;
  height = 20;

  heartTexture = texture;
}

LifeHeart::~LifeHeart() {}

void LifeHeart::render() {
  SDL_RenderCopy(Game::renderer, heartTexture, NULL, getBody());
}

SDL_Rect* LifeHeart::getBody() {
	SDL_Rect* body = new SDL_Rect();

	body->x = centerPos.getX() - (width / 2);
	body->y = centerPos.getY() - (height / 2);

	body->w = width;
	body->h = height;

	return body;
}
