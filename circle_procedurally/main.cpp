#include <GLFW/glfw3.h>
#include <cmath>
#include "common.h"
constexpr int steps = 100;
constexpr float angle = M_PI * 2. / steps;

int main() {
    auto window = create_window("Circle");
    float xPos = 0, yPos = 0, radius = 1;
    while (!glfwWindowShouldClose(window.get())) {
        glClearColor(1,1,1,0);
        glClear(GL_COLOR_BUFFER_BIT);

        float prevX = xPos,
              prevY = yPos - radius;
        for (int i = 0; i <= steps; i++) {
            float newX = radius * sin(angle*i),
                  newY = -radius * cos(angle*i);
            glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            glVertex2d(0,0);
            glVertex2d(prevX,prevY);
            glVertex2d((prevX = newX),(prevY = newY));
            glEnd();
        }

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
    return 0;
}
