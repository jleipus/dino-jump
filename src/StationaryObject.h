#ifndef STATIONARYOBJECT_H
#define STATIONARYOBJECT_H

#include "GameObject.h"
#include "Vector2D.h"
#include "Game.h"

class StationaryObject : public GameObject {
public:
	StationaryObject();
	virtual ~StationaryObject();

	virtual void update();
  virtual void render();

	virtual void updatePhysics();

	SDL_Rect* getBody() override;

	Vector2D& getPosition() { return centerPos; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	bool isDead() { return dead; }
	void kill() { dead = false;}

protected:
  Vector2D centerPos;

	int width;
	int height;

	bool dead;
};

#endif  //STATIONARYOBJECT_H
