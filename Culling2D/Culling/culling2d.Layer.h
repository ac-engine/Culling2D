#pragma once
#include <vector>
#include "culling2d.Grid.h"

namespace culling2d
{
	class Layer
	{
		int resolution;
		std::vector<Grid*> grids;

	public:		
		Layer(int resolution);
		~Layer();

		int GetResolution();
		std::vector<Grid*> GetGrids();
	};
}