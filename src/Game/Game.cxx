module;

#include <cstdint>
#include <memory>

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
       : renderer_{ std::make_unique<Renderer>(defaultWidth, defaultHeight) }
   {
   }

   void play() noexcept
   {
      Logger::Info("Starting game!");
      timer_ = std::make_unique<Timer>(Timer::Seconds(10), [&]() { zombieMgr_.SpawnZombie(); });
      Timer moveHandler{ Timer::Milliseconds(10), [&]() { zombieMgr_.Move(); } };

      zombieMgr_.SpawnZombie(0, 100, Direction::Right);
      while (true)
      {
         const InputState input = renderer_->Update();

         if (input.closeRequested || input.keyEscape)
         {
            break;
         }

         if (timer_->Tick())
         {
            timer_->Reset();
         }

         if (moveHandler.Tick())
         {
            moveHandler.Reset();
         }

         renderer_->Clear();
         zombieMgr_.ForEach([&](ZombieMgr::ZombiePos const& pos, Direction const dir)
           { renderer_->DrawZombie(pos.x, pos.y, dir == Direction::Right); });
         renderer_->Display();
      }

      Logger::Info("Closing game!");
      renderer_->Close();
   }

private:
   std::uint16_t defaultWidth{ 640 };
   std::uint16_t defaultHeight{ 480 };
   ZombieMgr zombieMgr_{ defaultWidth, defaultHeight };
   std::unique_ptr<Renderer> renderer_{};
   std::unique_ptr<Timer> timer_{};
};
} // namespace TinyEngine
