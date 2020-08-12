#include "StationaryObject.h"

StationaryObject::StationaryObject(): GameObject() {
	dead = false;
}

StationaryObject::~StationaryObject() {}

void StationaryObject::update() {}

void StationaryObject::render() {}

void StationaryObject::updatePhysics() {}

SDL_Rect* StationaryObject::getBody() {
	SDL_Rect* body = new SDL_Rect();

	body->x = centerPos.getX() - (width / 2);
	body->y = centerPos.getY() - (height / 2);

	body->w = width;
	body->h = height;

	return body;
}
