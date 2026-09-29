cmake_minimum_required(VERSION 3.25)
project(queens-plus-plus VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include(GNUInstallDirs)

# Lay out the build tree like the install tree (bin/ and lib/), so the game and
# SDL's shared library end up where the game expects to find them at runtime.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

set(SDL_SHARED ON CACHE BOOL "Build SDL as a shared library")
set(SDL_STATIC OFF CACHE BOOL "Build SDL as a static library")
set(SDL_TEST_LIBRARY OFF CACHE BOOL "Build the SDL3_test library")

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.16
    GIT_SHALLOW    TRUE
    SYSTEM
)
FetchContent_MakeAvailable(SDL3)

add_executable(queens-plus-plus
    src/app/main.cpp
)

target_include_directories(queens-plus-plus PRIVATE src)

target_link_libraries(queens-plus-plus PRIVATE SDL3::SDL3)

set_target_properties(queens-plus-plus PROPERTIES
    # On Windows, only open a console window for debug builds.
    WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>
    # On Linux, look for libSDL3.so in ../lib relative to the executable.
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}"
)

if(MSVC)
    target_compile_options(queens-plus-plus PRIVATE /W4)
else()
    target_compile_options(queens-plus-plus PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS queens-plus-plus
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# SDL is built as part of this project, so it has to be shipped with the game.
install(TARGETS SDL3-shared
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} NAMELINK_SKIP
    ARCHIVE EXCLUDE_FROM_ALL
)
