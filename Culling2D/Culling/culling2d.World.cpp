#include "culling2d.World.h"

namespace culling2d
{
	World::World(int resolution, RectF worldRange) :
		resolution(resolution),
		worldRange(worldRange)
	{

	}

	World::~World()
	{
		for (auto object : objects)
		{
			delete object;
		}
		objects.clear();
	}

	std::vector<Object*> &World::GetCullingObjects(RectF cullingRange)
	{
		for (auto object : objects)
		{
			delete object;
		}
		objects.clear();

		//ここでオブジェクト摘み

		return objects;
	}

	void World::Update()
	{

	}

	int World::GetResolution()
	{
		return resolution;
	}

	int World::RecalculateResolution()
	{
		return resolution;
	}

	RectF World::GetWorldRange()
	{
		return worldRange;
	}

	bool World::AddObject(Object* object)
	{
		return false;
	}

	bool World::RemoveObject(Object* object)
	{
		return false;
	}
}