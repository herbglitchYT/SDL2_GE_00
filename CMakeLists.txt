if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the SDL source code and run \"cmake -S ${CMAKE_SOURCE_DIR} -B .\" from there")
endif()

cmake_minimum_required(VERSION 3.10)

project(ge CXX)

add_library(ge)

target_sources(ge PRIVATE
    src/ge.cpp

    src/entities/entity.cpp
    src/entities/sprite.cpp

    src/resources/config.cpp
    src/resources/spritesheet.cpp
)

target_include_directories(ge PUBLIC src/)

if(WIN32)
    target_compile_definitions(ge PRIVATE -DDLL_EXPORT)
endif()

target_link_libraries(ge
    PUBLIC SDL2::SDL2
    PUBLIC SDL2_image
)
