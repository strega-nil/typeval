#include <tv/typeval.h>

template <typename T>
struct FormatArgs {
  static_assert(
    tv::is_constant_string_v<T>,
    "Template argument to format_args must be a string_constant"
  );
};
