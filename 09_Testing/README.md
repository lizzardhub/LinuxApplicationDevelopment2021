## Компиляция и запуск тестов

mkdir build
cd build
cmake .. && cmake --build .
ctest
make ExperimentalCoverage

Удалить генераты через rm -r ../build/*

## Использовались материалы

https://cliutils.gitlab.io/modern-cmake/chapters/features/cpp11.html (опции компиляторов в CMake)
https://habr.com/ru/post/433822/ (тестирование в CMake)
https://neerc.ifmo.ru/wiki/index.php?title=CMake_Tutorial (создание библиотек в CMake)
https://jhbell.com/using-cmake-and-gcov (CMake и gcov)
https://gitlab.kitware.com/cmake/community/-/wikis/doc/ctest/Coverage (CMake и gcov)