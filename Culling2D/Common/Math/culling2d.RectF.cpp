
#include "../../Culling2D.h"

using namespace std;

namespace culling2d
{
	RectF::RectF()
		: X(0), Y(0), Width(0), Height(0)
	{
	}

	RectF::RectF(float x, float y, float width, float height)
		: X(x), Y(y), Width(width), Height(height)
	{
	}

	Vector2DF RectF::GetPosition() const
	{
		return Vector2DF(X, Y);
	}

	Vector2DF RectF::GetSize() const
	{
		return Vector2DF(Width, Height);
	}

	array<Vector2DF, 4> RectF::GetVertexes() const
	{
		array<Vector2DF, 4> result =
		{
			Vector2DF(X, Y),
			Vector2DF(X + Width, Y),
			Vector2DF(X + Width, Y + Height),
			Vector2DF(X, Y + Height)
		};
		return result;
	}

	bool RectF::GetCollision(Circle circle)
	{
		if (circle.Position.X >= X&&circle.Position.Y >= Y&&circle.Position.X <= X + Width&&circle.Position.Y <= Y + Height)return true;

		Vector2DF closest = Vector2DF(Clamp(circle.Position.X, X + Width, X), Clamp(circle.Position.Y, Y + Height, Y));
		float distanceSquared = (closest - circle.Position).GetSquaredLength();
		return (distanceSquared < (circle.Radius*circle.Radius));
	}
}