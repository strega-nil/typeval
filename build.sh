#! /bin/sh
clang++ -std=c++14 -Wall -Wextra -Werror -Iinclude -c test/fmt.cpp || exit
clang++ -std=c++11 -Wall -Wextra -Werror -Iinclude test/fmt_cpp11.cpp
