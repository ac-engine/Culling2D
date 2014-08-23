#pragma once
#include <vector>
#include <set>
#include <map>
#include "../Common/Math/culling2d.RectF.h"
#include "culling2d.Layer.h"
#include "culling2d.Object.h"
#include "culling2d.Grid.h"
#include "../culling2d.ReferenceObject.h"

namespace culling2d
{
	class World
		:public ReferenceObject
	{
		int resolution;
		int maxResolution;
		RectF worldRange;
		std::vector<Layer*> layers;
		std::vector<Object*> tempObjects;
		std::set<Object*> improperObjects;
		std::map<Object*, Grid*> mapObjectToGrid;

		void initQuadtreeGrids(int layerResolution, RectF range);
		void initQuadtree();

		Grid* searchDestinationGrid(Object * object);
	public:
		World(int resolution, RectF worldRange);
		~World();

		std::vector<Object*> &GetCullingObjects(RectF cullingRange);
		void NotifyImproperGrid(Object *object);
		void Update();
		int GetResolution() const;
		int RecalculateResolution();
		RectF GetWorldRange() const;
		Grid* AddObject(Object* object);
		bool RemoveObject(Object* object);
	};
}