#include "window.hpp"

Window::Window()
{
    this->width = 1024;
    this->height = 720;
    this->initWindow(this->width, this->height);
    this->setWindowTitle(this->defaultWindowTitle);
    this->initKeys();
}

Window::Window(GLuint width, GLuint height)
{
    this->initWindow(width, height);
    this->setWindowTitle(this->defaultWindowTitle);
    this->initKeys();
}

Window::Window(GLuint width, GLuint height, const char *wTitle)
{
    this->initWindow(width, height);
    this->setWindowTitle(wTitle);
    this->initKeys();
}

Window::~Window()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Window::initWindow(GLuint width, GLuint height)
{
    this->width = width;
    this->height = height;

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1024, 720, "Title", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        return;
    }

    glfwSetWindowUserPointer(this->window, this);
}

void Window::initGUI()
{

}

void Window::setWindowTitle(const char *windowTitle)
{
    glfwSetWindowTitle(window, windowTitle);
}

void Window::initKeys()
{
    for (size_t i = 0; i < 1024; i++)
    {
        this->keys[i] = false;
    }
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    Window *windowInstance = static_cast<Window *>(glfwGetWindowUserPointer(window));

    glViewport(0, 0, windowInstance->width, windowInstance->height);
}

void Window::inputCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Window *windowInstance = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(windowInstance->window, GLFW_TRUE);
    }

    if (key >= 0 && key <= 1024)
    {
        if (action == GLFW_PRESS)
        {
            windowInstance->keys[key] = true;
        }

        if (action == GLFW_RELEASE)
        {
            windowInstance->keys[key] = false;
        }
    }
}

void Window::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    Window *windowInstance = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            glfwSetInputMode(windowInstance->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            windowInstance->mouseButtons[GLFW_MOUSE_BUTTON_RIGHT] = true;
        }
        if (action == GLFW_RELEASE)
        {
            glfwSetInputMode(windowInstance->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            windowInstance->mouseButtons[GLFW_MOUSE_BUTTON_RIGHT] = false;
        }
    }
    
}

void Window::cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    Window *windowInstance = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (windowInstance->firstMouseMove)
    {
        windowInstance->cursorLastPosX = xpos;
        windowInstance->cursorLastPosY = ypos;
        windowInstance->firstMouseMove = false;
    }
    
    windowInstance->cursorLastDifX = xpos - windowInstance->cursorLastPosX;
    windowInstance->cursorLastDifY = windowInstance->cursorLastPosY - ypos;

    windowInstance->cursorLastPosX = xpos;
    windowInstance->cursorLastPosY = ypos;
}

void Window::setCallbacks()
{
    this->setFrameBufferSizeCallback(framebufferSizeCallback);
    this->setKeyboardInputCallback(inputCallback);
    this->setMouseButtonCallback(mouseButtonCallback);
    this->setCursorPosCallback(cursorPosCallback);
}

void Window::setFrameBufferSizeCallback(GLFWframebuffersizefun callback)
{
    glfwSetFramebufferSizeCallback(this->window, callback);
}

void Window::setKeyboardInputCallback(GLFWkeyfun callback)
{
    glfwSetKeyCallback(this->window, callback);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(this->window, callback);
}

void Window::setCursorPosCallback(GLFWcursorposfun callback)
{
    glfwSetCursorPosCallback(this->window, callback);
};

void Window::swapBuffer()
{
    glfwSwapBuffers(this->window);
}