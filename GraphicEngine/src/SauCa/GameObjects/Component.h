#ifndef COMPONENT_H
#define COMPONENT_H

#include "Exports.h"

class Transform;
class GameObject;

class SAUCA_API Component
{
public:
	GameObject* gameobject = nullptr;
	Transform* transform = nullptr;
	
	bool isRenderizable = false;
	bool isEnable = true;
	
	Component(bool isRenderizable = false); // Destructor virtual
	virtual ~Component() {} // Destructor virtual
	virtual void Draw(){}
};

#endif