#pragma once

#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <iostream>

class Window
{
public:
    Window();
    Window(GLuint width, GLuint height);
    ~Window();

    void initWindow(GLuint width, GLuint height);

    void setWindowTitle(const char* windowTitle);

    void setFrameBufferSizeCallback(GLFWframebuffersizefun callback);

    void setKeyboardInputCallback(GLFWkeyfun callback);

    void setMouseButtonCallback(GLFWmousebuttonfun callback);

    GLuint getBufferWidth() { return width; };

    GLuint getBufferHeight() { return height; };

    bool getShouldClose() { return glfwWindowShouldClose(window); };

    void swapBuffer();
private:
    GLFWwindow *window;
    GLuint width, height;

    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

}
;


