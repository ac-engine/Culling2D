#pragma once
#include <vector>
#include "../Common/Math/culling2d.RectF.h"
#include "culling2d.Layer.h"
#include "culling2d.Object.h"
#include "culling2d.Grid.h"

namespace culling2d
{
	class World
	{
		int resolution;
		RectF worldRange;
		std::vector<Layer*> layers;

	public:
		std::vector<Grid&> GetCullingObjects(RectF cullingRange);
		void Update();
		int GetResolution();
		int RecalculateResolution();
		RectF GetWorldRange();
		bool AddObject(Object* object);
		bool RemoveObject(Object* object);
	};
}