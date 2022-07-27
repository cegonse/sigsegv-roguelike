cmake_minimum_required(VERSION 3.5)

project(Roguelite)

# Main definitions
set(CORE_INCLUDES
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/vendor
)

set(TEST_INCLUDES
    ${CORE_INCLUDES}
    ${PROJECT_SOURCE_DIR}/vendor/cest/include
    ${PROJECT_SOURCE_DIR}/test
)

set(TEST_CFLAGS
    -g -O0 --std=c++14 -Werror
)

## Core library
# Platform agnostic source files
set(CORE_SOURCES
    src/game/game.c
    src/engine/list.c
    src/engine/hashmap.c
    src/engine/log.c
    src/engine/texture_repository.c
    src/engine/resource_pack.c
    src/engine/resource_file.c
)

# Stubbed sources for testing purposes
if(TEST_PLATFORM)
    set(PLATFORM_CORE_SOURCES
        ${CORE_SOURCES}
        src/engine/null/window.c
        src/engine/null/drawing.c
        src/engine/null/platform.c
        src/engine/pc/file.c
    )
endif()

# Sources for PC version (Raylib)
if(PC_PLATFORM)
    set(PLATFORM_CORE_SOURCES
        ${CORE_SOURCES}
        src/engine/pc/window.c
        src/engine/pc/drawing.c
        src/engine/pc/file.c
        src/engine/pc/platform.c
    )
endif()

add_library(core STATIC ${PLATFORM_CORE_SOURCES})
target_include_directories(core PUBLIC ${CORE_INCLUDES})
target_compile_options(core PRIVATE -Werror -g)

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
# test_list
add_executable(test_list
    test/test_list.cpp
)

target_compile_options(test_list PRIVATE ${TEST_CFLAGS})
target_include_directories(test_list PRIVATE ${TEST_INCLUDES})
target_link_libraries(test_list PRIVATE core)

# test_texture_repository
add_executable(test_texture_repository
    test/test_texture_repository.cpp
)

target_compile_options(test_texture_repository PRIVATE ${TEST_CFLAGS})
target_include_directories(test_texture_repository PRIVATE ${TEST_INCLUDES})
target_link_libraries(test_texture_repository PRIVATE core)

# test_hashmap
add_executable(test_hashmap
    test/test_hashmap.cpp
)

target_compile_options(test_hashmap PRIVATE ${TEST_CFLAGS})
target_include_directories(test_hashmap PRIVATE ${TEST_INCLUDES})
target_link_libraries(test_hashmap PRIVATE core)

# test_resource_pack
add_executable(test_resource_pack
    test/test_resource_pack.cpp
)

target_compile_options(test_resource_pack PRIVATE ${TEST_CFLAGS})
target_include_directories(test_resource_pack PRIVATE ${TEST_INCLUDES})
target_link_libraries(test_resource_pack PRIVATE core)

# test_resource_file
add_executable(test_resource_file
    test/test_resource_file.cpp
)

target_compile_options(test_resource_file PRIVATE ${TEST_CFLAGS})
target_include_directories(test_resource_file PRIVATE ${TEST_INCLUDES})
target_link_libraries(test_resource_file PRIVATE core)
