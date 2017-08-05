
#include "../../Culling2D_AABB.h"

using namespace std;

namespace culling2d_aabb
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

	bool RectF::GetCollision(RectF rectf)
	{
		return std::abs(rectf.X - X) < rectf.Width / 2 + Width / 2 &&
			std::abs(rectf.Y - Y) < rectf.Height / 2 + Height / 2;
	}

	bool RectF::operator==(RectF rectF) const {
		return X == rectF.X && Y == rectF.Y && Width == rectF.Width && Height == rectF.Height;
	}
	bool RectF::operator!=(RectF rectF) const {
		return X != rectF.X || Y != rectF.Y || Width != rectF.Width || Height != rectF.Height;
	}

	bool RectF::GetIsContainingPoint(Vector2DF point) const {
		return point.X >= X && point.X <= X + Width && point.Y >= Y && point.Y <= Y + Height;
	}
}
