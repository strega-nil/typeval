#define TV_STD_CPP11
#include <tv/typeval.h>

template <typename T>
struct FormatArgs {
  static_assert(
    tv::is_string_constant<T>::value,
    "Template argument to format_args must be a string_constant"
  );
};
