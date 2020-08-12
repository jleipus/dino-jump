#include "InputHandler.h"
#include "Game.h"

#include <iostream>

InputHandler* InputHandler::instance = 0;

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {
	delete keystates;
}

void InputHandler::onKeyUp() {
	keystates = SDL_GetKeyboardState(NULL);
}

void InputHandler::onKeyDown() {
	keystates = SDL_GetKeyboardState(NULL);
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
	if(keystates != NULL) 	{
		if(keystates[key] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void InputHandler::update() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			//Game::Instance()->quit();
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		default:
			break;
		}
	}
}

void InputHandler::reset() {}

void InputHandler::clean() {}
