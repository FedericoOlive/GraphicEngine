#ifndef PRINTINCONSOLE_H
#define PRINTINCONSOLE_H
#include <string>
#include "GameObjects/GameObject.h"
#include "GameObjects/Transform.h"

static class PrintInConsole
{
private:
    static	void ShowHierarchyInConsole(Transform* transf, std::string preText, int depth);

    enum Colors
    {
        ColorLightDisable = 6,
        ColorGameobjectEnable = 7,
        ColorGameobjectDisable = 8,
        ColorComponentRenderizable = 10,
        ColorComponent = 11,
        ColorLightEnable = 14
    };

public:
    static void PrintHierarchyInConsole(std::list<GameObject*> gameobjects); 	
    static std::string AsString(glm::vec3 vec);
    static void PrintComponentsInConsole(GameObject* gameobject, std::string preText);
    static void SetColorColsoleByType();
};
#endif