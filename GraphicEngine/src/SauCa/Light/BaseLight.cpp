#include "BaseLight.h"

#include "Entity/Entity2D/Triangle.h"
#include "GameObjects/GameObject.h"

BaseLight::BaseLight(Renderer* renderer) : Component()
{
	isRenderizable = false;
	isLighteable = true;
	this->renderer = renderer;
	
	ambient = { 0, 0, 0 };
	diffuse = { 0, 0, 0 };
	specular = { 0, 0, 0 };
}

void BaseLight::OnAsigned()
{
	isEnable = true;
	gameobject->AddComponent(new Triangle(renderer, true));
}