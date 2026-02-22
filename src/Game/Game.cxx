module;

#include <cstdint>
#include <memory>

export module Game;

import Renderer;
import Input;

export namespace TinyEngine {
struct Game {
  explicit Game()
      : renderer_{std::make_unique<Renderer>(defaultWidth, defaultHeight)} {}

  void play() noexcept {
    while (true) {
      const InputState input = renderer_->Update();

      if (input.closeRequested || input.keyEscape) {
        break;
      }

      renderer_->Draw();
    }

    renderer_->Close();
  }

private:
  std::uint16_t defaultWidth{640};
  std::uint16_t defaultHeight{480};
  std::unique_ptr<Renderer> renderer_{};
};
} // namespace TinyEngine
