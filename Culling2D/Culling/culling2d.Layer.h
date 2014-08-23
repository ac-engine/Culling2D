#pragma once
#include <vector>
#include "culling2d.Grid.h"

namespace culling2d
{
	class Layer
		:public ReferenceObject
	{
		int resolution;
		std::vector<Grid*> grids;

	public:		
		Layer(int resolution);
		~Layer();

		int GetResolution() const;
		const std::vector<Grid*> &GetGrids();
		void AddGrid(Grid* grid);
		void RemoveGrid(Grid* grid);
	};
}