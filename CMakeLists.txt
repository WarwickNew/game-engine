cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)

project(Game)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp)

configure_file(src/helpers/RootDir.h.in src/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/src)

link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Generic OpenGL and windowing libraries.
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

# Model loading
#find_package(assimp REQUIRED)
#if (assimp_VERSION VERSION_LESS "5.1")
#    message(FATAL_ERROR "Assimp ${assimp_VERSION} out of date, Assimp 5.1.0 or newer is required!")
#endif()
set(CPM_DOWNLOAD_VERSION 0.38.1)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD
    https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    ${CPM_DOWNLOAD_LOCATION}
  )
endif()
include(${CPM_DOWNLOAD_LOCATION})
set(CPM_USE_LOCAL_PACKAGES ON)

#CPMAddPackage(
#  NAME SDL2_image
#  VERSION 2.0.5
#  URL https://libsdl.org/projects/old/SDL_image/release/SDL2_image-2.0.5.zip
#)
#CPMAddPackage(
#  NAME SDL2
#  VERSION 2.0.12
#  URL https://libsdl.org/release/SDL2-2.0.12.zip
#)
#if (SDL2_ADDED)
#  add_library(SDL2::SDL2 ALIAS SDL2)
#endif()

#CPMAddPackage(
#  NAME GLM
#  VERSION 0.9.9.8
#  GITHUB_REPOSITORY "g-truc/glm"
#  GIT_TAG "0.9.9.8"
#)
#
#
#CPMAddPackage(
#  NAME GLEW
#  VERSION 2.2.0
#  GITHUB_REPOSITORY "nigels-com/glew"
#  GIT_TAG "glew-2.2.0"
#)

CPMAddPackage(
  NAME assimp
  VERSION 5.2.5
  GITHUB_REPOSITORY "assimp/assimp"
  GIT_TAG "v5.2.5"
)

# Build FastNoise2 Library
#set(FASTNOISE2_NOISETOOL ON CACHE BOOL "Build Noise Tool" FORCE)
#set(BUILD_SHARED_LIBS ON CACHE BOOL "Build Noise Tool Dynamic Library" FORCE)
##add_subdirectory(deps/FastNoise2)
#CPMAddPackage(
#  NAME FastNoise2
#  VERSION 0.9.7
#  GITHUB_REPOSITORY "Auburn/FastNoise2"
#  GIT_TAG "v0.9.2-alpha"
#)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    assimp::assimp
    )
