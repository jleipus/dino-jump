#ifndef TEXT_H
#define TEXT_H

#include "Vector2D.h"
#include <string>

#include "SDL.h"

class Text {
public:
  Text(const char*  _message);
  Text(const char*  _message, Uint8 r, Uint8 g, Uint8 b);
  ~Text();

  SDL_Rect* getBody();

  void setPos(int x, int y) {
    centerPos.setX(x);
    centerPos.setY(y);
  }

  void setSize(int w, int h) {
    width = w;
    height = h;
  }

  void render();

private:
  Vector2D centerPos;

  std::string message;

  int width = 100;
  int height = 100;

  SDL_Texture* messageTexture;

  TTF_Font* font;
  SDL_Color color;
};

#endif //TEXT_H
