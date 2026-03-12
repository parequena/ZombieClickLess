module;

#include <cstdint>
#include <functional>
#include <tuple>

export module Button;

import Input;
import Math;

export namespace TinyEngine
{
struct [[nodiscard]] Button
{
   Button(Vector2Du16 const& position, std::uint16_t const w, std::uint16_t const h, auto&& onClick)
       : position_{ position }
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

      if (input.mouseX >= position_.X() && input.mouseX <= position_.X() + w_ && input.mouseY >= position_.Y()
        && input.mouseY <= position_.Y() + h_)
      {
         onClick_();
      }
   }

   [[nodiscard]] constexpr auto GetPositions() const noexcept { return std::tuple{ position_, w_, h_ }; }

private:
   Vector2Du16 position_{ };
   std::uint16_t w_{ };
   std::uint16_t h_{ };
   std::function<void()> onClick_{ };
};
} // namespace TinyEngine
