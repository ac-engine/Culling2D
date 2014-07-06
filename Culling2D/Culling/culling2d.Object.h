#pragma once
#include "../Common/Math/culling2d.Circle.h"

namespace culling2d
{
	class World;

	class Object
	{
		Circle circle;
		void *userData;
		World *worldRef;
	public:
		const Circle& GetCircle();
		void SetCircle(Circle circle);
		const void* GetUserData();
		void SetUserData(void* userData);
	};
}