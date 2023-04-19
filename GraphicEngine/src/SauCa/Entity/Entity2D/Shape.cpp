#include "Shape.h"

Shape::Shape()
{

}

void Shape::Draw()
{
	renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), NULL, material, alpha);
}