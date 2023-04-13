#ifndef COMPONENT_H
#define COMPONENT_H

#include "Exports.h"

class Transform;
class GameObject;
class BaseGame;

class SAUCA_API Component
{
public:
	GameObject* gameobject = nullptr;
	Transform* transform = nullptr;
	
	bool isRenderizable = false;
	bool isEnable = true;
	
	Component(bool isRenderizable = false);
	virtual ~Component() {} // Destructor virtual
	virtual void Draw(){}
	virtual void Update();
	virtual void Input();
	virtual void OnAsigned();
};

#endif