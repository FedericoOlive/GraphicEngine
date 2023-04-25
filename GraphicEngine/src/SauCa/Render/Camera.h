#ifndef CAMERA_H
#define CAMERA_H

#include "Exports.h"
#include "GameObjects/Component.h"
#include "glm/glm/gtc/type_ptr.hpp"

class SAUCA_API  Camera : public Component
{
private:
	// Todo: Agregar comportamiento de movimiento (No se actualizan las matrices)
	
public:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	float aspect;
	
	Camera(int width, int height);
	~Camera();

	void SetCameraOrthogonal(int width = 1280, int height = 720, float near = 0.0f, float far = 1000.0f);
	void SetCameraPerspective(float fov = 45.0f, float near = 0.1f, float far = 1000.0f);
	void OnAsigned() override;
	void OnUpdatePosition();
	void UpdateViewMatrix();
};

#endif