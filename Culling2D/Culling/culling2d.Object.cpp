#include "../Culling2D.h"

namespace culling2d
{
	Object::Object(void* userData, World *worldRef):
		userData(userData)
		,worldRef(worldRef)
	{
		SafeAddRef(worldRef);
		circle = culling2d::Circle(culling2d::Vector2DF(0, 0), 0);
	}

	Object::Object(Circle c,void* userData, World *worldRef) :
		  userData(userData)
		, worldRef(worldRef)
		, circle(c)
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