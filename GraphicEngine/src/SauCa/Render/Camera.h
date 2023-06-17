#ifndef CAMERA_H
#define CAMERA_H
#include <list>

#include "Exports.h"
#include "Collision/AABBOld.h"
#include "GameObjects/Component.h"
#include "glm/gtc/type_ptr.hpp"

class SAUCA_API  Camera : public Component
{
public:
	enum CameraType { Perspective, Orthogonal };
	
private:
	CameraType cameraType = Perspective;
	float cameraZoom = 1;
	
public:
	float aspect;
	float fov;
	float near;
	float far;
	bool autoAddGameObjects = true;
	bool isDrawSkybox = true;
	Frustum* frustum;
	std::list<Component*> cameraRenderList;
	
	glm::vec2 viewportPosition;
	glm::vec2 viewportSize;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	
	Camera(glm::vec2 viewportPosition, glm::vec2 viewportSize, CameraType cameraType = Perspective);
	~Camera();
	void BeginDraw();
	void SetCameraOrthogonal(float near = 0.1f, float far = 1000.0f);
	void SetCameraPerspective(float fov = 45.0f, float near = 0.1f, float far = 1000.0f);
	void OnAsigned() override;
	void OnUpdatePosition();
	void UpdateViewMatrix();
	void SetFov(float fov);
	void SetZoom(float cameraZoom, float fov = 45.0f);
	void SetCameraType(CameraType cameraType);
	float GetZoom() const { return cameraZoom; }
};

#endif