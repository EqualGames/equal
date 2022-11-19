#pragma once

#include <equal/equal.h>

class DemoScene : public eq::Scene {

public:
//    ~DemoScene() override {
//        registry.on_construct<eq::SpriteComponent>()
//                .disconnect<&DemoScene::on_sprite_update>(this);
//        registry.on_update<eq::SpriteComponent>()
//                .disconnect<&DemoScene::on_sprite_update>(this);
//    }

    void init() override;

    void event(const eq::Event &event) override;

    void update(float delta_time) override;

    void draw(eq::Renderer *renderer) override;

private:
    eq::Entity camera;
    eq::Entity player;

    eq::Entity &get_camera() override {
        return camera;
    }

    eq::Entity &get_player() override {
        return player;
    }

    void on_sprite_update(entt::registry &registry, entt::entity entity);
};
