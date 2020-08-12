#include "Player2.h"
#include "Game.h"
#include <cmath>
#include <iostream>

Player2::Player2(SDL_Texture *texture) : FallingObject() {
  std::cout << "Player2 constructor called!\n";

  playerTexture = texture;

	width = 48;
	height = 48;

  centerPos.setX(1224 - 24); // offset by size
  centerPos.setY(0 + 24);

	std::cout << "Player2 created\n";;
}

Player2::~Player2() {}

void Player2::handleInput() {
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		this->jump();
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		speed.setX(-SPEED);
		setDirection(Direction::LEFT);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		speed.setX(SPEED);
		setDirection(Direction::RIGHT);
	}
  if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		if(!hitGround) {
      this->drop();
      return;
    }
	}
}

void Player2::update() {
  if(textureTimer == 50 && playerTexture == Game::playerTextures[2]) {
    playerTexture = Game::playerTextures[1];
    textureTimer = 0;
    std::cout << "texture reset\n";
  }

  textureTimer++;

	speed.setX(0);

  if(hitGround) {
    isJumping = false;
    isDoubleJumping = false;
  }

  handleInput();

	FallingObject::update();
}

void Player2::render() {
	SDL_RenderCopyEx(Game::renderer, playerTexture, NULL, getBody(), 0, NULL, (direction != Direction::LEFT)? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Player2::takeHit() {
  std::cout << "player2 hit!\n";

  playerTexture = Game::playerTextures[2];
  textureTimer = 0;

  centerPos.setX(1224 - 24); // offset by size
  centerPos.setY(0 + 24);

  speed.setX(0);
  speed.setY(0);

  FallingObject::takeHit();
}

int Player2::getPlayerNum() {
  std::cout << "playerNum = 2\n";
  return 2;
}

void Player2::jump() {
  if(isDoubleJumping == true && isJumping == true) {
    return;
  }
  else if(isJumping == true && isDoubleJumping == false && speed.getY() >= 0) {
    isDoubleJumping = true;
    ay = -(JUMP_FORCE) * SPEED;
  }
  else if(isJumping == false && isDoubleJumping == false) {
    isJumping = true;
    ay = -(JUMP_FORCE) * SPEED;
  }

  return;
}

void Player2::drop() {
  if(hitGround || isDropping) {
    return;
  }

  ay = JUMP_FORCE * SPEED;
  isDropping = true;
}

void Player2::setDirection(Direction _direction) {
  direction = _direction;
}
