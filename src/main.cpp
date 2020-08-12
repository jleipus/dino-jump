// JORIS LEIPUS
// CPP OOP 2019

#include "Game.h"
#include "SDL.h"

#include <iostream>
#include <stdexcept>

using namespace std;

Game *g = nullptr;

int main() {
	try {
		SDL::init();

		g = new Game();

		g->init(false); //true for fullscreen, false for else
		g->loop();
		g->~Game();
	}
	catch (const exception& e) {
    cerr << "error: " << e.what() << endl;
  }

	SDL::exit();
}
