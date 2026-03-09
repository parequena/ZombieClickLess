module;

#include <cstdint>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
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

   constexpr auto SpawnZombie() -> void
   {
      auto getRandomNumber = [](int const min, int const max)
      {
         std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_int_distribution<> distrib(min, max);
         return distrib(gen);
      };

      int const x = getRandomNumber(left_, right_);
      int const y = getRandomNumber(top_, bot_);
      Direction const dir = getRandomNumber(0, 1) == 0 ? Direction::Left : Direction::Right;

      SpawnZombie(x, y, dir);
   }

   constexpr auto SpawnZombie(int const x, int const y, Direction const dir) -> void
   {
      // Logger::Debug("Spawning zombie!");
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

         if (newX <= left_ + boundaries)
         {
            dir = Direction::Right;
            newX = pos.x + 1;
         }
         else if (newX >= right_ - boundaries)
         {
            dir = Direction::Left;
            newX = pos.x - 1;
         }

         pos.x = newX;
      }
   }

   constexpr auto SetBoundaries(std::uint16_t top, std::uint16_t bot, std::uint16_t left, std::uint16_t right) noexcept
     -> void
   {
      top_ = top;
      bot_ = bot;
      left_ = left;
      right_ = right;
   }

   constexpr auto ZombieCount() const noexcept -> std::size_t { return lastZombie_; }

private:
   std::uint16_t top_{};
   std::uint16_t bot_{};
   std::uint16_t left_{};
   std::uint16_t right_{};
   std::vector<ZombiePos> zombiePositions_{};
   std::vector<Direction> zombieDirections_{};
   std::size_t lastZombie_{};
};
} // namespace TinyEngine
