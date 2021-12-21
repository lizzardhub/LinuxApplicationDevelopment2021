Программа угадывает загаданное Вами число от 1 до 3999.

Компиляция и запуск

```
mkdir build
cd build
cmake .. && cmake --build .
LANG=ru_RU.UTF-8 ./guess
```

Документация Doxygen находится в `html/index.html`.

Удалить генераты

```
rm -rf build/* ru/
```
