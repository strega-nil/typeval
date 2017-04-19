#! /bin/sh
clang++ -std=c++14 -Wall -Wextra -Werror -Iinclude -c test/fmt.cpp
clang++ -std=c++11 -Wall -Wextra -Werror -Iinclude -c test/fmt_cpp11.cpp
