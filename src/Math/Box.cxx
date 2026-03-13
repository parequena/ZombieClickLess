module;

#include <type_traits>

export module Math:Box;

import :Vector2D;

export namespace TinyEngine
{
template <Numeric T>
struct [[nodiscard]] Box
{
   explicit Box() = default;
   explicit Box(Vector2D<T> const& position, T const width, T const height)
       : position_{ position }
       , width_{ width }
       , height_{ height }
   {
   }

   [[nodiscard]] constexpr auto Position() const noexcept -> Vector2D<T> { return position_; }
   [[nodiscard]] constexpr auto Width() const noexcept -> T { return width_; }
   [[nodiscard]] constexpr auto Height() const noexcept -> T { return height_; }
   [[nodiscard]] constexpr auto Top() const noexcept -> T { return position_.Y(); }
   [[nodiscard]] constexpr auto Bot() const noexcept -> T { return position_.Y() + height_; }
   [[nodiscard]] constexpr auto Left() const noexcept -> T { return position_.X(); }
   [[nodiscard]] constexpr auto Right() const noexcept -> T { return position_.X() + width_; }
   [[nodiscard]] constexpr auto X() const noexcept -> T { return position_.X(); }
   [[nodiscard]] constexpr auto Y() const noexcept -> T { return position_.Y(); }
   [[nodiscard]] constexpr auto W() const noexcept -> T { return width_; }
   [[nodiscard]] constexpr auto H() const noexcept -> T { return height_; }

private:
   Vector2D<T> position_{};
   T width_{};
   T height_{};
};
}
