#pragma once
#include "../culling2d.common.Base.h"
#include "culling2d.Vector2DF.h"

namespace culling2d
{
	struct Circle
	{
		Vector2DF Position;
		float Radius;

		Circle(){}

		Circle(Vector2DF position, float radius)
		{
			Position = position;
			Radius = radius;
		}
	};
}