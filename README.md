typeval
---

An experiment in constexpr parameters.

A note on macro naming: For options, use `TV_OPTION_ON` and `TV_OPTION_OFF`. If
one defines both, the library will error at you. For standard defaults,
use `TV_STD_CPPXY`; the default option is `CPP14`. Internal macros are denoted
by `TV_INTERNAL` - do not touch these.

Options:

* `VARIABLE_TEMPLATES` -- Whether to define variable templates (`_v` templates)

* `DECLTYPE_AUTO` -- Whether to use `decltype(auto)`, or `-> decltype(...)`.
  With the latter, you can't use `typeval` with lambdas, but it's legal under
  C++11

* `KEYWORD` -- Whether to define `make_typeval` (otherwise, use `TV_MAKE_TYPEVAL`)

* `CONSTEXPR_LAMBDA` -- Whether to make the lambdas constexpr. This is the only
  way one would be able to use `make_typeval` in a constant expression.

Standard defaults:

* CPP11:
  * `VARIABLE_TEMPLATES` - off
  * `CONSTEXPR_LAMBDA` - off
  * `DECLTYPE_AUTO` - off
* CPP14 (default):
  * `VARIABLE_TEMPLATES` - on
  * `CONSTEXPR_LAMBDA` - off
  * `DECLTYPE_AUTO` - on
* CPP17
  * `VARIABLE_TEMPLATES` - on
  * `CONSTEXPR_LAMBDA` - off
  * `DECLTYPE_AUTO` - on

`KEYWORD` is on by default in all standards
