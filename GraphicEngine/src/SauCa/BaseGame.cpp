#include "BaseGame.h"
string BaseGame::version = "0.5.0";

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
    timer = nullptr;
}

BaseGame::~BaseGame()
{
    if (input != nullptr)
    {
		delete input;
        input = nullptr;
    }
    if (window != nullptr)
    {
        delete window;
        window = nullptr;
    }
    if (renderer != nullptr)
    {
        delete renderer;
        renderer = nullptr;
    }
    if (collisionManager != nullptr)
    {
        delete collisionManager;
        collisionManager = nullptr;
    }
    if (timer != nullptr)
    {
        delete timer;
        timer = nullptr;
    }
}

int BaseGame::Init()
{
    window = new Window();
    renderer = new Renderer();
    input = new Input();
    timer = new Timer();
	
    window->InitLibrary();
    window->CreateWindow();
    window->CheckWindow(window->GetWindow());
    window->AssignContext(window->GetWindow());
    renderer->CreateRenderer();
    
    LoadInfo();

    renderer->CreateShader();
    input->InitInput(window);
    
    Initialize();
    while (!window->WindowShouldClose(window->GetWindow()))
    {
        timer->Update();
        Inputs();
        Update();
        
        BeforeDraw();
        Draw();
        AfterDraw();
    	
        window->PollEvents();
    }
    DeInitialize();
    
    window->TerminateLibrary();

    
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

bool BaseGame::IsKeyReleased(KeyCode keyCode)
{
    return input->IsKeyReleased(keyCode);
}

bool BaseGame::IsKeyDown(KeyCode keyCode)
{
    return input->IsKeyDown(keyCode);
}

bool BaseGame::IsKeyPressed(KeyCode keyCode)
{
    return input->IsKeyPressed(keyCode);
}

int BaseGame::GetKey()
{
    return input->GetKey();
}

double BaseGame::DeltaTime()
{
    return Timer::DeltaTime();
}

double BaseGame::ElapsedTime()
{
    return timer->ElapsedTime();
}

void BaseGame::ModifyWindow(const char* name, float width, float height)
{
    //Window::Screen_Height = height;
    //Window::Screen_Width = width;
    //
    //glViewport(0, 0, width, height);
    //glfwSetWindowTitle(window->GetWindow(), name);
}

void BaseGame::LoadInfo()
{
    int width = 0, height = 0;
    glfwGetWindowSize(window->GetWindow(), &width, &height);
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    string dataTab = "Data: \t > ";
    std::cout << "Data: Initialize SauCa " << version << "\n";
    std::cout << dataTab << "Display Size:    " << width << " x " << height << "\n";
    std::cout << dataTab << "Screen Size:     " << mode->width << " x " << mode->height << "\n";
    std::cout << dataTab << "Render Size:     " << mode->width << " x " << mode->height << "\n";
    std::cout << dataTab << "Viewport Offset: " << "0, 0" << "\n";
    std::cout << "\n";

    std::cout << "Data: OpenGL device information:\n";
    std::cout << dataTab << "Device:   " << glGetString(GL_VENDOR) << "\n";
    std::cout << dataTab << "Version:  " << glGetString(GL_VERSION) << "\n";
    std::cout << dataTab << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << dataTab << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    std::cout << "\n";
}