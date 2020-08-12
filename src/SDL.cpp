#include "SDL.h"
#include "Exceptions.h"

bool SDL::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		throw sdl_init_fail();
	}

	return true;
}

void SDL::exit() {
	if(TTF_WasInit()) {
		TTF_Quit();
  }

	SDL_Quit();
}
