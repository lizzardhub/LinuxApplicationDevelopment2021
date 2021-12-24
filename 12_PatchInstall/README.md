Программа угадывает загаданное Вами число от 1 до 3999.

Компиляция

```
mkdir build
cd build
cmake .. -DDOXYGEN_INSTALL:BOOL=ON && cmake --build .
```

Установка и запуск

```
cd build
cmake --install . --prefix "."
cd bin
LANG=ru_RU.UTF-8 ./guess
```
или
```
cd build
sudo cmake --install . --prefix "/usr"
LANG=ru_RU.UTF-8 guess
```

Документация Doxygen находится в `<prefix>/share/guess/html/index.html`.

Удалить генераты

```
rm -rf build/*
```

Использовались материалы

https://evileg.com/en/post/536/ (using CMake path variables in C)
https://stackoverflow.com/a/12899005/13644436 (command line variables in CMake)