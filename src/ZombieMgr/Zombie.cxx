module;

export module ZombieMgr.Zombie;

import Math;

export namespace TinyEngine
{

/*
       (x,y)
(0,  0)     (10,  0)

(0, 10)     (10, 10)
*/

struct [[nodiscard]] Zombie
{
   [[nodiscard]] explicit constexpr Zombie(
     Vector2Df const& position, Vector2Df const& speed = Vector2Df{ 100.F, 0.F }) noexcept
       : position_{ position }
       , speed_{ speed }
   {
   }

   void Move(float const dt) noexcept
   {
      auto const& realSpeed = speed_ * dt;
      position_ += realSpeed;
   }

   [[nodiscard]] constexpr auto& Position(this auto& self) noexcept { return self.position_; }
   [[nodiscard]] constexpr auto& Speed(this auto& self) noexcept { return self.speed_; }

private:
   Vector2Df position_{};
   Vector2Df speed_{ 100.F, 0.F };
};
} // namespace TinyEngine
