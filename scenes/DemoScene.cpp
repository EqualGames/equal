#include "DemoScene.h"


void DemoScene::init(SDL_Renderer *renderer) {
    {
        this->camera = this->registry.create();

        auto &cam = this->registry.emplace<Camera>(this->camera);
        cam.position = Position{0, 0};
        cam.size = app->window_size;
    }

    {
        this->player = this->registry.create();

        auto &input = this->registry.emplace<Input>(player);

        if (SDL_NumJoysticks() > 0) {
            if (SDL_IsGameController(input.number)) {
                input.controller = SDL_GameControllerOpen(input.number);
                input.joystick = SDL_GameControllerGetJoystick(input.controller);
                input.joystick_instance_id = SDL_JoystickInstanceID(input.joystick);
            } else {
                input.joystick = SDL_JoystickOpen(input.number);
                input.joystick_instance_id = SDL_JoystickInstanceID(input.joystick);
                input.controller = SDL_GameControllerFromInstanceID(input.joystick_instance_id);
            }
        }

        auto &transform = this->registry.emplace<Transform>(this->player);
        transform.position = Position{0, 0};
        transform.size = Size{48, 60};

        auto &sprite = this->registry.emplace<Sprite>(this->player);
        sprite.color = Color{255, 255, 255};

        sprite.textures.emplace_back(
                std::make_tuple(load_texture(renderer, "assets/hero.png"), Position{0, 0}, Size{48, 60}));
    }

    {
        this->map = this->registry.create();
        auto &map_comp = this->registry.emplace<Map>(this->map);

        const char *source = "assets/map/demo.tmx";
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(source);

        if (!result) {
            printf(
                    "XML [%s] parsed with errors, offset %i (error at [...%s])\n%s\n\n",
                    source, result.offset,
                    (source + result.offset),
                    result.description()
            );

            throw std::exception("Error on read the map file");
        }

        pugi::xml_node tile_map = doc.child("map");

        for (pugi::xml_node tileset = tile_map.child("tileset"); tileset; tileset = tileset.next_sibling("tileset")) {

            uint32_t firstgid = tileset.attribute("firstgid").as_uint();
            std::string texture =
                    split_pair(tileset.attribute("source").as_string(), '.')
                            .first;

            printf("loading tileset %i %s\n", firstgid, texture.c_str());

            map_comp.textures.emplace(
                    std::make_pair(firstgid, load_texture(renderer, "assets/map/" + texture + ".png")));
        }

        for (pugi::xml_node floor = tile_map.child("group"); floor; floor = floor.next_sibling("group")) {
            int number = strtol(split_pair(floor.attribute("name").as_string(), ' ').second.c_str(), nullptr, 10);

            auto map_floor = new Floor{};
            map_floor->number = number;

            for (pugi::xml_node layer = floor.child("layer"); layer; layer = layer.next_sibling("layer")) {

                auto map_layer = new Layer{};

                for (pugi::xml_node data = layer.child("data"); data; data = data.next_sibling("data")) {

                    for (pugi::xml_node chunk = data.child("chunk"); chunk; chunk = chunk.next_sibling("chunk")) {

                        int cx = chunk.attribute("x").as_int();
                        int cy = chunk.attribute("y").as_int();
                        int cw = chunk.attribute("width").as_int();
                        int ch = chunk.attribute("height").as_int();

                        int tn = 0;
                        for (pugi::xml_node tile = chunk.child("tile"); tile;
                             tile = tile.next_sibling("tile")) {
                            auto map_tile = new Tile{};

                            map_tile->texture_id =
                                    static_cast<uint32_t>(tile.attribute("gid").as_uint());

                            map_tile->position.x = cx + (tn % cw) * 32;
                            map_tile->position.y = cy + (tn / ch) * 32;

                            map_layer->tiles.emplace_back(map_tile);
                            tn = tn + 1;
                        }
                    }
                }

                map_floor->layers.emplace_back(map_layer);
            }

            map_comp.floors.emplace_back(map_floor);
        }

    }
}

void DemoScene::update(SDL_Renderer *renderer, SDL_Event &event) {
    input_system(this->registry, event);
    camera_system(this->registry, this->camera, this->player);
    renderer_system(this->registry, renderer, this->camera);
}
