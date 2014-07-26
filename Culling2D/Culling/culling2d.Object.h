#pragma once
#include "../Common/Math/culling2d.Circle.h"
#include "../Common/Math/culling2d.RectF.h"

namespace culling2d
{
	class World;
	class Grid;

	class Object
	{
		Circle circle;
		void *userData;
		World *worldRef;

		RectF currentRange;
	public:
		Object(Circle circle, void* userData, World *worldRef);
		~Object();

		const Circle& GetCircle() const;
		void SetCircle(Circle circle);
		const void* GetUserData() const;
		void SetUserData(void* userData);

		RectF GetCurrentRange() const;
		void SetCurrentRange(RectF range);

		bool IsProperPosition();

	};
}