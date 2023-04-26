#include "PrintInConsole.h"
#include <Windows.h>
#include <iostream>

void PrintInConsole::ShowHierarchyInConsole(Transform* transf, std::string preText, int depth)
{
    if (!(depth == 0 && transf->parent != nullptr))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), transf->gameObject->IsActive() ? ColorGameobjectEnable : ColorGameobjectDisable);
        std::cout << preText << "* " << transf->gameObject->name;
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        std::cout << " Pos: " << AsString(transf->GetWorldPosition()) << " Rot: " << AsString(transf->GetWorldRotation()) << " Scale: " << AsString(transf->GetWorldScale()) << "\n";
        PrintComponentsInConsole(transf->gameObject, preText);

        depth++;
        preText += "\t";
        for (auto iter = transf->childrens.begin(); iter != transf->childrens.end(); ++iter)
        {
            ShowHierarchyInConsole((*iter), preText, depth);
        }
    }
	
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void PrintInConsole::PrintHierarchyInConsole(std::list<GameObject*> gameobjects)
{
    std::string preText = "";
    int depth = 0;
    std::cout << "++++++++++ Scene Hierarchy ++++++++++\n";
    for (auto iter = gameobjects.begin(); iter != gameobjects.end(); ++iter)
    {
        ShowHierarchyInConsole((*iter)->transform, preText, depth);
    }
    std::cout << "---------- Scene Hierarchy ----------\n";
}

std::string PrintInConsole::AsString(glm::vec3 vec)
{
    std::string text = "{ " + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + " }";
    return text;
}

void PrintInConsole::PrintComponentsInConsole(GameObject* gameobject, std::string preText)
{
    for (auto iter = gameobject->components.begin(); iter != gameobject->components.end(); ++iter)
    {
        int color = 0;
    	if((*iter)->isEnable)
    	{            
            if ((*iter)->IsRenderizable()) color = ColorComponentRenderizable;            
            else if((*iter)->IsLighteable()) color = ColorLightEnable;            
            else  color = ColorComponent;
    	}
        else
        {
            if ((*iter)->IsRenderizable()) color = ColorComponentRenderizable;
            else if ((*iter)->IsLighteable()) color = ColorLightDisable;
            else  color = ColorComponent;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        std::cout << preText << "\t- " << (*iter)->name << "\n";

    }
}

void PrintInConsole::SetColorColsoleByType()
{
    
}