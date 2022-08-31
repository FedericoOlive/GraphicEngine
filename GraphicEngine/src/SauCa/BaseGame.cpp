#include "BaseGame.h"
#include "Window.h"
#include "Renderer.h"

#include <glfw3.h>

int BaseGame::Init()
{
        Window* window = new Window();
        Renderer* rend = new Renderer();

        /* Initialize the library */
        window->InitLibrary();

        /* Create a windowed mode window and its OpenGL context */
        window->CreateWindow();
        
        window->CheckWindow(window->GetWindow());

        /* Make the window's context current */
        window->AssignContext(window->GetWindow());

        renderer->CreateShader();
	
        /* Loop until the user closes the window */
        while (!window->WindowShouldClose(window->GetWindow()))
        {
            /* Render here */
            rend->Clear(GL_COLOR_BUFFER_BIT);

            renderer->DrawTriangle();
        	
            /* Swap front and back buffers */
            rend->SwapBuffers(window->GetWindow());

            /* Poll for and process events */
            window->PollEvents();
        }
        renderer->DestroyShader();
        window->TerminateLibrary();

        delete window;
        delete rend;
        return 0;
}