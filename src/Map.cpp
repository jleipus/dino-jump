#include "Map.h"
#include "Exceptions.h"

#include <fstream>
#include <iostream>

extern int blockMap[18][32];

Map::Map(const char* path) {
  char c;
	std::ifstream mapFile(path);

	if(mapFile) {
  	std::cout << "File opened: " << path << "\n";
	}
	else {
    throw map_file_missing(path);
	}

	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 32; x++) {
			mapFile.get(c);

      if(atoi(&c) != 0 && atoi(&c) != 1 && atoi(&c) != 2 && atoi(&c) != 3 && atoi(&c) != 4) {
        throw file_format_error(y, x);
      }

			blockMap[y][x] = atoi(&c);

			mapFile.ignore();
		}
	}

  mapFile.close();
}

Map::~Map() {
  //delete[] blockMap;
}

int Map::getBlock(int y, int x) {
  return this->blockMap[y][x];
}
