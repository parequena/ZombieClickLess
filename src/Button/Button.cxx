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
   Button(Box<std::uint16_t> const& box, auto&& onClick)
       : box_{ box }
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

      if (input.mouseX >= box_.X() && input.mouseX <= box_.X() + box_.W() && input.mouseY >= box_.Y()
        && input.mouseY <= box_.Y() + box_.H())
      {
         onClick_();
      }
   }

   [[nodiscard]] constexpr auto GetBox() const noexcept { return box_; }

private:
   Box<std::uint16_t> box_{ };
   std::function<void()> onClick_{ };
};
} // namespace TinyEngine
