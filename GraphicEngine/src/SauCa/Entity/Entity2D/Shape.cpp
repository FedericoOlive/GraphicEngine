#include "Shape.h"

Shape::Shape()
{

}

void Shape::Draw()
{
	renderer->DrawShape(sizeIndices, VAO, modelMatrix);
}