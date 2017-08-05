
#include "../Culling2DCommon.h"

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


	bool RectF::GetCollision(Circle circle)
	{
		if (GetIsContainingPoint(circle.Position))
			return true;

		Vector2DF closest = Vector2DF(Clamp(circle.Position.X, X + Width, X), Clamp(circle.Position.Y, Y + Height, Y));
		float distanceSquared = (closest - circle.Position).GetSquaredLength();
		return (distanceSquared < (circle.Radius*circle.Radius));
	}

	bool RectF::GetIsContainingPoint(Vector2DF point) const
	{
		return X <= point.X&&Y <= point.Y&&X + Width >= point.X&&Y + Height >= point.Y;
	}
}
