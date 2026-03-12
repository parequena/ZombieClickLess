module;

#include <cstdint>
#include <memory>
#include <array>
#include <vector>

export module Game;

import Renderer;
import Input;
import ZombieMgr;
import Helpers;
import Button;
import Math;

export namespace TinyEngine
{
struct Game
{
   static constexpr std::size_t WIDTH{ 640 };
   static constexpr std::size_t HEIGHT{ 480 };
   explicit Game()
       : renderer_{ std::make_unique<Renderer>(WIDTH, HEIGHT) }
       , closeButton_{ Box<std::uint16_t>{ Vector2Du16{ WIDTH - 64, 0 }, 64, 64 }, [&]() { keepPlaying_ = false; } }
   {
   }

   void play(float const dt) noexcept
   {
      static constexpr std::size_t nManagers{ 5 };

      managers_.reserve(nManagers);
      for (std::uint16_t i = 0; i < nManagers; ++i)
      {
         std::uint16_t const spacing = (HEIGHT - 64) / nManagers;
         std::uint16_t const top = 64 + i * spacing;
         std::uint16_t const bot = (i == nManagers - 1) ? HEIGHT : top + spacing;
         managers_.emplace_back(
           Box<std::uint16_t>{ Vector2Du16{ 0, top }, WIDTH, static_cast<std::uint16_t>(bot - top) });
      }

      std::array<Timer, nManagers> spawners{ };
      std::array<Timer, nManagers> movements{ };

      for (std::size_t i = 0; i < nManagers; ++i)
      {
         spawners[i].SetTime(Timer::Seconds(5 + i));
         spawners[i].SetCallback([&, i]() { managers_[i].SpawnZombie(); });

         movements[i].SetTime(Timer::Milliseconds(100 + i * 10));
         movements[i].SetCallback([&, i]() { managers_[i].Move(dt); });
      }

      Logger::Info("Starting game!");

      constexpr auto TickAllTimers = [](auto& timers)
      {
         for (auto& timer : timers)
         {
            if (timer.Tick())
            {
               timer.Reset();
            }
         }
      };

      while (true)
      {
         const InputState input = renderer_->Update();

         if (input.closeRequested || input.keyEscape)
         {
            break;
         }

         closeButton_.Update(input);
         if (!keepPlaying_)
         {
            break;
         }

         TickAllTimers(spawners);
         TickAllTimers(movements);

         Draw();
      }

      Logger::Info("Closing game!");
      renderer_->Close();
   }

   void Draw()
   {
      renderer_->Clear();

      renderer_->DrawButton(closeButton_.GetBox());

      for (auto const& manager : managers_)
      {
         renderer_->DrawManager(manager.GetBox());
         manager.ForEach(
           [&](Vector2Df const& pos, Direction const dir) { renderer_->DrawZombie(pos, dir == Direction::Right); });
      }
      renderer_->Display();
   }

private:
   std::unique_ptr<Renderer> renderer_{ };
   std::vector<ZombieMgr> managers_{ };
   Button closeButton_;
   bool keepPlaying_{ true };
};
} // namespace TinyEngine
