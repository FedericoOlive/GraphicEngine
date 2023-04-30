#include "Window.h"
#include <iostream>

float Window::Screen_Width = 1280;
float Window::Screen_Height = 720;
bool Window::isLocked = false;
GLFWwindow* Window::window = nullptr;

Window::Window()
{
    windowBaseName = "No Name";
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
    windowBaseName = "Hello World";
    window = glfwCreateWindow(Screen_Width, Screen_Height, windowBaseName.c_str(), NULL, NULL);
}

void Window::SetWindowTitle(std::string newTitle)
{
    windowBaseName = newTitle;
    glfwSetWindowTitle(window, windowBaseName.c_str());
}

void Window::AddStringToNameWindow(std::string stringToAdd) const
{
    glfwSetWindowTitle(window, (windowBaseName + "  " + stringToAdd).c_str());
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

void Window::LockCursor(bool enable)
{
    isLocked = enable;
    if (enable)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}