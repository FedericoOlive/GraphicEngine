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
	
public:
	std::string name;
    bool isActive = true;
    GameObject(std::string name = "");
    ~GameObject();
	
    Transform* transform;	
    std::vector<Component*> components;
	
    void AddComponent(Component* component);
    template<typename T> T* GetComponent();
    template<typename T> void RemoveComponent();
};

#endif