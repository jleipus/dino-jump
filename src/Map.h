#ifndef MAP_H
#define MAP_H

class Map {
public:
  Map(const char* path);
  ~Map();

  int getBlock(int y, int x);

private:
  int blockMap[18][32] = { 0 };
};

#endif //MAP_H
