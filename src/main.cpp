#include <print>

import Game;

auto main() -> int
{
   std::println("Hello!");

   TinyEngine::Game game{};
   game.play();

   return 0;
}
