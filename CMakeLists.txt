cmake_minimum_required(VERSION 3.16)
project(seasonal_tree_raylib LANGUAGES CXX)

# Allow dependencies with older policy baselines to configure on modern CMake.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(RAYLIB_VERSION 5.0)

if (EMSCRIPTEN)
  # Raylib expects this cache variable for web builds.
  set(PLATFORM Web CACHE STRING "" FORCE)
endif()

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

if (EMSCRIPTEN)
  # Generate .html launcher plus .js/.wasm for browser execution.
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
  target_link_options(${PROJECT_NAME} PRIVATE
    "-sUSE_GLFW=3"
    "-sMAX_WEBGL_VERSION=2"
    "-sMIN_WEBGL_VERSION=2"
    "-sALLOW_MEMORY_GROWTH=1"
    "-sASSERTIONS=1"
    "-sEXPORTED_FUNCTIONS=['_main','_st_adjustBranchLength','_st_adjustBranchAngle','_st_adjustScaleFactor','_st_adjustMinBranchLength','_st_setSeason','_st_resetTree','_st_saveScreenshot']"
    "-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
  )
elseif (WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()
