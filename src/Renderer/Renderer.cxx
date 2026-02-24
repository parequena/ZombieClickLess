module;

#include <SFML/Graphics.hpp>
#include <array>

export module Renderer;

import Input;

export namespace TinyEngine {
struct Renderer {
  explicit Renderer(std::uint16_t const width, std::uint16_t height)
      : window_{sf::VideoMode({width, height}), "ZombieClickless",
                sf::Style::Close} {
    window_.setFramerateLimit(60);

    // auto const &desktop = sf::VideoMode::getDesktopMode();
    // sf::Vector2i const bottomRight{int(desktop.size.x) - width,
    //                                int(desktop.size.y) - (height + 150)};
    // window_.setPosition(bottomRight);

    // Load textures
    textures_[0] = sf::Texture{"assets/menus/buttons/button_x.png"};
  }

  auto Update() -> InputState {
    InputState state{};

    while (const std::optional event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        state.closeRequested = true;
      }

      if (const auto *key = event->getIf<sf::Event::KeyPressed>()) {
        using Key = sf::Keyboard::Key;
        if (key->code == Key::Escape)
          state.keyEscape = true;
        if (key->code == Key::Space)
          state.keySpace = true;
        if (key->code == Key::W)
          state.keyW = true;
        if (key->code == Key::A)
          state.keyA = true;
        if (key->code == Key::S)
          state.keyS = true;
        if (key->code == Key::D)
          state.keyD = true;
      }

      if (const auto *click = event->getIf<sf::Event::MouseButtonPressed>()) {
        using Btn = sf::Mouse::Button;
        if (click->button == Btn::Left)
          state.mouseLeft = true;
        if (click->button == Btn::Right)
          state.mouseRight = true;
        state.mouseX = click->position.x;
        state.mouseY = click->position.y;
      }
    }

    return state;
  }

  void Draw() {
    sf::Sprite shape{textures_[0]};

    window_.clear(sf::Color::Transparent);
    window_.draw(shape);
    window_.display();
  }

  constexpr auto MustClose() const noexcept -> bool { return mustClose_; }
  constexpr void Close() noexcept { window_.close(); }

private:
  std::array<sf::Texture, 1> textures_{};
  sf::RenderWindow window_{};
  bool mustClose_{false};
};
} // namespace TinyEngine
