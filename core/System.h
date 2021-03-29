#ifndef EQUAL_SYSTEM_H
#define EQUAL_SYSTEM_H

#include <entt/entity/registry.hpp>

struct System {
  virtual ~System(){};

  virtual void run(entt::registry &registry, float delta_time) = 0;
};

#endif // EQUAL_SYSTEM_H
