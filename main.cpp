#include "core/Application.h"
#include "core/Exception.h"
#include "scenes/DemoScene.h"
#include <iostream>

int main(int argc, char *args[]) {
  try {
    auto *app = new Application{};

    if (app->init()) {
      app->set_scene(new DemoScene{});

      return app->run();
    } else {
      EQ_LOG("Could not possible to initialize the application\n");
    }

    return 0;
  } catch (std::exception &error) {
    StackTrace(error);
    return 1;
  }
}
