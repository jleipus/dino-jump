#ifndef FALLINGOBJECT_H
#define FALLINGOBJECT_H

#include "GameObject.h"
#include "Vector2D.h"
#include "Game.h"

#define SPEED 5
#define MAX_SPEED 50
#define JUMP_FORCE 2

enum Direction {
  LEFT, RIGHT
};

class FallingObject : public GameObject {
public:
	FallingObject();
	virtual ~FallingObject();

	virtual void update();
  virtual void render();

  virtual void updatePhysics();

	SDL_Rect* getBody() override;

	Vector2D& getPosition() { return centerPos; }
	void setPosition(Vector2D pos) { centerPos = pos; }

  void placeOnTop(SDL_Rect* other);

	int getWidth() { return width; }
	int getHeight() { return height; }

	bool isDead() { return dead; }
	void kill() { dead = false;}

	virtual void takeHit();
  virtual int getPlayerNum();

  int getLives() { return lives; }

	void stopMovement();
  void stopFalling();

  void startFalling() { hitGround = false; }

  float getSpeedY() { return speed.getY();}

protected:
  Vector2D centerPos;
  Vector2D speed;

	Vector2D gravity;
	float ay;

	int width;
	int height;

  int lives;

	bool dead;
	bool hitGround;
  bool isJumping;
  bool isDoubleJumping;
  bool isDropping;
};

#endif  //FALLINGOBJECT_H
