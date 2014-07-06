#pragma once
#include "../Common/Math/culling2d.RectF.h"
#include <array>

namespace culling2d
{
	class Grid
	{
		int resolutionLevel;
		RectF gridRange;
		int index;
	public:
		Grid(int resolutionLevel, int index, RectF gridRange);
		~Grid();
		int GetResolutionLevel();
		RectF GetGridRange();
		std::array<int,4> GetChildrenIndice();
	};
}