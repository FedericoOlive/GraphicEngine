#ifndef ENTITY_H
#define ENTITY_H

#include "Exports.h"
#include "Renderer.h"

class SAUCA_API Entity
{
protected:
	Renderer* renderer;
public:
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
	glm::vec3 colorTint;
	float alpha;
	
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

	glm::vec3 GetPosition() { return translate; }
	glm::vec3 GetScale() { return rotation; }
	glm::vec3 GetRotation() { return scale; }
	
};

#endif