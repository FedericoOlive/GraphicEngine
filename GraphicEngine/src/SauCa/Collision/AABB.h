#ifndef AABB_H
#define AABB_H

#include "Exports.h"
#include <glm/glm.hpp>
#include <array>
#include <glm/ext/scalar_constants.hpp>

//class SAUCA_API AABBOld
//{
//public:
//	glm::vec3 min;
//	glm::vec3 max;
//
//	AABBOld();
//	//AABB(glm::vec3 inCenter, float inExtent) : BoundingVolume{}, center{ inCenter }, extent{ inExtent } {}
//	void BeforeUpdate();
//	void AfterUpdate();
//};

struct Plane
{
	glm::vec3 normal = { 0.f, 1.f, 0.f };	// unit vector
	float     distance = 0.f;				// Distance with origin

	Plane() = default;

	Plane(const glm::vec3& p1, const glm::vec3& norm) : normal(glm::normalize(norm)),
	distance(glm::dot(normal, p1)) {}

	float getSignedDistanceToPlane(const glm::vec3& point) const
	{
		return glm::dot(normal, point) - distance;
	}

	void SetPositionAndNormal(glm::vec3 point, glm::vec3 normal)
	{
		this->normal = glm::normalize(normal);
		distance = glm::dot(this->normal, point);
	}

	// Todo: Pendiente quiero dibujar el frustum con DrawLine para ver y tratar de debugear el error de que se dejan de dibujar 
	glm::vec3 FindIntersectionPoint(const Plane& plane1, const Plane& plane2, const Plane& plane3)
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
			return glm::vec3(NAN, NAN, NAN); // Punto inválido
		}

		// Calcular las coordenadas del punto de intersección
		float x = (b1 * (c2 * d3 - c3 * d2) - c1 * (b2 * d3 - b3 * d2)) / determinant;
		float y = (a1 * (c3 * d2 - c2 * d3) - c1 * (a3 * d2 - a2 * d3)) / determinant;
		float z = (a1 * (b2 * d3 - b3 * d2) - b1 * (a2 * d3 - a3 * d2)) / determinant;

		return { x, y, z };
	}
};

struct Frustum
{
	Plane topFace;
	Plane bottomFace;
	Plane rightFace;
	Plane leftFace;
	Plane farFace;
	Plane nearFace;

	void Update(float fov, float aspect, float far, float near, glm::vec3 camPos, glm::vec3 camForward, glm::vec3 camRight, glm::vec3 camUp)
	{
		float halfheight = far * (glm::tan((fov * .5f) * glm::pi<float>() / 180.f));
		float halfWidth = halfheight * aspect;
		glm::vec3 frontFar = far * camForward;

		nearFace	.SetPositionAndNormal(camPos + near * camForward, camForward);
		farFace		.SetPositionAndNormal(camPos + frontFar, -camForward);
		rightFace	.SetPositionAndNormal(camPos, glm::cross(camUp, frontFar + camRight * halfWidth));
		leftFace	.SetPositionAndNormal(camPos, glm::cross(frontFar - camRight * halfWidth, camUp));
		topFace		.SetPositionAndNormal(camPos, glm::cross(camRight, frontFar - camUp * halfheight));
		bottomFace	.SetPositionAndNormal(camPos, glm::cross(frontFar + camUp * halfheight, camRight));
	}
};

struct BoundingVolume
{
	virtual bool isOnFrustum(const Frustum& camFrustum, const glm::mat4& model, const glm::vec3& rightT, const glm::vec3& upT, const glm::vec3& forwardT) const = 0;

	virtual bool isOnOrForwardPlane(const Plane& plane) const = 0;

	bool isOnFrustum(const Frustum& camFrustum) const
	{
		return (isOnOrForwardPlane(camFrustum.leftFace) &&
				isOnOrForwardPlane(camFrustum.rightFace) &&
				isOnOrForwardPlane(camFrustum.topFace) &&
				isOnOrForwardPlane(camFrustum.bottomFace) &&
				isOnOrForwardPlane(camFrustum.nearFace) &&
				isOnOrForwardPlane(camFrustum.farFace));
	}
};

struct AABB : public BoundingVolume
{
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 center{ 0.f, 0.f, 0.f };
	glm::vec3 extents{ 0.f, 0.f, 0.f };

	AABB(){}
	AABB(const glm::vec3& min, const glm::vec3& max)
		: BoundingVolume{}, center{ (max + min) * 0.5f }, extents{ max.x - center.x, max.y - center.y, max.z - center.z }
	{}

	AABB(const glm::vec3& inCenter, float iI, float iJ, float iK)
		: BoundingVolume{}, center{ inCenter }, extents{ iI, iJ, iK }
	{}
	
	void BeforeUpdate()
	{
		min = glm::vec3(std::numeric_limits<float>::max());
		max = -glm::vec3(std::numeric_limits<float>::max());
	}
	
	void AfterUpdate()
	{
		center = { (max + min) * 0.5f };
		extents = { max.x - center.x, max.y - center.y, max.z - center.z };
	}

	std::array<glm::vec3, 8> getVertice() const
	{
		std::array<glm::vec3, 8> vertice;
		vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
		vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
		vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
		vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
		vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
		vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
		vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
		vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
		return vertice;
	}

	//see https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html
	bool isOnOrForwardPlane(const Plane& plane) const final
	{
		// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
		const float r = extents.x * std::abs(plane.normal.x) + extents.y * std::abs(plane.normal.y) +
			extents.z * std::abs(plane.normal.z);

		return -r <= plane.getSignedDistanceToPlane(center);
	}

	bool isOnFrustum(const Frustum& camFrustum, const glm::mat4& model, const glm::vec3& rightT, const glm::vec3& upT, const glm::vec3& forwardT) const final
	{
		//Get global scale thanks to our transform
		const glm::vec3 globalCenter{ model * glm::vec4(center, 1.f) };

		// Scaled orientation
		const glm::vec3 right = rightT * extents.x;
		const glm::vec3 up = upT * extents.y;
		const glm::vec3 forward = forwardT * extents.z;

		const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

		const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

		const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
			std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

		const AABB globalAABB(globalCenter, newIi, newIj, newIk);

		return (globalAABB.isOnOrForwardPlane(camFrustum.leftFace) &&
			globalAABB.isOnOrForwardPlane(camFrustum.rightFace) &&
			globalAABB.isOnOrForwardPlane(camFrustum.topFace) &&
			globalAABB.isOnOrForwardPlane(camFrustum.bottomFace) &&
			globalAABB.isOnOrForwardPlane(camFrustum.nearFace) &&
			globalAABB.isOnOrForwardPlane(camFrustum.farFace));
	}
};

#endif