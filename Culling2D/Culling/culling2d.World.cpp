#include "culling2d.World.h"
#include "../Common/Math/culling2d.RectI.h"

namespace culling2d
{
	void World::initQuadtree()
	{
		for (int i = 0; i <= resolution; ++i)
		{
			layers.push_back(new Layer(i));
			initQuadtreeGrids(i, worldRange);
		}
	}

	void World::initQuadtreeGrids(int layerResolution, RectF range)
	{
		int division = (int)pow(2, layerResolution);

		Vector2DF cellSize = range.GetSize() / division;
		Vector2DF place = range.GetPosition();

		for (int i = 0; i < division; ++i)
		{
			place.X = 0;
			for (int j = 0; j < division; ++j)
			{
				layers[layerResolution]->GetGrids().push_back(new Grid(layerResolution, RectF(place.X, place.Y, cellSize.X, cellSize.Y)));
				place.X += cellSize.X;
			}
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

		int currentResolution = 0;
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
				auto children = Grid::GetChildrenIndices(belongIndex, currentResolution);
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
			++currentResolution;
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