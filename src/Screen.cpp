#include "Screen.h"

Screen::Screen(int _width, int _height): StationaryObject() {
  width = _width;
  height = _height;

  centerPos.setX(width / 2);
  centerPos.setY(height / 2);
}

Screen::~Screen() {}

void Screen::update() {}

void Screen::render() {}

void Screen::clean() {}
