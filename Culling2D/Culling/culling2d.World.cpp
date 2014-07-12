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
		for (auto layer : layers)
		{
			delete layer;
		}
		layers.clear();
	}

	std::vector<Object*> &World::GetCullingObjects(RectF cullingRange)
	{
		tempObjects.clear();

		for (int i = 0; i <= resolution; ++i)
		{
			auto layer = layers[i];

			auto cellSize = layer->GetGrids()[0]->GetGridRange().GetSize();

			RectF searchRange = RectF(cullingRange.X - cellSize.X / 2, cullingRange.Y - cellSize.Y / 2, cullingRange.Width + cellSize.X, cullingRange.Height + cellSize.Y);

			Vector2DI upperLeft;
			Vector2DI lowerRight;

			//カリング対象のグリッド区間絞込
			{
				Vector2DF upperLeftRaw = (searchRange.GetPosition() - worldRange.GetPosition()) / cellSize;
				Vector2DF lowerRightRaw = (searchRange.GetPosition() + searchRange.GetSize() - worldRange.GetPosition()) / cellSize;

				upperLeftRaw.X = max(0, upperLeftRaw.X);
				upperLeftRaw.Y = max(0, upperLeftRaw.Y);

				lowerRightRaw.X = min(worldRange.GetSize().X, lowerRightRaw.X);
				lowerRightRaw.Y = min(worldRange.GetSize().Y, lowerRightRaw.Y);

				upperLeft = Vector2DI((int)floor(upperLeftRaw.X), (int)(floor)(upperLeftRaw.Y));
				lowerRight = Vector2DI((int)floor(lowerRightRaw.X), (int)(floor)(lowerRightRaw.Y));
			}

			int xSize = 2 << resolution;

			for (int j = upperLeft.X; j <= lowerRight.X; ++j)
			{
				for (int k = upperLeft.Y; k <= lowerRight.Y; ++k)
				{
					auto grid = layer->GetGrids()[k*xSize + j];

					grid->GetCullingObjects(searchRange, tempObjects);
				}
			}
		}

		return tempObjects;
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