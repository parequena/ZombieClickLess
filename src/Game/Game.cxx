module;

#include <cstdint>
#include <memory>

export module Game;

import Renderer;
import Input;
import ZombieMgr;
import Helpers;

export namespace TinyEngine {
struct Game {
  explicit Game()
      : renderer_{std::make_unique<Renderer>(defaultWidth, defaultHeight)} {}

  void play() noexcept {
    Logger::Info("Starting game!");
    timer_ = std::make_unique<Timer>(Timer::ThousandMilliseconds(),
                                     []() { Logger::Info("Timer fired!"); });

    while (true) {
      const InputState input = renderer_->Update();

      if (input.closeRequested || input.keyEscape) {
        break;
      }

      timer_->Tick();
      renderer_->Draw();
    }

    Logger::Info("Closing game!");
    renderer_->Close();
  }

private:
  std::uint16_t defaultWidth{640};
  std::uint16_t defaultHeight{480};
  ZombieMgr zombieMgr_{};
  std::unique_ptr<Renderer> renderer_{};
  std::unique_ptr<Timer> timer_{};
};
} // namespace TinyEngine
