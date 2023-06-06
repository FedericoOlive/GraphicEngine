#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"

class SAUCA_API GameObject
{
private:
    unsigned static int id;
    bool isActive = true;
    bool isActiveInHierarchy = true;
	
public:
	std::string name;
    GameObject(std::string name = "");
    ~GameObject();
	
    Transform* transform;
    std::list<Component*> components;
    bool IsActive();
    bool IsActiveInHierarch();
    void SetActive(bool isActive);
    void SetActiveInHierarch(bool isActiveInHierarchy);
    void AddComponent(Component* component);
    template<typename T> T* GetComponent();
    template<typename T> void RemoveComponent();
};

#endif