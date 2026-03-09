module;

#include <cstdint>
#include <functional>
#include <tuple>

export module Button;

import Input;

export namespace TinyEngine
{
struct [[nodiscard]] Button
{
   Button(std::uint16_t const x, std::uint16_t const y, std::uint16_t const w, std::uint16_t const h, auto&& onClick)
       : x_{ x }
       , y_{ y }
       , w_{ w }
       , h_{ h }
       , onClick_{ std::move(onClick) }
   {
   }

   void SetCallback(std::function<void()> const& callback) { onClick_ = callback; }

   void Update(InputState const& input)
   {
      if (!input.mouseLeft)
      {
         return;
      }

      if (input.mouseX >= x_ && input.mouseX <= x_ + w_ && input.mouseY >= y_ && input.mouseY <= y_ + h_)
      {
         onClick_();
      }
   }

   [[nodiscard]] constexpr auto GetPositions() const noexcept { return std::tuple{ x_, y_, w_, h_ }; }

private:
   std::uint16_t x_{};
   std::uint16_t y_{};
   std::uint16_t w_{};
   std::uint16_t h_{};
   std::function<void()> onClick_{};
};
} // namespace TinyEngine
