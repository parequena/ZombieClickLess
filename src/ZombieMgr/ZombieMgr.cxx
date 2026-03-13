module;

#include <cstdint>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
export module ZombieMgr;

import Helpers;
import Math;
import ZombieMgr.Zombie;

export namespace TinyEngine
{

/*
       (x,y)
(0,  0)     (10,  0)

(0, 10)     (10, 10)
*/
struct ZombieMgr
{
   explicit ZombieMgr(Box<std::uint16_t> const& boundaries)
       : boundaries_{ boundaries }
   {
   }

   template <Numeric T>
   constexpr auto GetRandomNumber(T const min, T const max) noexcept -> T
   {
      if constexpr (is_float<T>)
      {
         std::uniform_real_distribution<T> distribution(min, max);
         return distribution(randomGenerator_);
      }

      std::uniform_int_distribution<T> distribution(min, max);
      return distribution(randomGenerator_);
   }

   constexpr auto SpawnZombie() -> void
   {
      float const x = GetRandomNumber(boundaries_.Left(), boundaries_.Right());
      float const y = GetRandomNumber(boundaries_.Top(), boundaries_.Bot());

      SpawnZombie(Vector2Df(x, y));
   }

   constexpr auto SpawnZombie(Vector2Df const& pos) -> void
   {
      zombies_.emplace_back(pos);
      ++lastZombie_;
   }

   constexpr auto ForEach(auto&& func) const noexcept
   {
      for (auto const& zombie : zombies_)
      {
         func(zombie);
      }
   }

   constexpr auto Move(float const dt) noexcept
   {
      auto const bX = boundaries_.X();
      auto const bW = boundaries_.W();

      for (auto& zombie : zombies_)
      {
         auto& speed = zombie.Speed();
         auto const& nextPos = zombie.Position() + speed;
         if (nextPos.X() <= bX || nextPos.X() >= bW)
         {
            [[maybe_unused]] auto a = 1;
            speed *= -1.f;
         }
         zombie.Move(dt);
      }
   }

   constexpr auto ZombieCount() const noexcept -> std::size_t { return lastZombie_; }
   constexpr auto GetBox() const noexcept -> Box<std::uint16_t> { return boundaries_; }

private:
   Box<std::uint16_t> boundaries_{};
   std::vector<Zombie> zombies_{};
   std::ranlux24_base randomGenerator_{ std::random_device{}() };
   std::size_t lastZombie_{};
};
} // namespace TinyEngine
