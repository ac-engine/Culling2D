#include "culling2d.Grid.h"

namespace culling2d
{
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

	std::array<int, 4> Grid::GetChildrenIndices(int index)
	{
		std::array<int, 4> indices{ { 4 * index, 4 * index + 1, 4 * index + 2, 4 * index + 3 } };

		return indices;
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