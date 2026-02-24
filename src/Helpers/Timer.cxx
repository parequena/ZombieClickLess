module;

#include <chrono>
#include <functional>

export module Helpers:Timer;

export namespace TinyEngine {

struct Timer {
  using Clock_t = std::chrono::high_resolution_clock;
  using TimePoint_t = Clock_t::time_point;
  using Duration_t = std::chrono::milliseconds;
  using Callback_t = std::function<void()>;

  explicit constexpr Timer(Duration_t const &duration,
                           Callback_t &&onElapsed) noexcept
      : duration_{duration}, onElapsed_{std::move(onElapsed)} {}

  auto Tick() noexcept -> bool {
    auto const now = Clock_t::now();
    auto const elapsed =
        std::chrono::duration_cast<Duration_t>(now - lastTime_);

    if (elapsed < duration_) {
      return false;
    }

    lastTime_ = now;
    if (onElapsed_) {
      onElapsed_();
    }
    return true;
  }

  void Reset() noexcept { lastTime_ = Clock_t::now(); }
  void SetDuration(Duration_t duration) noexcept { duration_ = duration; }

  [[nodiscard]] static auto ThousandMilliseconds() noexcept -> Duration_t {
    return Duration_t{1000};
  }

private:
  Duration_t duration_;
  Callback_t onElapsed_;
  TimePoint_t lastTime_{Clock_t::now()};
};

} // namespace TinyEngine
