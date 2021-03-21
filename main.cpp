#include "core/Application.h"
#include "scenes/DemoScene.h"
#include <iostream>

int main(int argc, char *args[]) {
  try {
    auto *app = new Application{{800, 600}};

    if (app->init()) {
      app->set_scene(new DemoScene{});

      return app->run();
    }

    return 0;
  } catch (std::exception &error) {
    std::cout << "Error: " << error.what() << std::endl;
    return 1;
  }
}
