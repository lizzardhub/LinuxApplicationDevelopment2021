Программа угадывает загаданное Вами число от 1 до 100.


Компиляция и запуск

mkdir build
cd build
cmake .. && cmake --build . && make update_local && make write_local
cd ..
LANG=ru_RU.UTF-8 ./build/guess


Добавление новых строк из guess.c, требующих локализации, в файл build/po/ru/guess.po

cd build
make update_local && make write_local


Удалить генераты

cd build
rm -rf ../build/* ../ru


Использовались материалы

https://gist.github.com/baiwfg2/39881ba703e9c74e95366ed422641609 (CMake custom target and command)
https://stackoverflow.com/questions/44212101/cmake-how-to-have-add-custom-command-run-after-all-project-files-are-built (CMake custom command)