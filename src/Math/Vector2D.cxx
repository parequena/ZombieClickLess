module;

#include <type_traits>
#include <cstdint>

export module Math:Vector2D;

export namespace TinyEngine
{

template <typename T>
concept Numeric = std::is_integral_v<T> or std::is_floating_point_v<T>;

template <Numeric T>
constexpr bool is_float = std::is_floating_point_v<T>;

template <Numeric T>
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

   constexpr auto operator+=(Vector2D const& other) noexcept -> Vector2D&
   {
      x_ += other.x_;
      y_ += other.y_;
      return *this;
   }

   [[nodiscard]] constexpr auto operator+(Vector2D const& other) const noexcept -> Vector2D
   {
      return Vector2D{ x_ + other.x_, y_ + other.y_ };
   }

   constexpr auto operator*=(T const scalar) noexcept -> Vector2D&
   {
      x_ *= scalar;
      y_ *= scalar;
      return *this;
   }

   [[nodiscard]] constexpr auto operator*(T const scalar) const noexcept -> Vector2D
   {
      return Vector2D{ x_ * scalar, y_ * scalar };
   }

   constexpr auto operator*=(Vector2D const& other) noexcept -> Vector2D&
   {
      x_ *= other.x_;
      y_ *= other.y_;
      return *this;
   }

   [[nodiscard]] constexpr auto operator*(Vector2D const& other) const noexcept -> Vector2D
   {
      return Vector2D{ x_ * other.x_, y_ * other.y_ };
   }

private:
   T x_{};
   T y_{};
};

using Vector2Du16 = Vector2D<std::uint16_t>;
using Vector2Df = Vector2D<float>;
} // namespace TinyEngine
