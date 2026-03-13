module;

#include <SFML/Graphics.hpp>
#include <array>

export module Renderer;

import Input;
import Math;
import ZombieMgr.Zombie;

static constexpr auto g_FontPath{ "assets/fonts/tuffy.ttf" };
static constexpr auto g_ButtonPath{ "assets/menus/buttons/button_x.png" };
static constexpr auto g_ZombiePath{ "assets/Zombie/01-Idle/__Zombie01_Idle_000.png" };
static constexpr auto g_ManagerPath{ "assets/menus/character.png" };

export namespace TinyEngine
{
struct Renderer
{
   enum class Texture : std::uint8_t
   {
      Button,
      Zombie,
      Manager,
      Count
   };

   static constexpr std::uint16_t FPS{ 60 };
   explicit Renderer(std::uint16_t const width, std::uint16_t height)
       : window_{ sf::VideoMode({ width, height }), "ZombieClickless", sf::Style::Close }
   {
      window_.setFramerateLimit(FPS);

      // auto const &desktop = sf::VideoMode::getDesktopMode();
      // sf::Vector2i const bottomRight{int(desktop.size.x) - width,
      //                                int(desktop.size.y) - (height + 150)};
      // window_.setPosition(bottomRight);

      // Load textures
      textures_[std::size_t(Texture::Button)] = sf::Texture{ g_ButtonPath, false, sf::IntRect({ 0, 0 }, { 24, 24 }) };
      textures_[std::size_t(Texture::Zombie)] = sf::Texture{ g_ZombiePath };
      textures_[std::size_t(Texture::Manager)] = sf::Texture{ g_ManagerPath };
   }

   auto Update() -> InputState
   {
      InputState state{};
      while (const std::optional event = window_.pollEvent())
      {
         if (event->is<sf::Event::Closed>())
         {
            state.closeRequested = true;
         }

         if (const auto* key = event->getIf<sf::Event::KeyPressed>())
         {
            using Key = sf::Keyboard::Key;
            state.keyEscape = key->code == Key::Escape;
            state.keySpace = key->code == Key::Space;
            state.keyW = key->code == Key::W;
            state.keyA = key->code == Key::A;
            state.keyS = key->code == Key::S;
            state.keyD = key->code == Key::D;
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

   constexpr auto DrawZombie(Zombie const& zombie)
   {
      auto const x = zombie.Position().X();
      auto const y = zombie.Position().Y();

      sf::Sprite sp{ textures_[std::size_t(Texture::Zombie)] };
      auto const textureSize = textures_[std::size_t(Texture::Zombie)].getSize();
      sp.setOrigin({ float(textureSize.x) / 2.f, float(textureSize.y) / 2.f });

      float const sx = (zombie.Speed().X() >= 0.0f) ? 0.1f : -0.1f;
      sp.setScale({ sx, 0.1f });
      sp.setPosition({ x, y });
      window_.draw(sp);
   }

   constexpr auto DrawText(std::string_view const str, Vector2Df const& position)
   {
      auto const x = position.X();
      auto const y = position.Y();

      sf::Text text{ font_ };
      text.setString(str.data());
      text.setPosition({ x, y });
      window_.draw(text);
   }

   constexpr auto DrawButton(Box<std::uint16_t> const& box) { DrawBox(box, Texture::Button); }
   constexpr auto DrawManager(Box<std::uint16_t> const& box) { DrawBox(box, Texture::Manager, { 255, 255, 255, 128 }); }

   constexpr void Close() noexcept { window_.close(); }

private:
   std::array<sf::Texture, std::size_t(Texture::Count)> textures_{};
   sf::RenderWindow window_{};
   sf::Font font_{ g_FontPath };

   constexpr auto DrawBox(
     Box<std::uint16_t> const& box, Texture const textureIdx, sf::Color const& color = { 255, 255, 255, 255 }) -> void
   {
      sf::Sprite sprite{ textures_[std::size_t(textureIdx)] };
      sprite.setPosition({ float(box.X()), float(box.Y()) });
      auto const texSize = textures_[std::size_t(textureIdx)].getSize();
      sprite.setScale({ float(box.W()) / float(texSize.x), float(box.H()) / float(texSize.y) });
      sprite.setColor(color);
      window_.draw(sprite);
   }
};
} // namespace TinyEngine
