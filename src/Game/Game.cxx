module;

#include <cstdint>
#include <memory>
#include <array>

export module Game;

import Renderer;
import Input;
import ZombieMgr;
import Helpers;
import Button;

export namespace TinyEngine
{
struct Game
{
   explicit Game()
       : renderer_{ std::make_unique<Renderer>(defaultWidth_, defaultHeight_) }
       , closeButton_{ 10, 10, 64, 64, [&]() { keepPlaying_ = false; } }
   {
   }

   void play() noexcept
   {
      static constexpr std::size_t nManagers{ 5 };
      std::array<ZombieMgr, nManagers> managers{};
      for (std::uint16_t i = 0; i < nManagers; ++i)
      {
         std::uint16_t const spacing = (defaultHeight_ - 5) / nManagers;
         std::uint16_t const top = 5 + i * spacing;
         std::uint16_t const bot = (i == nManagers - 1) ? defaultHeight_ : top + spacing;
         managers[i].SetBoundaries(/* top */ top, /* bot */ bot, /* left*/ 0, /* right */ defaultWidth_);
      }

      std::array<Timer, nManagers> spawners{};
      std::array<Timer, nManagers> movements{};

      for (std::size_t i = 0; i < nManagers; ++i)
      {
         spawners[i].SetTime(Timer::Seconds(5));
         spawners[i].SetCallback([&managers, i]() { managers[i].SpawnZombie(); });

         movements[i].SetTime(Timer::Milliseconds(50));
         movements[i].SetCallback([&managers, i]() { managers[i].Move(); });
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

      managers[0].SpawnZombie(55, 100, Direction::Right);

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

         renderer_->Clear();

         auto const [x, y, w, h] = closeButton_.GetPositions();
         renderer_->DrawButton(x, y, w, h);

         for (auto const& manager : managers)
         {
            manager.ForEach([&](ZombieMgr::ZombiePos const& pos, Direction const dir)
              { renderer_->DrawZombie(pos.x, pos.y, dir == Direction::Right); });
         }
         renderer_->Display();
      }

      Logger::Info("Closing game!");
      renderer_->Close();
   }

private:
   std::uint16_t defaultWidth_{ 640 };
   std::uint16_t defaultHeight_{ 480 };
   std::unique_ptr<Renderer> renderer_{};
   Button closeButton_;
   bool keepPlaying_{ true };
};
} // namespace TinyEngine
