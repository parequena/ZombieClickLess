module;

#include <chrono>
#include <functional>

export module Helpers:Timer;

import :Logger;

export namespace TinyEngine
{

struct [[nodiscard]] Timer
{
   using Clock_t = std::chrono::high_resolution_clock;
   using TimePoint_t = Clock_t::time_point;
   using Duration_t = std::chrono::milliseconds;
   using Callback_t = std::function<void()>;

   explicit constexpr Timer(Duration_t const& duration, Callback_t&& onElapsed) noexcept
       : duration_{ duration }
       , onElapsed_{ std::move(onElapsed) }
   {
   }

   auto Tick() noexcept -> bool
   {
      auto const now = Clock_t::now();
      auto const elapsed = std::chrono::duration_cast<Duration_t>(now - lastTime_);

      if (elapsed < duration_)
      {
         return false;
      }

      lastTime_ = now;
      if (onElapsed_)
      {
         onElapsed_();
      }
      return true;
   }

   void Reset() noexcept
   {
      Logger::Debug("Timer::Reset()");
      lastTime_ = Clock_t::now();
   }

   [[nodiscard]] static auto OneSecond() noexcept -> Duration_t { return Duration_t{ 1000 }; }

   template <std::uint8_t N>
   [[nodiscard]] static auto XSeconds() noexcept -> Duration_t
   {
      return N * OneSecond();
   }

private:
   Duration_t duration_;
   Callback_t onElapsed_;
   TimePoint_t lastTime_{ Clock_t::now() };
};

} // namespace TinyEngine
