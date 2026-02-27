module;

export module Counter;

export namespace TinyEngine
{
struct Counter
{
   constexpr void Add() noexcept { ++value_; }
   [[nodiscard]] constexpr std::size_t GetValue() const noexcept { return value_ };

private:
   std::size_t value_{};
};
} // namespace TinyEngine
