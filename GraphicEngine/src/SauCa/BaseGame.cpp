#include "BaseGame.h"
#include "Window.h"
#include "Renderer.h"

#include <glfw3.h>

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
	
        /* Loop until the user closes the window */
        while (!window->WindowShouldClose(window->GetWindow()))
        {
            /* Render here */
            renderer->Clear(GL_COLOR_BUFFER_BIT);

            renderer->DrawTriangle();
        	
            /* Swap front and back buffers */
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