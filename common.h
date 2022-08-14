#ifndef GLFWOPENGL_COMMON_H
#define GLFWOPENGL_COMMON_H
#include <GLFW/glfw3.h>
#include <memory>

struct GlfwWindowDeleter {
    void operator()(GLFWwindow* window) {
        glfwTerminate();
    }
};

std::unique_ptr<GLFWwindow, GlfwWindowDeleter> create_window(const std::string& title, int width = 800, int height = 600,
                                                             GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr) {
    std::unique_ptr<GLFWwindow, GlfwWindowDeleter> window;
    if (!glfwInit())
        throw std::runtime_error("Init error");
    window.reset(glfwCreateWindow(800, 600, "Hello", monitor, share));
    if (!window)
        throw std::runtime_error("Window creation error");
    glfwMakeContextCurrent(window.get());
    return window;
}
#endif //GLFWOPENGL_COMMON_H
