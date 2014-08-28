#include "culling2d.Object.h"
#include "culling2d.World.h"
#include "../culling2d.ReferenceObject.h"

namespace culling2d
{
	Object::Object(Circle circle, void* userData, World *worldRef):
		circle(circle),
		userData(userData),
		worldRef(worldRef)
	{
		SafeAddRef(worldRef);
	}

	Object::~Object()
	{
		printf("deleted");
		SafeRelease(worldRef);
	}

	const Circle& Object::GetCircle() const
	{
		return circle;
	}

	void Object::SetCircle(Circle circle)
	{
		this->circle = circle;
	}

	const void* Object::GetUserData() const
	{
		return userData;
	}

	void Object::SetUserData(void* userData)
	{
		this->userData = userData;
	}

	RectF Object::GetCurrentRange() const
	{
		return currentRange;
	}

	void Object::SetCurrentRange(RectF range)
	{
		this->currentRange = range;
	}

	bool Object::IsProperPosition() const
	{
		auto position = circle.Position;
		auto radius = circle.Radius;

		return currentRange.X <= position.X&&currentRange.Y <= position.Y&&currentRange.X + currentRange.Width >= position.X&&currentRange.Y + currentRange.Height >= position.Y
			&& currentRange.Height >= radius&&currentRange.Width >= radius;
	}
};