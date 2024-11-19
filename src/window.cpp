#include "window.hpp"

Window::Window()
{
    this->width = 1024;
    this->height = 720;
}

Window::Window(GLuint width, GLuint height)
{
    this->initWindow(width, height);
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
}

void Window::setWindowTitle(const char *windowTitle)
{
    glfwSetWindowTitle(window, windowTitle);
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

void Window::swapBuffer()
{
    glfwSwapBuffers(this->window);
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}