#pragma once

#define BLACK 0
#define WHITE 1
#define INVERSE 2

#ifndef GU800_WIDTH
  #define GU800_WIDTH 128
#endif

#ifndef GU800_HEIGHT
  #define GU800_HEIGHT 64
#endif

#define GU800_HEIGHTBYTES (GU800_HEIGHT / 8)

namespace noritake {

enum class GU800_Func {
  AND = 0b10,
  XOR = 0b01,
  OR  = 0b00
};

enum class GU800_ShiftDir {
  UP, DOWN
};

class GU800_Raw {
  public:
};

} // namespace noritake