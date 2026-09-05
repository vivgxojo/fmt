#include <chrono>
#include <complex>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/compile.h>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/printf.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

struct Point {
  double x, y;
};

template <> struct fmt::formatter<Point> : fmt::formatter<fmt::string_view> {
  auto format(const Point& p, format_context& ctx) const {
    return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
  }
};

static void separator(const char* title) {
  fmt::print("\n{:=^60}\n", fmt::format(" Example {}", title));
}

int main() {
  fmt::print("{:=^60}\n", " fmt library demo ");

  // 1. Basic string formatting
  separator("1: Basic Formatting");
  fmt::print("Hello, {}!\n", "world");
  fmt::print("{0} + {1} = {2}\n", 1, 2, 3);
  fmt::print("Reorder: {1} before {0}\n", "second", "first");
  using namespace fmt::literals;
  fmt::print("{name} is {age} years old\n", "name"_a = "Alice", "age"_a = 30);

  // 2. Number formatting (alignment, fill, base, precision)
  separator("2: Number Formatting");
  fmt::print("Right-aligned:  [{:>10}]\n", 42);
  fmt::print("Center-filled:  [{:*^10}]\n", 42);
  fmt::print("Hex:            {:#x}\n", 255);
  fmt::print("Binary:         {:#010b}\n", 42);
  fmt::print("Float precision: {:.4f}\n", 3.14159265);
  fmt::print("Grouped digits: {}\n", fmt::group_digits(1234567890));

  // 3. Colored and styled terminal output
  separator("3: Colored Output");
  fmt::print(fg(fmt::color::dodger_blue), "  Blue text\n");
  fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "  Bold red text\n");
  fmt::print(fg(fmt::color::green) | bg(fmt::color::dark_slate_gray),
             "  Green on dark background\n");
  fmt::print("  Inline styled: {}\n",
             fmt::styled(42, fg(fmt::color::gold) | fmt::emphasis::bold));

  // 4. Chrono: durations and time points
  separator("4: Chrono Formatting");
  using namespace std::chrono_literals;
  fmt::print("Duration:    {}\n", 42s);
  fmt::print("Minutes:sec: {:%M:%S}\n", 90s);
  fmt::print("Quantity:    {:%Q %q}\n", 1500ms);
  auto now = std::chrono::system_clock::now();
  fmt::print("Local time:  {:%Y-%m-%d %H:%M:%S}\n", now);

  // 5. Ranges and containers
  separator("5: Ranges & Containers");
  std::vector<int> v = {1, 2, 3, 5, 8, 13};
  fmt::print("Vector:  {}\n", v);
  fmt::print("Hex vec: {::#x}\n", v);
  std::map<std::string, int> m = {{"one", 1}, {"two", 2}, {"three", 3}};
  fmt::print("Map:     {}\n", m);
  auto tup = std::make_tuple(42, "hello", 3.14);
  fmt::print("Tuple:   {}\n", tup);

  // 6. Join
  separator("6: Join");
  std::vector<std::string> words = {"fmt", "is", "great"};
  fmt::print("Joined:  {}\n", fmt::join(words, " "));
  std::vector<int> nums = {1, 2, 3, 4, 5};
  fmt::print("Dashed:  {:02}\n", fmt::join(nums, "-"));

  // 7. Compile-time format strings
  separator("7: Compile-Time Format Strings");
  auto compiled = fmt::format(FMT_COMPILE("Compiled: {} + {} = {}"), 3, 4, 7);
  fmt::print("{}\n", compiled);
  fmt::print(FMT_COMPILE("Hex via compile: {:#x}\n"), 0xBEEF);

  // 8. printf-style formatting
  separator("8: printf-Style");
  std::string s = fmt::sprintf("sprintf: %s is %d", "answer", 42);
  fmt::print("{}\n", s);
  fmt::printf("printf:  pi = %.5f\n", 3.14159265);
  fmt::printf("positional: %1$s = %2$d\n", "value", 99);

  // 9. Standard library types
  separator("9: Standard Library Types");
  fmt::print("complex:  {}\n", std::complex<double>(1.5, 2.5));
  fmt::print("optional: {}\n", std::optional<int>{42});
  fmt::print("empty:    {}\n", std::optional<int>{});
  fmt::print("pair:     {}\n", std::make_pair("key", 100));

  // 10. Custom type formatting
  separator("10: Custom Formatter");
  Point p1{1.5, 2.5};
  Point p2{-3.0, 4.0};
  fmt::print("Point: {}\n", p1);
  fmt::print("Points: {}\n", std::vector<Point>{p1, p2});

  fmt::print("\n{:=^60}\n", " done ");
  return 0;
}
