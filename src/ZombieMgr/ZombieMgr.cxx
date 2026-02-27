module;

#include <cstdint>
#include <vector>

export module ZombieMgr;

export namespace TinyEngine
{

template <class T>
struct Position
{
   T x{};
   T y{};
};

enum class Direction
{
   Up,
   Down,
   Left,
   Right,
};

struct ZombieMgr
{
   using ZombiePos = Position<std::uint8_t>;
   inline constinit static std::size_t reserveZombies{ 100 };

   explicit ZombieMgr() noexcept
   {
      zombiePositions_.reserve(reserveZombies);
      zombieDirections_.reserve(reserveZombies);
   }

   auto SpawnZombie() -> std::size_t
   {
      zombiePositions_.emplace_back();
      zombieDirections_.emplace_back();
      return zombiePositions_.size() - 1;
   }

private:
   std::vector<ZombiePos> zombiePositions_{};
   std::vector<Direction> zombieDirections_{};
};
} // namespace TinyEngine
