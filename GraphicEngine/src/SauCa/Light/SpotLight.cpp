#include "SpotLight.h"

#include <glm/glm/trigonometric.hpp>

SpotLight::SpotLight()
{
    // lightingShader.setVec3("spotLight.position", camera.Position);   ???
    // lightingShader.setVec3("spotLight.direction", camera.Front);     ???
	
    ambient = { 0.0f, 0.0f, 0.0f };
    diffuse = { 1.0f, 1.0f, 1.0f };
    specular = { 1.0f, 1.0f, 1.0f };
    lightColor = { 1.0f, 1.0f, 1.0f };
	
    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
    cutOff = 12.5f;
    outerCutOff = 15.0f;
	
    isEnable = false;
}

void SpotLight::OnAsigned()
{
    isEnable = true;
}