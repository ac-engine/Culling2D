#include "../Culling2D.h"

namespace culling2d
{
	Object::Object(Circle circle, void* userData, World *worldRef, unsigned int id):
		circle(circle),
		userData(userData),
		worldRef(worldRef),
		id(id)
	{
		SafeAddRef(worldRef);
	}

	Object::~Object()
	{
		SafeRelease(worldRef);
	}

	const Circle& Object::GetCircle() const
	{
		return circle;
	}

	void Object::SetCircle(Circle circle)
	{
		if (this->circle != circle)
		{
			this->circle = circle;
			worldRef->NotifyMoved(this);
		}
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

	void Object::SetID(unsigned int id)
	{
		this->id = id;
	}

	unsigned int Object::GetID()
	{
		return id;
	}
};