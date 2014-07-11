#include "culling2d.Object.h"

namespace culling2d
{
	Object::Object(Circle circle, void* userData, World *worldRef):
		circle(circle),
		userData(userData),
		worldRef(worldRef)
	{

	}

	Object::~Object()
	{

	}

	const Circle& Object::GetCircle()
	{
		return circle;
	}

	void Object::SetCircle(Circle circle)
	{
		this->circle = circle;
	}

	const void* Object::GetUserData()
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
};