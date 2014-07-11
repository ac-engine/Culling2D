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

	Grid* World::searchDestinationGrid(Object * object)
	{
		Layer* belongLayer = nullptr;
		int belongIndex = 0;

		for (Layer* layer : layers)
		{
			auto range = layer->GetGrids()[0]->GetGridRange();
			auto radius = object->GetCircle().Radius;
			if (range.Height >= radius&&range.Width >= radius)
			{
				belongLayer = layer;
			}
			else
			{
				break;
			}

			if (layer != layers.back())
			{
				auto position = object->GetCircle().Position;
				auto children = Grid::GetChildrenIndices(belongIndex);
				for (auto gridIndex : children)
				{
					RectF gridRange = (layer + 1)->GetGrids()[gridIndex]->GetGridRange();
					if (gridRange.X <= position.X&&gridRange.Y <= position.Y&&gridRange.X + gridRange.Width >= position.X&&gridRange.Y + gridRange.Height >= position.Y)
					{
						belongIndex = gridIndex;
						break;
					}
				}
			}
		}

		if (belongLayer == nullptr)
		{
			return layers[0]->GetGrids()[0];
		}
		else
		{
			return belongLayer->GetGrids()[belongIndex];
		}
	}

	bool World::AddObject(Object* object)
	{
		auto grid = searchDestinationGrid(object);
		object->SetCurrentRange(grid->GetGridRange());
		return grid->AddObject(object);
	}

	bool World::RemoveObject(Object* object)
	{
		auto grid = searchDestinationGrid(object);
		return grid->RemoveObject(object);
	}
}