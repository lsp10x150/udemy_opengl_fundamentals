#include <GL/glew.h>
#include "common.h"
#include <iostream>
#include <cmath>

const GLfloat vertices[] = {
        -1.0, -1.0, 0.0,
        1.0, -1.0, 0.0,
        1.0, 1.0, 0.0,
        -1.0, -1.0, 0.0,
        1.0, 1.0, 0.0,
        -1.0, 1.0, 0.0
};

const GLfloat colors[] = {
        0.0, 0.0, 1.0,
        0.0, 1.0, 0.0,
        1.0, 0.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0
};

const GLchar* vertex120 = R"END(
#version 120
attribute vec4 inColor;
attribute vec4 inPosition;
uniform mat4 matrix;
varying vec4 outColor;
void main()
{
    outColor = inColor;
    gl_Position = inPosition * matrix; // *inPosition
}
)END";

const GLchar* fragment120 = R"END(
#version 120
varying vec4 outColor;
void main()
{
    gl_FragColor = outColor;
}
)END";

int main() {
    auto window = create_window("Hello");
    glewInit();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex120, 0);
    glCompileShader(vertexShader);
    GLint compStatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compStatus);
    if (compStatus == GL_FALSE) {
        GLchar message[256];
        glGetShaderInfoLog(vertexShader, 256, nullptr, message);
        std::cout << "vertex shader error: \n" << message << std::endl;
        return 1;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment120, 0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compStatus);
    if (compStatus == GL_FALSE) {
        GLchar message[256];
        glGetShaderInfoLog(fragmentShader, 256, nullptr, message);
        std::cout << "fragment shader error: \n" << message << std::endl;
        return 2;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compStatus);
    if (compStatus == GL_FALSE) {
        GLchar message[256];
        glGetProgramInfoLog(shaderProgram, 256, 0, message);
        std::cout << "shader program error: \n" << message << std::endl;
        return 3;
    }
    glUseProgram(shaderProgram);

    // VBOs
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    GLuint colorsBuffer;
    glGenBuffers(1, &colorsBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint attribPos = glGetAttribLocation(shaderProgram, "inPosition");
    glEnableVertexAttribArray(attribPos);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(attribPos,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);
    GLuint attribCol = glGetAttribLocation(shaderProgram, "inColor");
    glEnableVertexAttribArray(attribCol);
    glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);
    glVertexAttribPointer(attribCol,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);


    GLuint attributeMatrix = glGetUniformLocation(shaderProgram, "matrix");

    float alpha = 0.0;
    while (!glfwWindowShouldClose(window.get())) {
        glClearColor(1,1,1,0);
        glClear(GL_COLOR_BUFFER_BIT);
        float sa = 0.5 * sin(alpha),
              ca = 0.5 * cos(alpha);
        alpha += 0.01;
        const GLfloat matrix[] = {
                sa, -ca, 0, 0,
                ca, sa, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1

        };

        glUniformMatrix4fv(attributeMatrix, 1, GL_FALSE, matrix);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
    return 0;
}
