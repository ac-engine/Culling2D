#include "../Culling2D.h"
#include "../../culling2d_common/src/Culling2DCommon.h"

namespace culling2d
{
	Object::Object(void* userdata, World *worldRef) :
		userData(userdata)
		, worldRef(worldRef)
		, sortedKey(0)
		, isInWorld(true)
	{
		SafeAddRef(worldRef);
		circle = culling2d::Circle(culling2d::Vector2DF(0, 0), 0);
	}

	bool Object::GetIsInWorld() const
	{
		return isInWorld;
	}

	void Object::SetIsInWorld(bool isinworld)
	{
		isInWorld = isinworld;
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
		isInWorld = range.GetIsContainingPoint(circle.Position);
	}

	bool Object::IsProperPosition() const
	{
		auto position = circle.Position;
		auto diameter = circle.Radius * 2;

		return currentRange.GetIsContainingPoint(position)
			&& currentRange.Height >= diameter&&currentRange.Width >= diameter;
	}

	void Object::SetSecondSortedKey(uint32_t secondKey)
	{
		uint64_t conv = secondKey;
		sortedKey |= conv;
	}

	uint32_t Object::GetSecondSortedKey()
	{
		uint64_t mask = 0x00000000ffffffff;
		uint64_t conv = sortedKey & mask;

		return (uint32_t)conv;
	}

	void Object::SetFirstSortedKey(uint32_t firstKey)
	{
		uint64_t conv = firstKey;
		conv <<= 32;
		sortedKey |= conv;
	}

	uint32_t Object::GetFirstSortedKey()
	{
		uint64_t mask = 0xffffffff00000000;
		uint64_t conv = sortedKey & mask;

		return (uint32_t)(conv >> 32);
	}


	Object* Object::Create(void *userdata, World* worldRef)
	{
		return new Object(userdata, worldRef);
	}

	uint64_t Object::GetSortedKey() const
	{
		return sortedKey;
	}

};
