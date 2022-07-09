cmake_minimum_required(VERSION 3.5)

project(Roguelite)

# Main definitions
set(CORE_INCLUDES
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/vendor
)

set(TEST_INCLUDES
    ${CORE_INCLUDES}
    vendor/cest/include
)

set(TEST_CFLAGS
    -g -O0 --std=c++14 -Wno-writable-strings
)

## Core library
# Platform agnostic source files
set(CORE_SOURCES
    src/game/game.c
    src/engine/list.c
    src/engine/log.c
)

# Stubbed sources for testing purposes
if(TEST_PLATFORM)
    set(PLATFORM_CORE_SOURCES
        ${CORE_SOURCES}
        src/engine/null/window.c
        src/engine/null/drawing.c
    )
endif()

# Sources for PC version (Raylib)
if(PC_PLATFORM)
    set(PLATFORM_CORE_SOURCES
        ${CORE_SOURCES}
        src/engine/pc/window.c
        src/engine/pc/drawing.c
    )
endif()

add_library(core STATIC ${PLATFORM_CORE_SOURCES})
target_include_directories(core PUBLIC ${CORE_INCLUDES})

# Linker settings for PC version
if(PC_PLATFORM)
    target_link_directories(core PUBLIC
        ${PROJECT_SOURCE_DIR}/vendor/raylib/linux-amd64
    )
    target_link_libraries(core PUBLIC
        raylib
        dl
        pthread
        m
    )
endif()

## Game binary
add_executable(game src/main.c)
target_link_libraries(game PRIVATE core)

## Tests
add_executable(test_list
    test/test_list.cpp
)

target_compile_options(test_list PRIVATE ${TEST_CFLAGS})
target_include_directories(test_list PRIVATE ${TEST_INCLUDES})
target_link_libraries(test_list PRIVATE core)
