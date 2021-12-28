# CMakeList.txt: проект CMake для SB_TFlex; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("SB_TFlex")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (SB_TFlex "SB_TFlex.cpp" "SB_TFlex.h"  "Canvas.cpp" "Figures.cpp" )

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
