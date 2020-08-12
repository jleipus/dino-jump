#include "FallingObject.h"

#include <iostream>

FallingObject::FallingObject(): GameObject() {
	dead = false;
	hitGround = false;
	isJumping = true;
	isDoubleJumping = false;
	isDropping = false;

	ay = SPEED;

	//std::cin >> centerPos;

	lives = 3;
}

FallingObject::~FallingObject() {}

void FallingObject::update() {
	centerPos += speed;
	/*
	if(isDropping) {
		speed.setY(0);
		isDropping = false;
	}
	*/
	if(hitGround) {
		isJumping = false;
		isDoubleJumping = false;
	}

	if(lives <= 0) { dead = true; }
}

void FallingObject::render() {}

SDL_Rect* FallingObject::getBody() {
	SDL_Rect* body = new SDL_Rect();

	body->x = centerPos.getX() - (width / 2);
	body->y = centerPos.getY() - (height / 2);

	body->w = width;
	body->h = height;

	return body;
}

void FallingObject::placeOnTop(SDL_Rect* other) {
	centerPos.setY(other->y - height / 2);
}

void FallingObject::updatePhysics() {
	if(hitGround) {
		isJumping = false;
		isDoubleJumping = false;
		isDropping = false;
	}

	if(speed.getY() + ay > -1 * MAX_SPEED  && speed.getY() + ay < MAX_SPEED) {
		float tmp = speed.getY();
		speed.setY(tmp = ay);
	}
	if((isJumping || isDoubleJumping) && ay < 1 * SPEED) { ay += 0.7f; }

	if(hitGround && speed.getY() > 0) { speed.setY(0); }

	Game::checkCollision();
}

void FallingObject::takeHit() {
	lives -= 1;
	if(lives <= 0) { dead = true; }
}

int FallingObject::getPlayerNum() {
	return 0;
}

void FallingObject::stopMovement() {
	speed.setX(0);
	if(speed.getY() <= 0) { speed.setY(0); }
}

void FallingObject::stopFalling() {
	hitGround = true;
	isDropping = false;
	isJumping = false;
	isDoubleJumping = false;
	if(speed.getY() > 0) {
		speed.setY(0);
	}
}
