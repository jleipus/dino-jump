#include "Enemy.h"
#include "Game.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(SDL_Texture *texture) : FallingObject() {
  enemyTexture = texture;

	width = 60;
	height = 60;

	centerPos.setX(1280 / 2);
  centerPos.setY(490);

  speed.setX(3);
  speed.setY(0);

  direction = Direction::RIGHT;

	std::cout << "Enemy created\n";;
}

Enemy::~Enemy() {}

void Enemy::update() {
  speed.setY(0);

  if(centerPos.getX() >= 1270 && speed.getX() == 3) {
    speed.setX(-3);
    direction = Direction::LEFT;
  }
  else if(centerPos.getX() <= 10 && speed.getX() == -3) {
    speed.setX(3);
    direction = Direction::RIGHT;
  }

  centerPos += speed;
}

void Enemy::render() {
	SDL_RenderCopyEx(Game::renderer, enemyTexture, NULL, getBody(), 0, NULL, (direction != Direction::LEFT)? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Enemy::setDirection(Direction _direction) {
  direction = _direction;
}
