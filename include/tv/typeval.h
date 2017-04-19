#include <cstddef>
#include <type_traits>

#ifdef TV_USE_CPP11
#define TV_NO_VARIABLE_TEMPLATES
#endif

namespace tv {

  namespace _impl {
    template <typename Of, typename T>
    struct is_carray_of : std::false_type { };

    template <typename T, std::size_t N>
    struct is_carray_of<T, T[N]> : std::true_type { };

    template <typename T, std::size_t N>
    struct is_carray_of<T, T(&)[N]> : std::true_type { };

#ifndef TV_NO_VARIABLE_TEMPLATES
    template <typename Of, typename T>
    static constexpr bool is_carray_of_v = is_carray_of<Of, T>::value;
#endif // TV_NO_VARIABLE_TEMPLATES
  }

  template <typename T>
  struct typeval {
    using value_type = decltype(T::value());
    using type = typeval<T>;
    constexpr static value_type value = T::value();
    constexpr operator value_type() const noexcept { return value; }
    constexpr auto operator()() const noexcept -> value_type { return value; }
  };

  template <typename T>
  struct is_typeval : std::false_type { };
  template <typename T>
  struct is_typeval<typeval<T>> : std::true_type { };

#ifndef TV_NO_VARIABLE_TEMPLATES
  template <typename T>
  constexpr static bool is_typeval_v = is_typeval<T>();
#endif // TV_NO_VARIABLE_TEMPLATES

  template <typename Of, typename T>
  struct is_typeval_of : std::false_type { };
  template <typename Of, typename T>
  struct is_typeval_of<Of, typeval<T>> : std::integral_constant<
    bool,
    std::is_same<Of, typename typeval<T>::type>::value
  > { };

#ifndef TV_NO_VARIABLE_TEMPLATES
  template <typename Of, typename T>
  constexpr static bool is_typeval_of_v = is_typeval_of<Of, T>();
#endif // TV_NO_VARIABLE_TEMPLATES

  template <typename T>
  struct is_string_constant : std::false_type { };
  template <typename T>
  struct is_string_constant<typeval<T>> : std::integral_constant<
    bool,
    _impl::is_carray_of<char const, typename typeval<T>::type>::value
  > { };

#ifndef TV_NO_VARIABLE_TEMPLATES
  template <typename T>
  constexpr static bool is_string_constant_v = is_string_constant<T>();
#endif // TV_NO_VARIABLE_TEMPLATES

}

#define TV_MAKE_TYPEVAL(...) []() {\
  struct _typeval_anon {\
    constexpr static decltype(auto) value() {\
      return __VA_ARGS__;\
    }\
  };\
  return typeval<_typeval_anon>();\
}()

#ifndef TV_NO_DEFINE_KEYWORD

#define make_typeval TV_MAKE_TYPEVAL

#endif // TV_NO_DEFINE_KEYWORD
