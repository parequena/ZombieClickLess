import Game;
import Renderer;

auto main() -> int
{
   auto const dt{ 1.F / static_cast<float>(TinyEngine::Renderer::FPS) };
   TinyEngine::Game game{ };
   game.play(dt);

   return 0;
}
