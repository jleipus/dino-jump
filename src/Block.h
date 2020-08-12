#ifndef BLOCK_H
#define BLOCK_H

#include "StationaryObject.h"

class Block : public StationaryObject {
public:
  Block(SDL_Texture *texture, int x, int y);
  virtual ~Block();

  void update() override;
  void render() override;
  void clean();

 private:
  SDL_Texture *blockTexture;
};

#endif //BLOCK_H
