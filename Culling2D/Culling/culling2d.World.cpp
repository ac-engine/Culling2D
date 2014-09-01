#include "culling2d.World.h"
#include "../Common/Math/culling2d.RectI.h"

namespace culling2d
{
	void World::initQuadtree()
	{
		for (int i = 0; i <= resolution; ++i)
		{
			auto layer = new Layer(i);
			SafeAddRef(layer);
			layers.push_back(layer);
			initQuadtreeGrids(i, worldRange);
		}
	}

	void World::initQuadtreeGrids(int layerResolution, RectF range)
	{
		int division = 1 << layerResolution;

		auto cellSize = range.GetSize() / division;
		auto place = range.GetPosition();
		auto firstX = place.X;

		for (int i = 0; i < division; ++i)
		{
			place.X = firstX;
			for (int j = 0; j < division; ++j)
			{
				layers[layerResolution]->AddGrid(new Grid(layerResolution, RectF(place.X, place.Y, cellSize.X, cellSize.Y)));
				place.X += cellSize.X;
			}
			place.Y += cellSize.Y;
		}
	}

	World::World(int resolution, RectF worldRange) :
		resolution(resolution),
		worldRange(worldRange),
		maxResolution(resolution)
	{
		initQuadtree();
		initQuadtreeGrids(resolution, worldRange);
	}

	World::~World()
	{
		for (auto layer : layers)
		{
			SafeDelete(layer);
		}
		layers.clear();
	}

	std::vector<Object*> &World::GetCullingObjects(RectF cullingRange)
	{
		tempObjects.clear();

		for (int r = 0; r <= resolution; ++r)
		{
			auto layer = layers[r];

			auto cellSize = layer->GetGrids()[0]->GetGridRange().GetSize();

			//分解能0の場合はワールド全部を探索
			RectF searchRange = (r != 0) ? RectF(cullingRange.X - cellSize.X / 2, cullingRange.Y - cellSize.Y / 2, cullingRange.Width + cellSize.X, cullingRange.Height + cellSize.Y)
				: layer->GetGrids()[0]->GetGridRange();

			Vector2DI upperLeft;
			Vector2DI lowerRight;

			//カリング対象のグリッド区間絞込
			{
				Vector2DF upperLeftRaw = (searchRange.GetPosition() - worldRange.GetPosition()) / cellSize;
				Vector2DF lowerRightRaw = (searchRange.GetPosition() + searchRange.GetSize() - worldRange.GetPosition()) / cellSize;

				upperLeftRaw.X = max(0, upperLeftRaw.X);
				upperLeftRaw.Y = max(0, upperLeftRaw.Y);

				lowerRightRaw.X = min(worldRange.GetSize().X / cellSize.X - 1, lowerRightRaw.X);
				lowerRightRaw.Y = min(worldRange.GetSize().Y / cellSize.Y - 1, lowerRightRaw.Y);

				upperLeft = Vector2DI((int)floor(upperLeftRaw.X), (int)(floor)(upperLeftRaw.Y));
				lowerRight = Vector2DI((int)floor(lowerRightRaw.X), (int)(floor)(lowerRightRaw.Y));
			}

#ifdef _DEBUG
			printf("R = %d\n", r);
			printf(" UL = %d %d\n", upperLeft.X, upperLeft.Y);
			printf(" LR = %d %d\n", lowerRight.X, lowerRight.Y);
#endif

			int xSize = 1 << r;

			for (int x = upperLeft.X; x <= lowerRight.X; ++x)
			{
				for (int y = upperLeft.Y; y <= lowerRight.Y; ++y)
				{
					auto grid = layer->GetGrids()[y*xSize + x];

					grid->GetCullingObjects(searchRange, tempObjects);
				}
			}
		}

		return tempObjects;
	}

	void World::Update()
	{
		for (auto improperObject : improperObjects)
		{
			auto grid = mapObjectToGrid[improperObject];
			grid->RemoveObject(improperObject);
			auto newGrid = AddObject(improperObject);
			assert(newGrid != nullptr);
			mapObjectToGrid[improperObject] = newGrid;
		}

		improperObjects.clear();
	}

	int World::GetResolution() const
	{
		return resolution;
	}

	int World::RecalculateResolution()
	{
		return resolution;
	}

	RectF World::GetWorldRange() const
	{
		return worldRange;
	}

	Grid* World::searchDestinationGrid(Object * object)
	{
		Layer* belongLayer = nullptr;
		int nextIndex = 0;
		int belongIndex = 0;

		for (int currentResolution = 0; currentResolution <= resolution; ++currentResolution)
		{
			auto range = layers[currentResolution]->GetGrids()[nextIndex]->GetGridRange();
			auto diameter = object->GetCircle().Radius * 2;

			//グリッドの縦横がそれぞれ円の直径を上回っていないか調べる。
			if (range.Height >= diameter && range.Width >= diameter)
			{
				belongLayer = layers[currentResolution];
				belongIndex = nextIndex;
			}
			else
			{
				break;
			}

			//次に遷移するレイヤーにおけるグリッドの添字を調べる。
			if (currentResolution >= layers.size() - 1)
			{
				continue;
			}

			auto position = object->GetCircle().Position;
			auto children = Grid::GetChildrenIndices(belongIndex, currentResolution);
			auto nextLayer = layers[currentResolution + 1];
			for (auto gridIndex : children)
			{
				RectF gridRange = nextLayer->GetGrids()[gridIndex]->GetGridRange();
				if (gridRange.X <= position.X&&gridRange.Y <= position.Y&&gridRange.X + gridRange.Width >= position.X&&gridRange.Y + gridRange.Height >= position.Y)
				{
					nextIndex = gridIndex;
					break;
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

	Grid* World::AddObject(Object* object)
	{
		auto grid = searchDestinationGrid(object);
		object->SetCurrentRange(grid->GetGridRange());
		mapObjectToGrid[object] = grid;
		return (grid->AddObject(object)) ? grid : nullptr;
	}

	bool World::RemoveObject(Object* object)
	{
		auto grid = mapObjectToGrid[object];
		mapObjectToGrid.erase(object);
		return grid->RemoveObject(object);
	}

	void World::NotifyImproperGrid(Object *object)
	{
		improperObjects.insert(object);
	}
}