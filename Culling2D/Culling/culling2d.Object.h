#pragma once
#include "../Common/Math/culling2d.Circle.h"
#include "../Common/Math/culling2d.RectF.h"
#include "../culling2d.ReferenceObject.h"

namespace culling2d
{
	class World;
	class Grid;

	class Object
		:public ReferenceObject
	{
		Circle circle;
		void *userData;
		World *worldRef;

		RectF currentRange;
		unsigned int id;
	public:
		Object(Circle circle, void* userData, World *worldRef,unsigned int id);
		~Object();

		const Circle& GetCircle() const;
		void SetCircle(Circle circle);
		const void* GetUserData() const;
		void SetUserData(void* userData);

		RectF GetCurrentRange() const;
		void SetCurrentRange(RectF range);

		bool IsProperPosition() const;

		void SetID(unsigned int id);
		unsigned int GetID();
	};
}