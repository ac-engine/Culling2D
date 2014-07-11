#include "culling2d.Layer.h"

namespace culling2d
{
	Layer::Layer(int resolution):
		resolution(resolution)
	{

	}

	Layer::~Layer(){
		for (int i = 0; i < grids.size(); ++i)
		{
			delete grids[i];
		}
		grids.clear();
	}

	int Layer::GetResolution()
	{
		return resolution;
	}

	std::vector<Grid*> &Layer::GetGrids()
	{
		return grids;
	}
};