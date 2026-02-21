#include <print>

import Renderer;

auto main() -> int {
  std::println("Hello!");

  TinyEngine::Renderer renderer{};
  renderer.Do();

  return 0;
}
