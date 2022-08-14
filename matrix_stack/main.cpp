#include "common.h"
#include <cmath>

constexpr int steps = 100;

void drawCircle(float r, float g, float b) {
    constexpr float angle = M_PI*2/steps;
    float oldX = 0, oldY = 0, radius = 1.;
    for (int i = 0; i <= steps; i++) {
        float newX = radius * sin(angle * i),
              newY = -radius * cos(angle * i);
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(oldX, oldY);
        glVertex2f(newX, newY);
        glEnd();
        oldX = newX;
        oldY = newY;
    }
}


int main() {
    auto window = create_window("Hello");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(0.1, 0.1, 1);
    float angle = 1, angleMoon = 1;
    while (!glfwWindowShouldClose(window.get())) {
        ++angle;

        glClearColor(1,1,1,0);
        glClear(GL_COLOR_BUFFER_BIT);


        drawCircle(1, 1, 0);

        {
            glPushMatrix();
            glRotatef(angle, 0, 0, 1);
            glTranslatef(0,5,0);
            glScalef(0.6, 0.6, 0);
            drawCircle(0, 0.3, 1);

            {
                angleMoon += 2;
                glPushMatrix();
                glRotatef(angleMoon, 0, 0, 1);
                glTranslatef(0, 2, 0);
                glScalef(0.2, 0.2, 0.2);
                drawCircle(0.2, 0.2, 0.2);
                glPopMatrix();
            }

            glPopMatrix();
        }

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
    return 0;
}
