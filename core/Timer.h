#ifndef EQUAL_TIMER_H
#define EQUAL_TIMER_H

#include <SDL2/SDL.h>

class Timer {
private:
  uint32_t start_ticks;
  uint32_t paused_ticks;
  bool paused;
  bool started;

public:
  Timer();

  void start();
  void stop();
  void pause();
  void unpause();

  uint32_t get_ticks();

  bool is_started();
  bool is_paused();
};

#endif // EQUAL_TIMER_H
