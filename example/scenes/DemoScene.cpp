#include "DemoScene.h"

void DemoScene::on_sprite_update(entt::registry &registry,
                                 entt::entity entity) {
    registry.sort<eq::SpriteComponent>(
            [](const eq::SpriteComponent &left, const eq::SpriteComponent &right) {
                return left.depth < right.depth;
            });
}

void DemoScene::init() {
    eq::Logger::debug("Registering the ECS listeners\n");

    registry.on_construct<eq::SpriteComponent>()
            .connect<&DemoScene::on_sprite_update>(this);
    registry.on_update<eq::SpriteComponent>()
            .connect<&DemoScene::on_sprite_update>(this);

    eq::Logger::debug("Registering the camera\n");
    {
        camera = eq::Entity(registry.create(), this);
        auto &cc = camera.add_component<eq::CameraComponent>();
        cc.size = app->viewport_size;
    }
    eq::Logger::debug("Registering the player\n");
    {
        player = eq::Entity(registry.create(), this);
        player.add_component<eq::PlayerComponent>();
        player.add_component<eq::TransformComponent>(eq::Position{},
                                                     eq::Size{32, 64});

        auto &player_sprite = player.add_component<eq::SpriteComponent>();
        player_sprite.color = eq::Color{255, 255, 255};
        player_sprite.texture_id = "player";
        player_sprite.transform = eq::Transform{{}, eq::Size{16, 32}};
    }
    eq::Logger::debug("Loading textures\n");
    {
        textures.load(app->window, "assets/player.png");
        textures.load(app->window, "assets/map/tilesets/grounds.png");
        textures.load(app->window, "assets/map/tilesets/trees.png");
        textures.load(app->window, "assets/map/tilesets/walls.png");
    }
    eq::Logger::debug("Loading map\n");
    {
        map = eq::make_ref<eq::Map>();
        map->load_from(this, "assets/map/demo.tmx",
                       "assets/map/objecttypes.xml");
    }
}

void DemoScene::event(const eq::Event &event) {
    if (!loading) {
        eq::InputSystem::run(event, player);
    }
}

void DemoScene::update(float delta_time) {
    if (loading) {
        if (map->state.load() == eq::Map::LoadingState::FINISHED &&
            map->thread->joinable()) {

            map->thread->join();
            map->thread = nullptr;

            map->state.store(eq::Map::LoadingState::LOADED);
        }

        if (map->state.load() == eq::Map::LoadingState::LOADED) {
            map->attach(player);

            loading = false;
            eq::Logger::debug("Scene loaded!\n");
        }
    }

    if (!loading) {
        eq::MovementSystem::run(map, registry, player, delta_time);
        eq::CameraSystem::run(map, registry, camera, player);
    }
}

void DemoScene::draw(eq::Renderer *renderer) {
    if (!loading) {
        eq::RendererSystem::run(this, registry, renderer);
    }
}
