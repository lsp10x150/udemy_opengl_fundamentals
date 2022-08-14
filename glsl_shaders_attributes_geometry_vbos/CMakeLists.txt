add_executable(glsl_shaders_attributes_geometry_vbos main.cpp ../common.h)
find_package(GLEW REQUIRED)
target_link_libraries(glsl_shaders_attributes_geometry_vbos glfw3 GL GLEW::GLEW)
target_include_directories(glsl_shaders_attributes_geometry_vbos PRIVATE ${ROOT_SOURCEDIR} )
