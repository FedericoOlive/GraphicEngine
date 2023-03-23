#ifndef FIRSTPERSON_H
#define FIRSTPERSON_H
#include <glm/glm/vec2.hpp>

#include "GameObjects/Component.h"
#include "Input/KeyCodes.h"

class SAUCA_API FirstPerson : public Component
{
	KeyCode forward = KeyCode::W;
	KeyCode left = KeyCode::A;
	KeyCode back = KeyCode::S;
	KeyCode right = KeyCode::D;
	
	float speedForward = 1.0f;
	float speedLeft = 1.0f;
	float speedBack = 1.0f;
	float speedRight = 1.0f;

	glm::vec2 mouseSensitive = { 0.50f, 0.50f };
	
public:
	FirstPerson();
	~FirstPerson() override;
	void BindMovements(KeyCode forward, KeyCode left, KeyCode back, KeyCode right, float speed);
	void SetSpeedMovements(float speed);
	void SetSpeedMovements(float speedForward, float speedLeft, float speedBack, float speedRight);
	void SetCameraSensitive(float sensitiveX, float sensitiveY);
	void Update() override;
	void Input() override;
	void OnAsigned() override;
	void OnMouseMove(double x, double y);
};

#endif