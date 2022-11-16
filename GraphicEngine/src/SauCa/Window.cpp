#include "Window.h"
float Window::Screen_Width = 1280;
float Window::Screen_Height = 720;

Window::Window()
{
    window = nullptr;
}

Window::~Window()
{
    //delete window;
}

int Window::InitLibrary()
{
    if (!glfwInit())
        return -1;
}

void Window::CreateWindow()
{
    window = glfwCreateWindow(Screen_Width, Screen_Height, "Hello World", NULL, NULL);
}

int Window::CheckWindow(GLFWwindow* window)
{
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
}

void Window::AssignContext(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
}

bool Window::WindowShouldClose(GLFWwindow* window)
{
    return glfwWindowShouldClose(window);
}

void Window::TerminateLibrary()
{
    glfwTerminate();
}

void Window::PollEvents()
{
    glfwPollEvents();
}

GLFWwindow* Window::GetWindow()
{
    return window;
}
