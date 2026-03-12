module;

#include <type_traits>

export module Math:Vector2D;

export namespace TinyEngine
{

template <typename T>
   requires(std::is_integral_v<T> or std::is_floating_point_v<T>)
struct [[nodiscard]] Vector2D
{
   explicit constexpr Vector2D() noexcept = default;
   explicit constexpr Vector2D(T const x, T const y) noexcept
       : x_{ x }
       , y_{ y }
   {
   }

   [[nodiscard]] constexpr auto X() const noexcept -> T { return x_; }
   constexpr auto X(T const x) noexcept -> void { x_ = x; }
   [[nodiscard]] constexpr auto Y() const noexcept -> T { return y_; }
   constexpr auto Y(T const y) noexcept -> void { y_ = y; }

private:
   T x_{ };
   T y_{ };
};

using Vector2Du16 = Vector2D<std::uint16_t>;
using Vector2Df = Vector2D<float>;
} // namespace TinyEngine
