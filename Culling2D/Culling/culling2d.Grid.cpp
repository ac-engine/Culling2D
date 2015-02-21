#include "../Culling2D.h"

namespace culling2d
{
	std::array<int, 4> Grid::childrenIndices;

	Grid::Grid(int resolutionLevel, RectF gridRange):
		resolutionLevel(resolutionLevel),
		gridRange(gridRange)
	{

	}

	Grid::~Grid()
	{
		for(auto object : objects)
		{
			SafeRelease(object);
		}
		
		objects.clear();
	}

	int Grid::GetResolutionLevel() const
	{
		return resolutionLevel;
	}

	RectF Grid::GetGridRange() const
	{
		return gridRange;
	}

	std::array<int, 4> &Grid::GetChildrenIndices(int index, int currentResolution)
	{
		int ro = 1 << currentResolution;
		int iox = index % ro;
		int ioy = index / ro;

		int inx = iox << 1;
		int iny = ioy << 1;

		int rn = ro << 1;

		childrenIndices[0] = inx + rn*iny;
		childrenIndices[1] = inx + 1 + rn*iny;
		childrenIndices[2] = inx + rn*(iny + 1);
		childrenIndices[3] = inx + 1 + rn*(iny + 1);

		return childrenIndices;
	}

	bool Grid::AddObject(Object* object)
	{
		bool inserted = objects.insert(object).second;
		if (inserted)
		{
			SafeAddRef(object);
		}
		return inserted;
	}

	bool Grid::RemoveObject(Object* object)
	{
		bool exists = objects.find(object) != objects.end();
		if (exists)
		{
			objects.erase(object);
			SafeRelease(object);
		}
		return exists;
	}

	int Grid::GetCullingObjects(RectF cullingRange, std::vector<Object*> &cullingObjects)
	{
		int count = 0;
		for (auto object : objects)
		{
			if (cullingRange.GetCollision(object->GetCircle()))
			{
				//SafeAddRef(object);
				cullingObjects.push_back(object);
				++count;
			}
		}
		return count;
	}
};
