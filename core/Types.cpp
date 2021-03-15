#include "Types.h"

Direction operator~(Direction a) { return (Direction) ~(int)a; }

Direction operator|(Direction a, Direction b) {
  return (Direction)((int)a | (int)b);
}

Direction operator&(Direction a, Direction b) {
  return (Direction)((int)a & (int)b);
}

Direction operator^(Direction a, Direction b) {
  return (Direction)((int)a ^ (int)b);
}

Direction &operator|=(Direction &a, Direction b) {
  return (Direction &)((int &)a |= (int)b);
}

Direction &operator&=(Direction &a, Direction b) {
  return (Direction &)((int &)a &= (int)b);
}

Direction &operator^=(Direction &a, Direction b) {
  return (Direction &)((int &)a ^= (int)b);
}
