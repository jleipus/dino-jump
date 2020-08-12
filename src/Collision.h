#ifndef COLLISION_H
#define COLLISION_H

#include "SDL.h"

#include <iostream>

class Collision {
public:
  bool AABB(SDL_Rect* A, SDL_Rect* B);
  bool onTopOf(SDL_Rect* A, SDL_Rect* B);
};

#endif  //COLLISION_H
