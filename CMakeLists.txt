cmake_minimum_required(VERSION 3.16)
project(seasonal_tree_raylib LANGUAGES CXX)

# Allow dependencies with older policy baselines to configure on modern CMake.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(RAYLIB_VERSION 5.0)

find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
  )
  FetchContent_MakeAvailable(raylib)
endif()

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/App.cpp
  src/Controls.cpp
  src/Renderer.cpp
  src/TreeGenerator.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if (WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()
