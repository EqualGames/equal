#include <equal/core/Application.h>

#include "scenes/DemoScene.h"

int main(int argc, char *args[]) {
    try {
        auto *app = new eq::Application();

        if (app->init()) {
            app->set_scene(new DemoScene);

            return app->run();
        } else {
            eq::Logger::debug("Could not possible to initialize the application\n");
        }

        return 0;
    } catch (std::exception &error) {
        eq::StackTrace(error);
        return 1;
    }
}
