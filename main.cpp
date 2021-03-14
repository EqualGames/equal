#include "core/Application.h"
#include "scenes/DemoScene.h"

int main(int argc, char *args[]) {
    auto *app = new Application();

    if (app->init()) {
        app->set_scene(new DemoScene());

        return app->run();
    }

    return 0;
}
