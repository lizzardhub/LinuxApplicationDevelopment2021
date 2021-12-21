cmake_minimum_required(VERSION 3.15)
project(Documenting)

#       Compilation

set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -pedantic -O0 -g)

add_executable(guess guess.c)

#       Localization

add_custom_command(
    TARGET guess
    POST_BUILD
    COMMENT "Create localization template po/guess.pot and russian template po/ru/guess.po  ..."

    COMMAND mkdir -p po/ru
    COMMAND xgettext --keyword=_ --language=C --sort-output -o po/guess.pot ${PROJECT_SOURCE_DIR}/guess.c
    COMMAND cp ${PROJECT_SOURCE_DIR}/guess.po po/ru/guess.po

    # Create new localization file
    #COMMAND msginit --input=po/guess.pot --locale=ru --output=po/ru/guess.po

    # New localization from source code
    COMMAND msgmerge --update po/ru/guess.po po/guess.pot
    COMMAND mkdir -p ru/LC_MESSAGES
    COMMAND msgfmt --output-file=ru/LC_MESSAGES/guess.mo po/ru/guess.po
)

#       Documentation: doxygen, man

find_package(Doxygen REQUIRED)
add_custom_command(
    TARGET guess
    POST_BUILD
    COMMENT "Generate documentation with doxygen and help2man  ..."
    COMMAND doxygen ../Doxygen.in
    COMMAND help2man ./guess -o guess.1
)