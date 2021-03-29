#ifndef EQUAL_LOGGER_H
#define EQUAL_LOGGER_H

#ifdef DEBUG
#define EQ_LOG(...)                                                            \
  { printf(__VA_ARGS__); }
#else
#define EQ_LOG(...)                                                            \
  {}
#endif

#endif // EQUAL_LOGGER_H
