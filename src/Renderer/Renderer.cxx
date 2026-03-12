module;

#include <SFML/Graphics.hpp>
#include <array>

export module Renderer;

import Input;
import Math;

export namespace TinyEngine
{
struct Renderer
{
   explicit Renderer(std::uint16_t const width, std::uint16_t height)
       : window_{ sf::VideoMode({ width, height }), "ZombieClickless", sf::Style::Close }
   {
      window_.setFramerateLimit(60);

      // auto const &desktop = sf::VideoMode::getDesktopMode();
      // sf::Vector2i const bottomRight{int(desktop.size.x) - width,
      //                                int(desktop.size.y) - (height + 150)};
      // window_.setPosition(bottomRight);

      // Load textures
      textures_[0] = sf::Texture{ "assets/menus/buttons/button_x.png", false, sf::IntRect({ 0, 0 }, { 24, 24 }) };
      textures_[1] = sf::Texture{ "assets/Zombie/01-Idle/__Zombie01_Idle_000.png" };
   }

   auto Update() -> InputState
   {
      InputState state{ };

      while (const std::optional event = window_.pollEvent())
      {
         if (event->is<sf::Event::Closed>())
         {
            state.closeRequested = true;
         }

         if (const auto* key = event->getIf<sf::Event::KeyPressed>())
         {
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

         if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
         {
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

   constexpr auto Clear() noexcept -> void { window_.clear(sf::Color::Transparent); }
   constexpr auto Display() noexcept -> void { window_.display(); }

   constexpr auto DrawZombie(Vector2Df const& position, bool const headingRight)
   {
      auto const x = position.X();
      auto const y = position.Y();

      sf::Sprite zombie{ textures_[1] };
      auto const textureSize = textures_[1].getSize();
      zombie.setOrigin({ float(textureSize.x) / 2.f, float(textureSize.y) / 2.f });

      float const sx = headingRight ? 0.1f : -0.1f;
      zombie.setScale({ sx, 0.1f });
      zombie.setPosition({ x, y });
      window_.draw(zombie);
   }

   constexpr auto DrawButton(Vector2Du16 const& position, int const w, int const h)
   {
      sf::Sprite btn{ textures_[0] };
      btn.setPosition({ float(position.X()), float(position.Y()) });
      auto const texSize = textures_[0].getSize();
      btn.setScale({ float(w) / float(texSize.x), float(h) / float(texSize.y) });
      window_.draw(btn);
   }

   constexpr void Close() noexcept { window_.close(); }

private:
   std::array<sf::Texture, 2> textures_{ };
   sf::RenderWindow window_{ };
};
} // namespace TinyEngine
