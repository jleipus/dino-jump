#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <sstream>

using namespace std;

class sdl_init_fail : public runtime_error {
public:
  sdl_init_fail() : runtime_error("sdl init fail") { }
};

class file_format_error : public runtime_error {
public:
  file_format_error(int line, int column) : runtime_error(format_message(line, column)) { }


private:
  static string format_message(int line, int column) {
    stringstream ss;
    ss << "file format error at line: " << line << ", column: " << column;
    return ss.str();
  }
};

class map_file_missing : public runtime_error {
public:
  map_file_missing(const char* filename) : runtime_error(format_message(filename)) { }

private:
  static string format_message(const char* filename) {
    stringstream ss;
    ss << "map file missing: " << filename;
    return ss.str();
  }
};

class game_init_fail : public runtime_error {
public:
  game_init_fail() : runtime_error("game init fail") { }
};

class object_error : public logic_error {
public:
  object_error(const char* object) : logic_error(format_message(object)) { }

private:
  static string format_message(const char* object) {
    stringstream ss;
    ss << "object error: " << object;
    return ss.str();
  }
};

#endif //EXCEPTIONS_H
