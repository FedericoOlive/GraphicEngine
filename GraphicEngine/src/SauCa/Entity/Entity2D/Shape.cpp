#include "Shape.h"

Shape::Shape()
{

}

void Shape::Draw()
{
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, translate);
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	transform = glm::scale(transform, scale);
	transform *= glm::mat4(1.0f) * glm::mat4(1.0f);
	renderer->DrawShape(sizeIndices, VAO, transform);
}