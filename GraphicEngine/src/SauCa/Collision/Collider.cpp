#include "Collider.h"

#include "Renderer.h"
#include "GameObjects/Transform.h"

Collider::Collider()
{
	name = "Collider";
	lineWidth = 2.0f;
	color = { 0.0f, 1.0f, 0.0f };
	isCollision = false;
	isRenderizable = true;
}

Collider::~Collider()
{
	
}

void Collider::Draw(Camera* camera)
{
	Renderer::DrawCubeLines(transform->aabbGlobal, lineWidth, color, camera);
}

void Collider::Update()
{
	
}

void Collider::Input()
{
	
}

void Collider::OnAsigned()
{

}