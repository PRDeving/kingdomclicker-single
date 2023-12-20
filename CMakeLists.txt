project(kingdom-clicker)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(external/entt/src)
include_directories(include)

set(EXTRA_LIBS ${EXTRA_LIBS} raylib)

add_subdirectory(external/entt)
add_subdirectory(external/raylib)
add_subdirectory(src)
