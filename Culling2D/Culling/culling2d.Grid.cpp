#include "culling2d.Grid.h"

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
			delete object;
		}
		
		objects.clear();
	}

	int Grid::GetResolutionLevel()
	{
		return resolutionLevel;
	}

	RectF Grid::GetGridRange()
	{
		return gridRange;
	}

	std::array<int, 4> &Grid::GetChildrenIndices(int index)
	{
		for (int i = 0; i < 4; ++i)
		{
			childrenIndices[i] = 4 * index + i;
		}

		return childrenIndices;
	}

	bool Grid::AddObject(Object* object)
	{
		return objects.insert(object).second;
	}

	bool Grid::RemoveObject(Object* object)
	{
		bool exists = objects.find(object) != objects.end();
		if (exists)
		{
			objects.erase(object);
		}
		return exists;
	}
};