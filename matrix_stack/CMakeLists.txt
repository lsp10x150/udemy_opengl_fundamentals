add_executable(matrix_stack main.cpp ../common.h)
target_link_libraries(matrix_stack glfw GL)
target_include_directories(matrix_stack PRIVATE ${ROOT_SOURCEDIR})