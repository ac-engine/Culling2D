#include "../Culling2D.h"

namespace culling2d
{
	const int CHANGE_OBJECT_NUM = 100;
	const float MIN_OBJECT_DIAMETER = 10;

	void World::initQuadtree()
	{
		for (int i = 0; i <= resolution; ++i)
		{
			auto layer = new Layer(i);
			//SafeAddRef(layer);
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
		nextFirstSortedKey(0),
		nextSecondSortedKey(0),
		outOfRangeObjectsCount(0),
		upperLeft_(Vector2DF(0,0)),
		lowerRight_(Vector2DF(0,0)),
		minRadius_(FLT_MAX)
	{
		initQuadtree();
		//initQuadtreeGrids(resolution, worldRange);
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

				upperLeftRaw.X = Max(0, upperLeftRaw.X);
				upperLeftRaw.Y = Max(0, upperLeftRaw.Y);

				lowerRightRaw.X = Min(worldRange.GetSize().X / cellSize.X - 1, lowerRightRaw.X);
				lowerRightRaw.Y = Min(worldRange.GetSize().Y / cellSize.Y - 1, lowerRightRaw.Y);

				upperLeft = Vector2DI((int)floor(upperLeftRaw.X), (int)floor(upperLeftRaw.Y));
				lowerRight = Vector2DI((int)floor(lowerRightRaw.X), (int)floor(lowerRightRaw.Y));
			}

			int xSize = 1 << r;

			for (int x = upperLeft.X; x <= lowerRight.X; ++x)
			{
				for (int y = upperLeft.Y; y <= lowerRight.Y; ++y)
				{
					auto grid = layer->GetGrids()[y*xSize + x];

					grid->GetCullingObjects(cullingRange, tempObjects);
				}
			}
		}
		std::sort(tempObjects.begin(), tempObjects.end(), [](Object* obj1, Object* obj2)
		{
			return obj1->GetSortedKey() < obj2->GetSortedKey();
		});
		return tempObjects;
	}

	void World::Update()
	{
		for (auto improperObject : improperObjects)
		{
			auto grid = mapObjectToGrid[improperObject];
			grid->RemoveObject(improperObject);
			auto newGrid = AddObjectInternal(improperObject);
			assert(newGrid != nullptr);
			mapObjectToGrid[improperObject] = newGrid;
		}

		improperObjects.clear();

#ifdef _DEBUG
		printf("%d\n", outOfRangeObjectsCount);
#endif

		if (outOfRangeObjectsCount >= CHANGE_OBJECT_NUM)
		{
			Vector2DF center = (upperLeft_ + lowerRight_) / 2;
			float diam = Max(lowerRight_.X - upperLeft_.X, lowerRight_.Y - upperLeft_.Y);
			Vector2DF upper = center - Vector2DF(diam, diam) / 2;

			auto obj_diam = Max(minRadius_ * 2, MIN_OBJECT_DIAMETER);

			int res = (int)floor(log2((diam / obj_diam)));

			ResetWorld(res, RectF(upper.X, upper.Y, diam, diam));
		}
	}

	int World::GetResolution() const
	{
		return resolution;
	}

	void World::ResetWorld(int newResolution, RectF newRange)
	{
		outOfRangeObjectsCount = 0;
		std::vector<Object*> objects;
		for (auto& obj : mapObjectToGrid)
		{
			objects.push_back(obj.first);
		}

		for (int i = 0; i < layers.size(); ++i)
		{
			SafeRelease(layers[i]);
		}
		layers.clear();

		resolution = newResolution;
		worldRange = newRange;

		initQuadtree();

		for (auto obj : objects)
		{
			AddObjectInternal(obj);
		}
	}

	RectF World::GetWorldRange() const
	{
		return worldRange;
	}

	Grid* World::searchDestinationGrid(Object * object, bool isInternal)
	{
		Layer* belongLayer = nullptr;
		int nextIndex = 0;
		int belongIndex = 0;

		auto position = object->GetCircle().Position;
		auto diameter = object->GetCircle().Radius * 2;

		for (int currentResolution = 0; currentResolution <= resolution; ++currentResolution)
		{

			auto range = layers[currentResolution]->GetGrids()[nextIndex]->GetGridRange();

			//グリッドの縦横がそれぞれ円の直径を上回っていないか調べる。
			if (range.GetIsContainingPoint(position) && range.Height >= diameter && range.Width >= diameter)
			{
				belongLayer = layers[currentResolution];
				belongIndex = nextIndex;
			}
			else
			{
				break;
			}

			if (currentResolution >= layers.size() - 1)
			{
				continue;
			}

			//次に遷移するレイヤーにおけるグリッドの添字を調べる。
			auto children = Grid::GetChildrenIndices(belongIndex, currentResolution);
			auto nextLayer = layers[currentResolution + 1];
			nextIndex = -1;
			for (auto gridIndex : children)
			{
				RectF gridRange = nextLayer->GetGrids()[gridIndex]->GetGridRange();
				if (gridRange.GetIsContainingPoint(position))
				{
					nextIndex = gridIndex;
					break;
				}
			}

			if (nextIndex == -1)
			{
				break;
			}

		}

		{
			auto& circle = object->GetCircle();
			upperLeft_.X = Min(upperLeft_.X, circle.Position.X);
			upperLeft_.Y = Min(upperLeft_.Y, circle.Position.Y);
			lowerRight_.X = Max(lowerRight_.X, circle.Position.X);
			lowerRight_.Y = Max(lowerRight_.Y, circle.Position.Y);
			minRadius_ = Min(minRadius_, circle.Radius);
		}

		if (belongLayer == nullptr)
		{
			if (object->GetIsInWorld())
			{
				++outOfRangeObjectsCount;
			}

			object->SetIsInWorld(false);

			return layers[0]->GetGrids()[0];
		}
		else
		{
			if (!object->GetIsInWorld())
			{
				--outOfRangeObjectsCount;
			}

			object->SetIsInWorld(true);

			return belongLayer->GetGrids()[belongIndex];
		}
	}

	Grid* World::AddObject(Object* object)
	{
		auto grid = searchDestinationGrid(object, false);
		object->SetCurrentRange(grid->GetGridRange());
		mapObjectToGrid[object] = grid;
		return (grid->AddObject(object)) ? grid : nullptr;
	}

	Grid* World::AddObjectInternal(Object* object)
	{
		auto grid = searchDestinationGrid(object, true);
		object->SetCurrentRange(grid->GetGridRange());
		mapObjectToGrid[object] = grid;
		return (grid->AddObject(object)) ? grid : nullptr;
	}

	bool World::RemoveObject(Object* object)
	{
		if (mapObjectToGrid.find(object) == mapObjectToGrid.end()) return false;

		auto grid = mapObjectToGrid.at(object);
		mapObjectToGrid.erase(object);
		return grid->RemoveObject(object);
	}

	void World::NotifyMoved(Object *object)
	{
		if (!object->IsProperPosition() || !object->GetIsInWorld())
		{
			improperObjects.insert(object);
		}
	}

	void World::ResetNextFirstSortedKey()
	{
		nextFirstSortedKey = 0;
	}

	void World::IncNextFirstSortedKey()
	{
		++nextFirstSortedKey;
	}

	uint32_t World::GetNextFirstSortedKey() const
	{
		return nextFirstSortedKey;
	}

	void World::ResetNextSecondSortedKey()
	{
		nextSecondSortedKey = 0;
	}

	void World::IncNextSecondSortedKey()
	{
		++nextSecondSortedKey;
	}

	uint32_t World::GetNextSecondSortedKey() const
	{
		return nextSecondSortedKey;
	}
}
