#pragma once
#include "../Common/Math/culling2d.RectF.h"
#include <array>

namespace culling2d
{
	class Grid
	{
		int resolutionLevel;
		RectF gridRange;

	public:
		Grid(int resolutionLevel, RectF gridRange);
		~Grid();
		int GetResolutionLevel();
		RectF GetGridRange();
		std::array<int,4> GetChildrenIndice();
	};
}