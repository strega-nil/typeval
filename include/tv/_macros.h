// STANDARD VERSION MACROS
#if (defined(TV_STD_CPP11) + defined(TV_STD_CPP14) + defined(TV_STD_CPP17)) > 1
#error "Cannot define more than one standard version at a time"
#endif
#if !defined(TV_STD_CPP11) && !defined(TV_STD_CPP14) && !defined(TV_STD_CPP17)
#define TV_STD_CPP14
#endif

// OPTION MACROS
#if defined(TV_OPTION_ON_KEYWORD) \
  && defined(TV_OPTION_OFF_KEYWORD)
#error "Cannot define both on and off options at the same time"
#endif
#if defined(TV_OPTION_ON_VARIABLE_TEMPLATES) \
  && defined(TV_OPTION_OFF_VARIABLE_TEMPLATES)
#error "Cannot define both on and off options at the same time"
#endif
#if defined(TV_OPTION_ON_CONSTEXPR_LAMBDA) \
  && defined(TV_OPTION_OFF_CONSTEXPR_LAMBDA)
#error "Cannot define both on and off options at the same time"
#endif
#if defined(TV_OPTION_ON_DECLTYPE_AUTO) \
  && defined(TV_OPTION_OFF_DECLTYPE_AUTO)
#error "Cannot define both on and off options at the same time"
#endif

#if !defined(TV_OPTION_ON_KEYWORD) && !defined(TV_OPTION_OFF_KEYWORD)
#define TV_OPTION_ON_KEYWORD
#endif


#if defined(TV_STD_CPP11)
  #if !defined(TV_OPTION_ON_VARIABLE_TEMPLATES) \
    && !defined(TV_OPTION_OFF_VARIABLE_TEMPLATES)
    #define TV_OPTION_OFF_VARIABLE_TEMPLATES
  #endif
  #if !defined(TV_OPTION_ON_CONSTEXPR_LAMBDA) \
    && !defined(TV_OPTION_OFF_CONSTEXPR_LAMBDA)
    #define TV_OPTION_OFF_CONSTEXPR_LAMBDA
  #endif
  #if !defined(TV_OPTION_ON_DECLTYPE_AUTO) \
    && !defined(TV_OPTION_OFF_DECLTYPE_AUTO)
    #define TV_OPTION_OFF_DECLTYPE_AUTO
  #endif
#elif defined(TV_STD_CPP14)
  #if !defined(TV_OPTION_ON_VARIABLE_TEMPLATES) \
    && !defined(TV_OPTION_OFF_VARIABLE_TEMPLATES)
    #define TV_OPTION_ON_VARIABLE_TEMPLATES
  #endif
  #if !defined(TV_OPTION_ON_CONSTEXPR_LAMBDA) \
    && !defined(TV_OPTION_OFF_CONSTEXPR_LAMBDA)
    #define TV_OPTION_OFF_CONSTEXPR_LAMBDA
  #endif
  #if !defined(TV_OPTION_ON_DECLTYPE_AUTO) \
    && !defined(TV_OPTION_OFF_DECLTYPE_AUTO)
    #define TV_OPTION_ON_DECLTYPE_AUTO
  #endif
#elif defined(TV_STD_CPP17)
  #if !defined(TV_OPTION_ON_VARIABLE_TEMPLATES) \
    && !defined(TV_OPTION_OFF_VARIABLE_TEMPLATES)
    #define TV_OPTION_ON_VARIABLE_TEMPLATES
  #endif
  #if !defined(TV_OPTION_ON_CONSTEXPR_LAMBDA) \
    && !defined(TV_OPTION_OFF_CONSTEXPR_LAMBDA)
    #define TV_OPTION_ON_CONSTEXPR_LAMBDA
  #endif
  #if !defined(TV_OPTION_ON_DECLTYPE_AUTO) \
    && !defined(TV_OPTION_OFF_DECLTYPE_AUTO)
    #define TV_OPTION_ON_DECLTYPE_AUTO
  #endif
#endif


// USABILITY MACROS
#ifdef TV_OPTION_ON_CONSTEXPR_LAMBDA
#define TV_INTERNAL_LAMBDA_CONSTEXPR constexpr
#else
#define TV_INTERNAL_LAMBDA_CONSTEXPR
#endif
