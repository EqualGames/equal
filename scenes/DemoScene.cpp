#include "DemoScene.h"

void DemoScene::on_sprite_update(entt::registry &registry,
                                 entt::entity entity) {
  registry.sort<SpriteComponent>(
      [](const SpriteComponent &left, const SpriteComponent &right) {
        return left.depth < right.depth;
      });
}

void DemoScene::init() {
  EQ_LOG("Registering the ECS listeners\n");

  registry.on_construct<SpriteComponent>()
      .connect<&DemoScene::on_sprite_update>(this);
  registry.on_update<SpriteComponent>().connect<&DemoScene::on_sprite_update>(
      this);

  EQ_LOG("Registering the camera\n");

  camera = registry.create();
  registry.emplace<TagComponent>(camera, "Camera");
  auto &camera_component = registry.emplace<CameraComponent>(camera);
  camera_component.position = Position{};
  camera_component.size = app->viewport_size;

  EQ_LOG("Registering the player\n");

  player = registry.create();
  registry.emplace<TagComponent>(player, "Player");
  auto &player_component = registry.emplace<PlayerComponent>(player);

  auto &player_transform = registry.emplace<TransformComponent>(player);
  player_transform.size = Size{32, 64};
  player_transform.position = Position{};

  auto &player_sprite = registry.emplace<SpriteComponent>(player);
  player_sprite.color = Color{255, 255, 255};

  player_sprite.texture_id = "player";
  player_sprite.transform = Transform{{}, Size{16, 32}};

  EQ_LOG("Loading textures\n");

  textures.load(app->window, "assets/player.png");
  textures.load(app->window, "assets/map/tilesets/grounds.png");
  textures.load(app->window, "assets/map/tilesets/trees.png");
  textures.load(app->window, "assets/map/tilesets/walls.png");

  EQ_LOG("Loading map\n");

  map =
      make_ref<Map>(this, "assets/map/demo.tmx", "assets/map/objecttypes.xml");
}

void DemoScene::event(const Event &event) {
  if (!loading) {
    InputSystem::run(registry, player, event);
  }
}

void DemoScene::update(float delta_time) {
  if (loading) {
    if (map->state.load() == Map::LoadingState::FINISHED &&
        map->thread->joinable()) {

      map->thread->join();
      map->thread = nullptr;

      map->attach(registry, player);

      map->state.store(Map::LoadingState::LOADED);
    }

    if (map->state.load() == Map::LoadingState::LOADED) {
      loading = false;
      EQ_LOG("Scene loaded!\n");
    }
  }

  if (!loading) {
    MovementSystem::run(map, registry, player, delta_time);
    CameraSystem::run(map, registry, camera, player);
  }
}

void DemoScene::draw(const Ref<sf::RenderWindow> &renderer) {
  if (!loading) {
    RendererSystem::run(this, registry, renderer);
  }
}
