#include "culling2d.World.h"

namespace culling2d
{
	void World::initQuadtree()
	{
		for (int i = 0; i <= resolution; ++i)
		{
			layers.push_back(new Layer(i));
		}

		initQuadtreeGrids(0, worldRange);
	}

	void World::initQuadtreeGrids(int depth, RectF range)
	{
		if (depth <= resolution)
		{
			layers[depth]->GetGrids().push_back(new Grid(depth, range));

			RectF d1 = RectF(range.X, range.Y, range.Width / 2, range.Height / 2);
			RectF d2 = RectF(range.X + range.Width / 2, range.Y, range.Width / 2, range.Height / 2);
			RectF d3 = RectF(range.X, range.Y + range.Height / 2, range.Width / 2, range.Height / 2);
			RectF d4 = RectF(range.X + range.Width / 2, range.Y + range.Height / 2, range.Width / 2, range.Height / 2);

			initQuadtreeGrids(depth + 1, d1);
			initQuadtreeGrids(depth + 1, d2);
			initQuadtreeGrids(depth + 1, d3);
			initQuadtreeGrids(depth + 1, d4);
		}
	}

	World::World(int resolution, RectF worldRange) :
		resolution(resolution),
		worldRange(worldRange)
	{

		initQuadtree();
		initQuadtreeGrids(0, worldRange);
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