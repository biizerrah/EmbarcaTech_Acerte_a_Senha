cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_project)

pico_sdk_init()

add_executable(Acerteasenha Acerteasenha.c)

target_link_libraries(pico_project pico_stdlib)

pico_add_extra_outputs(pico_project)

# Incluir o diretório de testes
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG devel
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests test_main.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2)
target_link_libraries(tests pico_stdlib)
pico_enable_stdio_usb(tests 1)
pico_enable_stdio_uart(tests 0)


