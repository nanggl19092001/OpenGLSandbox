#pragma once

#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <iostream>


class Window
{
public:
    Window();
    Window(GLuint width, GLuint height);
    Window(GLuint width, GLuint height, const char *wTitle);
    ~Window();

    void initWindow(GLuint width, GLuint height);

    void initGUI();

    void setWindowTitle(const char* windowTitle);

    void setCallbacks();

    void setFrameBufferSizeCallback(GLFWframebuffersizefun callback);

    void setKeyboardInputCallback(GLFWkeyfun callback);

    void setMouseButtonCallback(GLFWmousebuttonfun callback);

    void setCursorPosCallback(GLFWcursorposfun callback);

    GLuint getBufferWidth() { return width; };

    GLuint getBufferHeight() { return height; };

    bool* getKeys() { return this->keys; };

    bool* getMouseButton() { return this->mouseButtons; };

    double getChangedX() 
    { 
        double changed = this->cursorLastDifX;
        this->cursorLastDifX = 0.0f;
        return changed; 
    };

    double getChangedY() 
    { 
        double changed = this->cursorLastDifY;
        this->cursorLastDifY = 0.0f;
        return changed; 
    };

    bool getShouldClose() { return glfwWindowShouldClose(window); };

    void swapBuffer();
private:
    GLFWwindow *window;
    GLuint width, height;

    double cursorLastPosX, cursorLastPosY;
    double cursorLastDifX, cursorLastDifY;

    bool firstMouseMove;

    bool keys[1024];
    bool mouseButtons[8];

    const char* defaultWindowTitle = "Window";

    void initKeys();

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    static void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
}
;


