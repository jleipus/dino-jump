#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "SDL.h"

#include <vector>


class InputHandler {
private:
	InputHandler();
	~InputHandler();

	static InputHandler* instance;

	const Uint8* keystates;

	void onKeyDown();
	void onKeyUp();

public:
	static InputHandler* Instance()	{
		if(instance == 0) {
			instance = new InputHandler();
		}
		return instance;
	}

	bool isKeyDown(SDL_Scancode key);

	void update();
	
	void reset();
	void clean();
};

#endif //INPUTHANDLER_H
