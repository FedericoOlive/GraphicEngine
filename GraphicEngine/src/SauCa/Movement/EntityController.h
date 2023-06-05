#ifndef FIRSTPERSON_H
#define FIRSTPERSON_H
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "GameObjects/Component.h"
#include "Input/KeyCodes.h"
#include "Render/Camera.h"

class SAUCA_API EntityController : public Component
{
protected:
	KeyCode forward = KeyCode::W;
	KeyCode left = KeyCode::A;
	KeyCode back = KeyCode::S;
	KeyCode right = KeyCode::D;

	glm::vec3 direction = { 0, 0, 0};
	
	float speedForward = 1.0f;
	float speedLeft = 1.0f;
	float speedBack = 1.0f;
	float speedRight = 1.0f;

	bool rotateX = true;
	bool rotateY = true;
	glm::vec2 mouseSensitive = { 0.50f, 0.50f };
	GameObject* target;

public:
	float maxVerticalAngle = 45;
	float minVerticalAngle = -45;
	bool lockDirectionByLockCursor = true;
	
	EntityController();
	~EntityController() override;
	void BindMovements(KeyCode forward, KeyCode left, KeyCode back, KeyCode right, float speed);
	void SetSpeedMovements(float speed);
	void SetSpeedMovements(float speedForward, float speedLeft, float speedBack, float speedRight);
	void SetCameraSensitive(float sensitiveX, float sensitiveY);
	void Update() override;
	void Input() override;
	void OnAsigned() override;
	void OnMouseMove(double x, double y);
	void RemoveMovement(bool foward = true, bool left = true, bool back = true, bool right = true);
	void RemoveRotation(bool xAxis = true, bool yAxis = true);	
};

#endif