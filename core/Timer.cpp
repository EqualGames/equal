#include "Timer.h"

Timer::Timer() {
  this->start_ticks = 0;
  this->paused_ticks = 0;

  this->paused = false;
  this->started = false;
}

void Timer::start() {
  this->started = true;
  this->paused = false;

  this->start_ticks = SDL_GetTicks();
  this->paused_ticks = 0;
}

void Timer::stop() {
  this->started = false;
  this->paused = false;
  this->start_ticks = 0;
  this->paused_ticks = 0;
}

void Timer::pause() {
  // If the timer is running and isn't already paused
  if (this->started && !this->paused) {
    // Pause the timer
    this->paused = true;

    // Calculate the paused ticks
    this->paused_ticks = SDL_GetTicks() - this->start_ticks;
    this->start_ticks = 0;
  }
}

void Timer::unpause() {
  // If the timer is running and paused
  if (this->started && this->paused) {
    // Unpause the timer
    this->paused = false;

    // Reset the starting ticks
    this->start_ticks = SDL_GetTicks() - this->paused_ticks;

    // Reset the paused ticks
    this->paused_ticks = 0;
  }
}

uint32_t  Timer::get_ticks() {
  // The actual timer time
  uint32_t  time = 0;

  // If the timer is running
  if (this->started) {
    // If the timer is paused
    if (this->paused) {
      // Return the number of ticks when the timer was paused
      time = this->paused_ticks;
    } else {
      // Return the current time minus the start time
      time = SDL_GetTicks() - this->start_ticks;
    }
  }

  return time;
}

bool Timer::is_started() {
  return this->started;
}

bool Timer::is_paused() {
  return this->paused && this->started;
}
