module;

#include <cstdint>
#include <memory>
#include <array>

export module Game;

import Renderer;
import Input;
import ZombieMgr;
import Helpers;

export namespace TinyEngine
{
struct Game
{
   explicit Game()
       : renderer_{ std::make_unique<Renderer>(defaultWidth_, defaultHeight_) }
   {
   }

   void play() noexcept
   {
      static constexpr std::size_t nManagers{ 2 };
      std::array<ZombieMgr, nManagers> managers{};
      for (auto& man : managers)
      {
         man.SetBoundaries(defaultWidth_, defaultHeight_);
      }

      std::array<Timer, nManagers> spawners{};
      std::array<Timer, nManagers> movements{};

      for (std::size_t i = 0; i < nManagers; ++i)
      {
         spawners[i].SetTime(Timer::Seconds(10));
         spawners[i].SetCallback([&managers, i]() { managers[i].SpawnZombie(); });

         movements[i].SetTime(Timer::Milliseconds(10));
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

         TickAllTimers(spawners);
         TickAllTimers(movements);

         renderer_->Clear();

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
};
} // namespace TinyEngine
