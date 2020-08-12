#include "Collision.h"
#include "SDL.h"

#include <iostream>
#include <cmath>

bool Collision::AABB(SDL_Rect* A, SDL_Rect* B) {
  //The sides of the rectangles
  int leftA, leftB; int rightA, rightB;
  int topA, topB; int bottomA, bottomB;

  //Calculate the sides of rect A
  leftA = A->x; rightA = A->x + A->w; topA = A->y;
  bottomA = A->y + A->h;

  //Calculate the sides of rect B
  leftB = B->x; rightB = B->x + B->w;
  topB = B->y; bottomB = B->y + B->h;

  //If any of the sides from A are outside of B
  if(bottomA <= topB) { return false; }
  if(topA >= bottomB) { return false; }
  if(rightA <= leftB) { return false; }
  if(leftA >= rightB) { return false; }

  //If none of the sides from A are outside B return true;
  return true;
}

bool Collision::onTopOf(SDL_Rect* A, SDL_Rect* B) {
  //The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topB;
  int bottomA;

  //Calculate the sides of rect A
  leftA = A->x;
  rightA = A->x + A->w;
  bottomA = A->y + A->h;

  //Calculate the sides of rect B
  leftB = B->x;
  rightB = B->x + B->w;
  topB = B->y;

  /*
  std::cout << "onTopOf params: \n";
  std::cout << "abs(bottomA - topB) = " << abs(bottomA - topB) << "\n";
  std::cout << "rightA = " << rightA << "\n";
  std::cout << "leftB = " << leftB << "\n";
  std::cout << "leftA = " << leftA << "\n";
  std::cout << "rightB = " << rightB << "\n\n";
  */

  if(abs(bottomA - topB) <= 10) {
    if(rightA >= leftB && leftA <= rightB) {
      //std::cout << "on top of\n";
      return true;
    }
  }

  return false;
}
