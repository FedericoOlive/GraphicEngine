#include "BaseGame.h"
#include "Window.h"
#include "Renderer.h"
#include <glfw3.h>

#include "Entity/Entity2D/Triangle.h"
void BaseGame::BeforeDraw()
{
    renderer->Clear(GL_COLOR_BUFFER_BIT);
}

void BaseGame::AfterDraw()
{
    renderer->SwapBuffers(window->GetWindow());
}

BaseGame::BaseGame()
{
    input = nullptr;
    window = nullptr;
    renderer = nullptr;
    collisionManager = nullptr;	
}

BaseGame::~BaseGame()
{
    //delete input;
    //delete window;
    //delete renderer;
    //delete collisionManager;
}

int BaseGame::Init()
{
    window = new Window();
    renderer = new Renderer();
    
    window->InitLibrary();
    window->CreateWindow();
    window->CheckWindow(window->GetWindow());
    window->AssignContext(window->GetWindow());

    glewExperimental = GL_TRUE;
    glewInit();
    renderer->CreateShader();
	
    Initialize();
    while (!window->WindowShouldClose(window->GetWindow()))
    {
        Input();
        Update();

        BeforeDraw();
        Draw();
        AfterDraw();
    	
        window->PollEvents();
    }
    DeInitialize();
    
    window->TerminateLibrary();

    delete window;
    delete renderer;
    return 0;
}

Triangle* BaseGame::CreateTriangle()
{
    Triangle* triangle = new Triangle(renderer);
    return triangle;
}

Quad* BaseGame::CreateQuad()
{
    Quad* quad = new Quad(renderer);
    return quad;
}

Sprite* BaseGame::CreateSprite(Texture* texture)
{
    Sprite* sprite = new Sprite(texture, renderer);
    return sprite;
}