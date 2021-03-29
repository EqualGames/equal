#ifndef EQUAL_MAP_H
#define EQUAL_MAP_H

#include "../components/PlayerComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/TagComponent.h"
#include "../components/TransformComponent.h"
#include "../core/Exception.h"
#include "../core/Logger.h"
#include "Application.h"
#include "Helpers.h"
#include "Scene.h"
#include "Tile.h"
#include "Tileset.h"
#include "Types.h"
#include <atomic>
#include <filesystem>
#include <pugixml.hpp>
#include <thread>
#include <vector>

struct Map {
  Size size{0, 0};
  Size tile_size{32, 32};
  std::vector<Tileset> tilesets{};
  std::vector<Ref<Tile>> tiles{};

  enum LoadingState { IDLE = 0, STARTED = 1, FINISHED = 2, LOADED = 3 };
  std::atomic_int state;
  Scope<std::thread> thread{nullptr};

  Map(Scene *scene, const char *source, const char *types_source);

  Tileset &get_tileset(uint32_t gid);

  bool has_tile(const Position &position);
  const Ref<Tile> &get_tile(const Position &position);

  void attach(entt::registry &registry, entt::entity entity);

  bool has_collision(const Position &position);
  const Ref<Tile> &get_next_tile(entt::entity entity, const Position &position,
                                 const ControllerState &controller);
};

#endif // EQUAL_MAP_H
