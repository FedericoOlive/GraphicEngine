#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "Exports.h"

class Transform;
class GameObject;
class BaseGame;
class Camera;

class SAUCA_API Component
{
protected:
	bool isRenderizable = false;
	bool isLighteable = false;
	
public:
	GameObject* gameobject = nullptr;
	Transform* transform = nullptr;
	bool isEnable = true;
	bool alwaysDraw = false;
	std::string name = "Component";
	
	Component(bool isRenderizable = false);
	virtual ~Component() { }
	virtual void Draw(Camera* camera) { }
	virtual void Update();
	virtual void Input();
	virtual void OnAsigned();
	
	bool IsRenderizable() const { return isRenderizable; }
	bool IsLighteable() const { return isLighteable; }
};

#endif