#include "Application.h"

bool Application::init() {

  sf::VideoMode mode;
  uint32_t flags;

  if (fullscreen) {
    mode = sf::VideoMode::getDesktopMode();
    flags = sf::Style::None;
  } else {
    mode = sf::VideoMode{800, 600};
    flags = sf::Style::Default;
  }

  window = make_ref<sf::RenderWindow>(mode, title, flags);
  window->setFramerateLimit((uint32_t)limit_fps);
  window->setVerticalSyncEnabled(vsync);
  window->setKeyRepeatEnabled(true);

  adjust_scale({mode.width, mode.height});

  ImGui::SFML::Init(*window.get());

  return true;
}

void Application::adjust_scale(const SizeFloat &screen_size) {
  SizeFloat left_top = ((screen_size - viewport_size) / 2.0f);

  sf::View view;

  view.setSize(viewport_size.to_sfml());
  view.setCenter((viewport_size / 2).to_sfml());
  view.setViewport(
      {{left_top.w / screen_size.w, left_top.h / screen_size.h},
       {viewport_size.w / screen_size.w, viewport_size.h / screen_size.h}});

  window->setView(view);
}

void Application::set_scene(Scene *p_scene) {
  scene = p_scene;
  scene->app = (Ref<Application>)this;
  scene->init();
}

int Application::run() {
  if (scene == nullptr) {
    EQ_THROW("Invalid scene\n");
  }

  sf::Clock clock;
  sf::Event event{};

  while (window->isOpen()) {
    sf::Time elapsed = clock.restart();

    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
      }

      if (event.type == sf::Event::Resized) {
        adjust_scale({event.size.width, event.size.height});
      }

#ifdef DEV_TOOLS
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
          window->close();
        }

        if (event.key.code == sf::Keyboard::F1) {
          tools = !tools;
        }
      }
#endif

      scene->event(event);
      ImGui::SFML::ProcessEvent(event);
    }

    window->clear(sf::Color::Black);

    scene->update(elapsed.asSeconds());
    ImGui::SFML::Update(*window, elapsed);

#ifdef DEV_TOOLS
    {
      // Calculate FPS
      {
        float fps =
            std::min(limit_fps, std::max(0.0f, 1.f / elapsed.asSeconds()));

        if (frames.size() > 100) {
          for (size_t i = 1; i < frames.size(); i++) {
            frames[i - 1] = frames[i];
          }

          frames[frames.size() - 1] = fps;
        } else {
          frames.push_back(fps);
        }

        if (fps < min_fps && frames.size() > 90) {
          min_fps = fps;
        }

        if (fps > max_fps && fps <= limit_fps) {
          max_fps = fps;
        }

        avg_fps += (fps - avg_fps) / frames.size();
      }

      if (tools) {
        ImGui::Begin("Developer Tools", &tools);
        ImGui::SetWindowSize({300, 300}, ImGuiCond_FirstUseEver);
        ImGui::SetWindowPos({0, 0}, ImGuiCond_FirstUseEver);
        ImGui::Text("Loading: %s", scene->loading ? "true" : "false");

        ImGui::BeginGroup();
        ImGui::Columns(3);

        ImGui::Text("FPS: %.2f", avg_fps);

        ImGui::NextColumn();
        ImGui::Text("Min: %.2f", min_fps);

        ImGui::NextColumn();
        ImGui::Text("Max: %.2f", max_fps);

        ImGui::Columns();
        ImGui::EndGroup();

        ImGui::PlotHistogram("", &frames[0], frames.size(), 0, nullptr, 0.0f,
                             limit_fps, {300, limit_fps});
        ImGui::End();
      }
    }
#endif

    scene->draw(this->window);
    ImGui::SFML::Render(*window);

    window->display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
