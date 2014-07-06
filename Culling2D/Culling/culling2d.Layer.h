#pragma once
#include <vector>
#include "culling2d.Grid.h"

namespace culling2d
{
	class Layer
	{
		int resolution;
		std::vector<Grid*> cells;

	public:		
		Layer(int resolution);
		~Layer();

		int GetResolution();
		std::vector<Grid*> GetCells();
	};
}