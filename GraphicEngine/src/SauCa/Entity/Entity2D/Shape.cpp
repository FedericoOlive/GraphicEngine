#include "Shape.h"

Shape::Shape()
{

}

void Shape::Draw(Camera* camera)
{
	renderer->DrawEntity(vertexData->VAO, vertexData->sizeIndex, transform->GetModelMatrix(), NULL, material, alpha, camera);
}