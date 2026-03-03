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

   explicit constexpr Timer(Duration_t const& duration, Callback_t&& callback) noexcept
       : duration_{ duration }
       , callback_{ std::move(callback) }
   {
   }

   constexpr Timer() noexcept
       : Timer{ Duration_t{ 0 }, []() { } }
   {
   }

   constexpr auto SetTime(Duration_t const& dur) noexcept { duration_ = dur; }
   constexpr auto SetCallback(Callback_t&& callback) { callback_ = std::move(callback); }

   auto Tick() noexcept -> bool
   {
      auto const now = Clock_t::now();
      auto const elapsed = std::chrono::duration_cast<Duration_t>(now - lastTime_);

      if (elapsed < duration_)
      {
         return false;
      }

      lastTime_ = now;
      if (callback_)
      {
         callback_();
      }
      return true;
   }

   void Reset() noexcept
   {
      // Logger::Debug("Timer::Reset()");
      lastTime_ = Clock_t::now();
   }

   [[nodiscard]] static auto Seconds(std::size_t const N) noexcept -> Duration_t { return N * Duration_t{ 1000 }; }
   [[nodiscard]] static auto Milliseconds(std::size_t const N) noexcept -> Duration_t { return Duration_t{ N }; }

private:
   Duration_t duration_;
   Callback_t callback_;
   TimePoint_t lastTime_{ Clock_t::now() };
};

} // namespace TinyEngine
