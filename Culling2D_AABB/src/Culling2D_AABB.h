#pragma once

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <array>
#include <algorithm>
#include <functional>

#include <memory>
#include <chrono>
#include <thread>

#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#else
#endif

#include <Culling2DCommon.h>

#include <memory>
#include <atomic>
namespace culling2d_aabb
{

	using namespace culling2d;

	class Layer;
	class World;
	class Object;
	class Grid;

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


	class World
		:public ReferenceObject
	{
		friend Object;
		int resolution;
		uint32_t outOfRangeObjectsCount;
		RectF worldRange;
		uint32_t nextFirstSortedKey;
		uint32_t nextSecondSortedKey;
		std::vector<Layer*> layers;
		std::vector<Object*> tempObjects;
		std::unordered_set<Object*> improperObjects;
		std::unordered_map<Object*, Grid*> mapObjectToGrid;

		void initQuadtreeGrids(int layerResolution, RectF range);
		void initQuadtree();
		Grid* AddObjectInternal(Object* object);

		Grid* searchDestinationGrid(Object * object, bool isInternal);
		void NotifyMoved(Object *object);

		Vector2DF upperLeft_;
		Vector2DF lowerRight_;
		float minRadius_;

		int initialResolution;
	public:
		World(int resolution, RectF worldRange);
		~World();

		std::vector<Object*> &GetCullingObjects(RectF cullingRange);
		void Update();
		int GetResolution() const;
		void ResetWorld(int newResolution, RectF newRange);
		RectF GetWorldRange() const;
		Grid* AddObject(Object* object);
		bool RemoveObject(Object* object);

		uint32_t GetOutOfRangeObjectsCount() const;

		void ResetNextFirstSortedKey();
		void IncNextFirstSortedKey();
		uint32_t GetNextFirstSortedKey() const;

		void ResetNextSecondSortedKey();
		void IncNextSecondSortedKey();
		uint32_t GetNextSecondSortedKey() const;
	};

	class Object
		:public ReferenceObject
	{
		friend World;
		RectF aabb;
		void *userData;
		World *worldRef;
		bool isInWorld;

		RectF currentRange;
		uint64_t sortedKey;
		Object(void* userdata, World *worldRef);

		uint64_t GetSortedKey() const;
	public:
		~Object();

		bool GetIsInWorld() const;
		void SetIsInWorld(bool isinworld);

		const RectF& GetAABB() const;
		void SetAABB(RectF circle);
		void* GetUserData() const;
		void SetUserData(void* userData);

		RectF GetCurrentRange() const;
		void SetCurrentRange(RectF range);

		bool IsProperPosition() const;

		uint32_t GetSecondSortedKey();
		void SetSecondSortedKey(uint32_t secondKey);

		void SetFirstSortedKey(uint32_t firstKey);
		uint32_t GetFirstSortedKey();

		static Object* Create(void *userdata, World* worldRef);
	};

	class Grid
		:public ReferenceObject
	{
		int resolutionLevel;
		RectF gridRange;
		int index;
		std::unordered_set<Object*> objects;
		static std::array<int, 4> childrenIndices;
	public:
		Grid(int resolutionLevel, RectF gridRange);
		~Grid();
		int GetResolutionLevel() const;
		RectF GetGridRange() const;

		int GetCullingObjects(RectF cullingRange, std::vector<Object*> &cullingObjects);

		static std::array<int, 4> &GetChildrenIndices(int index, int currentResolution);

		bool AddObject(Object* object);
		bool RemoveObject(Object* object);
	};
}
