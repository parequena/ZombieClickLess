module;

#include <SFML/Graphics.hpp>

export module Renderer;

export namespace TinyEngine {
struct Renderer {
  explicit Renderer() : window_{sf::VideoMode({200, 200}), "SFML works!"} {}

  void Do() {
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window_.isOpen()) {
      while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>())
          window_.close();
      }

      window_.clear();
      window_.draw(shape);
      window_.display();
    }
  }

private:
  sf::RenderWindow window_{};
};
} // namespace TinyEngine
