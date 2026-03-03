module;

#include <cstdint>
#include <vector>
#include <random>

export module ZombieMgr;

import Helpers;

export namespace TinyEngine
{

/*
       (x,y)
(0,  0)     (10,  0)

(0, 10)     (10, 10)
*/
template <class T>
struct Position
{
   T x{};
   T y{};
};

enum class Direction
{
   Left,
   Right,
};

struct ZombieMgr
{
   using ZombiePos = Position<std::uint16_t>;
   inline constinit static std::size_t reserveZombies{ 100 };

   constexpr auto SpawnZombie() -> void
   {
      auto getRandomNumber = [](int const max)
      {
         std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_int_distribution<> distrib(0, max);
         return distrib(gen);
      };

      int const x = getRandomNumber(width_);
      int const y = getRandomNumber(height_);
      Direction const dir = getRandomNumber(1) == 0 ? Direction::Left : Direction::Right;

      SpawnZombie(x, y, dir);
   }

   constexpr auto SpawnZombie(int const x, int const y, Direction const dir) -> void
   {
      Logger::Debug("Spawning zombie!");
      zombiePositions_.emplace_back(x, y);
      zombieDirections_.emplace_back(dir);
      ++lastZombie_;
   }

   constexpr auto ForEach(auto&& func) const noexcept
   {
      for (std::size_t i{}; i < lastZombie_; ++i)
      {
         func(zombiePositions_[i], zombieDirections_[i]);
      }
   }

   constexpr auto Move() noexcept
   {
      constexpr int boundaries{ 30 }; // Placeholder!
      for (std::size_t i = 0; i < lastZombie_; ++i)
      {
         auto& dir = zombieDirections_[i];
         auto& pos = zombiePositions_[i];
         // Logger::Debug("[{},{}]", pos.x, pos.y);

         auto const step = dir == Direction::Left ? -1 : 1;
         auto newX = pos.x += step;

         if (newX <= boundaries)
         {
            dir = Direction::Right;
            newX = pos.x + 1;
         }
         else if (newX >= width_ - boundaries)
         {
            dir = Direction::Left;
            newX = pos.x - 1;
         }

         pos.x = newX;
      }
   }

   constexpr auto SetBoundaries(std::uint16_t const width, std::uint16_t const height) noexcept
   {
      width_ = width;
      height_ = height;
   }

private:
   std::uint16_t width_{};
   std::uint16_t height_{};
   std::vector<ZombiePos> zombiePositions_{};
   std::vector<Direction> zombieDirections_{};
   std::size_t lastZombie_{};
};
} // namespace TinyEngine
