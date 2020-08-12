#ifndef ENEMY_H
#define ENEMY_H

#include "FallingObject.h"
#include "InputHandler.h"
#include "Vector2D.h"

class Enemy : public FallingObject {
public:
  Enemy(SDL_Texture *texture);
  ~Enemy();

  void update() override;
  void render() override;

private:
  SDL_Texture *enemyTexture;

  void setDirection(Direction _direction);
  Direction direction = Direction::LEFT;
};

#endif //ENEMY_H
