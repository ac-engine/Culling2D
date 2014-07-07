#pragma once
#include "../Common/Math/culling2d.RectF.h"
#include "culling2d.Object.h"
#include <vector>
#include <array>

namespace culling2d
{
	class Grid
	{
		int resolutionLevel;
		RectF gridRange;
		int index;
		std::set<Object*> objects;
	public:
		Grid(int resolutionLevel, int index, RectF gridRange);
		~Grid();
		int GetResolutionLevel();
		RectF GetGridRange();
		std::array<int,4> GetChildrenIndice();
		
		bool AddObject(Object* object);
		bool RemoveObject(Object* object);
	};
}