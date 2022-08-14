#include <iostream>
#include "common.h"

int main() {
    auto window = create_window("Hello");
    bool toggle = false;
    while (!glfwWindowShouldClose(window.get())) {
        glClearColor(1,1,1,0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
    return 0;
}
