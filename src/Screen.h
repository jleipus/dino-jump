#ifndef SCREEN_H
#define SCREEN_H

#include "StationaryObject.h"

class Screen : public StationaryObject {
public:
	Screen(int _width, int _height);
	virtual ~Screen();

  void update() override;
  void render() override;
  void clean();

	void updatePhysics() {}
};

#endif  //SCREEN_H
