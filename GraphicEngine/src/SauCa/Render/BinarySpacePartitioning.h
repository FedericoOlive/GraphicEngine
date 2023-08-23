#ifndef BSP_H
#define BSP_H
#include "Exports.h"
#include "GameObjects/GameObject.h"

class SAUCA_API BinarySpacePartitioning
{
private:
	static Transform* target;
	static std::list<Transform*> planes;
	static bool SameSide(Transform* entity, Transform* plane);

public:
	static bool isEnable;
	static void SetTarget(Transform* newTarget);
	static void AddPlane(Transform* plane);
	static bool IsDraweable(Transform* entity);
};
#endif