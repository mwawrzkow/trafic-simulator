cmake_minimum_required(VERSION 4.3.4)
project(TraficSimulator LANGUAGES CXX)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
    OR CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
  message(FATAL_ERROR "GCC 16+ is required")
endif()

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CPM_DOWNLOAD_VERSION 0.43.2)
set(CPM_DOWNLOAD_LOCATION
    "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
if(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
  message(STATUS "Downloading CPM.cmake v${CPM_DOWNLOAD_VERSION}")
  file(DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    ${CPM_DOWNLOAD_LOCATION}
  )
endif()
include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(
  NAME SFML
  GITHUB_REPOSITORY SFML/SFML
  GIT_TAG 3.1.0
  OPTIONS
    "SFML_BUILD_AUDIO ON"
    "SFML_BUILD_NETWORK OFF"
)

set(SRC src/main.cpp
        src/graphics/window.cpp
        src/graphics/engine.cpp)

set(HPP include/main.hpp
        include/simulation/engine.hpp
        include/meta/Observer.hpp
        include/input/engine.hpp
        include/graphics/engine.hpp
        include/graphics/window.hpp
)

add_executable(${PROJECT_NAME} ${SRC} ${HPP})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_26)
target_compile_options(${PROJECT_NAME} PRIVATE -freflection)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SFML::Graphics SFML::Window SFML::System)
