#ifndef PLAYER1_H
#define PLAYER1_H

#include "FallingObject.h"
#include "InputHandler.h"
#include "Vector2D.h"

class Player1 : public FallingObject {
public:
  explicit Player1(SDL_Texture *texture);
  ~Player1();

  void handleInput();

  void update() override;
  void render() override;

  void takeHit() override;

  int getPlayerNum() override;

private:
  SDL_Texture *playerTexture;

  int textureTimer = 0;

  void jump();
  void drop();

  void setDirection(Direction _direction);
  Direction direction = Direction::LEFT;
};

#endif //PLAYER1_H
