#include "BaseGame.h"
#include "Window.h"
#include "Renderer.h"

#include <glfw3.h>

#include "Entity/Entity2D/Triangle.h"

int BaseGame::Init()
{
    window = new Window();
    renderer = new Renderer();

    /* Initialize the library */
    window->InitLibrary();

    /* Create a windowed mode window and its OpenGL context */
    window->CreateWindow();

    window->CheckWindow(window->GetWindow());

    /* Make the window's context current */
    window->AssignContext(window->GetWindow());

    glewExperimental = GL_TRUE;
    glewInit();

    renderer->CreateShader();
    Triangle* triangle = new Triangle();
    /* Loop until the user closes the window */
    renderer->BindVertex(triangle->vertices, triangle->size);
	
    while (!window->WindowShouldClose(window->GetWindow()))
    {
        /* Render here */
        renderer->Clear(GL_COLOR_BUFFER_BIT);
        //triangle->Draw();
        //renderer->DrawTriangle();
        Draw(triangle);
        renderer->SwapBuffers(window->GetWindow());

        /* Poll for and process events */
        window->PollEvents();
    }
    renderer->DestroyShader();
    window->TerminateLibrary();

    delete window;
    delete renderer;
    return 0;
}

void BaseGame::Draw(Triangle* triangle)
{
    renderer->BindVertex(triangle->vertices, triangle->size);
    renderer->DrawTriangle();
}
