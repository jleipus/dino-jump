#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL.h"

class GameObject {
protected:
  GameObject() {}

public:
  virtual ~GameObject() {}

  virtual void update() = 0;
  virtual void render() = 0;

  virtual void updatePhysics() = 0;

  virtual SDL_Rect* getBody() = 0;

  virtual bool isDead() = 0;
  virtual void kill() = 0;
};

#endif  //GAMEOBJECT_H
