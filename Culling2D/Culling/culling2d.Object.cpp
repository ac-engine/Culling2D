#include "../Culling2D.h"

namespace culling2d
{
	Object::Object(void* userdata, World *worldRef):
		userData(userdata)
		,worldRef(worldRef)
		, strongID(0)
		, id(0)
	{
		SafeAddRef(worldRef);
		circle = culling2d::Circle(culling2d::Vector2DF(0, 0), 0);
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

	void* Object::GetUserData() const
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

	void Object::SetID(unsigned long id)
	{
		this->id = id;
	}

	unsigned long Object::GetID() const
	{
		return id;
	}

	void Object::SetStrongID(int strongID)
	{
		this->strongID = strongID;
	}

	int Object::GetStrongID() const
	{
		return strongID;
	}


	Object* Object::Create(void *userdata, World* worldRef)
	{
		return new Object(userdata, worldRef);
	}
};