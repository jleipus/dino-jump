#ifndef PLAYER2_H
#define PLAYER2_H

#include "FallingObject.h"
#include "InputHandler.h"
#include "Vector2D.h"

class Player2 : public FallingObject {
public:
  explicit Player2(SDL_Texture *texture);
  ~Player2();

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

#endif //PLAYER2_H
