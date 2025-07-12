cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(
  "SpaceInvaders"
  VERSION 1.0.2
  HOMEPAGE_URL "https://github.com/mshirlaw/sfml-space-invaders")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# On macOS and Linux, use dynamic linking.
if(MSVC)
  set(SFML_STATIC_LIBRARIES TRUE)
endif()

# ==== UPDATE ME HERE ===========
# Absolute path where you installed SFML (Required on Windows only)
set(SFML_HOME "C:/SFML/SFML-2.6.1")
set(SFML_DIR ${SFML_HOME}/lib/cmake/SFML)
# ==========================

# Collect all sources
file(GLOB_RECURSE GAME_SRC "src/*.cpp" "src/*.h")
find_package(SFML 2.6 REQUIRED COMPONENTS "graphics" "audio" "window" "system")


if(WIN32)
  add_executable(SpaceInvaders WIN32 ${GAME_SRC} ${CMAKE_SOURCE_DIR}/res/win-icon.rc)
  target_link_libraries(SpaceInvaders PRIVATE sfml-main)
elseif(APPLE)
  include(${CMAKE_SOURCE_DIR}/cmake/macbundle.cmake)
  find_library(FOUNDATION_FRAMEWORK Foundation)
  target_link_libraries(SpaceInvaders PRIVATE ${FOUNDATION_FRAMEWORK})
else()
  add_executable(SpaceInvaders ${GAME_SRC})
endif()

# link all required libraries
target_link_libraries(SpaceInvaders PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)

# include SFML headers
target_include_directories(SpaceInvaders PUBLIC ${SFML_HOME}/include)

# show warnings (depending on C++ compiler)
if(MSVC)
  target_compile_options(SpaceInvaders PRIVATE /W4 /sdl)
else()
  target_compile_options(SpaceInvaders PRIVATE -Wall -Werror=constant-conversion -Werror=fortify-source)
endif()


# COPY resources folder into build dir (WINDOWS, LINUX)
if(NOT APPLE)
  add_custom_command(
    TARGET SpaceInvaders
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/res
            $<TARGET_FILE_DIR:SpaceInvaders>/res)
endif()

# COPY the audio DLL into build dir (Windows only)
if(WIN32)
  add_custom_command(
    TARGET SpaceInvaders
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SFML_HOME}/bin/openal32.dll
            $<TARGET_FILE_DIR:SpaceInvaders>/openal32.dll)
endif()