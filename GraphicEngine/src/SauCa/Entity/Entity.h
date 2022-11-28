#ifndef ENTITY_H
#define ENTITY_H

#include "Renderer.h"
#include "Entity2D/Material.h"

class SAUCA_API Entity
{
protected:
	Renderer* renderer;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	glm::mat4 modelMatrix;
	glm::mat4 translateMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::vec3 translate;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	float alpha;
	Material* material;

	Entity();
	void SetModelMatrix();

	void SetColorTint(float r, float g, float b, float a);
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z, bool time);

	void SetColorTint(glm::vec4 tint) { SetColorTint(tint.r, tint.g, tint.b, tint.a); }
	
	void SetPosition(glm::vec3 pos) { SetPosition(pos.x, pos.y, pos.z); }
	void SetScale(glm::vec3 scale) { SetScale(scale.x, scale.y, scale.z); }
	void SetRotation(glm::vec3 rot, bool time) { SetRotation(rot.x, rot.y, rot.z, time); }

	Entity* Move(glm::vec3 pos);
	Entity* Move(float x, float y, float z);
	
	glm::vec3 GetPosition() { return translate; }
	glm::vec3 GetScale() { return scale; }
	glm::vec3 GetRotation() { return rotation; }

	glm::vec3 GetViewportPosition();

	void AddCollision();
};

#endif