#include "PointLight.h"

PointLight::PointLight()
{
    // position = transform->globalPosition
    ambient = { 0.05f, 0.05f, 0.05f };
    diffuse = { 0.8f, 0.8f, 0.8f };
    specular = { 1.0f, 1.0f, 1.0f };
    lightColor = { 1.0f, 1.0f, 1.0f };

    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
    isEnable = false;
}

void PointLight::OnAsigned()
{
    isEnable = true;
}