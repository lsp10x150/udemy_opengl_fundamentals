cmake_minimum_required(VERSION 3.23)
project(glfwOpenGl)

set(ROOT_SOURCEDIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(circle_procedurally)
add_subdirectory(matrix_stack)
add_subdirectory(glsl_shaders_attributes_geometry_vbos)

