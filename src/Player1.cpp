#include "Player1.h"
#include "Game.h"
#include <cmath>
#include <iostream>

Player1::Player1(SDL_Texture *texture) : FallingObject() {
  std::cout << "Player1 constructor called!\n";

  playerTexture = texture;

	width = 48;
	height = 48;

	centerPos.setX(16 + 24); // offset by size
  centerPos.setY(0 + 24);

	std::cout << "Player1 created\n";;
}

Player1::~Player1() {}

void Player1::handleInput() {
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
    this->jump();
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
		speed.setX(-SPEED);
		setDirection(Direction::LEFT);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
		speed.setX(SPEED);
		setDirection(Direction::RIGHT);
	}
  if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
		if(!hitGround) {
      this->drop();
      return;
    }
	}
}

void Player1::update() {
  if(textureTimer == 50 && playerTexture == Game::playerTextures[2]) {
    playerTexture = Game::playerTextures[0];
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

void Player1::render() {
	SDL_RenderCopyEx(Game::renderer, playerTexture, NULL, getBody(), 0, NULL, (direction != Direction::LEFT)? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Player1::takeHit() {
  std::cout << "player1 hit!\n";

  playerTexture = Game::playerTextures[2];
  textureTimer = 0;

  centerPos.setX(16 + 24); // offset by size
  centerPos.setY(0 + 24);

  speed.setX(0);
  speed.setY(0);

  FallingObject::takeHit();
}

int Player1::getPlayerNum() {
  std::cout << "playerNum = 1\n";
  return 1;
}

void Player1::jump() {
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

void Player1::drop() {
  if(hitGround || isDropping) {
    return;
  }

  std::cout << "dropping\n";
  ay = JUMP_FORCE * SPEED;
  isDropping = true;
}

void Player1::setDirection(Direction _direction) {
  direction = _direction;
}
