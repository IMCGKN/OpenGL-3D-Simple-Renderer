#include "Window.h"

#include "Prerequisites.h"

void Window::Init(int w, int h, const std::string& title)
{
    width = w;
    height = h;
    if (!glfwInit())
        ERROR("Window", "Failed to Initialize GLFW.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
        ERROR("Window", "Failed to create GLFWwindow.");
    }

    INFO("Window", "Succesfully create GLFWwindow. Width: " << width << ", Height: " << height);

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        ERROR("Window", "Failed to load GLAD.");

    INFO("Window", "GPU: " << (char*)glGetString(GL_RENDERER));
    INFO("Window", "Vendor: " << (char*)glGetString(GL_VENDOR));
    INFO("Window", "Version: " << (char*)glGetString(GL_VERSION));

    glViewport(0, 0, width, height);
}

void Window::Destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::GetMousePos(double* x, double* y)
{
    glfwGetCursorPos(window, x, y);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::Input()
{
    glfwPollEvents();

    if (IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Window::CalculateDeltaTime()
{
    float newFrame = glfwGetTime();
    deltaTime = newFrame - lastFrame;
    lastFrame = newFrame;
}

float Window::GetAspectRatio() const
{
    return (float)width / (float)height;
}

float Window::GetDeltaTime() const
{
    return deltaTime;
}

int Window::GetWidth() const
{
    return width;
}

int Window::GetHeight() const
{
    return height;
}

bool Window::IsOpen() const
{
    return !glfwWindowShouldClose(window);
}

bool Window::IsKeyPressed(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}
