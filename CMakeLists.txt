cmake_minimum_required(VERSION 3.7)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Mandelpan)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package( SDL2 REQUIRED )

add_executable(Mandelpan
    src/main.cpp
    src/window.cpp
    src/renderer.cpp
    src/camera.cpp)

target_link_libraries(Mandelpan SDL2::Core)


set_target_properties(Mandelpan PROPERTIES
            CXX_STANDARD_REQUIRED ON)
set_target_properties(Mandelpan PROPERTIES
            CXX_STANDARD 17)
