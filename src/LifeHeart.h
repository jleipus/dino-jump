#ifndef LIFEHEART_H
#define LIFEHEART_H

#include "SDL.h"
#include "Vector2D.h"

class LifeHeart {
public:
  LifeHeart(SDL_Texture *texture, int x, int y);
  ~LifeHeart();

  void render();

  SDL_Rect* getBody();

  Vector2D& getPosition() { return centerPos; }
	int getWidth() { return width; }
	int getHeight() { return height; }

 private:
  SDL_Texture *heartTexture;

  Vector2D centerPos;

	int width;
	int height;
};

#endif //LIFEHEART_H
