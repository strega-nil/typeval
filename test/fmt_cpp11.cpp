#define TV_STD_CPP11
#include <tv/typeval.h>
#include <tuple>
#include <utility>
#include <iostream>

struct string_view {
  char const* ptr;
  std::size_t len;

  constexpr char const* begin() const {
    return ptr;
  }
  constexpr char const* end() const {
    return ptr + len;
  }
};

std::ostream& operator<<(std::ostream& os, string_view sv) {
  for (char c: sv) {
    os << c;
  }
  return os;
}

namespace _impl {
  template <std::size_t N, typename... Ts>
  auto make_format_tuple(char const(&fmt)[N], Ts const&... ts)
  -> std::tuple<std::pair<::string_view, Ts const&>...>
  {
    auto ret = std::make_tuple(
      std::pair<string_view, Ts const&>(string_view {nullptr, 0}, ts)...
    );
    (void)fmt;
    // CONTINUE HERE
    // write the pointers
    return ret;
  }
}

template <typename FmtString, typename... Ts>
struct formatter {
  std::tuple<std::pair<string_view, Ts const&>...> ts;

  formatter(Ts const&... ts):
    ts(_impl::make_format_tuple(FmtString::value, ts...)) { }
};

namespace _impl {
  template <typename... Ts>
  std::ostream& write_pairs(
    std::ostream& os,
    std::tuple<std::pair<string_view, Ts const&>...> const& tup
  ) {
    (void)tup;
    return os;
  }
}

template <typename Fmt, typename... Ts>
std::ostream& operator<<(std::ostream& os, formatter<Fmt, Ts...> f) {
  return _impl::write_pairs(os, f.ts);
}

template <typename T>
struct format_args {
  static_assert(
    tv::is_constant_string<T>::value,
    "Template argument to format_args must be a string_constant"
  );

  template <typename... Ts>
  constexpr auto operator()(Ts const&... ts) const -> formatter<T, Ts...> {
    return {ts...};
  }
};

template <typename T>
auto make_format_args(T const&) -> format_args<T> {
  return {};
}

int main() {
  std::cout << make_format_args(typeval("Hello, {}!\n"))("world!");
}
