#include "Plane.h"
#include <iostream>

Plane::Plane() {}

Plane::Plane(const glm::vec3& p1, const glm::vec3& norm) : normal(glm::normalize(norm)),
distance(glm::dot(normal, p1)) {}

bool Plane::GetSide(glm::vec3 point)
{
	return glm::dot(normal, point) - distance > 0.f;
}

float Plane::GetSignedDistanceToPlane(const glm::vec3& point) const
{
	return glm::dot(normal, point) - distance;
}

void Plane::SetPositionAndNormal(glm::vec3 point, glm::vec3 normal)
{
	this->normal = glm::normalize(normal);
	distance = glm::dot(this->normal, point);
}

glm::vec3 Plane::FindIntersectionPoint2(const Plane& plane1, const Plane& plane2, const Plane& plane3)
{
	// Construir la matriz de coeficientes
	glm::mat3 coefficients(plane1.normal, plane2.normal, plane3.normal);

	// Construir el vector de constantes
	glm::vec3 constants(-plane1.distance, -plane2.distance, -plane3.distance);

	// Calcular la matriz inversa de los coeficientes
	glm::mat3 inverse = glm::inverse(coefficients);

	// Calcular el punto de intersección
	glm::vec3 solution = inverse * constants;

	return solution;
}

glm::vec3 Plane::FindIntersectionPoint(const Plane& plane1, const Plane& plane2, const Plane& plane3)
{
	// Calcular los coeficientes de la ecuación de los tres planos
	float a1 = plane1.normal.x;
	float b1 = plane1.normal.y;
	float c1 = plane1.normal.z;
	float d1 = plane1.distance;

	float a2 = plane2.normal.x;
	float b2 = plane2.normal.y;
	float c2 = plane2.normal.z;
	float d2 = plane2.distance;

	float a3 = plane3.normal.x;
	float b3 = plane3.normal.y;
	float c3 = plane3.normal.z;
	float d3 = plane3.distance;

	// Resolver el sistema de ecuaciones lineales
	float determinant = a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);

	if (std::abs(determinant) < 1e-6)
	{
		// Los planos no se intersectan en un solo punto
		std::cout << "Los planos no se intersectan en un solo punto\n";
		return glm::vec3(NAN, NAN, NAN); // Punto inválido
	}

	// Calcular las coordenadas del punto de intersección
	float x = (b1 * (c2 * d3 - c3 * d2) - c1 * (b2 * d3 - b3 * d2)) / determinant;
	float y = (a1 * (c3 * d2 - c2 * d3) - c1 * (a3 * d2 - a2 * d3)) / determinant;
	float z = (a1 * (b2 * d3 - b3 * d2) - b1 * (a2 * d3 - a3 * d2)) / determinant;

	return { x, y, z };
}