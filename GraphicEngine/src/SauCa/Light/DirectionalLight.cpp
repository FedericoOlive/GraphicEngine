#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Renderer* renderer): BaseLight(renderer)
{
	name = "Directionl Light";
	ambient = {0.05f, 0.05f, 0.05f};
	diffuse = {0.4f, 0.4f, 0.4f};
	specular = {0.5f, 0.5f, 0.5f};
	lightColor = {1.0f, 1.0f, 1.0f};
}
