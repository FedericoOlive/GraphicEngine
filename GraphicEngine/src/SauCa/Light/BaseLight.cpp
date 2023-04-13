#include "BaseLight.h"

BaseLight::BaseLight() : Component()
{
	isRenderizable = false;

	ambient = { 0, 0, 0 };
	diffuse = { 0, 0, 0 };
	specular = { 0, 0, 0 };
}