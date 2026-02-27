module;

#include <format>
#include <print>
#include <string>

export module Helpers:Logger;

export namespace TinyEngine
{
// This struct acts as a namespace
class Logger
{
   constexpr static auto RedBoldColor{ "\033[1m\033[31m" };
   constexpr static auto YelowBoldColor{ "\033[1m\033[33m" };
   constexpr static auto CyanBoldColor{ "\033[1m\033[36m" };
   constexpr static auto EndColor{ "\033[0m" };

public:
   template <typename... Args>
   static void Error(std::format_string<Args...> fmt, Args&&... args) noexcept
   {
      print(RedBoldColor, "ERROR", fmt, std::forward<Args>(args)...);
   }

   template <typename... Args>
   static void Warning(std::format_string<Args...> fmt, Args&&... args) noexcept
   {
      print(YelowBoldColor, "WARN ", fmt, std::forward<Args>(args)...);
   }

   template <typename... Args>
   static void Info(std::format_string<Args...> fmt, Args&&... args) noexcept
   {
      print(CyanBoldColor, "INFO ", fmt, std::forward<Args>(args)...);
   }

   template <typename... Args>
   static void Debug(std::format_string<Args...> fmt, Args&&... args) noexcept
   {
      print("", "DEBUG", fmt, std::forward<Args>(args)...);
   }

   static void PrintVector(auto const& vector) noexcept
   {
      std::print("Vector [ ");
      for (auto const& v : vector)
      {
         std::print("{} ", v);
      }
      std::println("]");
   }

private:
   template <typename... Args>
   static void print(
     std::string const& color, std::string const& message, std::format_string<Args...> fmt, Args&&... args) noexcept
   {
      std::print("[{} {} {}] : ", color, message, EndColor);
      std::println(fmt, std::forward<Args>(args)...);
   }
};
} // namespace TinyEngine
