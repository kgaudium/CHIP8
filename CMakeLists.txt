cmake_minimum_required(VERSION 3.29)

# Название проекта и стандарт языка
project(CHIP8 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание библиотек
add_library(Chip8Opcodes Chip8OpCodes.cpp)

add_library(Chip8Class
        Chip8.cpp
        Chip8.h
)

add_library(Rom
        ROM.h
)

add_library(Emulator
        Emulator.cpp
        Emulator.h
)

add_library(Font
        Font.cpp
        Font.h
)

add_library(OpcodeTree
        OpcodeTree/OpcodeTree.h
        OpcodeTree/OpcodeTreeNode.h
)

add_library(Platform
        Platform.h
)

set_target_properties(Rom PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(OpcodeTree PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Platform PROPERTIES LINKER_LANGUAGE CXX)

# Включение заголовочных файлов
# Если библиотеки используют относительные пути, добавьте include-директории
target_include_directories(OpcodeTree PUBLIC OpcodeTree)
target_include_directories(Chip8Class PUBLIC .)
target_include_directories(Emulator PUBLIC .)

# Создание исполняемого файла
add_executable(CHIP8 main.cpp)

# Линковка библиотек
target_link_libraries(CHIP8
        PRIVATE
        Chip8Opcodes
        Chip8Class
        Rom
        Emulator
        OpcodeTree
        Font
        Platform
)

# Настройки для улучшения отладки и оптимизации
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(CHIP8 PRIVATE -g -Wall -Wextra -Wpedantic)
else ()
    target_compile_options(CHIP8 PRIVATE -O3 -DNDEBUG)
endif ()
