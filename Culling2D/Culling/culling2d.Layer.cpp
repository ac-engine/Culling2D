#include "../Culling2D.h"

namespace culling2d
{
	Layer::Layer(int resolution):
		resolution(resolution)
	{

	}

	Layer::~Layer()
	{
		for (int i = 0; i < grids.size(); ++i)
		{
			SafeDelete(grids[i]);
		}
		grids.clear();
	}

	int Layer::GetResolution() const
	{
		return resolution;
	}

	const std::vector<Grid*> &Layer::GetGrids()
	{
		return grids;
	}

	void Layer::AddGrid(Grid* grid)
	{
		SafeAddRef(grid);
		grids.push_back(grid);
	}

	void Layer::RemoveGrid(Grid* grid)
	{
		grids.erase(remove(grids.begin(), grids.end(), grid), grids.end());
		SafeRelease(grid);
	}


};