#include "Shape.h"

Shape::Shape()
{

}

void Shape::Draw()
{
	renderer->DrawEntity2D(NULL, sizeIndices, VAO, material, alpha, modelMatrix);
}