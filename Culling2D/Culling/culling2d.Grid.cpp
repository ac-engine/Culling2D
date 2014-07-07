#include "culling2d.Grid.h"

namespace culling2d
{
	Grid::Grid(int resolutionLevel, int index, RectF gridRange):
		resolutionLevel(resolutionLevel),
		index(index),
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

	std::array<int, 4> Grid::GetChildrenIndice()
	{
		std::array<int, 4> indice{ { 4 * index, 4 * index + 1, 4 * index + 2, 4 * index + 3 } };

		return indice;
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