module;

#include <cstdint>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
export module ZombieMgr;

import Helpers;
import Math;

export namespace TinyEngine
{

/*
       (x,y)
(0,  0)     (10,  0)

(0, 10)     (10, 10)
*/
enum class Direction
{
   Left,
   Right,
};

struct ZombieMgr
{
   explicit ZombieMgr(Box<std::uint16_t> const& boundaries)
       : boundaries_{ boundaries }
   {
   }

   constexpr auto SpawnZombie() -> void
   {
      auto getRandomNumber = [](int const min, int const max)
      {
         std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_int_distribution<> distrib(min, max);
         return distrib(gen);
      };

      int const x = getRandomNumber(boundaries_.Left(), boundaries_.Right());
      int const y = getRandomNumber(boundaries_.Top(), boundaries_.Bot());
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
      for (std::size_t i{ }; i < lastZombie_; ++i)
      {
         func(zombiePositions_[i], zombieDirections_[i]);
      }
   }

   constexpr auto Move(float const dt) noexcept
   {
      auto const vel{ 100.0F * dt };
      constexpr int boundaries{ 30 }; // Placeholder!

      for (std::size_t i = 0; i < lastZombie_; ++i)
      {
         auto& dir = zombieDirections_[i];
         auto& pos = zombiePositions_[i];

         auto const step = dir == Direction::Left ? -vel : vel;
         auto newX = pos.X() + step;

         if (newX <= boundaries_.Left() + boundaries)
         {
            dir = Direction::Right;
            newX = pos.X() + 1;
         }
         else if (newX >= boundaries_.Right() - boundaries)
         {
            dir = Direction::Left;
            newX = pos.X() - 1;
         }

         pos.X(newX);
      }
   }

   constexpr auto ZombieCount() const noexcept -> std::size_t { return lastZombie_; }

private:
   Box<std::uint16_t> boundaries_{ };
   std::vector<Vector2Df> zombiePositions_{ };
   std::vector<Direction> zombieDirections_{ };
   std::size_t lastZombie_{ };
};
} // namespace TinyEngine
