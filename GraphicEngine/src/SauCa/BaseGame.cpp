#include "BaseGame.h"

string BaseGame::version = "1.3.0";
Event<> BaseGame::OnUpdateEvent;
Event<> BaseGame::OnInputEvent;

void BaseGame::BeforeDraw()
{
    renderer->Clear(GL_COLOR_BUFFER_BIT);
}

void BaseGame::Draw()
{
    renderer->Draw();
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
    collisionManager = new CollisionManager();	
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
        window->PollEvents();    	
        timer->Update();

        OnInputEvent.Invoke();
        Inputs();
        OnUpdateEvent.Invoke();
        Update();

        BeforeDraw();
        Draw();
        AfterDraw();
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

Quad* BaseGame::CreateQuad(Material* mat)
{
    Quad* quad = new Quad(renderer,mat);
    return quad;
}

Sprite* BaseGame::CreateSprite(Texture* texture)
{
    Sprite* sprite = new Sprite(texture, renderer);
    return sprite;
}

Cube* BaseGame::CreateCube()
{
    Cube* sprite = new Cube(renderer);
    return sprite;
}

GameObject* BaseGame::CreateGameObject(string name)
{
    GameObject* gameObject = new GameObject(name);
    gameobjects.push_back(gameObject);
    return gameObject;
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

void BaseGame::AddCollision(Entity2D* entity, bool isStatic)
{
    collisionManager->AddToCollisionList(entity, isStatic);
}

TileMap* BaseGame::CreateTileMap(string filePath, string resPath)
{
    TileMap* tileMap = new TileMap(renderer);
    if (tileMap->ImportTileMap(filePath, resPath))
    {
        cout << "TileMap load successfully.\n";
    }
    else
    {
        cout << "TileMap can not load.\n";
    }
    return tileMap;
}

void BaseGame::ShowHierarchyInConsole(Transform* transf, string preText)
{
    std::cout << preText << "* " << transf->gameObject->name << " Pos: " << AsString(transf->GetWorldPosition()) << " Rot: " << AsString(transf->GetWorldRotation()) << " Scale: " << AsString(transf->GetWorldScale()) << "\n";
    preText += "\t";
    for (auto iter = transf->childrens.begin(); iter != transf->childrens.end(); ++iter)
    {
        ShowHierarchyInConsole((*iter), preText);
    }
    if (!transf->childrens.empty())
        std::cout << "\n";
}

void BaseGame::ShowHierarchyInConsole()
{	
    std::string preText = "";
    std::cout << "++++++++++ Scene Hierarchy ++++++++++\n";
    for (auto iter = gameobjects.begin(); iter != gameobjects.end(); ++iter)
    {
        ShowHierarchyInConsole((*iter)->transform, preText);
    }
    std::cout << "---------- Scene Hierarchy ----------\n";
}

std::string BaseGame::AsString(glm::vec3 vec)
{
    std::string text = "{ " + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + " }";
    return text;
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

void BaseGame::UpdateCollisions(TileMap* tileMap)
{
    collisionManager->UpdateCollisionsInTileMap(tileMap);
}