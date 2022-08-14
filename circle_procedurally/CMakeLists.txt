add_executable(circle main.cpp ../common.h)
target_link_libraries(circle glfw GL)
target_include_directories(circle PRIVATE ${ROOT_SOURCEDIR})