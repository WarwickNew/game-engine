cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE sources src/*.cpp src/*.h)

file(GLOB_RECURSE data libs/* src/*.glsl)

add_executable(SDL2Test ${sources} ${data})

file(COPY ${data} DESTINATION resources)

#target_include_directories(example PUBLIC src/)

target_link_libraries(SDL2Test
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${SDL2_LIBRARIES}
  # here you can add any library dependencies
)

#target_include_directories(SDL2Test PUBLIC
#  ${OpenGL_INCLUDE_DIRS}
#  ${SDL2_INCLUDE_DIRS}
#  ${GLEW_INCLUDE_DIRS}
#)
