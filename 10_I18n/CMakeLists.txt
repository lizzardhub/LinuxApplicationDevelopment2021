cmake_minimum_required(VERSION 3.15)
project(Internationalization)

set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -pedantic -O0 -g)

add_executable(guess guess.c)

#       Localization commands for make

add_custom_command(
    TARGET guess
    POST_BUILD
    COMMAND mkdir -p po/ru
    COMMENT "Create empty localization template po/guess.pot ..."
    COMMAND xgettext --keyword=_ --language=C --sort-output -o po/guess.pot ${PROJECT_SOURCE_DIR}/guess.c
    COMMAND cp ${PROJECT_SOURCE_DIR}/guess.po po/ru/guess.po
    # Create new localization file
    # COMMAND msginit --input=po/guess.pot --locale=ru --output=po/ru/guess.po
)

add_custom_target(update_local
    DEPENDS po/guess.pot
    COMMENT "Update localization from source code ..."
    COMMAND msgmerge --update po/ru/guess.po po/guess.pot
)

add_custom_target(write_local
    DEPENDS po/ru/guess.po
    COMMENT "Write new localization ..."
    COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/ru/LC_MESSAGES
    COMMAND msgfmt --output-file=${PROJECT_SOURCE_DIR}/ru/LC_MESSAGES/guess.mo po/ru/guess.po
)
