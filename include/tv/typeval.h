#include <cstddef>
#include <type_traits>

#ifndef TV_TYPEVAL_H
#define TV_TYPEVAL_H

#include "_macros.h"

namespace tv {

  namespace _impl {
    template <typename Of, typename T>
    struct is_carray_of : std::false_type { };

    template <typename T, std::size_t N>
    struct is_carray_of<T, T[N]> : std::true_type { };

    template <typename T, std::size_t N>
    struct is_carray_of<T, T(&)[N]> : std::true_type { };

#if defined(TV_OPTION_ON_VARIABLE_TEMPLATES)
    template <typename Of, typename T>
    static constexpr bool is_carray_of_v = is_carray_of<Of, T>::value;
#endif
  }

  template <typename T>
  struct constant {
    using value_type = decltype(T::value());
    using type = constant<T>;
    constexpr static value_type value = T::value();
    constexpr operator value_type() const noexcept { return value; }
    constexpr auto operator()() const noexcept -> value_type { return value; }
  };

  template <typename T>
  struct is_constant_type : std::false_type { };
  template <typename T>
  struct is_constant_type<constant<T>> : std::true_type { };

#if defined(TV_OPTION_ON_VARIABLE_TEMPLATES)
  template <typename T>
  constexpr static bool is_constant_type_v = is_constant_type<T>();
#endif

  template <typename Of, typename T>
  struct is_constant_type_of : std::false_type { };
  template <typename Of, typename T>
  struct is_constant_type_of<Of, constant<T>> : std::integral_constant<
    bool,
    std::is_same<Of, typename constant<T>::value_type>::value
  > { };

#if defined(TV_OPTION_ON_VARIABLE_TEMPLATES)
  template <typename Of, typename T>
  constexpr static bool is_constant_type_of_v = is_constant_type_of<Of, T>();
#endif

  template <typename T>
  struct is_constant_string : std::false_type { };
  template <typename T>
  struct is_constant_string<constant<T>> : std::integral_constant<
    bool,
    _impl::is_carray_of<char const, typename constant<T>::value_type>::value
  > { };

#if defined(TV_OPTION_ON_VARIABLE_TEMPLATES)
  template <typename T>
  constexpr static bool is_constant_string_v = is_constant_string<T>();
#endif

  namespace _impl {
    template <typename T>
    constexpr auto make_constant_of(T) -> constant<T> {
      return constant<T>();
    }
  }
}

#ifdef TV_OPTION_ON_DECLTYPE_AUTO
#define TV_MAKE_TYPEVAL(...) ::tv::_impl::make_constant_of(\
  []() TV_INTERNAL_LAMBDA_CONSTEXPR {\
    struct _typeval_anon {\
      constexpr static decltype(auto) value() {\
        return __VA_ARGS__;\
      }\
    };\
    return _typeval_anon();\
  }()\
)
#else
#define TV_MAKE_TYPEVAL(...) ::tv::_impl::make_constant_of(\
  []() TV_INTERNAL_LAMBDA_CONSTEXPR {\
    struct _typeval_anon {\
      constexpr static decltype(__VA_ARGS__) value() {\
        return __VA_ARGS__;\
      }\
    };\
    return _typeval_anon();\
  }()\
)
#endif

#if defined(TV_OPTION_ON_KEYWORD)
#define typeval TV_MAKE_TYPEVAL
#endif

#endif // TV_TYPEVAL_H
