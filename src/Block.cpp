#include "Block.h"
#include "Game.h"

Block::Block(SDL_Texture *texture, int x, int y) : StationaryObject() {
  centerPos.setX(x);
  centerPos.setY(y);

  width = 40;
  height = 40;

  blockTexture = texture;
}

Block::~Block() {}

void Block::update() {}

void Block::render() {
  SDL_RenderCopy(Game::renderer, blockTexture, NULL, getBody());
}

void Block::clean() {}
