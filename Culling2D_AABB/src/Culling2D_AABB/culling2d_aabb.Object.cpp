#include "../Culling2D_AABB.h"

namespace culling2d_aabb
{
	Object::Object(void* userdata, World *worldRef) :
		userData(userdata)
		, worldRef(worldRef)
		, sortedKey(0)
		, isInWorld(true)
	{
		SafeAddRef(worldRef);
		aabb = RectF(0,0,0,0);
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

	const RectF& Object::GetAABB() const
	{
		return aabb;
	}

	void Object::SetAABB(RectF aabb)
	{
		if (this->aabb != aabb)
		{
			this->aabb = aabb;
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
		auto center = aabb.GetPosition() + aabb.GetSize() / 2;

		return currentRange.GetIsContainingPoint(center)
			&& currentRange.Height >= aabb.Height&&currentRange.Width >= aabb.Width;
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
