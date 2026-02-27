module;

#include <cstdint>

export module Input;

export namespace TinyEngine
{
struct InputState
{
   bool closeRequested{ false };

   // Keyboard
   bool keyEscape{ false };
   bool keySpace{ false };
   bool keyW{ false };
   bool keyA{ false };
   bool keyS{ false };
   bool keyD{ false };

   // Mouse
   bool mouseLeft{ false };
   bool mouseRight{ false };
   std::int32_t mouseX{ 0 };
   std::int32_t mouseY{ 0 };
};
} // namespace TinyEngine
